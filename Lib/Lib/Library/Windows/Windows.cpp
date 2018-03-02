#include"Windows.h"

/* ������ */

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wp)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

Window::Window() :m_hWnd(nullptr)
{

}

Window::~Window()
{
	Finalize();
}

bool Window::Initialize(LPCTSTR pWindowName, float windowWidth, float windowHeight)
{
	//Window�N���X�̐ݒ�
	WNDCLASSEX Wndclass;
	Wndclass.cbSize = sizeof(Wndclass);
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WinProc;
	//�\�񂷂�g���������̃T�C�Y yuki
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = GetModuleHandle(nullptr);
	Wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszMenuName = nullptr;
	//Window�̖��O �����ł�����Ă���
	Wndclass.lpszClassName = pWindowName;
	Wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	/* Window�̏c�Ɖ��̑傫����ϐ��Ɋi�[���Ă��� */
	m_WndPos.Posx = windowWidth;
	m_WndPos.Posy = windowHeight;

	if (!RegisterClassEx(&Wndclass))
	{
		return false;
	}

	m_hWnd = CreateWindow(
		pWindowName,
		pWindowName,
		//WS_POPUP | WS_VISIBLE,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0,
		0,
		windowWidth,
		windowHeight,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr);

	if (m_hWnd == nullptr)
	{
		DebugBreak();
		/*�G���[���O�t�@�C���̏o�����炢���ȁ[*/
		return false;
	}

	UpdateWindow(m_hWnd);

	ZeroMemory(&m_WindowMsg, sizeof(m_WindowMsg));
	
	return true;
}

bool Window::Update()
{
	if (m_WindowMsg.message != WM_QUIT)
	{
		if (PeekMessage(&m_WindowMsg, nullptr, 0, 0, PM_REMOVE))	//PeekMessage�Ń��b�Z�[�W�����Ă��Ȃ����m�F���ė��Ă��������
		{
			TranslateMessage(&m_WindowMsg);		//���b�Z�[�W��Proc���ǂ߂�悤�ɖ|�󂷂�
			DispatchMessage(&m_WindowMsg);		//���b�Z�[�W��Proc�ɑ��M���Ă���
		}
		return false;
	}

	m_hWnd = nullptr;

	return true;
}

void Window::Finalize()
{
	if (m_hWnd != nullptr)
	{
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
	}
}