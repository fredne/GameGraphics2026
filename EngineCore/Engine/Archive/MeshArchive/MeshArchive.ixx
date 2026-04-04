#include "pch.h"
export module MeshArchive;
import Archive;
import Mesh;

export namespace F
{
	class MeshArchive : public Archive<MeshArchive, Mesh>
	{
	public:
		virtual void Initialize() override;
	};

}