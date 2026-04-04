#include "pch.h"
export module Camera;
import Module;

export namespace F
{
	enum class ProjectionType
	{
		Orthographic,
		Perspective,
	};	

	class Camera : public Module
	{
	private:
		ProjectionType projectionType;

	public:
		static Camera* mainCamera;
		Camera();
		void Initialize() override;	
		void Update(float dt) override;

		DirectX::XMMATRIX GetCameraMatrix();

	};
}