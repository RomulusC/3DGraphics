#pragma once
#include <glad>
#include <glm/glm.hpp>


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{    
public:
    enum Camera_Movement 
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        DOWN,
        UP
    };
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float defaultZoom;

    // Constructor with vectors
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float speed, float sensitivity, float zoom);

    
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float speed, float sensitivity, float zoom);
  

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    
    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
   

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
  

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);
 

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
   
};