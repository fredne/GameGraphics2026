#include "pch.h"
export module Config;

export namespace F
{
	class Window;
	struct VideoMode
	{
		Vector2<uint32_t> resolution;
		bool fullscreen;
		bool mustResize;

		void Resize(Window* window);

	};

	class Config
	{
		VideoMode videoMode;

		Config() = default;
		Config(const Config&) = delete;
		Config& operator=(const Config&) = delete;
		Config(Config&&) = delete;
		Config& operator=(Config&&) = delete;

		void VideoModeUpdate();

	public:
		static Config& Get()
		{
			static Config instance;
			return instance;
		}

		void Update();

	};

}