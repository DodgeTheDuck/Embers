#include "stdafx.h"
#include "gui.h"

namespace Core::Gui {

	void GuiManager::Init(HWND hwnd) {
		IMGUI_CHECKVERSION();
		_context = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_InitForOpenGL(hwnd);
		ImGui_ImplOpenGL3_Init();
	}

	void GuiManager::AddWidget(Ref<Widget> widget) {
		_widgets.push_back(widget);
	}

	void GuiManager::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void GuiManager::DrawWidgets()
	{
		for (auto& widget : _widgets) {
			widget->Draw();
		}
	}

	void GuiManager::End() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	ImGuiContext* GuiManager::GetContext()
	{
		return _context;
	}

}