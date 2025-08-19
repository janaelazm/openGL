#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position){
    Camera::width = width;
    Camera::height = height;
    Camera::cameraPosition = position;
}

void Camera::Matrix(Shader& shader, const char* uniform){

     // Exports camera to vertex shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

}

 void Camera::UpdateMatrix(float FOVDegree, float nearPlane, float farPlane){

    // Declare two identity matrices so that they aren't null
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Makes camera look in right direction from right position
    view = glm::lookAt(cameraPosition, cameraPosition + cameraOrientation, up);
    // Creates a projection matrix, which defines how the 3D scene is projected onto a 2D screen, simulating a realistic camera lens.
    projection = glm::perspective(glm::radians(FOVDegree), (float)(width/height), nearPlane, farPlane);
    cameraMatrix = projection * view;

 }

 void Camera::Inputs(GLFWwindow* window){

    //Checks if W is pressed, moves camera FORWARD 
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){

        cameraPosition += speed * cameraOrientation;
    }
    
    //Checks if S is pressed, moves camera BACKWARDS 
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){

        cameraPosition += speed * -cameraOrientation;
    }

    //Checks if A is pressed, moves camera LEFT 
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){

         cameraPosition += speed * -glm::normalize(glm::cross(cameraOrientation, up));
    }

    //Checks if D is pressed, moves camera RIGHT 
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){

        cameraPosition += speed * glm::normalize(glm::cross(cameraOrientation, up));
    }

    //Checks if SPACE is pressed, moves camera UP 
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){

        cameraPosition += speed * up;
    }

    //Checks if LEFT CONTROL is pressed, moves camera DOWN
     if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){

        cameraPosition += speed * -up;
    }

    //Checks if LEFT SHIFT is pressed, moves camera FASTER 
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){

        speed = 0.004f;
    }

    //Checks if LEFT SHIFT is pressed, moves camera SLOWER 
    else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){

        speed = 0.001f;
    }


    //Checks if RIGHT MOUSE BUTTON is pressed, ROTATES camera
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){

        // Hide cursor when click is registerd
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        // Stop the camera from jumping on the first click
        if(firstClick){
            glfwSetCursorPos(window, width/2, height/2);
            firstClick = false;
        }

        // Mouse cursor coordinates
        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the mouse cursor such that they begin in the middle of the window
        // and then converts them to degrees for rotation control
        float rotX = sensitivity * (float)((mouseY - (height/2))/height);
        float rotY = sensitivity * (float)((mouseX - (height/2))/height);
        // Calculates upcoming vertical changes in orienetation
        glm::vec3 newOrientation = glm::rotate(cameraOrientation, glm::radians(-rotX), glm::normalize(glm::cross(cameraOrientation, up)));
        // Checks if the next vertical orientation is valid or not
        if( ! ((glm::angle(newOrientation, up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -up) <= glm::radians(5.0f))) ){
            cameraOrientation = newOrientation;
        };
        // Rotates the orientation left and right
        cameraOrientation = glm::rotate(cameraOrientation, glm::radians(-rotY), up);
        // Set the cursor position to the middle of the window so it doesn't move around
        glfwSetCursorPos(window, (width/2), (height/2) );

    }
    // Makes cursor appear again after releasing the RIGHT MOUSE BUTTON and resets first click to prevent camera from jumping
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){

         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
         firstClick = true;
    }
 }

