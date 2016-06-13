#include <windows.h>
const char g_szClassName[] = "myWindowClass";
HWND textfield, button, textbox;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	case WM_CREATE:
		textfield = CreateWindow("STATIC", "Carte de telefon", WS_VISIBLE | WS_CHILD, 80, 30, 225, 25, hwnd, NULL, NULL, NULL);
		button = CreateWindow("BUTTON", "Modificati contacte", WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 70, 140, 20, hwnd, NULL, NULL, NULL);
		textbox = CreateWindow("EDIT", "Introduceti nodurile", WS_BORDER | WS_CHILD | WS_VISIBLE, 25, 100, 140, 20, hwnd, NULL, NULL, NULL);
		button = CreateWindow("BUTTON", "Ruleaza", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 80, 80, 25, hwnd, (HMENU)1, NULL, NULL);
		break;
	case WM_COMMAND:

	{
		switch (LOWORD(wParam))
		{
		case 1:
		{
			MessageBox(NULL, "Eroare", "Loading..", MB_OK | MB_ICONINFORMATION);
			break;
		}
		}
	}
	return 0;
	}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Proiect TP",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 360, 190,
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
