#include "pch.h"
import PlayerController;
import Keyboard;
import Transform;
import Agent;

namespace F
{
    void PlayerController::Update(float dt)
    {
        Transform* transform = agent->GetModule<Transform>();
        float move = speed * dt;
        if (Keyboard::Get().aKey.IsPressed())
        {
            transform->position.x -= move;
        }
        if (Keyboard::Get().dKey.IsPressed())
        {
            transform->position.x += move;
        }
        if (Keyboard::Get().wKey.IsPressed())
        {
            transform->position.y += move;
        }
        if (Keyboard::Get().sKey.IsPressed())
        {
            transform->position.y -= move;
        }
    }
}