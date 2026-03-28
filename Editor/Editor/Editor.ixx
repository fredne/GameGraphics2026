export module Editor;

export namespace F
{
	class Editor
	{
	public:
		static Editor& Get()
		{
			static Editor instance;
			return instance;
		}

		void Initialize();
		void Release();
		void Update();
		void Render();



	};
}