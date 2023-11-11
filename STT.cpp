// This class is used to perform speech recognition using the Google Cloud Speech-to-Text API.
// it will take in audio input from a microphone and output the transcribed text to a file.

#include "STT.h"
#include "SpeechRecognizer.h"
#include <iostream>
#include <string>
#include <vector>
#include "portaudio.h"
#include <curl/curl.h>

// Global constant for API key
const std::string apikey = "AIzaSyC7nOfOCovoNDIT8bzIdFh_X9n0lSWdnt4";


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
    // Initialize PortAudio and libcurl
    PaError err = Pa_Initialize();
    curl_global_init(CURL_GLOBAL_ALL);

    if (err != paNoError) {
        std::cerr << "PortAudio initialization failed: " << Pa_GetErrorText(err) << std::endl;
        curl_global_cleanup();
        return 1;
    }

    try {
        SpeechRecognizer recognizer(apikey); // Create a speechRecognizer object

        // List all available audio devices
        ListAudioDevices();

        // Wait for user input
        std::cout << "Press ENTER to start recording..." << std::endl;
        std::cin.get();

        // Record the audio into a buffer
        std::vector<float> audioBuffer = RecordAudio(kRecordTimeSecs);

        // Perform the speech recognition
        auto response = recognizer.performSpeechRecognition(audioBuffer);
        try {
            std::string transcribedText = recognizer.getTranscribedText(response);
            std::cout << "Transcribed Text: " << transcribedText << std::endl;

            // ... [Code to write transcribed text to a file or further processing]
        } catch (const std::exception &e) {
            std::cerr << "Error processing transcription: " << e.what() << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        Pa_Terminate();
        curl_global_cleanup();
        return 1;
    }

    Pa_Terminate(); // Terminate PortAudio
    curl_global_cleanup(); // Cleanup libcurl
    return 0;
}
