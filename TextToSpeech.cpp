#include <iostream>
#include <string>
#include <stdexcept>

class TextToSpeech {
public:
    void speak(const std::string& text) {
        std::string command = "espeak \"" + text + "\"";
        int result = system(command.c_str());
        if (result != 0) {
            throw std::runtime_error("Failed to invoke espeak.");
        }
    }
};

int main() {
    TextToSpeech tts;
    tts.speak("this is a test");

    return 0;
}
