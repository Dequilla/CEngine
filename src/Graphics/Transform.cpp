#include "Transform.h"

glm::mat4 ce::graphics::Transform::getAsMatrix()
{
	glm::mat4 rot = glm::mat4_cast(this->getOrientation());

	glm::mat4 matrix;
	matrix = glm::translate(matrix, m_position);
	matrix = glm::scale(matrix, m_scale);
	matrix *= rot;

	return matrix;
}

void ce::graphics::Transform::pitch(float degrees)
{
	m_rotation.x += degrees;
}

void ce::graphics::Transform::yaw(float degrees)
{
	m_rotation.y += degrees;
}

void ce::graphics::Transform::roll(float degrees)
{
	m_rotation.z += degrees;
}

void ce::graphics::Transform::rotate(float x, float y, float z)
{
	m_rotation += glm::vec3(x, y, z);
}

void ce::graphics::Transform::rotate(glm::vec3 degrees)
{
	m_rotation += degrees;
}

void ce::graphics::Transform::setRotation(float x, float y, float z)
{
	m_rotation = glm::vec3(x, y, z);
}

void ce::graphics::Transform::setRotation(glm::vec3 degrees)
{
	m_rotation = degrees;
}

glm::quat ce::graphics::Transform::getOrientation()
{
	// Order XYZ
	glm::quat orientX = glm::angleAxis(glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat orientY = glm::angleAxis(glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat orientZ = glm::angleAxis(glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	return orientX * orientY * orientZ;
}

void ce::graphics::Transform::translate(float x, float y, float z)
{
	m_position += glm::vec3(x, y, z) * this->getOrientation();
}

void ce::graphics::Transform::translate(glm::vec3 xyz)
{
	m_position += xyz * this->getOrientation();
}

void ce::graphics::Transform::move(float x, float y, float z)
{
	m_position += glm::vec3(x, y, z);
}

void ce::graphics::Transform::move(glm::vec3 xyz)
{
	m_position += xyz;
}

void ce::graphics::Transform::setPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void ce::graphics::Transform::setPosition(glm::vec3 xyz)
{
	m_position = xyz;
}

void ce::graphics::Transform::scale(float x, float y, float z)
{
	m_scale += glm::vec3(x, y, z);
}

void ce::graphics::Transform::scale(glm::vec3 xyz)
{
	m_scale += xyz;
}

void ce::graphics::Transform::setScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

void ce::graphics::Transform::setScale(glm::vec3 xyz)
{
	m_scale = xyz;
}