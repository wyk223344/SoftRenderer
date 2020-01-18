#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>


Model::Model(const std::string path) {
    std::ifstream in;
    in.open (path, std::ifstream::in);
    if (in.fail()) {
        std::cout << "Model load fail" << std::endl;
        return;
    }
    std::string line;
    std::vector<Vector3> vertexes;
    std::vector<Vector3> normals;
    std::vector<Vector2> texcoords;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vector3 vertex;
            iss >> vertex.x;
            iss >> vertex.y;
            iss >> vertex.z;
            vertexes.push_back(vertex);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vector3 normal;
            iss >> normal.x;
            iss >> normal.y;
            iss >> normal.z;
            normal.normalize();
            normals.push_back(normal);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vector2 texcoord;
            iss >> texcoord.x;
            iss >> texcoord.y;
            texcoords.push_back(texcoord);
        }  else if (!line.compare(0, 2, "f ")) {
            iss >> trash;
            int index[3];
            while(iss >> index[0] >> trash >> index[1] >> trash >> index[2]) {
                Vertex data;
                data.position = vertexes[index[0] - 1];
                data.texcoord = texcoords[index[1] - 1];
                data.normal = normals[index[2] - 1];
                data.color = Vector4(1.0,1.0,1.0,1.0);
                m_Indices.push_back(m_Vertexes.size());
                m_Vertexes.push_back(data);
            }
        }
    }
    in.close();
    std::cout << "Model load finish" << std::endl;
    size_t dotIndex = path.find_last_of(".");
    if (dotIndex != std::string::npos) {
        std::string fileName = path.substr(0, dotIndex);
        m_DiffuseMapImage.readTgaFile((fileName + "_diffuse.tga").c_str());
    }
};