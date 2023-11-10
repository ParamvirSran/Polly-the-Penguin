#include "Polly.h"
#include <chrono>  // Include for sleep
#include <thread>  // Include for sleep
#include <iostream>
#include <string>
Polly::Polly() {}

void Polly::run() {
    tts.speak("test");
    display.pollyFeels("meh");
    //std::string textInput = "how are you feeling today?";//this will be replaced w/ parms STT
    std::string textInput;
    std::cout << "Talk to Polly :) ";
    std::getline(std::cin, textInput);

    std::string response = llmProcessor.generateResponse(textInput);
    std::string emotion = llmProcessor.determineEmotion(response);

    //std::cout << "Response: " << response << std::endl;
    //std::cout << "Emotion: " << emotion << std::endl;


    // Narrate the response
    //tts.speak("parm is a bum");
    display.pollyFeels(emotion);
    tts.speak(response);
    
}

int main() {
    // Create an instance of the Display class
    Display display;
    Polly polly;
    polly.run();
    return 0;
}