// TextToSpeech.cpp

#include "TextToSpeech.h"
#include <cstdlib>
#include <stdexcept>

void TextToSpeech::speak(const std::string& text) {
    std::string command = "espeak \"" + text + "\"";
    int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("Failed to invoke espeak.");
    }
}
