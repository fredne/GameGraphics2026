#include "pch.h"
import PlayerController;
import Keyboard;
import Transform;
import Agent;

namespace F
{
    void PlayerController::Initialize()
    {
        agent->GetModule<Transform>()->position = { -1.f, 0.f, 0.f };
    }

    void PlayerController::Update(float dt)
    {
        Transform* transform = agent->GetModule<Transform>();

		Vector3 move = { 0.f, 0.f, 0.f };
        if (Keyboard::Get().aKey.IsPressed()) move.x -= 1;
        if (Keyboard::Get().dKey.IsPressed()) move.x += 1;
        if (Keyboard::Get().wKey.IsPressed()) move.y += 1;
        if (Keyboard::Get().sKey.IsPressed()) move.y -= 1;

		velocity += move.Normalized() * (speed * dt);
        velocity *= std::pow(drag, dt);

		transform->position += velocity * dt;
    }
}