#include "Polly.h"
#include "TextToSpeech.h" // Include the TextToSpeech header

#include <iostream>
#include <string>
Polly::Polly() {}
void Polly::run() {


    std::string textInput = "how are you feeling today?";
    std::string response = llmProcessor.generateResponse(textInput);
    std::string emotion = llmProcessor.determineEmotion(response);

    std::cout << "Response: " << response << std::endl;
    std::cout << "Emotion: " << emotion << std::endl;


    // Narrate the response
    tts.speak(response);
    
}

int main() {
    Polly polly;
    polly.run();
    return 0;
}