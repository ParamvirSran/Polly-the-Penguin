// Description: This program records audio from the default input device and sends it to the Google Cloud Speech-to-Text API for transcription.
// The transcription is then output to the console and written to a file named 'transcription.txt'.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "portaudio.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <chrono>

// Constants
const int kSampleRate = 44100;
const int kFramesPerBuffer = 256;
const int kNumChannels = 1;
const int kRecordTimeSecs = 10;

// Global constant for API key
const std::string kApiKey = "8fb8d669305fdc492038989bfc970553a876b470";

// function to encode audio data to Base64
std::string Base64Encode(const std::vector<float>& buffer) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Ignore newlines - write everything in one line
    BIO_write(bio, buffer.data(), buffer.size() * sizeof(float));
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);

    // Copy memory buffer
    std::string encodedAudio(bufferPtr->data, bufferPtr->length);

    BIO_free_all(bio);
    BUF_MEM_free(bufferPtr);

    return encodedAudio;
}

// Callback for receiving the data from libcurl
size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
        return newLength;
    } catch (std::bad_alloc& e) {
        // Handle memory problem
        return 0;
    }
}

// Function to perform the API request and return the transcription
std::string PerformSpeechRecognition(const std::vector<float>& audioBuffer) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string encodedAudio = Base64Encode(audioBuffer);
    std::string jsonPayload = R"({"config":{"encoding":"LINEAR16","sampleRateHertz":44100,"languageCode":"en-US"},"audio":{"content":")" + encodedAudio + R"("}})";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, ("https://speech.googleapis.com/v1p1beta1/speech:recognize?key=" + kApiKey).c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();

    return readBuffer;
}

// Function to write text to a file
void WriteToFile(const std::string& filename, const std::string& text) {
    std::ofstream outFile(filename);
    outFile << text;
    outFile.close();
}


// Function to check and list available audio devices
void ListAudioDevices() {
    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 1) {
        std::cerr << "No audio devices found!" << std::endl;
    } else {
        std::cout << "Available audio devices:" << std::endl;
        for (int i = 0; i < numDevices; i++) {
            const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
            std::cout << "Device " << i << ": " << deviceInfo->name << std::endl;
        }
    }
}


// Function to record audio from default input device for a specified duration
std::vector<float> RecordAudio(int recordTimeSecs) {
    // Initialize PortAudio
    PaError err = Pa_Initialize();

    if (err != paNoError) throw std::runtime_error("PortAudio initialization failed");

    PaStreamParameters inputParameters;
    memset(&inputParameters, 0, sizeof(inputParameters)); // Use `memset` to clear the structure
    inputParameters.device = Pa_GetDefaultInputDevice();
    inputParameters.channelCount = kNumChannels;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    PaStream *stream;
    err = Pa_OpenStream(&stream, &inputParameters, nullptr, kSampleRate, kFramesPerBuffer, paClipOff, nullptr, nullptr);
    if (err != paNoError) throw std::runtime_error("Failed to open stream");

    err = Pa_StartStream(stream);
    if (err != paNoError) throw std::runtime_error("Failed to start stream");

    int totalFramesToRecord = kSampleRate * recordTimeSecs;
    std::vector<float> audioBuffer(totalFramesToRecord);

    // Record loop
    int framesLeftToRecord = totalFramesToRecord;
    while (framesLeftToRecord > 0) {
        int framesToRead = std::min(kFramesPerBuffer, framesLeftToRecord);
        err = Pa_ReadStream(stream, &audioBuffer[totalFramesToRecord - framesLeftToRecord], framesToRead);
        if (err) throw std::runtime_error("Failed to read stream");
        framesLeftToRecord -= framesToRead;
    }

    err = Pa_StopStream(stream);
    if (err != paNoError) throw std::runtime_error("Failed to stop stream");

    err = Pa_CloseStream(stream);
    if (err != paNoError) throw std::runtime_error("Failed to close stream");

    Pa_Terminate();

    return audioBuffer;
}

int main() {
    PaError err = Pa_Initialize();

    if (err != paNoError) {
        std::cerr << "PortAudio initialization failed: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    try {

    // List all available audio devices
    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 1) {
        std::cerr << "No audio devices found!" << std::endl;
        Pa_Terminate();
        return 1;
    }

    std::cout << "Available audio devices:" << std::endl;
    for (int i = 0; i < numDevices; i++) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        std::cout << "Device " << i << ": " << deviceInfo->name << std::endl;
    }

    // Attempt to get the default input device
    PaDeviceIndex defaultDeviceIndex = Pa_GetDefaultInputDevice();
    if (defaultDeviceIndex == paNoDevice) {
        std::cerr << "Error: No default input device." << std::endl;
        Pa_Terminate();
        return 1;
    }

    // Set up the input parameters for recording using the default device
    PaStreamParameters inputParameters;
    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.device = defaultDeviceIndex;
    inputParameters.channelCount = kNumChannels;
    inputParameters.sampleFormat = paFloat32; // Assuming the PortAudio build supports float32
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;


         // Open an audio I/O stream.
        PaStream *stream;
        err = Pa_OpenStream(&stream, &inputParameters, nullptr, kSampleRate, kFramesPerBuffer, paClipOff, nullptr, nullptr);
        if (err != paNoError) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
            Pa_Terminate();
            return 1;
        }

        // Start the audio stream
        err = Pa_StartStream(stream);
        if (err != paNoError) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
            Pa_CloseStream(stream);
            Pa_Terminate();
            return 1;
        }

        // Record the audio into a buffer
        std::vector<float> audioBuffer(kSampleRate * kRecordTimeSecs); // Create a buffer for the audio data
        err = Pa_ReadStream(stream, audioBuffer.data(), audioBuffer.size());
        if (err) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
            Pa_StopStream(stream);
            Pa_CloseStream(stream);
            Pa_Terminate();
            return 1;
        }

        // Stop and close the stream
        err = Pa_StopStream(stream);
        if (err != paNoError) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
            Pa_CloseStream(stream);
            Pa_Terminate();
            return 1;
        }

        err = Pa_CloseStream(stream);
        if (err != paNoError) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
            Pa_Terminate();
            return 1;
        }

        // Perform speech recognition on the recorded audio
        std::string response = PerformSpeechRecognition(audioBuffer);

        // Parse the JSON response
        nlohmann::json jsonResponse = nlohmann::json::parse(response, nullptr, false);
        if (jsonResponse.is_discarded()) {
            std::cerr << "Error parsing JSON response." << std::endl;
            return 1;
        }

        // Extract the transcribed text
        std::string transcribedText;
        try {
            transcribedText = jsonResponse["results"][0]["alternatives"][0]["transcript"];
        } catch (nlohmann::json::exception& e) {
            std::cerr << "Error extracting transcript: " << e.what() << std::endl;
            return 1;
        }

        // Output the transcribed text
        std::cout << transcribedText << std::endl;

        // Write the transcription to a file
        std::ofstream outFile("transcription.txt");
        if (outFile) {
            outFile << transcribedText;
            outFile.close();
        } else {
            std::cerr << "Error opening file for writing." << std::endl;
            return 1;
        }

   } catch (const std::exception& e) {
        // Catch any other std::exception based errors
        std::cerr << "An error occurred: " << e.what() << std::endl;
        Pa_Terminate(); // Ensure PortAudio is terminated in case of an exception
        return 1;
    }
    // Terminate PortAudio
    Pa_Terminate();

    return 0;
}
