#include "Camera.h"
#include "glm/ext.hpp"

glm::mat4 Camera::getVeiwMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 forward = glm::vec3(
		glm::cos(phiR) * cos(thetaR),
		glm::sin(phiR),
		glm::cos(phiR) * sin(thetaR)
	);

	return glm::lookAt(
		m_position,
		m_position + forward,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}
