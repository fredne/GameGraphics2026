#include "pch.h"
export module Material;

export namespace F
{
	class Shader;
	class Material
	{
	private:
		Shader* shader;

	public:
		void Bind(ID3D11DeviceContext* context);
		Shader* GetShader();
		void SetShader(Shader* shader);
	};

}
