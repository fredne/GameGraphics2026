#pragma once
import Debug;
#include "Resource.h"
import Archive;
namespace F
{
	class ResourceArchive : public Archive<ResourceArchive, Resource>
	{
	private:

	public:
		void Initialize() override;

	};

}

