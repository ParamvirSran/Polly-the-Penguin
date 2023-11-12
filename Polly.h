#ifndef POLLY_H
#define POLLY_H
#include "STT.h"
#include "LLMProcessing.h"
#include "TextToSpeech.h"
#include "Display.h"
#include "VoiceCustomization.h"

//forward declaration of STT

class Polly {
private:
    LLMProcessing llmProcessor;
    TextToSpeech tts;
    Display display;
    VoiceCustomization voice;
    STT stt;

public:
    Polly(); // Constructor declaration
    void run();
};

#endif // POLLY_H
