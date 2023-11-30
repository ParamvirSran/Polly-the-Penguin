#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

namespace tinygltf {
    class Model; //forward dec
}

class Display {
public:
    void pollyFeels(const std::string& emotion);
    void loadGLTFModel(const std::string& filename);
    void parseGLTFModel(const tinygltf::Model& model);
    void pollyWaves();
};

#endif // DISPLAY_H
