// TextToSpeech.cpp

#include "TextToSpeech.h"
#include <cstdlib>
#include <stdexcept>

void TextToSpeech::speak(const std::string& text) {
    std::string command = "espeak \"" + text + "\"";
    int result = std::system(command.c_str());
}

/*
Error chevking version:

int TextToSpeech::speak(const std::string& text) {
    std::string command = "espeak \"" + text + "\"";
    int result = std::system(command.c_str());
    return result == 0 ? 1 : 0; // Return 1 if the command was successful, 0 otherwise
}
*/
