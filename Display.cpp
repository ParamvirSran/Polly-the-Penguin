#include "Display.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>  // Include for sleep

void Display::pollyFeels(const std::string& emotion) {
    // Determine which image to display based on the emotion
    std::string imageFile;

    if (emotion == "SAD") {
        imageFile = "graphics/sad.jpg";
    } else if (emotion == "ANGRY") {
        imageFile = "graphics/angry.jpg";
    } else if (emotion == "LIT") {
        imageFile = "graphics/happy.jpg";
    } else {
        // Default to base image for unknown emotions
        imageFile = "graphics/base.jpg";
    }

    // Close the previous image viewer (CentOS-specific)
    system("pkill -f xdg-open");

    // Open the image in a new image viewer process
    std::string command = "xdg-open " + imageFile + " &";  // Linux

    // Execute the command to open the image
    system(command.c_str());

    // Sleep for a short duration to allow the image viewer to open
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
