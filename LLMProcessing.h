#ifndef LLMPROCESSING_H
#define LLMPROCESSING_H

#include <string>
#include <list>

class LLMProcessing {
private:
    std::list<std::string> conversationContext;
    std::string emotionState;

public:
    LLMProcessing() = default;
    ~LLMProcessing() = default;

    std::string generateResponse(const std::string& textInput);
    std::string determineEmotion(const std::string& response);
};

std::string exec(const char* cmd); //executing system commands

#endif // LLMPROCESSING_H
