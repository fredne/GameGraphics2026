#include "pch.h"
import CameraAgent;
import Camera;
import Transform;

namespace F
{
	CameraAgent::CameraAgent()
	{
		AddModule<Camera>();
	}

    DirectX::XMMATRIX CameraAgent::GetCameraMatrix()
    {
        Transform* tr = GetModule<Transform>();
        XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&tr->rotation));
        XMVECTOR eye = XMLoadFloat3(&tr->position);
        XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), R);
        XMVECTOR target = eye + forward;

        return XMMatrixLookAtLH(eye, target, XMVectorSet(0, 1, 0, 0));
    }
}