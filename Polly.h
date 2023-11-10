#ifndef POLLY_H
#define POLLY_H

#include "LLMProcessing.h"
#include "TextToSpeech.h"
#include "Display.h"
#include "VoiceCustomization.h"

class Polly {
private:
    LLMProcessing llmProcessor;
    TextToSpeech tts;
    Display display;
    VoiceCustomization voice;

public:
    Polly(); // Constructor declaration
    void run();
};

#endif // POLLY_H
