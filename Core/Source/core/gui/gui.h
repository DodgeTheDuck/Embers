#pragma once

#include "dll.h"
#include "widget.h"

namespace Core::Gui {

	class ENGINE_API GuiManager {

	public:
		void Init(HWND hwnd);
		Ref<Widget> AddWidget(Ref<Widget> widget);
		void Begin();
		void DrawWidgets();
		void End();
		ImGuiContext* GetContext();
	private:
		ImGuiContext* _context;
		std::vector<Ref<Widget>> _widgets;

	};

}