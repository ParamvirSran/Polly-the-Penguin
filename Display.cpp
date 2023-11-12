#include "Display.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>  // Include for sleep

void Display::pollyFeels(const std::string& emotion) {
    // Determine which image to display based on the emotion
    // LLMProcessing returns one of the following emotions: anger, fear, joy, love, sadness, and surprise
    std::string imageFile;

    if (emotion == "sadness") {
        imageFile = "graphics/sad.jpg";
    } else if (emotion == "anger") {
        imageFile = "graphics/angry.jpg";
    } else if (emotion == "love") {
        imageFile = "graphics/love.jpg";
    } else if (emotion == "surprise") {
        imageFile = "graphics/surprise.jpg";
    } else if (emotion == "joy") {
        imageFile = "graphics/happy.jpg";
    } else if (emotion == "fear") {
        imageFile = "graphics/fear.jpg";
    } else {
        // Default to base image for unknown emotions
        imageFile = "graphics/base.jpg";
    }

    // Close the previous image viewer (CentOS-specific)
    system("pkill -f xdg-open"); //fix this or find alternative

    // Open the image in a new image viewer process
    std::string command = "xdg-open " + imageFile + " &";  // Linux

    // Execute the command to open the image
    system(command.c_str());

    // Sleep for a short duration to allow the image viewer to open
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
