#pragma once
#include "glm/mat4x4.hpp"

class Camera
{
public:
	Camera() {}
	Camera(float feildOfVeiw, float nearClip, float farClip) :
		m_feildOfVeiw{ feildOfVeiw }, m_nearClip{ nearClip }, m_farClip{ farClip } {}
	~Camera() {}

	/*glm::mat4 getTransform() { return m_transform;  }
	void setTransform(glm::mat4 transform) { m_transform = transform; }*/
	glm::mat4 getVeiwMatrix();
	glm::vec3 getPosition() { return m_position; }
	void setPosition(glm::vec3 position) { m_position = position; }
	float getTheta() { return m_theta; }
	void setTheta(float theta) { m_theta = theta; }
	float getPhi() { return m_phi; }
	void setPhi(float phi) { m_phi = phi; }

	float getFeildOfVeiw() { return m_feildOfVeiw; }
	void setFeildOfVeiw(float feildOfVeiw) { m_feildOfVeiw = feildOfVeiw; }
	float getNearClip() { return m_nearClip; }
	void setNearClip(float nearClip) { m_nearClip = nearClip; }
	float getFarClip() { return m_farClip; }
	void setFarClip(float farClip) { m_farClip = farClip; }

private:
	/*glm::mat4 m_transform = glm::mat4(1.0f);*/
	glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
	float m_theta{ 0.0f };
	float m_phi{ 0.0f };

	float m_feildOfVeiw{ 45.0f };
	float m_nearClip{ 0.001f };
	float m_farClip{ 1000.0f };
};

