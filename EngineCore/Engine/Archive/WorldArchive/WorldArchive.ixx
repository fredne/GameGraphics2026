#include "pch.h"
export module WorldArchive;
import Archive;
import World;

export namespace F
{
	class WorldArchive : public Archive<WorldArchive, World>
	{
	private:

	public:
		void Initialize() override;

	};

}