#ifndef TEXT_TO_SPEECH_H
#define TEXT_TO_SPEECH_H

#include <string>

class VoiceCustomization; // Forward declaration

class TextToSpeech {
public:
    void speak(const std::string& text);
    void setVoiceCustomization(VoiceCustomization* voice);

private:
    VoiceCustomization* voice;
};

#endif // TEXT_TO_SPEECH_H
