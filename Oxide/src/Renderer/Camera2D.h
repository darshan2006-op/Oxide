#pragma once
#include "glm/glm.hpp"

namespace Oxide {
	class Camera2D {
	public:
		Camera2D();
		glm::mat4 getProjectionMatrix();
		void setCameraPosition(glm::vec3& pos);
		glm::vec3& getCameraPosition();
		virtual ~Camera2D();
	private:
		glm::mat4 m_view;
		glm::vec3 m_camPos;
	};
}