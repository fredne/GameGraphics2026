#include "pch.h"
export module CameraAgent;
import Agent;

export namespace F
{
	class CameraAgent : public Agent
	{
	public:
		CameraAgent();

		DirectX::XMMATRIX GetCameraMatrix();
	};

}