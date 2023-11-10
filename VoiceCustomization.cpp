#include "VoiceCustomization.h
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

std::string voiceNum = "en";

class TextToSpeech {
public:
    void changeVoice() {
        std::string response1 = "espeak -v en \" Just say the number associated with the voice you would like to hear \"";
        tts.speak(response1);
        std::string response2 = "espeak -v en \" This is voice one \"";
        tts.speak(response2);
        std::string response3 = "espeak -v en+f1 \" This is voice two \"";
        tts.speak(response3);

        int i = 0;
        while (i == 0){
            // Call speech to Text
            std::string userResponse = speechToText(); //Change this

            if (userResponse == "One") {
                voiceNum = "en";
                break;
            } else if (userResponse == "Two") {
                voiceNum = "en+f1";
                break;
            } else{
                std::string invalid = "espeak -v en \" Invalid response try agian \"";
                tts.speak(invalid);
            }
        }
    }


};

// if the user says a certain text it will call changeVoice function 
// the functin will output all its options and call the speech to text for its next response 
// if text is Voice One it will set global variable to 0 or if text is Voice Two it will set global varibel to 1
// if the response is invalid it will ask it for another response 
// then the text to speech will always call voice() before outputting anyhting to always keep the saem voice unless specically changing it 
