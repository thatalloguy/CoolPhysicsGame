#pragma once
#include <raylib.h>

class Window {

public:
	void createWindow(const int width, const int height, const char* title, bool isFullscreen) {
		InitWindow(width, height, title);
		if (isFullscreen) {
			SetWindowState(FLAG_FULLSCREEN_MODE);
		}
		SetTargetFPS(60);
	}
	bool shouldClose() {
		return WindowShouldClose();
	}
	void closeWindow() {
		CloseWindow();
	}
};