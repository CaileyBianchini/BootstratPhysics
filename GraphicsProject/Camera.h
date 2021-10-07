#pragma once
#include "Transform.h"

class Camera
{
public:
	Camera() {}
	Camera(float feildOfVeiw, float nearClip, float farClip) :
		m_feildOfVeiw{ feildOfVeiw }, m_nearClip{ nearClip }, m_farClip{ farClip } {}
	~Camera() {}

	Transform getTransform() { return m_transform;  }
	void setTransform(Transform transform) { m_transform = transform; }
	float getFeildOfVeiw() { return m_feildOfVeiw; }
	void setFeildOfVeiw(float feildOfVeiw) { m_feildOfVeiw = feildOfVeiw; }
	float getNearClip() { return m_nearClip; }
	void setNearClip(float nearClip) { m_nearClip = nearClip; }
	float getFarClip() { return m_farClip; }
	void setFarClip(float farClip) { m_farClip = farClip; }

private:
	Transform m_transform = Transform();
	float m_feildOfVeiw = 45.0f;
	float m_nearClip = 0.001f;
	float m_farClip = 1000.0f;
};

