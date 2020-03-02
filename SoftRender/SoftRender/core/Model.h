#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Vertex.h"
#include "Image.h"

class Model {
public:
    std::vector<Vertex> m_Vertexes; 
    std::vector<unsigned int> m_Indices;
    Image *m_DiffuseMapImage;

    Model(const std::string path);
};


#endif