#pragma once
#include "../Core.h"
#include <fstream>

namespace FractalViewer::Util {

	static std::string ReadFile(const std::string& path) {

		std::fstream fin = std::fstream(path, std::ios::in);

		ASSERT(fin.good(), "Couldn't open file!");

		return std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
	}

	static std::string SaveFileDialog() {

		OPENFILENAMEA ofn;
		char file[MAX_PATH] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = file;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = "PNG File\0*.png";
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST;

		if (GetSaveFileNameA(&ofn) == 1) {

			return std::string(ofn.lpstrFile);
		}
		else {

			MessageBoxA(nullptr, "Operation cancelled", "Abort", NULL);
			return std::string();
		}
	}
}