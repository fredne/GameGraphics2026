#include "pch.h"
import PC;
import Agent;
import Transform;
import Keyboard;

namespace F
{
    void PC::Initialize()
    {
    }

    void PC::Update(float dt)
	{
        Transform* transform = agent->GetModule<Transform>();

        Vector3 move = { 0.f, 0.f, 0.f };
        if (Keyboard::Get().left.IsPressed()) move.x -= 1;
        if (Keyboard::Get().right.IsPressed()) move.x += 1;
        if (Keyboard::Get().up.IsPressed()) move.y += 1;
        if (Keyboard::Get().down.IsPressed()) move.y -= 1;

        velocity += move.Normalized() * (speed * dt);
        velocity *= std::pow(drag, dt);

        transform->position += velocity * dt;
	}
}