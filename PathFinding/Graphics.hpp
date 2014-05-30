#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Vector>
#include <string>
#include <memory>

namespace GejbEngine {
	class Sprite;

	struct Texture {
		bool imageLoaded;
		bool collidable;
		int textureIndex;
		int width, height;
		D3DCOLOR color;
	};

	bool InitGraphics(HWND hWnd, int width, int height, bool fullscreen,
										int colordepth = 32);
	void ShutdownGraphics();
	void ClearScreen(D3DCOLOR color = 0x0);

	bool Reset(void);

	void AdjustWindow();

	void DrawString(std::string text, int x, int y);

	bool LoadSprite(std::string filename, Texture &texture,
									D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));
	void ReleaseSprite(Texture &texture);

	bool BeginGraphics(void);
	void EndGraphics(void);

	//accessor/mutators
	int  getColorDepth(void);
	void setColorDepth(int value);
	void setProgramTitle(std::string title);
	void setTransparency(bool transparency);
	DWORD getClearColor(void);
	void setClearColor(DWORD value);

	void ReleaseTexture(Texture *texture);
	bool LoadTexture(std::string filename, Texture *texture,
									 D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));
	void DrawTexture(Texture *texture, int x, int y);
	void TransformTexture();
}

#endif