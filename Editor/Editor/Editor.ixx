export module Editor;

export namespace F
{
	class Editor
	{
	private:
		bool imguiInit = false;
		bool imguiRelease = false;
	
		Editor();
	
	public:
		static Editor& Get()
		{
			static Editor instance;
			return instance;
		}

		void Initialize();
		void ImGuiInit();
		void Release();
		void Update();
		void Render();



	};
}