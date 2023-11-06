// SpeechToText.h
#include <string>

class SpeechToText {
private:
    bool isActive;
    std::string language;

public:
    SpeechToText() : isActive(false), language("English") {}

    bool listen();
    std::string convertToText(const std::string& speech);
    bool stopListening();
};

// SpeechToText.cpp
#include "SpeechToText.h"

bool SpeechToText::listen() {
    // Implementation
}

std::string SpeechToText::convertToText(const std::string& speech) {
    // Implementation
}

bool SpeechToText::stopListening() {
    // Implementation
}
