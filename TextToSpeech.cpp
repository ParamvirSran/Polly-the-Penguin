// TextToSpeech.cpp

#include "TextToSpeech.h"
#include "VoiceCustomization.h"
#include <cstdlib>
#include <stdexcept>

void TextToSpeech::speak(const std::string& text) {

    std::string voiceVariant = voice->getVoice();
    std::string command = "espeak -v" + voiceVariant + " \"" + text + "\"";

    //std::string command = "espeak -v en+f1 \" Testing voice change \"";
    std::system(command.c_str());
}
void TextToSpeech::setVoiceCustomization(VoiceCustomization* voice) {
    this->voice = voice;
}
/*
Error chevking version:

int TextToSpeech::speak(const std::string& text) {
    std::string command = "espeak \"" + text + "\"";
    int result = std::system(command.c_str());
    return result == 0 ? 1 : 0; // Return 1 if the command was successful, 0 otherwise
}
*/
