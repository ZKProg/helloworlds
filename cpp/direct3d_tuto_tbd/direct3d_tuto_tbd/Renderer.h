#pragma once

#include <Windows.h>
#include "MainActivity.h"
#include <d3d11.h>

class Renderer
{
public:
	Renderer(MainActivity &win);
	virtual ~Renderer();

	void createDevice(MainActivity &win);
	void createRenderTarget();

	void paintFrame();
	void updateFrame();

protected:
	IDXGISwapChain *_pSwapChain;
	ID3D11Device *_pDevice;
	ID3D11DeviceContext *_pDeviceContext;

	// Render target
	ID3D11RenderTargetView *_pRenderTargetView = nullptr;
};

