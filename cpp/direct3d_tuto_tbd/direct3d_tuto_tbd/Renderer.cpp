#include "Renderer.h"
#include <d3d11.h>


Renderer::Renderer(MainActivity &win) :
	_pSwapChain(nullptr), _pDevice(nullptr), _pDeviceContext(nullptr)
{
	this->createDevice(win);
	this->createRenderTarget();
}


Renderer::~Renderer()
{
}

void Renderer::createDevice(MainActivity &win) {

	// Define our swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = win.getTheHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	// Create the swapchain device context
	auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &_pSwapChain, &_pDevice, nullptr, &_pDeviceContext);

	// Check the result
	if (result != S_OK) {
		MessageBox(nullptr, "Problem creating context", "Error", MB_OK);
		exit(0);
	}

}

void Renderer::createRenderTarget() {

	ID3D11Texture2D *backBuffer;
	this->_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	this->_pDevice->CreateRenderTargetView(backBuffer, nullptr, &this->_pRenderTargetView);
	backBuffer->Release();

}

void Renderer::paintFrame() {

	float clearColor[] = {1, 0.5, 0.5, 1.0};
	this->_pDeviceContext->ClearRenderTargetView(this->_pRenderTargetView, clearColor);

}

void Renderer::updateFrame() {
	this->_pSwapChain->Present(1, 0);
}