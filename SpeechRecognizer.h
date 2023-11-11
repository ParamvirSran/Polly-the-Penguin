
#ifndef SPEECHRECOGNIZER_H
#define SPEECHRECOGNIZER_H


#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


class SpeechRecognizer {
public:

    SpeechRecognizer(const std::string &apiKey);


    std::string performSpeechRecognition(const std::vector<float> &audioBuffer);


    std::string getTranscribedText(const std::string &jsonResponse);


private:
    std::string apiKey;


    static size_t curlWriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);


    std::string base64Encode(const std::vector<float> &buffer);


};

#endif //SPEECHRECOGNIZER_H
