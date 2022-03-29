#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;
    // euler Angles
    float mYaw;
    float mPitch;
    // camera options
    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;

public:
    Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),glm::uvec3 up = glm::vec3(0.0f,1.0f,0.0f),float yaw =YAW,float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    ~Camera();

    glm::mat4 GetViewMatrix();
    void processKeyboard(Camera_Movement direct, float deltaTime);
    void processMouseMove(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScoll(float yoffset);
private:
    __inline void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        mFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        mUp = glm::normalize(glm::cross(mRight, mFront));
   };
};

