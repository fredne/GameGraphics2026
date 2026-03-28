#include "pch.h"
export module ShaderArchive;
import Archive;
import Shader;

export namespace F
{
	class ShaderArchive : public Archive<ShaderArchive, Shader>
	{
	public:
		void Initialize() override;

	};

}