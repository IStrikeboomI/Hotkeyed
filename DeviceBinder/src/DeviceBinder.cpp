#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <device/DeviceManager.h>

#pragma comment (lib,"Hotkeyed.lib")
#pragma comment (lib,"Gdiplus.lib")

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_SIZE: {
            //redraw window after resizing
            RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case WM_PAINT: {
            //initalize ps and hdc
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            //get dimensions of coordinates
            RECT client;
            GetClientRect(hwnd, &client);
            int width = client.right - client.left;
            int height = client.bottom - client.top;

            //create a separate hdc for double buffering to prevent flicker
            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP hBM = CreateCompatibleBitmap(hdc, width, height);
            SelectObject(memDC, hBM);

            //Fill
            RECT r;
            SetRect(&r, 0, 0, width, height);
            FillRect(memDC, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

            //make graphics
            Gdiplus::Graphics graphics(memDC);
            //adds anti-aliasing to make the line look smoother
            graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

            //Draw
            Gdiplus::Pen blackPen(Gdiplus::Color::Black,5);
            graphics.DrawRectangle(&blackPen,100,100,width - 200,height - 200);


            //paint on window
            BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

            //free up to prevent resource leak
            DeleteObject(hBM);
            DeleteDC(memDC);
            //stop painting
            EndPaint(hwnd, &ps);
            break;
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}
int main() {
	DeviceManager::populate();
	DeviceManager::createOrApplyMapping("mapping.mapping");
	std::cout << DeviceManager::devices.size() << "\n";

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    WNDCLASS wc = { 0 };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(wc.hInstance, IDC_ARROW);
    wc.lpszClassName = L"deviceBinder";
    wc.lpfnWndProc = windowProcedure;
    wc.lpszMenuName = L"Device Binder";
    //Adds icon in corner (117 is icon)
    wc.hIcon = (HICON)LoadImage(wc.hInstance, MAKEINTRESOURCEW(117), IMAGE_ICON, 10, 0, LR_DEFAULTSIZE | LR_SHARED);

    if (!RegisterClass(&wc)) {
        return -1;
    }

    //Gets screen to center window
    RECT screen;
    GetWindowRect(GetDesktopWindow(), &screen);

    //Creates Window
    constexpr int BASE_WIDTH = 1440;
    constexpr int BASE_HEIGHT = 810;
    CreateWindow(wc.lpszClassName, wc.lpszMenuName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, screen.right / 2 - BASE_WIDTH / 2, screen.bottom / 2 - BASE_HEIGHT / 2, BASE_WIDTH, BASE_HEIGHT, nullptr, nullptr, wc.hInstance, nullptr);

    MSG msg = { nullptr };

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}