#include <Windows.h>
#include "Graphics.h"

// Graphics pointer
Graphics * graphics;

LRESULT CALLBACK WindowProc
(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);


int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	/* Register class */

	// Make class
	WNDCLASSEX wc;

	// Empty it!
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Fill it with some crap!
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = "Class 1";
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// Register the class
	RegisterClassEx(&wc);

	/* Create Window */

	// The rect for the client
	RECT rect = { 0, 0, 800, 600 };
	
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, NULL, WS_EX_OVERLAPPEDWINDOW);

	// Make Window and fill it
	HWND hWnd = CreateWindowEx
	(
		WS_EX_OVERLAPPEDWINDOW,
		"Class 1",
		"Heyo",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// If the window doesn't get created, it returns an error
	if (!hWnd)
		return -1;

	/* Create Graphics */
	graphics = new Graphics();
	if (graphics->Init(hWnd) == false)
	{
		delete graphics;
		return -1;
	}

	/* Show Window */
	ShowWindow(hWnd, nCmdShow);

	/* Message Loop */

	// Create message struct
	MSG message;

	// Loop
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);

		DispatchMessage(&message);
	}

	return 0;
}

LRESULT CALLBACK WindowProc
(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
		break;
	}
	case WM_PAINT:
	{
		graphics->BeginDraw();

		graphics->ClearScreen(0.0f, 0.0f, 0.5f);

		for (int i = 0; i < 1000; i++)
		{
			graphics->DrawCircle(rand() % 800, rand() % 600, rand() % 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
		}

		graphics->EndDraw();
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}