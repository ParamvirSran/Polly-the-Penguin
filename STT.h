// This file contains the declarations for the functions used in the STT.cpp file.
#ifndef STT_H_
#define STT_H_

#include <vector>
#include <string>
#include "portaudio.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SpeechRecognizer.h"


// Constants
const int kSampleRate = 44100;
const int kFramesPerBuffer = 256;
const int kNumChannels = 1;
const int kRecordTimeSecs = 10;


// Global constant for API key
extern const std::string apikey;


// Function to check and list available audio devices
void ListAudioDevices();


// Function to record audio from default input device for a specified duration
std::vector<float> RecordAudio(int recordTimeSecs);


#endif // STT_H_
