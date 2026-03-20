#pragma once

using namespace DirectX;

namespace F
{
    class Transform
    {
    public:
        XMFLOAT3 position = { 0.f, 0.f, 0.f };
        XMFLOAT3 rotation = { 0.f, 0.f, 0.f };
        XMFLOAT3 scale = { 1.f, 1.f, 1.f };

        XMMATRIX GetMatrix() const
        {
            return  XMMatrixScalingFromVector(XMLoadFloat3(&scale)) *
                XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation)) *
                XMMatrixTranslationFromVector(XMLoadFloat3(&position));
        }

        XMMATRIX GetMatrixInverse() { return XMMatrixTranspose(GetMatrix()); }
    };


}