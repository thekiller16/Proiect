#define _CRT_SECURE_NO_WARNINGS
#define agenda 320
#define adaugare 321
#define resetare 322
#define search 323
#define search1 324
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

HINSTANCE _hInstance;
int _nCmdShow;
HWND _hwnd;
MSG msg;
HWND numar, nume, cautare_pers, cautare_nr, output1, output2;

HDC hDC;
PAINTSTRUCT Ps;
HFONT font;
LOGFONT LogFont;

FILE *in = fopen("lista.txt", "r");;
FILE *out = fopen("out.txt", "w");

typedef struct nod {
	char key[20];
	char priority[50];
	nod *stg, *dr;
};
nod *rad;
nod *construire(FILE *in)
{
	char nume[50];
	nod *p;
	int n;
	char numar[20];
	n = sizeof(nod);
	fgets(nume, 50, in);
	nume[strlen(nume) - 1] = NULL;
	if (strcmp(nume, "0") == 0)
		return 0;
	else
	{
		p = (nod*)malloc(n);
		fgets(numar, 20, in);
		numar[strlen(numar) - 1] = NULL;
		strcpy(p->priority, nume);
		strcpy(p->key, numar);
		p->stg = construire(in);
		p->dr = construire(in);
	}
	return p;
}
void preordine(nod *p, FILE *out)
{
	if (p != 0)
	{
		fprintf(out, "%s - %s\n", p->priority, p->key);
		preordine(p->stg, out);
		preordine(p->dr, out);
	}
}

nod *inserare(nod *rad, char priority[50], char key[20])
{
	nod *p;
	int n;
	if (rad == 0) {
		n = sizeof(nod);
		p = (nod *)malloc(n);
		strcpy(p->key, key);
		strcpy(p->priority, priority);
		p->stg = 0;
		p->dr = 0;
		return p;
	}
	else {
		if (strcmp(priority, rad->priority)<0)
			rad->stg = inserare(rad->stg, priority, key);
		else {
			if (strcmp(priority, rad->priority) > 0)
				rad->dr = inserare(rad->dr, priority, key);
		}
	}
	return rad;
}
char s[200];
char* cautare_nume(nod *rad, char key[20])
{
	if (rad != 0)
	{
		if (strcmp(key, rad->key) == 0)
		{
			strcpy(s, rad->priority);

		}
		cautare_nume(rad->stg, key);
		cautare_nume(rad->dr, key);
	}
	return s;
}
char s1[200];
char* cautare_numar(nod *rad, char priority[50])
{
	if (rad != 0)
	{
		if (strcmp(priority, rad->priority) == 0)
		{
			strcpy(s1, rad->key);
		}
		cautare_numar(rad->stg, priority);
		cautare_numar(rad->dr, priority);
	}
	return s1;
}
void write() {
	hDC = BeginPaint(_hwnd, &Ps);
	HPEN hPenOld;
	HPEN hLinePen;
	COLORREF qLineColor;

	LogFont.lfStrikeOut = 0;
	LogFont.lfUnderline = 0;
	LogFont.lfWeight = FW_BOLD;
	LogFont.lfHeight = 20;
	LogFont.lfEscapement = 0;
	LogFont.lfItalic = FALSE;

	qLineColor = RGB(0, 0, 255);
	font = CreateFontIndirect(&LogFont);
	SelectObject(hDC, font);
	SetTextColor(hDC, qLineColor);
	TextOut(hDC, 10, 160, "Pentru adaugare", 15);
	TextOut(hDC, 10, 200, "numar:", 6);
	TextOut(hDC, 10, 300, "nume:", 5);
	TextOut(hDC, 10, 400, "Introduceti numar:", 18);
	TextOut(hDC, 10, 540, "Introduceti nume:", 18);
	DeleteObject(font);
}

void buttons(HWND hwnd)
{
	CreateWindow("BUTTON", "Afiseaza agenda", WS_BORDER | WS_CHILD | WS_VISIBLE, 140, 80, 120, 40, hwnd, (HMENU)agenda, _hInstance, NULL);
	CreateWindow("BUTTON", "Adauga", WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 350, 120, 40, hwnd, (HMENU)adaugare, _hInstance, NULL);
	CreateWindow("BUTTON", "Resetare", WS_BORDER | WS_CHILD | WS_VISIBLE, 200, 350, 120, 40, hwnd, (HMENU)resetare, _hInstance, NULL);
	CreateWindow("BUTTON", "Cauta", WS_BORDER | WS_CHILD | WS_VISIBLE, 200, 440, 120, 40, hwnd, (HMENU)search, _hInstance, NULL);
	numar = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 140, 200, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	nume = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 140, 300, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	cautare_nr = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 50, 440, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	cautare_pers = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 50, 580, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	CreateWindow("BUTTON", "Cauta", WS_BORDER | WS_CHILD | WS_VISIBLE, 200, 580, 120, 40, hwnd, (HMENU)search1, _hInstance, NULL);
}

LRESULT CALLBACK WndProc_Agenda(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
	{
		preordine(rad, out);
		fclose(out);
		FILE *f = fopen("out.txt", "r");
		char l[1024];
		int k = 0;
		while (fgets(l, 1024, f))
		{
			CreateWindow("static", l, WS_CHILD | WS_VISIBLE, 0, k * 20, 300, 30, hwnd, (HMENU)1, NULL, NULL);
			k++;
		}
		fclose(f);
		out = fopen("out.txt", "w");
	}
	break;

	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

	case WM_PAINT:
		write();
		break;

	case WM_CREATE:
		buttons(hwnd);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case agenda:
		{
			WNDCLASSW wc;

			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.lpszClassName = L"Agenda";
			wc.hInstance = _hInstance;
			wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
			wc.lpszMenuName = NULL;
			wc.lpfnWndProc = WndProc_Agenda;
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

			RegisterClassW(&wc);

			HWND _agenda = CreateWindowW(L"Agenda", L"Agenda",
				WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
				0, 0, 350, 600, hwnd, NULL, _hInstance, NULL);

			ShowWindow(_agenda, _nCmdShow);
			UpdateWindow(_agenda);
		}
		break;

		case adaugare:
		{
			char v1[20];
			SendMessage(nume, WM_GETTEXT, sizeof(v1) / sizeof(char), reinterpret_cast<LPARAM>(v1));
			char v2[20];
			SendMessage(numar, WM_GETTEXT, sizeof(v2) / sizeof(char), reinterpret_cast<LPARAM>(v2));
			rad = inserare(rad, v1, v2);
		}
		break;

		case search:
		{
			char v3[50];
			SendMessage(cautare_nr, WM_GETTEXT, sizeof(v3) / sizeof(char), reinterpret_cast<LPARAM>(v3));
			char* v4 = (char*)malloc(strlen(cautare_nume(rad, v3))*sizeof(char));
			strcpy(v4, s);
			output1 = CreateWindow("static", v4, WS_CHILD | WS_VISIBLE, 50, 500, 120, 40, hwnd, (HMENU)1, NULL, NULL);
		}
		break;

		case search1:
		{
			char v5[50];
			SendMessage(cautare_pers, WM_GETTEXT, sizeof(v5) / sizeof(char), reinterpret_cast<LPARAM>(v5));
			char* v6 = (char*)malloc(strlen(cautare_numar(rad, v5))*sizeof(char));
			strcpy(v6, s1);
			output2 = CreateWindow("static", v6, WS_CHILD | WS_VISIBLE, 50, 650, 120, 40, hwnd, (HMENU)1, NULL, NULL);
		}
		break;

		case resetare:
		{
			DestroyWindow(nume);
			DestroyWindow(numar);
			DestroyWindow(cautare_nr);
			DestroyWindow(cautare_pers);
			DestroyWindow(output1);
			DestroyWindow(output2);
			numar = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 140, 200, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			nume = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 140, 300, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			cautare_nr = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 50, 440, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			cautare_pers = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 50, 580, 120, 40, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
		}
		break;



		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_hInstance = hInstance;
	_nCmdShow = nCmdShow;

	rad = construire(in);

	WNDCLASSW wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"MainWindow";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);

	_hwnd = CreateWindowW(L"MainWindow", L"Agenda Telefonica",
		WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
		0, 0, 400, 750, NULL, NULL, hInstance, NULL);

	ShowWindow(_hwnd, nCmdShow);
	UpdateWindow(_hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
