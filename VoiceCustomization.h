#ifndef VOICE_CUSTOMIZATION_H
#define VOICE_CUSTOMIZATION_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

extern int voiceNum;  // Declare the global variable as extern

class TextToSpeech {
public:
    void changeVoice();
    std::string voice();
    std::string speechToText();  // You need to define this function or include its declaration if it's in another file
};

#endif // VOICE_CUSTOMIZATION_H
