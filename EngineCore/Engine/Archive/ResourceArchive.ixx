#include"pch.h"
export module ResourceArchive;
import Archive;
import Resource;

export namespace F
{
	class ResourceArchive : public Archive<ResourceArchive, Resource>
	{
	private:

	public:
		void Initialize() override;

	};

}