#pragma once

namespace F
{
    class VertexBuffer;
    class Transform;
    class Model
    {
    private:
        Transform* transform;
        float speed = 1.f;

        bool b = false;

    public:
        VertexBuffer* vBuffer;

        Model();
        ~Model();

        void Release();

        void Update(float dt);
        void Render(ID3D11DeviceContext* context);
  
    };

}

