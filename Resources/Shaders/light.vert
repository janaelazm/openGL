#version 330 core

// Light coordinates/position
layout (location = 0) in vec3 aPos;

// Gets camera matrix from main function
uniform mat4 camMatrix;
// Gets model matrix from main function
uniform mat4 model;


void main()
{
    // Outputs all the coordinates for light vertices
    gl_Position = camMatrix * model * vec4(aPos, 1.0f);
  
}