#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera{
    public:
    glm::vec3 cameraPosition;
    glm::vec3 cameraOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm:: mat4 cameraMatrix = glm::mat4(1.0f);
    
    // Stores height and width of window
    int width;
    int height;

    // Handles camera speed and rotation sensitivity 
    float speed = 0.001f;
    float sensitivity = 100.0f;

    // To pervent the camera jumping
    bool firstClick = true;

    // Init camera members
    Camera(int width, int height, glm::vec3 position);
    // Updates and exports camera matrix to the vertex shader
    void Matrix(Shader& shader, const char* uniform);
    void UpdateMatrix(float FOVDegree, float nearPlane, float farPlane);
    // Handles camera controls
    void Inputs(GLFWwindow* window);

};

#endif