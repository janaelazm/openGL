#include "shaderClass.h"

std::string get_file_contents(const char* FileName){
    std::ifstream in (FileName, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile){
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

     // Create a vertex shader object and get reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the source code to the vertex shader object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //compile it to machine code so that the computer understands it
    glCompileShader(vertexShader);

    // Create a fragment shader object and get reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach the source code to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    //compile it to machine code so that the computer understands it
    glCompileShader(fragmentShader);

    // Create a shader program and get its reference
    ID = glCreateProgram();

    // Attach the vertex and fragment shader to the program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    //Link the shaders to the program and wrap up
    glLinkProgram(ID);
   
    // Delete the vertex and fragment shaders now that they are in the program shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}