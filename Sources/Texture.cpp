#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType){

    type = texType;

    int widthImg, heightImg, numColCh;
    // To flip the image upon loading to fit openGLs UV Coordinates
    stbi_set_flip_vertically_on_load(true);
    // Load the image and transfom it to bytes we can work with
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Create a new texture object
    glGenTextures(1, &ID);
    // activate the slot we are using GL_TEXTURE0, GL_TEXTURE1....etc
    glActiveTexture(slot + GL_TEXTURE0);
    unit = slot;
    // Tell openGL to make the texture the current one
    glBindTexture(texType, ID);
    // Tell OpenGL how to sample the texture when scaling
    // MIN: when the texture is displayed smaller (minification)
    // MAG: when the texture is displayed larger (magnification)
    // GL_NEAREST = nearest-neighbor (sharp, blocky look)
    // GL_LINEAR  = linear interpolation (smooth, blurry look)
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Tell OpenGL how to handle texture coordinates outside [0,1]
    // S = horizontal (x axis), T = vertical (y axis)
    // GL_REPEAT = tile the texture infinitely
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload the texture data to GPU
    // internalFormat = GL_RGBA means store with 4 channels in GPU
    // format = GL_RGBA means our source image also has 4 channels
    // pixelType = GL_UNSIGNED_BYTE since stb_image gives 8-bit per channel
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, pixelType, bytes);

    // Generate mipmaps (smaller versions of the texture for distance rendering)
    glGenerateMipmap(texType);;

    // Free the image data from RAM (already copied into GPU memory)
    stbi_image_free(bytes);

    // Unbind the texture to prevent accidental modifications
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit){
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind(){
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

void Texture::Unbind(){
    glBindTexture(type, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}