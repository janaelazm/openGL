#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb_image.h>
#include "shaderClass.h"

class Texture{

    public:
    GLuint ID;
    GLenum type;
    //e.g image.png, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE
    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

   // Associates a sampler uniform in the fragment shader with a specific texture unit.
   // Example: texUnit(shader, "tex0", 0) makes sampler2D tex0 use GL_TEXTURE0.
    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};

#endif