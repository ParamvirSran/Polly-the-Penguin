#include "STT.h"
#include "SpeechRecognizer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "portaudio.h"
#include <curl/curl.h>

const std::string apikey = "AIzaSyC7nOfOCovoNDIT8bzIdFh_X9n0lSWdnt4";

void ListAudioDevices() {
  int numDevices = Pa_GetDeviceCount();
  if (numDevices < 1) {
    std::cerr << "No audio devices found!" << std::endl;
    return;
  }
  std::cout << "Available audio devices:" << std::endl;
  for (int i = 0; i < numDevices; i++) {
    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
    std::cout << "Device " << i << ": " << deviceInfo->name << std::endl;
  }
}

// WAV file header structure
struct WAVHeader {
    char riffHeader[4] = {'R', 'I', 'F', 'F'};
    uint32_t riffChunkSize;
    char waveHeader[4] = {'W', 'A', 'V', 'E'};
    char fmtHeader[4] = {'f', 'm', 't', ' '};
    uint32_t fmtChunkSize = 16; // for PCM
    uint16_t audioFormat = 1;   // PCM = 1
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char dataHeader[4] = {'d', 'a', 't', 'a'};
    uint32_t dataChunkSize;
};


void WriteWAVHeader(std::ofstream &file, int numChannels, int sampleRate, int bitsPerSample, int dataSize) {
  WAVHeader wavHeader;
  wavHeader.numChannels = numChannels;
  wavHeader.sampleRate = sampleRate;
  wavHeader.bitsPerSample = bitsPerSample;
  wavHeader.byteRate = sampleRate * numChannels * bitsPerSample / 8;
  wavHeader.blockAlign = numChannels * bitsPerSample / 8;
  wavHeader.dataChunkSize = dataSize;
  wavHeader.riffChunkSize = 36 + dataSize;

  file.write(reinterpret_cast<const char *>(&wavHeader), sizeof(WAVHeader));
}

void SaveAudioToFile(const std::vector<float> &buffer, const std::string &filename) {
  std::ofstream file(filename, std::ios::binary);

  // Assuming your buffer is mono-channel, 44100 Hz, 32-bit float PCM
  int numChannels = 1;
  int sampleRate = 44100;
  int bitsPerSample = 32;
  int dataSize = buffer.size() * sizeof(float);

  // Write WAV header
  WriteWAVHeader(file, numChannels, sampleRate, bitsPerSample, dataSize);

  // Write audio data
  file.write(reinterpret_cast<const char *>(buffer.data()), dataSize);

  file.close();
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

  // After recording:
  SaveAudioToFile(audioBuffer, "recorded_audio.wav");
  return audioBuffer;
}

int main() {
  PaError err = Pa_Initialize();
  curl_global_init(CURL_GLOBAL_ALL);
  if (err != paNoError) {
    std::cerr << "PortAudio initialization failed: " << Pa_GetErrorText(err) << std::endl;
    return 1;
  }

  try {
    SpeechRecognizer recognizer(apikey);
    ListAudioDevices();
    std::cout << "Press ENTER to start recording..." << std::endl;
    std::cin.get();

    auto audioBuffer = RecordAudio(kRecordTimeSecs);
    auto response = recognizer.performSpeechRecognition(audioBuffer);
    try {
      auto transcribedText = recognizer.getTranscribedText(response);
      std::cout << "Transcribed Text: " << transcribedText << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "Error processing transcription: " << e.what() << std::endl;
    }
    std::cout << "Full API Response: " << response << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "An error occurred: " << e.what() << std::endl;
  }

  Pa_Terminate();
  curl_global_cleanup();
  return 0;
}
