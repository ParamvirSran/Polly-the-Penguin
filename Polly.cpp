#include "Polly.h"
#include <iostream>
#include <string>
#include <algorithm>

Polly::Polly() : voice(&tts){
    tts.setVoiceCustomization(&voice);
}
void Polly::run() {
    tts.speak("STARTING UP"); //startup message
    tts.speak("Welcome to Polly. How can I assist you today?");
    while (true) {
        std::string textInput;
        std::cout << "Polly is listening: ";
        //for testing purposes.replace with STT function to get text
        std::getline(std::cin, textInput);

        // Convert textInput to lowercase lambda f'n applies tolower to each char of textInput
        std::transform(textInput.begin(), textInput.end(), textInput.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        //str compare returns 0 if equal
        if (textInput == "change voice") {
            std::cout << "Ok, I'll change my voice";
            voice.changeVoice();
            tts.speak("Voice has been changed.");
        }
        else if (textInput == "shutdown") {
            tts.speak("Shutting down. Goodbye!");
            break;  // Exit the loop, thus ending the program
        }
        else if (textInput == "test") {
            tts.speak("Say something now::");
            std::string transcribedText = stt.run();  // Use the STT instance to get the transcribed text
            if (!transcribedText.empty()) {
                std::string response = llmProcessor.generateResponse(transcribedText);
                std::string emotion = llmProcessor.determineEmotion(response);

                std::cout << "Transcribed Text: " << transcribedText << std::endl;
                std::cout << "Response: " << response << std::endl;
                std::cout << "Emotion: " << emotion << std::endl;

                display.pollyFeels(emotion);
                tts.speak(response);
            }
        }

        else {
            std::string response = llmProcessor.generateResponse(textInput);
            std::string emotion = llmProcessor.determineEmotion(response);

            std::cout << "Response: " << response << std::endl;
            std::cout << "Emotion: " << emotion << std::endl;

            display.pollyFeels(emotion);
            tts.speak(response);
        }
    }
}
int main() {
    // Create an instance of the Display class
    //Display display;
    Polly polly;
    polly.run();
    return 0;
}
