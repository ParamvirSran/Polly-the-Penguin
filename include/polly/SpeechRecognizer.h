#ifndef SPEECHRECOGNIZER_H
#define SPEECHRECOGNIZER_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class SpeechRecognizer {
public:
    // Constructor to initialize with an API key
    SpeechRecognizer(const std::string &apiKey);

    // Perform speech recognition on audio buffer
    std::string performSpeechRecognition(std::vector<int16_t> audioBuffer);

    // Extract transcribed text from JSON response
    std::string getTranscribedText(const std::string &jsonResponse);

private:
    std::string apiKey; // API key for the speech service

    // Callback for writing data received from CURL
    static size_t curlWriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);

    // Encode audio buffer to Base64
    std::string base64Encode(const std::vector<int16_t> &buffer);
};

#endif //SPEECHRECOGNIZER_H
