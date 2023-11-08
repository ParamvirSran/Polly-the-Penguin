#ifndef POLLY_H
#define POLLY_H

#include "LLMProcessing.h" // Include the header of LLMProcessing to use its functionality
#include "TextToSpeech.h"

class Polly {
private:
    LLMProcessing llmProcessor; // Instance of LLMProcessing to use its methods
    TextToSpeech tts;
public:
    Polly(); //declare constructor
    void run();
};

#endif // POLLY_H
