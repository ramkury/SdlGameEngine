#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& associated) : Component(associated)
{
}

void CameraFollower::Update(float dt)
{
	associated.Box.x = Camera::pos.x;
	associated.Box.y = Camera::pos.y;
}

void CameraFollower::Render()
{
}

bool CameraFollower::Is(const std::string& type)
{
	return type == "cameraFollower";
}
