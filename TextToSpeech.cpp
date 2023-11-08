#include "TextToSpeech.h"
#include <cstdlib>
#include <iostream>

TextToSpeech::TextToSpeech() {
    // Constructor could be empty if all logic is handled in the speak function.
}

TextToSpeech::~TextToSpeech() {
    // Destructor could be empty as well.
}

bool TextToSpeech::speak(const std::string& text) {
    //must change to path of your Python3.10 exe
    std::string command = "C:/Users/16474/AppData/Local/Programs/Python/Python310/python.exe speak.py \"" + text + "\"";
    int result = std::system(command.c_str());
    return result == 0;
}

bool TextToSpeech::setVoice(const std::string& voice) {
    // This functionality would need to be set in the Python script or omitted.
    return true;
}

bool TextToSpeech::setSpeakingRate(float rate) {
    // This functionality would need to be handled in the Python script or omitted.
    return true;
}
