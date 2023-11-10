#ifndef POLLY_H
#define POLLY_H

#include "LLMProcessing.h"
#include "TextToSpeech.h"
#include "Display.h"

class Polly {
private:
    LLMProcessing llmProcessor;
    TextToSpeech tts;
    Display display;
public:
    Polly(); //declare constructor
    void run();
};

#endif // POLLY_H
