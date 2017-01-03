#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <Windows.h>
#include <d2d1.h>

class Graphics
{
private:
	// COM Interfaces
	ID2D1Factory * factory;
	ID2D1HwndRenderTarget * renderTarget;
	ID2D1SolidColorBrush * brush;
public:
	// Constructors
	Graphics();
	~Graphics();

	// This function runs once in main to initialize the interfaces with the necessary values
	bool Init(HWND windowHandle);

	// Our drawing functions?
	void BeginDraw()
	{
		renderTarget->BeginDraw();
	}
	void EndDraw()
	{
		renderTarget->EndDraw();
	}

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
};

#endif // !GRAPHICS_H