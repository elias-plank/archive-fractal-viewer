#include "editor/Editor.h"

int main(int argc, char** argv) {

	// Suppress compiler warnings
	UNUSED(argc);
	UNUSED(argv);

	try {

		auto instance = std::make_unique<FractalViewer::Editor>("FractalViewer", 1280, 720);
		instance->Run();
	}
	catch (const std::exception& e) {

		ASSERT(false, e.what());
	}

	return 0;
}
