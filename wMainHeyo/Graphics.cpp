#include "Graphics.h"


// Constructor
// Makes sure there is nothing in them initially
Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}


// Destructor
// Makes sure they are released if they were used.
Graphics::~Graphics()
{
	if (factory)
	{
		factory->Release();
	}
	if (renderTarget)
	{
		renderTarget->Release();
	}
	if (brush)
	{
		brush->Release();
	}
}


bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	// makes sure it all went well
	if (res != S_OK)
	{
		return false;
	}

	// Checks for the size of the client window size
	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget
	(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget
	);

	// if something busted up, return false
	if (res != S_OK)
	{
		return false;
	}

	// for the brush
	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	// check again if it went well
	if (res != S_OK)
	{
		return false;
	}

	// if it all somehow went well, return true
	return true;
}


// To clear the screen?
void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}


// to draw a circle
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	// had to convert our r g b a into a SolidColorBrush value
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	// this draws the ellipse :D
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}