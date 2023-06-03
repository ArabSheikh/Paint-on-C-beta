#include <Windows.h>
#include <vector>

struct Point
{
	int x;
	int y;
};
#define IDM_COLOR_RED 1
#define IDM_COLOR_ORANGE 2
#define IDM_COLOR_YELLOW 3
#define IDM_COLOR_GREEN 4
#define IDM_COLOR_AZURE 5
#define IDM_COLOR_BLUE 6
#define IDM_COLOR_PURPLE 7
#define IDM_COLOR_BLACK 8
#define IDM_COLOR_BROWN 9
#define IDM_COLOR_PINK 10
#define IDM_TYPE_POINT_SYSTEM 11
#define IDM_TYPE_FREE 12
#define IDM_FILE_EXIT 13

COLORREF g_Color = RGB(0, 0, 0);
int g_Size = 5;
std::vector<Point> g_Points;
bool Point_sys = false;

void CreateFileMenu(HWND hWnd)
{
	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreatePopupMenu();

	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_RED, L"&Red");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_ORANGE, L"&Orange");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_YELLOW, L"&Yellow");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_GREEN, L"&Green");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_AZURE, L"&Azure");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_BLUE, L"&Blue");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_PURPLE, L"Purple");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_BLACK, L"&Black");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_BROWN, L"&Brown");
	AppendMenu(hFileMenu, MF_STRING, IDM_COLOR_PINK, L"&Pink");
	AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hFileMenu, MF_STRING, IDM_TYPE_POINT_SYSTEM, L"Point System");
	AppendMenu(hFileMenu, MF_STRING, IDM_TYPE_FREE, L"Free drawing");
	AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, L"&Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&Settings");

	SetMenu(hWnd, hMenu);
}
void DrawPoint(HWND hWnd, int x, int y)
{
	Point point = { x, y };
	g_Points.push_back(point);
	InvalidateRect(hWnd, NULL, TRUE);
}
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{

		switch (uMsg)
		{
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDM_FILE_EXIT:
					PostQuitMessage(0);
					break;
				case IDM_COLOR_RED:
					g_Color = RGB(255, 0, 0);
					break;
				case IDM_COLOR_ORANGE:
					g_Color = RGB(255, 120, 0);
					break;
				case IDM_COLOR_YELLOW:
					g_Color = RGB(255, 180, 0);
					break;
				case IDM_COLOR_GREEN:
					g_Color = RGB(0, 255, 0);
					break;
				case IDM_COLOR_AZURE:
					g_Color = RGB(90, 90, 255);
					break;
				case IDM_COLOR_BLUE:
					g_Color = RGB(0, 0, 255);
					break;
				case IDM_COLOR_PURPLE:
					g_Color = RGB(120, 0, 255);
					break;
				case IDM_COLOR_BLACK:
					g_Color = RGB(0, 0, 0);
					break;
				case IDM_COLOR_BROWN:
					g_Color = RGB(150, 110, 50);
					break;
				case IDM_COLOR_PINK:
					g_Color = RGB(255, 90, 90);
					break;
				case IDM_TYPE_POINT_SYSTEM:
				{
					Point_sys = true;
					break;
				}
				case IDM_TYPE_FREE:
				{
					Point_sys = false;
					break;
				}

			}
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			HBRUSH hBrush = CreateSolidBrush(g_Color), gray_90 = CreateSolidBrush(RGB(90, 90, 90)), 
				gray_120 = CreateSolidBrush(RGB(120, 120, 120)), black = CreateSolidBrush(RGB(0, 0, 0)),
				white = CreateSolidBrush(RGB(255, 255, 255));

            SelectObject(hdc, gray_90);
			Rectangle(hdc, 0, 0, 70, 2000);
			SelectObject(hdc, gray_120);
			Rectangle(hdc, 0, 0, 5000, 70);
			if (Point_sys == true) 
			{
				SelectObject(hdc, black);
				for (int x = 70; x > 5000; x = x + 30)
				{
					Rectangle(hdc, x, 70, x + 2, 2000);
				}
				for (int y = 70; y > 2000; y = y + 30)
				{
					Rectangle(hdc, 70, y, y + 2, 5000);
				}
			}
			if (Point_sys == false)
			{
				SelectObject(hdc, white);
				Rectangle(hdc, 70, 70, 5000, 2000);
			}
			for (auto& point : g_Points)
			{
				if (point.x - g_Size > 70 && point.y - g_Size > 70)
				{
					SelectObject(hdc, hBrush);
					Ellipse(hdc, point.x - g_Size, point.y - g_Size, point.x + g_Size, point.y + g_Size);
					DeleteObject(hBrush);
				}
			}
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			DrawPoint(hWnd, x, y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			int minDistance = INT_MAX;
			int minIndex = -1;
			for (int i = 0; i < g_Points.size(); i++)
			{
				int distance = (x - g_Points[i].x) * (x - g_Points[i].x) + (y - g_Points[i].y) * (y - g_Points[i].y);
				if (distance < minDistance)
				{
					minDistance = distance;
					minIndex = i;
				}
			}
			if (minIndex != -1)
			{
				g_Points.erase(g_Points.begin() + minIndex);
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
			break;
		}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = L"Class";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;
	if (hwnd = CreateWindowEx(0, wc.lpszClassName, L"Just draw", WS_OVERLAPPEDWINDOW, 150, 150, 1500, 700, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	CreateFileMenu(hwnd);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}