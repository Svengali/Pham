//////////////////////////////////////////////////////////////////////////////
//
// P H A M
//
// copyright 2005-2008 Marc Hernandez
#pragma once

namespace grx
{

typedef unsigned short IndexType;

// NOTE: This data could be compressed, but it's not really the bottleneck at the moment
struct Vertex
{
  float x;
  float y;
  float z;
  float nx;
  float ny;
  float nz;
};


struct SimpleMesh
{
  void clear()
  {
    vertices.clear();
    indices.clear();
  }

  std::vector<Vertex> vertices;
  std::vector<IndexType> indices;
};



void CreateIcosahedron(SimpleMesh *pOutMesh)
{
    static const float a = std::sqrt(2.0f / (5.0f - std::sqrt(5.0f)));
    static const float b = std::sqrt(2.0f / (5.0f + std::sqrt(5.0f)));

    static const size_t num_vertices           = 12;
    static const Vertex vertices[num_vertices] = // x, y, z
        {
            {-b, a, 0},
            {b, a, 0},
            {-b, -a, 0},
            {b, -a, 0},
            {0, -b, a},
            {0, b, a},
            {0, -b, -a},
            {0, b, -a},
            {a, 0, -b},
            {a, 0, b},
            {-a, 0, -b},
            {-a, 0, b},
        };

    static const size_t    num_triangles = 20;
    static const IndexType indices[num_triangles * 3] =
        {
            0,  5, 11,
            0,  1,  5,
            0,  7,  1,
            0, 10,  7,
            0, 11, 10,
            1, 9, 5,
            5, 4, 11,
            11, 2, 10,
            10, 6, 7,
            7, 8, 1,
            3, 4, 9,
            3, 2, 4,
            3, 6, 2,
            3, 8, 6,
            3, 9, 8,
            4, 5, 9,
            2, 11, 4,
            6,10, 2,
            8, 7, 6,
            9, 1, 8,
        };

    pOutMesh->clear();
    pOutMesh->vertices.insert(pOutMesh->vertices.end(), vertices, vertices + num_vertices);
    pOutMesh->indices.insert(pOutMesh->indices.end(), indices, indices + num_triangles * 3);
}












}