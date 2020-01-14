#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Vertex.h"

class Model {
public:
    std::vector<Vertex> m_Vertexes; 
    std::vector<unsigned int> m_Indices;

    Model(const std::string &path);
    // void loadFile(const std::string &path);
};


#endif