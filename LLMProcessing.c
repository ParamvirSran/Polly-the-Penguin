// LLMProcessing.cpp

#include "LLMProcessing.h"
#include <cstdlib>

std::string LLMProcessing::generateResponse(const std::string& textInput) {
// Construct the JSON payload
std::string payload = "{\"text\": \"" + textInput + "\"}";

// Use a system call to invoke the Python service with curl (make sure to handle special characters and escape quotes properly)
std::string command = "curl -X POST -H \"Content-Type: application/json\" -d '" + payload + "' http://localhost:5000/generate";
std::string output = exec(command.c_str()); // exec is a placeholder for a function that would run the command and capture the output

return output;
}
