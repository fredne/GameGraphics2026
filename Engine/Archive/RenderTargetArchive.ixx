#include "pch.h"
export module RenderTargetArchive;
import Archive;
import RenderTarget;

export namespace F
{
	class RenderTargetArchive : public Archive<RenderTargetArchive, RenderTarget>
	{
	public:

	};
}