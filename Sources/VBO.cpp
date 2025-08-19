#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size){
    glGenBuffers(1, &ID);
    // Bind the VBO, specifiying it as GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Introduce the vertices to VBO by using GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, size ,vertices, GL_STATIC_DRAW);
}

void VBO::Bind(){
     glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind(){
     glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
    glDeleteBuffers(1, &ID);
}