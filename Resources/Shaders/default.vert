#version 330 core

//Coordinates / position
layout (location = 0) in vec3 aPos;
// Texture Coordinates
layout (location = 1) in vec2 aTex;
//Normals (not specfically normalized)
layout (location = 2) in vec3 aNormal;

// Exports texture coordinates for fragment shader
out vec2 texCoor;
// Exports the current position for fragment shader
out vec3 crntPos;
// Exports the normals for fragment shader
out vec3 Normal;

// Gets camera matrix from main function 
uniform mat4 camMatrix;
// Gets the model matrix from main function
uniform mat4 model;


void main()
{
    crntPos = vec3(model * vec4(aPos, 1.0f));

    // Outpouts the position/coordinates of all vertices
    gl_Position = camMatrix * vec4(crntPos, 1.0);
    texCoor = aTex;
    Normal = aNormal;
}