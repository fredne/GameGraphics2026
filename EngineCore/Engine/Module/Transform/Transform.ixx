#include "pch.h"
export module Transform;
import Module;

export namespace F
{
    class Transform : public Module
    {
    public:

        Vector3 position = { 0.f, 0.f, 0.f };
        Vector3 rotation = { 0.f, 0.f, 0.f };
        Vector3 scale = { 1.f, 1.f, 1.f };

        XMMATRIX GetMatrix() const
        {
			XMVector3Dot(XMVECTOR{ 1.f, 1.f, 1.f, 0.f }, XMLoadFloat3(&scale));
            return  XMMatrixScalingFromVector(XMLoadFloat3(&scale)) *
                    XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation)) *
                    XMMatrixTranslationFromVector(XMLoadFloat3(&position));
        }

        XMMATRIX GetMatrixTranpose() const { return XMMatrixTranspose(GetMatrix()); }
        XMMATRIX GetMatrixInverse() const { return XMMatrixInverse(nullptr, GetMatrix()); }

        void Update(float dt) override;

    };

}