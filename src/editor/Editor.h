#pragma once
#include "../core/App.h"
#include "../core/Core.h"
#include "views/EditorView.h"

namespace FractalViewer {

	class Editor : public App {

	private:
		std::unique_ptr<EditorView> editorView;

	public:
		Editor() = delete;
		Editor(const std::string& title, uint32_t width, uint32_t height);
	};
}

