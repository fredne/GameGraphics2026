#include "pch.h"
import MeshArchive;

namespace F
{
	void MeshArchive::Initialize()
	{
        std::vector<Vertex> trianglVertices =
        {
            {  0.0f,  0.5f, 0.5f, 1.0f, 1.0f },
            {  0.5f, -0.5f, 0.5f, 1.0f, 1.0f },
            { -0.5f, -0.5f, 0.5f, 1.0f, 1.0f },
        };
        Register<Mesh>("Triangle")->Initialize(trianglVertices);
	}
}