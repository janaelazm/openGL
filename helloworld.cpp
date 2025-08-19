#include <fmt/core.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{
    // COORDINATES        // COLORS           // TexCoord   // NORMALS          // SIDE
    -0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f, // Bottom side
    -0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 5.0f,  0.0f, -1.0f,  0.0f, // Bottom side
     0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 5.0f,  0.0f, -1.0f,  0.0f, // Bottom side
     0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 0.0f,  0.0f, -1.0f,  0.0f, // Bottom side

    -0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f, -0.8f,  0.5f,  0.0f, // Left side
    -0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 0.0f, -0.8f,  0.5f,  0.0f, // Left side
     0.0f, 0.8f,  0.0f,   0.92f, 0.86f, 0.76f,  2.5f, 5.0f, -0.8f,  0.5f,  0.0f, // Left side

    -0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 0.0f,  0.0f,  0.5f, -0.8f, // Non-facing side
     0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f,  0.0f,  0.5f, -0.8f, // Non-facing side
     0.0f, 0.8f,  0.0f,   0.92f, 0.86f, 0.76f,  2.5f, 5.0f,  0.0f,  0.5f, -0.8f, // Non-facing side

     0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f,  0.8f,  0.5f,  0.0f, // Right side
     0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 0.0f,  0.8f,  0.5f,  0.0f, // Right side
     0.0f, 0.8f,  0.0f,   0.92f, 0.86f, 0.76f,  2.5f, 5.0f,  0.8f,  0.5f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 0.0f,  0.0f,  0.5f,  0.8f, // Facing side
    -0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f,  0.0f,  0.5f,  0.8f, // Facing side
     0.0f, 0.8f,  0.0f,   0.92f, 0.86f, 0.76f,  2.5f, 5.0f,  0.0f,  0.5f,  0.8f, // Facing side

};



// Tells opengl which order of indcies to use when drawing elements
// Vertices are reusable for multiple primitives
// Each index is 6 floats long, so add the color values doesn't affect the order
GLuint indices[] = {
     // Base
    0, 1, 2,
    0, 2, 3,

    4, 6, 5,
    7, 9, 8,
    10, 12, 11,
    13, 15, 14
 };

 GLfloat lightVertices[] = {
    // coordinates
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
 };

 GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

int main()
{
     if (!glfwInit()) {
        std::cout << "GLFW initialization failed\n";
        return -1;
    }

    glfwInit();

    // Tell glfw which openGL version to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell glfw to use CORE profile for openGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "My Title", nullptr, nullptr);
    
    if (!window) {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0,0, width, height);
    glEnable(GL_DEPTH_TEST);

    // Create a new program using our shader codes, attachs and links both shaders and then deletes them
    Shader shaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");

    // Create a Vertex Array Buffer, it tells openGL how to interpet the raw data in VBO
    VAO VAO1;
    // Tells openGL to make VAO1 the current Vertex Array
    // All vertex setups like Atrrib belong to VAO1
    VAO1.Bind();

    // Create Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Create Vertex Element Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VAO to VBO and specifies how to read the vertices
    // Specifies that each lump of data is 6 float (3 for coordinates, 3 for color)
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11*sizeof(float),(void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11*sizeof(float),(void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11*sizeof(float),(void*)(6*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11*sizeof(float),(void*)(8*sizeof(float)));
    // Unbind all objects to avoid accidently modifying it
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    Shader lightShader("Resources/Shaders/light.vert", "Resources/Shaders/light.frag");
    // Create a Vertex Array Buffer, it tells openGL how to interpet the raw data in VBO
    VAO lightVAO;
    // Tells openGL to make VAO1 the current Vertex Array
    // All vertex setups like Atrrib belong to VAO1
    lightVAO.Bind();

    // Create Vertex Buffer Object and links it to vertices
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    // Create Vertex Element Object and links it to indices
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    // Links VAO to VBO and specifies how to read the vertices
    // Specifies that each lump of data is 6 float (3 for coordinates, 3 for color)
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3*sizeof(float),(void*)0);
    // Unbind all objects to avoid accidently modifying it
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPosition);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    // Texture
    Texture plankton("Resources/Texture/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    plankton.texUnit(shaderProgram, "tex0", 0);

    //Camera
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


    // Main loop: runs until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Handles camera controls
        camera.Inputs(window);
        // Updates and exports camera matrix to the vertex shader
        camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

        shaderProgram.Activate();
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.cameraPosition.x, camera.cameraPosition.y, camera.cameraPosition.z);
        camera.Matrix(shaderProgram, "camMatrix");
        plankton.Bind();
        // Make the VAO the current one after we unbound it for saftey reasons
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        // Poll for events (keyboard, mouse, etc.)
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    plankton.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}