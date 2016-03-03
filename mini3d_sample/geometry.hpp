
// Copyright (c) <2011> Daniel Peterson
// This file is part of Mini3D <www.mini3d.org>
// It is distributed under the MIT Software License <www.mini3d.org/license.php>


// ----- GEOMETRY DATA --------------------------------------------------------

// Vertex Data Structure
struct VertexPCT { float x,y,z,w;  float r,g,b,a;  float u,v; };

// Vertex array
VertexPCT vertices[] = {
    // Front
    {-1.0f, -1.0f,  1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  0.0f, 0.0f}, // Corner 0
    { 1.0f, -1.0f,  1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  1.0f, 0.0f}, // Corner 1
    { 1.0f,  1.0f,  1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  1.0f, 1.0f}, // Corner 2
    {-1.0f,  1.0f,  1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  0.0f, 1.0f}, // Corner 3
                        
    // Back
    { 1.0f, -1.0f, -1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  0.0f, 0.0f}, // Corner 4
    {-1.0f, -1.0f, -1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  1.0f, 0.0f}, // Corner 5
    {-1.0f,  1.0f, -1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  1.0f, 1.0f}, // Corner 6
    { 1.0f,  1.0f, -1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  0.0f, 1.0f}, // Corner 7

    // Right
    { 1.0f, -1.0f,  1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  0.0f, 0.0f}, // Corner 1
    { 1.0f, -1.0f, -1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  1.0f, 0.0f}, // Corner 4
    { 1.0f,  1.0f, -1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  1.0f, 1.0f}, // Corner 7
    { 1.0f,  1.0f,  1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  0.0f, 1.0f}, // Corner 2

    // Left
    {-1.0f, -1.0f, -1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  0.0f, 0.0f}, // Corner 5
    {-1.0f, -1.0f,  1.0f, 1.0f,  0.9f, 0.9f, 0.9f, 1.0f,  1.0f, 0.0f}, // Corner 0
    {-1.0f,  1.0f,  1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  1.0f, 1.0f}, // Corner 3
    {-1.0f,  1.0f, -1.0f, 1.0f,  0.6f, 0.6f, 0.6f, 1.0f,  0.0f, 1.0f}, // Corner 6

    // Top
    {-1.0f, -1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f}, // Corner 5
    { 1.0f, -1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f}, // Corner 4
    { 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f}, // Corner 1
    {-1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f}, // Corner 0

    //Bottom
    { 1.0f,  1.0f, -1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f,  0.0f, 0.0f}, // Corner 7
    {-1.0f,  1.0f, -1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f,  1.0f, 0.0f}, // Corner 6
    {-1.0f,  1.0f,  1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f,  1.0f, 1.0f}, // Corner 3
    { 1.0f,  1.0f,  1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f,  0.0f, 1.0f}  // Corner 2
};

// Index array
unsigned int indices[] = {0, 1, 2, 0, 2, 3,    4, 5, 6, 4, 6, 7,    8, 9, 10, 8, 10, 11,    12, 13, 14, 12, 14, 15,    16, 17, 18, 16, 18, 19,    20, 21, 22, 20, 22, 23};
