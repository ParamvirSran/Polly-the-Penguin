## Set the minimum version of CMake that's required
#cmake_minimum_required(VERSION 3.10)
#
## Set the project name and version
#project(SpeechToText VERSION 1.0)
#
## Specify the C++ standard
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
#
## Optionally set the build type if not set on the command line
#if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Release)
#endif()
#
## Find packages for CURL
#find_package(CURL REQUIRED)
#
## Find the nlohmann_json package using CMake's configuration file
#find_package(nlohmann_json 3.11.2 REQUIRED)
#
## Find OpenSSL package
#find_package(OpenSSL REQUIRED)
#
## Find the necessary macOS frameworks
#find_library(COREAUDIO_LIBRARY CoreAudio)
#find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
#find_library(AUDIOUNIT_LIBRARY AudioUnit)
#find_library(CORESERVICES_LIBRARY CoreServices)
#find_library(COREFOUNDATION_LIBRARY CoreFoundation)
#
## Add the include directory for PortAudio
#include_directories(/opt/homebrew/Cellar/portaudio/19.7.0/include)
#
## Add an executable with the above sources
#add_executable(${PROJECT_NAME} STT.cpp)
#
## Link the target with the manually specified PortAudio library, CURL, nlohmann_json, OpenSSL, and macOS frameworks
#target_link_libraries(${PROJECT_NAME}
#    /opt/homebrew/Cellar/portaudio/19.7.0/lib/libportaudio.a
#    ${CURL_LIBRARIES}
#    nlohmann_json::nlohmann_json
#    ${OPENSSL_LIBRARIES}
#    ${COREAUDIO_LIBRARY}
#    ${AUDIOTOOLBOX_LIBRARY}
#    ${AUDIOUNIT_LIBRARY}
#    ${CORESERVICES_LIBRARY}
#    ${COREFOUNDATION_LIBRARY})
#
## Set up the API Key as a preprocessor definition
## WARNING: For production, use a more secure method of managing API keys
#target_compile_definitions(${PROJECT_NAME} PRIVATE API_KEY="8fb8d669305fdc492038989bfc970553a876b470")
#
## If needed, you can set custom compile options
#target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# Set the minimum version of CMake that's required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SpeechToText VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optionally set the build type if not set on the command line
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Find packages for CURL and nlohmann_json
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)

# Attempt to find PortAudio using find_package, if available
find_package(PortAudio)

# If PortAudio wasn't found, manually specify the path
if(NOT PortAudio_FOUND)
  set(PORTAUDIO_INCLUDE_DIR /opt/homebrew/Cellar/portaudio/19.7.0/include)
  set(PORTAUDIO_LIBRARY /opt/homebrew/Cellar/portaudio/19.7.0/lib/libportaudio.a)
endif()

# Find the necessary macOS frameworks
find_library(COREAUDIO_LIBRARY CoreAudio)
find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
find_library(AUDIOUNIT_LIBRARY AudioUnit)
find_library(CORESERVICES_LIBRARY CoreServices)
find_library(COREFOUNDATION_LIBRARY CoreFoundation)

# Include directories for all the found packages
include_directories(
  ${PORTAUDIO_INCLUDE_DIR}
  ${CURL_INCLUDE_DIRS}
  ${OPENSSL_INCLUDE_DIR}
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} STT.cpp)

# Link the target with the found libraries
target_link_libraries(${PROJECT_NAME}
  ${PORTAUDIO_LIBRARY}
  ${CURL_LIBRARIES}
  nlohmann_json::nlohmann_json
  ${OPENSSL_LIBRARIES}
  ${COREAUDIO_LIBRARY}
  ${AUDIOTOOLBOX_LIBRARY}
  ${AUDIOUNIT_LIBRARY}
  ${CORESERVICES_LIBRARY}
  ${COREFOUNDATION_LIBRARY}
)

# Set up the API Key as a preprocessor definition
target_compile_definitions(${PROJECT_NAME} PRIVATE API_KEY="8fb8d669305fdc492038989bfc970553a876b470")

# If needed, you can set custom compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
