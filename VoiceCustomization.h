#ifndef VOICE_CUSTOMIZATION_H
#define VOICE_CUSTOMIZATION_H

#include <string>

class TextToSpeech; // Forward declaration

class VoiceCustomization {
public:
    VoiceCustomization(TextToSpeech* tts);
    void changeVoice();
    std::string getVoice();

private:
    TextToSpeech* tts; // Pointer
};

#endif // VOICE_CUSTOMIZATION_H
