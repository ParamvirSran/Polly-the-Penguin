// SAAD MAHMOOD

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Display.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>  // Include for sleep
#include <sstream>
#include <crow.h>

extern crow::websocket::connection* current_ws_conn;

void Display::pollyFeels(const std::string& emotion) {
    if (current_ws_conn){
        crow::json::wvalue msg;
        msg["emotion"] = emotion;
        current_ws_conn->send_text(crow::json::dump(msg));
    }
}

