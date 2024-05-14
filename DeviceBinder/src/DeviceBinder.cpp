#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <device/DeviceManager.h>
#include <CommCtrl.h>
#include <string>
#include <random>

#pragma comment (lib,"Hotkeyed.lib")
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"Comctl32.lib")

#define DEVICES 200
#define KEYBOARD_LOG 201
#define MOUSE_LOG 202

HFONT systemFont;

HWND devicePane;
HWND keyboardLogPane;
HWND mouseLogPane;

HWND keyboardLogText;

bool CALLBACK setFont(HWND hwnd) {
    SendMessage(hwnd, WM_SETFONT, (WPARAM)systemFont, true);
    return true;
}
LRESULT CALLBACK childWindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_COMMAND: {
            break;
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}
LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_GETMINMAXINFO: {
            RECT screen;
            GetWindowRect(GetDesktopWindow(), &screen);
            MINMAXINFO* mmi = (MINMAXINFO*)lparam;
            mmi->ptMinTrackSize.x = screen.right >> 2;
            mmi->ptMinTrackSize.y = screen.bottom >> 2;
            break;
        }
        case WM_NOTIFY: {
            NMHDR* notification = (LPNMHDR)lparam;
            if (notification->code == TCN_SELCHANGING) return false;
            if (notification->code == TCN_SELCHANGE) {
                int tab =  TabCtrl_GetCurSel(notification->hwndFrom);
                std::cout << tab << "\n";
                if (tab == 0) {
                    ShowWindow(devicePane, SW_SHOW);
                    ShowWindow(keyboardLogPane, SW_HIDE);
                    ShowWindow(mouseLogPane, SW_HIDE);
                }
                if (tab == 1) {
                    ShowWindow(devicePane, SW_HIDE);
                    ShowWindow(keyboardLogPane, SW_SHOW);
                    ShowWindow(mouseLogPane, SW_HIDE);
                }
                if (tab == 2) {
                    ShowWindow(devicePane, SW_HIDE);
                    ShowWindow(keyboardLogPane, SW_HIDE);
                    ShowWindow(mouseLogPane, SW_SHOW);
                }
            }
            break;
        }
        case WM_CREATE: {
            RECT window;
            GetClientRect(hwnd,&window);

            INITCOMMONCONTROLSEX icex;
            icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
            icex.dwICC = ICC_TAB_CLASSES;
            InitCommonControlsEx(&icex);

            HWND tabControl = CreateWindow(WC_TABCONTROL, L"",WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,0, 0, window.right, 25,hwnd, NULL, nullptr, NULL);
            
            TCITEM devicesTab;
            devicesTab.mask = TCIF_TEXT;
            devicesTab.pszText = (LPWSTR)L"Devices";

            TCITEM keyboardLogTab;
            keyboardLogTab.mask = TCIF_TEXT;
            keyboardLogTab.pszText = (LPWSTR)L"Keyboard Log";

            TCITEM mouseLogTab;
            mouseLogTab.mask = TCIF_TEXT;
            mouseLogTab.pszText = (LPWSTR)L"Mouse Log";

            TabCtrl_InsertItem(tabControl, 0, &devicesTab);
            TabCtrl_InsertItem(tabControl, 1, &keyboardLogTab);
            TabCtrl_InsertItem(tabControl, 2, &mouseLogTab);

            RECT tabControlSize;
            GetWindowRect(tabControl, &tabControlSize);
            int tabHeight = tabControlSize.bottom - tabControlSize.top;
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, -6);

            devicePane = CreateWindow(L"Pane", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER, 0, tabHeight, window.right, window.bottom, hwnd, (HMENU)DEVICES, hInstance, 0);
            CreateWindowW(WC_STATIC, L"DE", WS_VISIBLE | WS_CHILD, 80, 200, 100, 30, devicePane, (HMENU)DEVICES, hInstance, nullptr);
            CreateWindowW(WC_BUTTON, L"Start", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 40, 400, 100, 30, devicePane, (HMENU)DEVICES, hInstance, nullptr);
            std::cout << GetLastError() << "\n";
            ShowWindow(devicePane, SW_SHOW);
            UpdateWindow(devicePane);

            keyboardLogPane = CreateWindow(L"Pane", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER, 0, tabHeight, window.right, window.bottom, hwnd, (HMENU)KEYBOARD_LOG, nullptr, 0);
            keyboardLogText = CreateWindowW(WC_EDIT, nullptr, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_BORDER | WS_HSCROLL, 100, 20, window.right - 300, window.bottom, keyboardLogPane, (HMENU)KEYBOARD_LOG, nullptr, nullptr);
            std::wstring text = L"";
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(48, 122);
            for (int i = 0; i < 100;i++) {
                for (int j = 0; j < 900; j++) {
                    text += (char)dist(rng);
                }
                text += L" \\n \r\n";
            }
            SendMessage(keyboardLogText, WM_SETTEXT, 0, (LPARAM)text.c_str());
            ShowWindow(keyboardLogPane, SW_HIDE);
            //UpdateWindow(keyboardLogPane);


            mouseLogPane = CreateWindow(L"Pane", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, tabHeight, window.right, window.bottom, hwnd, (HMENU)MOUSE_LOG, nullptr, 0);
            CreateWindowW(WC_STATIC, L"MO", WS_VISIBLE | WS_CHILD , 80, 200, 100, 30, mouseLogPane, (HMENU)MOUSE_LOG, nullptr, nullptr);
            ShowWindow(mouseLogPane, SW_HIDE);
            //UpdateWindow(mouseLogPane);
            //HWND devicesTab = CreateWindowA(WC_TABCONTROLA,"Devices", WS_VISIBLE,0,0,100,100,hwnd,(HMENU) 0,nullptr, nullptr);
            //change all gui objects to use default system font
            EnumChildWindows(hwnd, (WNDENUMPROC)setFont, NULL);
            break;
        }
        case WM_SIZE: {
            //redraw window after resizing
            int width = LOWORD(lparam);
            int height = HIWORD(lparam);
            std::cout << width << "x" << height << "\n";
            RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
            SetWindowPos(keyboardLogPane,nullptr,0,0, width, height, SWP_NOMOVE);
            SetWindowPos(keyboardLogText, nullptr, 0, 0, width * .9, height * .9, SWP_NOMOVE);
            break;
        }
        case WM_PAINT: {
            //initalize ps and hdc
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(devicePane, &ps);

            //get dimensions of coordinates
            RECT client;
            GetWindowRect(devicePane, &client);
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
            EndPaint(devicePane, &ps);
            break;
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}
int main() {
	DeviceManager::populate();
	DeviceManager::createOrApplyMapping("mapping.mapping");
	//std::cout << DeviceManager::devices.size() << "\n";

    NONCLIENTMETRICS metrics = {};
    metrics.cbSize = sizeof(metrics);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);
    systemFont = CreateFontIndirect(&metrics.lfCaptionFont);

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

    WNDCLASS pane = { 0 };
    pane.hbrBackground = (HBRUSH)COLOR_WINDOW;
    pane.hInstance = wc.hInstance;
    pane.hCursor = LoadCursor(wc.hInstance, IDC_ARROW);
    pane.lpszClassName = L"Pane";
    pane.lpfnWndProc = childWindowProcedure;
    if (!RegisterClass(&pane)) {
        return -1;
    }

    //Gets screen to center window
    RECT screen;
    GetWindowRect(GetDesktopWindow(), &screen);

    //Creates Window
    constexpr int BASE_WIDTH = 1440;
    constexpr int BASE_HEIGHT = 810;
    CreateWindow(wc.lpszClassName, wc.lpszMenuName, WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN, screen.right / 2 - BASE_WIDTH / 2, screen.bottom / 2 - BASE_HEIGHT / 2, BASE_WIDTH, BASE_HEIGHT, nullptr, nullptr, wc.hInstance, nullptr);

    MSG msg = { nullptr };

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}