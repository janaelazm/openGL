#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include "shaderClass.h"

class Texture{

    public:
    GLuint ID;
    GLenum type;
    GLuint unit;
    glm::vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 diffuse =  glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float shininess = 32.0f;

    //e.g image.png, GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE
    Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

   // Associates a sampler uniform in the fragment shader with a specific texture unit.
   // Example: texUnit(shader, "tex0", 0) makes sampler2D tex0 use GL_TEXTURE0.
    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
    void setMaterialLighting(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, float shiniess);
};

#endif