#include "Editor.h"

namespace FractalViewer {
	
	Editor::Editor(const std::string& title, uint32_t width, uint32_t height) : App(title, width, height) {
	
		editorView = std::make_unique<EditorView>();
		PushView(editorView.get());
	}
}