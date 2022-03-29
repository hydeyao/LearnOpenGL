#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::uvec3 up, float yaw, float pitch) :\
	mFront(glm::vec3(0.0f,0.0f,-1.0f)),mMouseSensitivity(SENSITIVITY),mMovementSpeed(SPEED),mZoom(ZOOM)
{
	mPosition = position;
	mWorldUp = up;
	mYaw = yaw;
	mPitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : \
	mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mMouseSensitivity(SENSITIVITY), mMovementSpeed(SPEED),mZoom(ZOOM)
{
	mPosition = glm::vec3(posX, posY, posZ);
	mWorldUp = glm::vec3(upX, upY, upZ);
	mYaw = yaw;
	mPitch = pitch;
	updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(mPosition,mPosition + mFront,mUp);
}

void Camera::processKeyboard(Camera_Movement direct, float deltaTime)
{
	float velocity = mMovementSpeed * deltaTime;
	if (direct == FORWARD)
		mPosition += mFront * velocity;
	if (direct == BACKWARD)
		mPosition -= mFront * velocity;
	if (direct == LEFT)
		mPosition -= mRight * velocity;
	if (direct == RIGHT)
		mPosition += mRight * velocity;
}

void Camera::processMouseMove(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= mMouseSensitivity;
	yoffset *= mMouseSensitivity;

	mYaw += xoffset;
	mPitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (mPitch > 89.0f)
			mPitch = 89.0f;
		if (mPitch < -89.0f)
			mPitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::processMouseScoll(float yoffset)
{
	mZoom -= (float)yoffset;
	if (mZoom < 1.0f)
		mZoom = 1.0f;
	if (mZoom > 45.0f)
		mZoom = 45.0f;
}
