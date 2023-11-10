// This file contains the declarations for the functions used in the STT.cpp file.
#ifndef STT_H_
#define STT_H_

#include <vector>
#include <string>
#include "portaudio.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// Constants
const int kSampleRate = 44100;
const int kFramesPerBuffer = 256;
const int kNumChannels = 1;
const int kRecordTimeSecs = 10;

// Global constant for API key
extern const std::string kApiKey;

// if error in compilation, try to remove the extern keyword
// inline const std::string kApiKey = "your_api_key_here";

// Function to encode audio data to Base64
std::string Base64Encode(const std::vector<float>& buffer);

// Callback for receiving the data from libcurl
size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);

// Function to perform the API request and return the transcription
std::string PerformSpeechRecognition(const std::vector<float>& audioBuffer);

// Function to write text to a file
void WriteToFile(const std::string& filename, const std::string& text);

// Function to check and list available audio devices
void ListAudioDevices();

// Function to record audio from default input device for a specified duration
std::vector<float> RecordAudio(int recordTimeSecs);

#endif // STT_H_
