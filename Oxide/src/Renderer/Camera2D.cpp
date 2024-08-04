#include "Camera2D.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Oxide {
	Camera2D::Camera2D(): m_view(1.0f), m_camPos(0.0f, 0.0f, 0.0f)
	{
	}
	glm::mat4 Camera2D::getProjectionMatrix()
	{
		return m_view;
	}
	void Camera2D::setCameraPosition(glm::vec3& pos)
	{
		m_camPos = pos;
		m_view = glm::translate(glm::mat4(1.0f), pos);
	}
	glm::vec3& Camera2D::getCameraPosition()
	{
		return m_camPos;
	}
	Camera2D::~Camera2D()
	{
	}
}