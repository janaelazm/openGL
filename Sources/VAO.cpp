#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponenets, GLenum type, GLsizeiptr stride, void* offset){
    VBO.Bind();
    // Write the instructions so openGL knows how to read VBO data
    glVertexAttribPointer(layout ,numComponenets, type, GL_FALSE, stride, offset);
    // Enable the vertex attrib array so openGL uses it
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind(){
     glBindVertexArray(ID);
}

void VAO::Unbind(){
     glBindVertexArray(0);
}

void VAO::Delete(){
    glDeleteVertexArrays(1, &ID);
}