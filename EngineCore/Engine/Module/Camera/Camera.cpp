#include "pch.h"
import Camera;
import Transform;
import Agent;     
import DX;

namespace F
{
	Camera* Camera::mainCamera = nullptr;
	Camera::Camera() :
		projectionType(ProjectionType::Orthographic)
    { }

    void Camera::Initialize()
    {
		mainCamera = this;
		agent->GetModule<Transform>()->position.z = -10;

    }

    void Camera::Update(float dt)
    {
    }

    DirectX::XMMATRIX Camera::GetCameraMatrix()
    {
		Transform* tr = agent->GetModule<Transform>();
        XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&tr->rotation));
        XMVECTOR eye = XMLoadFloat3(&tr->position);
        XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), R);
        XMVECTOR target = eye + forward;

		XMMATRIX view = XMMatrixLookAtLH(eye, target, XMVectorSet(0, 1, 0, 0));
		
		Vector2<uint32_t> renderSize = DX::Get().GetCurrentRenderSize();
		float aspectRatio = (float)renderSize.x / renderSize.y;
		XMMATRIX projection;
		switch (projectionType)
		{
		case F::ProjectionType::Orthographic:
			projection = XMMatrixOrthographicLH(2.f * aspectRatio, 2.f, 0.1f, 100.f);
			break;
		case F::ProjectionType::Perspective:
			projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, aspectRatio, 0.1f, 100.f);
			break;
		default:
			break;
		}

		return view * projection;
    }
}