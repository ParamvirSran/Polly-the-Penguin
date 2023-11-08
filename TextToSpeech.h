#ifndef TEXTTOSPEECH_H
#define TEXTTOSPEECH_H

#include <string>

class TextToSpeech {
public:
    TextToSpeech();
    ~TextToSpeech();

    bool speak(const std::string& text);
    bool setVoice(const std::string& voice);
    bool setSpeakingRate(float rate);

};

#endif // TEXTTOSPEECH_H
