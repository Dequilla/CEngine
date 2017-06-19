#include "Camera.h"

ce::graphics::Camera::Camera(glm::vec3 position) : m_position(position) 
{
	// Setup a default projection
	int w = ce::core::Application::getInstance().screenWidth;
	int h = ce::core::Application::getInstance().screenHeight;
	
	setProjection(m_fov, (float)w / (float)h, m_near, m_far);
}

glm::mat4 ce::graphics::Camera::getViewMatrix() const
{
	return glm::translate(glm::mat4_cast(m_orientation), m_position);
}

glm::mat4 ce::graphics::Camera::getProjectionMatrix() const
{
	return m_projection;
}

void ce::graphics::Camera::setFOV(float fov)
{
	setProjection(fov, m_aspectRatio, m_near, m_far);
}

void ce::graphics::Camera::setNearFar(float near, float far)
{
	setProjection(m_fov, m_aspectRatio, near, far);
}

void ce::graphics::Camera::setAspectRatio(float ratio)
{
	setProjection(m_fov, ratio, m_near, m_far);
}

void ce::graphics::Camera::setProjection(float fov, float aspectRatio, float near, float far)
{
	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_near = near;
	m_far = far;

	m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

glm::vec3 ce::graphics::Camera::getPosition() const
{
	return m_position;
}

glm::vec3 ce::graphics::Camera::getForwardVector() const
{
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f) * m_orientation;
	return forward;
}

glm::vec3 ce::graphics::Camera::getLeftVector() const
{
	glm::vec3 left = glm::vec3(-1.0f, 0.0f, 0.0f) * m_orientation;
	return left;
}

void ce::graphics::Camera::resetOriantation()
{
	m_orientation = glm::quat();
}

void ce::graphics::Camera::rotate(float angle, const glm::vec3 &axis)
{
	m_orientation *= glm::angleAxis(glm::radians(angle), axis * m_orientation);
}

void ce::graphics::Camera::rotate(float angle, float x, float y, float z)
{
	m_orientation *= glm::angleAxis(glm::radians(angle), glm::vec3(x, y, z) * m_orientation);
}

void ce::graphics::Camera::move(const glm::vec3 & vec)
{
	m_position += vec;
}

void ce::graphics::Camera::move(float x, float y, float z)
{
	m_position += glm::vec3(x, y, z);
}

void ce::graphics::Camera::translate(const glm::vec3 & vec)
{
	m_position += vec * m_orientation;
}

void ce::graphics::Camera::translate(float x, float y, float z)
{
	m_position += glm::vec3(x, y, z) * m_orientation;
}

void ce::graphics::Camera::pitch(float angle)
{
	rotate(angle, 1.0f, 0.0f, 0.0f);
}

void ce::graphics::Camera::yaw(float angle)
{
	rotate(angle, 0.0f, 1.0f, 0.0f);
}

void ce::graphics::Camera::roll(float angle)
{
	rotate(angle, 0.0f, 0.0f, 1.0f);
}

void ce::graphics::Camera::setPosition(glm::vec3 pos)
{
	this->m_position = pos;
}

void ce::graphics::Camera::setPosition(float x, float y, float z)
{
	this->m_position = glm::vec3(x, y, z);
}