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
    bool success = tts.speak(response);
    if (!success) {
        std::cerr << "Failed to narrate the response." << std::endl;
    }
    // testing
    bool testSuccess = tts.speak("Hello, world!");
    if (!testSuccess) {
        std::cerr << "Text-to-speech test failed." << std::endl;
        return; // Exit if the test failed
    }

}

int main() {
    Polly polly;
    polly.run();
    return 0;
}