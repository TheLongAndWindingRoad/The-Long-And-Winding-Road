#ifndef WINDOWS_H
#define	WINDOWS_H

#include<Windows.h>


class Window
{
public:
	Window();
	~Window();
	bool Initialize(LPCTSTR pWindowName, float windowWidth, float windowHeight);
	void Finalize();
	bool Update();
	inline HWND GetWndHandle() const { return m_hWnd; }
	inline float GetPosX() const { return m_WndPos.Posx; }
	inline float GetPosY() const { return m_WndPos.Posy; }
private:
	struct WindowPos
	{
		float Posx;
		float Posy;
	};

	HWND m_hWnd;
	MSG m_WindowMsg;
	WindowPos m_WndPos;
};

#endif