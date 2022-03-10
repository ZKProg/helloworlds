#include "MainActivity.h"
#include "Renderer.h"

#include <Windows.h>

#include <iostream>
#include <memory>
#include <vector>

int WinMain(HINSTANCE current, HINSTANCE previous, LPSTR cmdLine, int cmdCount) {

	MainActivity main(800, 600);
	Renderer renderer(main);

	MSG msg = { 0 };

	while (true) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) break;
		}

		renderer.paintFrame();
		renderer.updateFrame();
	}

	return 0;
}