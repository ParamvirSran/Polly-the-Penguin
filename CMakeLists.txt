# Set the minimum version of CMake that's required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SpeechToText VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optionally set the build type if not set on the command line
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

#set(PortAudio_DIR "/usr/lib64/")
include_directories(/usr/include)
#find PortAudio library
find_library(PORTAUDIO_LIBRARY NAMES portaudio PATHS /usr/lib64)

# Find packages for CURL, nlohmann_json, and OpenSSL
find_package(CURL REQUIRED)
#find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)

# Try to find PortAudio using find_package
# find_package(PortAudio)

# If not found, use hardcoded paths
#if (NOT PortAudio_FOUND)
    # Append the CMake prefix path with the path to PortAudio's CMake configuration
#    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/portaudio/19.7.0/lib/cmake/portaudio")

    # Set up the include directory and library for PortAudio
#    set(PORTAUDIO_INCLUDE_DIR /opt/homebrew/Cellar/portaudio/19.7.0/include)
#    set(PORTAUDIO_LIBRARY /opt/homebrew/Cellar/portaudio/19.7.0/lib/libportaudio.a)
#endif ()

# Find the necessary macOS frameworks
#find_library(COREAUDIO_LIBRARY CoreAudio)
#find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
#find_library(AUDIOUNIT_LIBRARY AudioUnit)
#find_library(CORESERVICES_LIBRARY CoreServices)
#find_library(COREFOUNDATION_LIBRARY CoreFoundation)

# Include directories for all the found packages
include_directories(
        ${PORTAUDIO_INCLUDE_DIR}
        ${CURL_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} STT.cpp
        SpeechRecognizer.cpp
        SpeechRecognizer.h
        STT.h)

# Link the target with the manually specified PortAudio library (if not found) and the other libraries
target_link_libraries(${PROJECT_NAME}
        ${PORTAUDIO_LIBRARY}
        ${CURL_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        # ${COREAUDIO_LIBRARY}
        # ${AUDIOTOOLBOX_LIBRARY}
        # ${AUDIOUNIT_LIBRARY}
        # ${CORESERVICES_LIBRARY}
        # ${COREFOUNDATION_LIBRARY}
)

# Set up the API Key as a preprocessor definition
target_compile_definitions(${PROJECT_NAME} PRIVATE API_KEY="AIzaSyC7nOfOCovoNDIT8bzIdFh_X9n0lSWdnt4")

# If needed, you can set custom compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
