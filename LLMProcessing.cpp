//SAAD MAHMOOD
#include "LLMProcessing.h"
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string exec(const char* cmd);
std::string cleanResponse(const std::string& resp);


std::string LLMProcessing::generateResponse(const std::string& textInput) {
    //JSON payload needs to be escaped otherwise error 500
    //std::string payload = "{\"text\": \"" + textInput + "\"}";
    // Use a system call to invoke the Python service with curl
    //LAST WORKING!! std::string command = "curl -X POST -H \"Content-Type: application/json\" -d \"{\\\"text\\\": \\\"hey man im having trouble quitting smoking, could you give me some pointers?\\\"}\" http://localhost:5000/generate > temp.txt";

    //escaping for JSON
    std::string escapedTextInput;
    for (char c : textInput) {
        if (c == '\"') {
            escapedTextInput += "\\\"";
        } else {
            escapedTextInput += c;
        }
    }
    std::string command = "curl -X POST -H \"Content-Type: application/json\" -d \"{\\\"text\\\": \\\"" + escapedTextInput + "\\\"}\" http://localhost:5000/generate > temp.txt";

    /////////////////this works as a proof of concept
    //std::string command = "curl -X POST -H \"Content-Type: application/json\" -d \"{\\\"text\\\": \\\"" + textInput + "\\\"}\" http://localhost:5000/generate > temp.txt";
    //////////////////////////

    system(command.c_str());
    //std::string output = exec(command.c_str());

    //Parse -- in production use a proper JSON parser??
    //auto startPos = output.find("{\"result\":\"");
    //auto endPos = output.rfind("\"}");
    //std::string response = (startPos != std::string::npos && endPos != std::string::npos) ? output.substr(startPos + 11, endPos - startPos - 11) : "";

    //Emulate context saving
    //conversationContext.push_back(response);
    std::ifstream ifs("temp.txt");
    std::string response((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    ifs.close();
    //std::remove("temp.txt"); //garbage coll

    response = cleanResponse(response);
    return response;
}

std::string LLMProcessing::determineEmotion(const std::string& response) {
    //extract the emotion from the response -- IDEA
    //size_t emotionStart = response.find(":[");
    //size_t emotionEnd = response.find("]:", emotionStart);
    //if (emotionStart != std::string::npos && emotionEnd != std::string::npos) {
    //    emotionState = response.substr(emotionStart + 2, emotionEnd - emotionStart - 2);
    //} else {
    //    emotionState = "CONFUSED"; // Default emotion if parsing fails
    //}
    //return emotionState;

    return "SAD";
}

//int main() {
//    LLMProcessing llmProcessor;
//    std::string textInput = "how are you feeling today?";
//    std::string response = llmProcessor.generateResponse(textInput);
//    std::string emotion = llmProcessor.determineEmotion(response);
//
//    std::cout << "Response: " << response << std::endl;
//    std::cout << "Emotion: " << emotion << std::endl;
//
//    return 0;
//}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string cleanResponse(const std::string& resp) {
    std::string modifiedResp = resp;  // Make a copy of the input string

    // Find the position of "result":
    size_t resultPos = modifiedResp.find("\"result\":");

    // If "result" is found, remove it and the surrounding characters
    if (resultPos != std::string::npos) {
        modifiedResp.erase(0, resultPos + 10); // 10 is the length of "\"result\":"
    }

    std::string cleanResp = "";

    for (size_t i = 0; i < modifiedResp.length(); ++i) {
        char currentChar = modifiedResp[i];

        if (currentChar == '{' || currentChar == '}' || currentChar == '"') {
            // Don't append '{' to cleanResp
            continue;
        }

        if (currentChar == '\\') {
            // Check if the next character is 'n'
            if (i + 1 < modifiedResp.length() && modifiedResp[i + 1] == 'n') {
                // Skip the '\n' character
                ++i;
                continue;
            }
        }

        // Append the character to cleanResp
        cleanResp += currentChar;
    }

    return cleanResp;
}


