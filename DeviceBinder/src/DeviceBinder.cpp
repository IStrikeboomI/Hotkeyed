#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <device/DeviceManager.h>
#include <windows/Interceptor.h>
#include <CommCtrl.h>
#include <string>
#include <thread>
#include <algorithm>
#include <memory>
#include <bitset>

#pragma comment (lib,"Hotkeyed.lib")
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"Comctl32.lib")


#define IDM_SAVE_MAPPING 100
#define IDM_FILE_EXPORT_KEYBOARD_LOG 101
#define IDM_FILE_EXPORT_MOUSE_LOG 102
#define IDM_FILE_EXPORT_MAPPING 103
#define IDM_APPLY_MAPPING 104
#define MOUSE_POSITION 195
#define CLEAR_MOUSE_LOG 196
#define MOUSE_LOG_START_PAUSE 197
#define CLEAR_KEYBOARD_LOG 198
#define KEYBOARD_LOG_START_PAUSE 199
#define DEVICES 200
#define KEYBOARD_LOG 201
#define MOUSE_LOG 202

HFONT systemFont;

HWND devicePane;
HWND keyboardLogPane;
HWND mouseLogPane;

HWND deviceListView;

HWND keyboardLogText;
HWND keyboardIncludeDeviceInterfaceNameCheckbox;
HWND keyboardIncludeProductNameCheckbox;
HWND keyboardIncludeManufacturerNameCheckbox;
HWND keyboardIncludeDeviceKeyCheckbox;
HWND keyboardIncludeIdCheckbox;
HWND keyboardKeyDownCheckbox;
HWND keyboardKeyUpCheckbox;
HWND keyboardLogStartPauseButton;

bool keyboardLogRunning = true;

unsigned int keyboardLogLineNumber = 0;

HWND mouseLogText;
HWND mouseIncludeDeviceInterfaceNameCheckbox;
HWND mouseIncludeProductNameCheckbox;
HWND mouseIncludeManufacturerNameCheckbox;
HWND mouseIncludeDeviceKeyCheckbox;
HWND mouseIncludeIdCheckbox;
HWND mouseKeyDownCheckbox;
HWND mouseKeyUpCheckbox;
HWND mousePositionCheckbox;
HWND mouseXPositionCheckbox;
HWND mouseYPositionCheckbox;
HWND mouseLogStartPauseButton;

bool mouseLogRunning = true;

unsigned int mouseLogLineNumber = 0;
bool CALLBACK setFont(HWND hwnd) {
    SendMessage(hwnd, WM_SETFONT, (WPARAM)systemFont, true);
    return true;
}
bool sortIntAscending = false;
int CALLBACK sortInt(LPARAM one, LPARAM two, LPARAM ascending) {
    std::cout << one << " " << two << "\n";
    if (ascending) {
        if (one < two) {
            return -1;
        }
        if (one > two) {
            return 1;
        }
    } else {
        if (one < two) {
            return 1;
        }
        if (one > two) {
            return -1;
        }
    }
    if (one == two) {
        return 0;
    }
}
LRESULT CALLBACK childWindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_COMMAND: {
            switch (wparam) {
                case KEYBOARD_LOG_START_PAUSE: {
                    keyboardLogRunning = !keyboardLogRunning;
                    if (keyboardLogRunning) {
                        SendMessage(keyboardLogStartPauseButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCEW(119), IMAGE_ICON, 100, 100, LR_DEFAULTSIZE | LR_SHARED));
                    } else {
                        SendMessage(keyboardLogStartPauseButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCEW(118), IMAGE_ICON, 90, 90, LR_DEFAULTSIZE | LR_SHARED));
                    }
                    break;
                }
                case CLEAR_KEYBOARD_LOG: {
                    keyboardLogLineNumber = 0;
                    SendMessage(keyboardLogText, WM_SETTEXT, 0, (LPARAM)L"");
                    break;
                }
                case MOUSE_LOG_START_PAUSE: {
                    mouseLogRunning = !mouseLogRunning;
                    if (mouseLogRunning) {
                        SendMessage(mouseLogStartPauseButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCEW(119), IMAGE_ICON, 100, 100, LR_DEFAULTSIZE | LR_SHARED));
                    } else {
                        SendMessage(mouseLogStartPauseButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCEW(118), IMAGE_ICON, 90, 90, LR_DEFAULTSIZE | LR_SHARED));
                    }
                    break;
                }
                case CLEAR_MOUSE_LOG: {
                    mouseLogLineNumber = 0;
                    SendMessage(mouseLogText, WM_SETTEXT, 0, (LPARAM)L"");
                    break;
                }
                case MOUSE_POSITION: {
                    if (SendMessage(mousePositionCheckbox, BM_GETCHECK, 0, 0)) {
                        EnableWindow(mouseXPositionCheckbox, true);
                        EnableWindow(mouseYPositionCheckbox, true);
                    } else {
                        EnableWindow(mouseXPositionCheckbox, false);
                        EnableWindow(mouseYPositionCheckbox, false);
                    }
                    break;
                }
                default:break;
            }
            break;
        }
        case WM_NOTIFY:{
            switch (((LPNMHDR)lparam)->code) {
                case LVN_ENDLABELEDIT: {
                    NMLVDISPINFOW* info = (LPNMLVDISPINFOW)lparam;
                    if (info->item.pszText) {
                        std::wstring text(info->item.pszText);
                        if (text.size() <= 10) {
                            if (DeviceManager::isNumber(std::string(text.begin(),text.end()))) {
                                info->item.mask |= LVIF_PARAM;
                                info->item.lParam = (LPARAM)std::stoi(info->item.pszText);
                                ListView_SetItem(deviceListView,&info->item);
                                return true;
                            }
                        }
                    }
                    return false;
                    break;
                }
                case LVN_COLUMNCLICK: {
                    NMLISTVIEW* view = (NMLISTVIEW*)lparam;
                    //Id Column;
                    if (view->iSubItem == 0) {
                        ListView_SortItems(deviceListView, sortInt, sortIntAscending);
                        sortIntAscending = !sortIntAscending;
                    }
                    break;
                }
                //Makes it easier to edit label by just clicking on it
                case NM_DBLCLK: {
                    NMITEMACTIVATE* info = (LPNMITEMACTIVATE)lparam;
                    //Id Column
                    if (info->iSubItem == 0) {
                        ListView_EditLabel(info->hdr.hwndFrom,info->iItem);
                    }
                    break;
                }
            }
            break;
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}
LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        case WM_GETMINMAXINFO: {
            RECT screen;
            GetWindowRect(GetDesktopWindow(), &screen);
            MINMAXINFO* mmi = (MINMAXINFO*)lparam;
            mmi->ptMinTrackSize.x = screen.right >> 2;
            mmi->ptMinTrackSize.y = screen.bottom >> 2;
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wparam)) {
                case IDM_SAVE_MAPPING: {

                    break;
                }
                case IDM_APPLY_MAPPING:
                {

                    break;
                }
                case IDM_FILE_EXPORT_MAPPING: {
                    OPENFILENAME ofn;

                    wchar_t szFileName[MAX_PATH] = L"mapping";

                    ZeroMemory(&ofn, sizeof(ofn));

                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFilter = L"Device Mapping (*.mapping)\0*.mapping\0Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
                    ofn.lpstrFile = szFileName;
                    ofn.nMaxFile = MAX_PATH;
                    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
                    ofn.lpstrDefExt = L"mapping";

                    if (GetSaveFileName(&ofn)) {
                        std::wstring filename(ofn.lpstrFile);
                        DeviceManager::saveMapping(std::string(filename.begin(),filename.end()));
                    }
                    break;
                }
                case IDM_FILE_EXPORT_KEYBOARD_LOG: {
                    OPENFILENAME ofn;
                    
                    wchar_t szFileName[MAX_PATH] = L"Keyboard Log";

                    ZeroMemory(&ofn, sizeof(ofn));

                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
                    ofn.lpstrFile = szFileName;
                    ofn.nMaxFile = MAX_PATH;
                    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
                    ofn.lpstrDefExt = L"txt";

                    if (GetSaveFileName(&ofn)) {
                        std::wfstream file(ofn.lpstrFile, std::ios::out);
                        std::unique_ptr<wchar_t[]> keyboardLog(new wchar_t[1 << 24]);
                        SendMessage(keyboardLogText,WM_GETTEXT,(1 << 24) * sizeof(wchar_t), (LPARAM)keyboardLog.get());
                        if (file.is_open()) {
                            std::wstring wstr(keyboardLog.get());
                            std::replace(wstr.begin(),wstr.end(), '\r',' ');
                            file << wstr;
                        }
                        file.close();
                    }
                    break;
                }
                case IDM_FILE_EXPORT_MOUSE_LOG: {
                    OPENFILENAME ofn;

                    wchar_t szFileName[MAX_PATH] = L"Mouse Log";

                    ZeroMemory(&ofn, sizeof(ofn));

                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
                    ofn.lpstrFile = szFileName;
                    ofn.nMaxFile = MAX_PATH;
                    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
                    ofn.lpstrDefExt = L"txt";

                    if (GetSaveFileName(&ofn)) {
                        std::wfstream file(ofn.lpstrFile, std::ios::out);
                        std::unique_ptr<wchar_t[]> mouseLog(new wchar_t[1 << 24]);
                        SendMessage(mouseLogText, WM_GETTEXT, (1 << 24) * sizeof(wchar_t), (LPARAM)mouseLog.get());
                        if (file.is_open()) {
                            std::wstring wstr(mouseLog.get());
                            std::replace(wstr.begin(), wstr.end(), '\r', ' ');
                            file << wstr;
                        }
                        file.close();
                    }
                    break;
                }
                default:break;
            }
            break;
        }
        case WM_NOTIFY: {
            NMHDR* notification = (LPNMHDR)lparam;
            if (notification->code == TCN_SELCHANGING) return false;
            if (notification->code == TCN_SELCHANGE) {
                int tab =  TabCtrl_GetCurSel(notification->hwndFrom);
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

            HMENU menubar = CreateMenu();
            HMENU file = CreateMenu();

            AppendMenuW(file, MF_STRING, IDM_SAVE_MAPPING, L"Save Mapping");
            AppendMenuW(file, MF_STRING, IDM_APPLY_MAPPING, L"Apply Mapping (From File)");
            AppendMenuW(file, MF_STRING, IDM_FILE_EXPORT_MAPPING, L"Export Mapping");
            AppendMenuW(file, MF_SEPARATOR, 0, 0);
            AppendMenuW(file,MF_STRING,IDM_FILE_EXPORT_KEYBOARD_LOG,L"Export Keyboard Log");
            AppendMenuW(file, MF_STRING, IDM_FILE_EXPORT_MOUSE_LOG, L"Export Mouse Log");

            AppendMenuW(menubar,MF_POPUP,(UINT_PTR)file,L"File");
            SetMenu(hwnd,menubar);

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

            devicePane = CreateWindow(L"Pane", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, tabHeight, window.right, window.bottom, hwnd, (HMENU)DEVICES, hInstance, 0);
            int deviceCount = DeviceManager::devices.size();
            int keyboardCount = 0;
            int mouseCount = 0;
            for (std::shared_ptr<Device> d : DeviceManager::devices) {
                if (d->type == RIM_TYPEKEYBOARD) {
                    keyboardCount++;
                }
                if (d->type == RIM_TYPEMOUSE) {
                    mouseCount++;
                }
            }

            CreateWindowW(WC_STATIC, std::format(L"Device Count: {}   Keyboard Count: {}   Mouse Count: {}", deviceCount, keyboardCount, mouseCount).c_str(), WS_VISIBLE | WS_CHILD, 10, 0, 500, 20, devicePane, (HMENU)DEVICES, hInstance, nullptr);
            INITCOMMONCONTROLSEX listICEX;
            listICEX.dwICC = ICC_LISTVIEW_CLASSES;
            InitCommonControlsEx(&listICEX);

            deviceListView = CreateWindow(WC_LISTVIEW,
                                             L"Devices",
                                             WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_ALIGNTOP | WS_BORDER,
                                             10, 20,
                                             1000,
                                             500,
                                             devicePane,
                                             nullptr,
                                             nullptr,
                                                NULL);

            LVCOLUMN deviceIDColumn;
            deviceIDColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            deviceIDColumn.iSubItem = 0;
            deviceIDColumn.pszText = const_cast <LPWSTR>(L"Device ID");
            deviceIDColumn.cx = 100;
            deviceIDColumn.fmt = LVCFMT_CENTER;
            ListView_InsertColumn(deviceListView, 0, &deviceIDColumn);

            LVCOLUMN deviceNameColumn;
            deviceNameColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            deviceNameColumn.iSubItem = 1;
            deviceNameColumn.pszText = const_cast < LPWSTR>(L"Device Name");
            deviceNameColumn.cx = 200;              
            deviceNameColumn.fmt = LVCFMT_CENTER;
            ListView_InsertColumn(deviceListView, 1, &deviceNameColumn);

            LVCOLUMN manufacturerNameColumn;
            manufacturerNameColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            manufacturerNameColumn.iSubItem = 2;
            manufacturerNameColumn.pszText = const_cast<LPWSTR>(L"Manufacturer Name");
            manufacturerNameColumn.cx = 200;
            manufacturerNameColumn.fmt = LVCFMT_CENTER;
            ListView_InsertColumn(deviceListView, 3, &manufacturerNameColumn);

            LVCOLUMN deviceInterfaceNameColumn;
            deviceInterfaceNameColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            deviceInterfaceNameColumn.iSubItem = 3;
            deviceInterfaceNameColumn.pszText = const_cast <LPWSTR>(L"Device Interface Name");
            deviceInterfaceNameColumn.cx = 700;
            deviceInterfaceNameColumn.fmt = LVCFMT_CENTER;
            ListView_InsertColumn(deviceListView, 4, &deviceInterfaceNameColumn);    

            LVGROUP miceGroup;
            miceGroup.cbSize = sizeof(LVGROUP);
            miceGroup.mask = LVGF_HEADER | LVGF_GROUPID | LVGF_STATE;
            miceGroup.state = LVGS_COLLAPSIBLE;
            miceGroup.pszHeader = const_cast <LPWSTR>(L"Mice");
            miceGroup.iGroupId = 0;
            ListView_InsertGroup(deviceListView, -1, &miceGroup);

            LVGROUP keyboardGroup;
            keyboardGroup.cbSize = sizeof(LVGROUP);
            keyboardGroup.mask = LVGF_HEADER | LVGF_GROUPID | LVGF_STATE;
            keyboardGroup.state = LVGS_COLLAPSIBLE;
            keyboardGroup.pszHeader = const_cast <LPWSTR>(L"Keyboards");
            keyboardGroup.iGroupId = 1;
            ListView_InsertGroup(deviceListView, -1, &keyboardGroup);

            int i = 0;
            for (std::shared_ptr<Device> d : DeviceManager::devices) {
                LVITEM lvI;
                lvI.pszText = LPSTR_TEXTCALLBACK;
                lvI.cchTextMax = 10;
                lvI.mask = LVIF_TEXT | LVIF_STATE | LVIF_PARAM | LVIF_GROUPID;
                lvI.stateMask = 0;
                lvI.iSubItem = 0;
                lvI.state = 0;
                lvI.iItem = i;
                lvI.lParam = (LPARAM)d->id;
                lvI.iGroupId = d->type;
                ListView_InsertItem(deviceListView, &lvI);
                std::wstring deviceIdTemp = std::to_wstring(d->id);
                ListView_SetItemText(deviceListView, i, 0, const_cast<LPWSTR>(&deviceIdTemp[0]));
                ListView_SetItemText(deviceListView, i, 1, const_cast<LPWSTR>(d->productName.c_str()));
                ListView_SetItemText(deviceListView, i, 2, const_cast<LPWSTR>(d->manufacturerName.c_str()));
                std::wstring deviceInterfaceNameTemp(d->deviceInterfaceName.begin(), d->deviceInterfaceName.end());
                ListView_SetItemText(deviceListView, i, 3, const_cast<LPWSTR>(&deviceInterfaceNameTemp[0]));
                i++;
            }
            ListView_EnableGroupView(deviceListView,true);
            ListView_SortItems(deviceListView, sortInt, true);

            ShowWindow(devicePane, SW_SHOW);
            UpdateWindow(devicePane);

            keyboardLogPane = CreateWindow(L"Pane", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, tabHeight, window.right, window.bottom, hwnd, (HMENU)KEYBOARD_LOG, nullptr, 0);
            keyboardLogText = CreateWindowW(WC_EDIT, nullptr, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_BORDER | WS_HSCROLL | ES_WANTRETURN, 200, 20, window.right - 200, window.bottom, keyboardLogPane, (HMENU)KEYBOARD_LOG, nullptr, nullptr);
            SendMessage(keyboardLogText, WM_SETTEXT, 0, (LPARAM)L"");
            SendMessage(keyboardLogText, EM_SETLIMITTEXT, 0, 0);
            HideCaret(keyboardLogText);

            CreateWindowW(WC_BUTTON, L"Options", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_GROUPBOX, 10, 20, 150, 400, keyboardLogPane, (HMENU)0, nullptr, nullptr);
            keyboardIncludeDeviceInterfaceNameCheckbox = CreateWindowW(WC_BUTTON,L"Device Interface Name", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | WS_GROUP | BS_MULTILINE,20,50,100,50, keyboardLogPane,(HMENU) 0,nullptr,nullptr);
            keyboardIncludeProductNameCheckbox = CreateWindowW(WC_BUTTON, L"Product Name", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 100, 100, 50, keyboardLogPane, (HMENU)0, nullptr, nullptr);
            keyboardIncludeManufacturerNameCheckbox = CreateWindowW(WC_BUTTON, L"Manufacturer Name", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 150, 100, 50, keyboardLogPane, (HMENU)0, nullptr, nullptr);
            keyboardIncludeDeviceKeyCheckbox = CreateWindowW(WC_BUTTON, L"Device Key", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 200, 100, 50, keyboardLogPane, (HMENU)0, nullptr, nullptr);
            keyboardIncludeIdCheckbox = CreateWindowW(WC_BUTTON, L"Device ID", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 250, 100, 50, keyboardLogPane, (HMENU)0, nullptr, nullptr);
            keyboardKeyDownCheckbox = CreateWindowW(WC_BUTTON, L"Key Down", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 300, 100, 50, keyboardLogPane, (HMENU)0, nullptr, nullptr);
            keyboardKeyUpCheckbox = CreateWindowW(WC_BUTTON, L"Key Up", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 350, 100, 50, keyboardLogPane, (HMENU)0, nullptr, nullptr);
            
            
            SendMessage(keyboardIncludeDeviceInterfaceNameCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(keyboardIncludeDeviceKeyCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(keyboardIncludeIdCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(keyboardKeyDownCheckbox, BM_SETCHECK, BST_CHECKED, 0);

            keyboardLogStartPauseButton = CreateWindowW(WC_BUTTON, L"", WS_VISIBLE | WS_CHILD | BS_ICON | BS_CENTER, 50, 450, 100, 100, keyboardLogPane, (HMENU)KEYBOARD_LOG_START_PAUSE, nullptr, nullptr);
            SendMessage(keyboardLogStartPauseButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCEW(119), IMAGE_ICON, 100, 100, LR_DEFAULTSIZE | LR_SHARED));
            
            HWND clearKeyboardLogButton = CreateWindowW(WC_BUTTON, L"Clear Log", WS_VISIBLE | WS_CHILD, 50, 575, 100, 25, keyboardLogPane, (HMENU)CLEAR_KEYBOARD_LOG, nullptr, nullptr);
            ShowWindow(keyboardLogPane, SW_HIDE);


            mouseLogPane = CreateWindow(L"Pane", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, tabHeight, window.right, window.bottom, hwnd, (HMENU)MOUSE_LOG, nullptr, 0);
            mouseLogText = CreateWindowW(WC_EDIT, nullptr, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_BORDER | WS_HSCROLL | ES_WANTRETURN, 200, 20, window.right - 200, window.bottom, mouseLogPane, (HMENU)MOUSE_LOG, nullptr, nullptr);
            SendMessage(mouseLogText, WM_SETTEXT, 0, (LPARAM)L"");
            SendMessage(mouseLogText, EM_SETLIMITTEXT, 0, 0);
            HideCaret(mouseLogText);

            CreateWindowW(WC_BUTTON, L"Options", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_GROUPBOX, 10, 20, 150, 500, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseIncludeDeviceInterfaceNameCheckbox = CreateWindowW(WC_BUTTON, L"Device Interface Name", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | WS_GROUP | BS_MULTILINE, 20, 50, 100, 50, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseIncludeProductNameCheckbox = CreateWindowW(WC_BUTTON, L"Product Name", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 100, 100, 50, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseIncludeManufacturerNameCheckbox = CreateWindowW(WC_BUTTON, L"Manufacturer Name", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 150, 100, 50, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseIncludeDeviceKeyCheckbox = CreateWindowW(WC_BUTTON, L"Device Key", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 200, 100, 50, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseIncludeIdCheckbox = CreateWindowW(WC_BUTTON, L"Device ID", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 250, 100, 50, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseKeyDownCheckbox = CreateWindowW(WC_BUTTON, L"Key Down", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 300, 100, 50, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseKeyUpCheckbox = CreateWindowW(WC_BUTTON, L"Key Up", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 350, 100, 50, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mousePositionCheckbox = CreateWindowW(WC_BUTTON, L"Position", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 20, 400, 100, 25, mouseLogPane, (HMENU)MOUSE_POSITION, nullptr, nullptr);
            mouseXPositionCheckbox = CreateWindowW(WC_BUTTON, L"X", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 35, 425, 100, 25, mouseLogPane, (HMENU)0, nullptr, nullptr);
            mouseYPositionCheckbox = CreateWindowW(WC_BUTTON, L"Y", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, 35, 450, 100, 25, mouseLogPane, (HMENU)0, nullptr, nullptr);

            SendMessage(mouseIncludeDeviceInterfaceNameCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(mouseIncludeDeviceKeyCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(mouseIncludeIdCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(mouseKeyDownCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(mouseXPositionCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            SendMessage(mouseYPositionCheckbox, BM_SETCHECK, BST_CHECKED, 0);
            EnableWindow(mouseXPositionCheckbox, false);
            EnableWindow(mouseYPositionCheckbox, false);

            mouseLogStartPauseButton = CreateWindowW(WC_BUTTON, L"", WS_VISIBLE | WS_CHILD | BS_ICON | BS_CENTER, 50, 550, 100, 100, mouseLogPane, (HMENU)MOUSE_LOG_START_PAUSE, nullptr, nullptr);
            SendMessage(mouseLogStartPauseButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCEW(119), IMAGE_ICON, 100, 100, LR_DEFAULTSIZE | LR_SHARED));

            HWND clearMouseLogButton = CreateWindowW(WC_BUTTON, L"Clear Log", WS_VISIBLE | WS_CHILD, 50, 675, 100, 25, mouseLogPane, (HMENU)CLEAR_MOUSE_LOG, nullptr, nullptr);

            ShowWindow(mouseLogPane, SW_HIDE);
            //change all gui objects to use default system font
            EnumChildWindows(hwnd, (WNDENUMPROC)setFont, NULL);
            break;
        }
        case WM_SIZE: {
            //redraw window after resizing
            int width = LOWORD(lparam);
            int height = HIWORD(lparam);
            SetWindowPos(devicePane, nullptr, 0, 0, width, height, SWP_NOMOVE);
            SetWindowPos(deviceListView, nullptr, 0, 0, width * .95, height * .9, SWP_NOMOVE);
            SetWindowPos(keyboardLogPane,nullptr,0,0, width, height, SWP_NOMOVE);
            SetWindowPos(keyboardLogText, nullptr, 0, 0, width * .8, height * .9, SWP_NOMOVE);
            SetWindowPos(mouseLogPane, nullptr, 0, 0, width, height, SWP_NOMOVE);
            SetWindowPos(mouseLogText, nullptr, 0, 0, width * .8, height * .9, SWP_NOMOVE);
            break;
        }
        case WM_PAINT: {
            ////initalize ps and hdc
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(devicePane, &ps);
            //
            ////get dimensions of coordinates
            //RECT client;
            //GetWindowRect(devicePane, &client);
            //int width = client.right - client.left;
            //int height = client.bottom - client.top;
            //
            ////create a separate hdc for double buffering to prevent flicker
            //HDC memDC = CreateCompatibleDC(hdc);
            //HBITMAP hBM = CreateCompatibleBitmap(hdc, width, height);
            //SelectObject(memDC, hBM);
            //
            ////Fill
            //RECT r;
            //SetRect(&r, 0, 0, width, height);
            //FillRect(memDC, &r, (HBRUSH)COLOR_WINDOW);
            //
            ////make graphics
            //Gdiplus::Graphics graphics(memDC);
            ////adds anti-aliasing to make the line look smoother
            //graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
            //
            ////Draw
            //Gdiplus::Pen blackPen(Gdiplus::Color::Black,5);
            //std::cout << graphics.DrawRectangle(&blackPen,100,800, 200, 200) << "\n";
            //
            //
            ////paint on window
            //BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
            //
            ////free up to prevent resource leak
            //DeleteObject(hBM);
            //DeleteDC(memDC);
            ////stop painting
            //EndPaint(devicePane, &ps);
            //break;
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}
void keyboardInterceptor(const Keyboard& keyboard, const KEYSTATE state, const DeviceKey& key) {
    if (keyboardLogRunning) {
        std::wstring line = std::to_wstring(keyboardLogLineNumber) + L":";
        if (SendMessage(keyboardIncludeDeviceInterfaceNameCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Device Interface Name: " + std::wstring(keyboard.deviceInterfaceName.begin(), keyboard.deviceInterfaceName.end());
        }
        if (SendMessage(keyboardIncludeProductNameCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Product Name: " + keyboard.productName;
        }
        if (SendMessage(keyboardIncludeManufacturerNameCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Manufacturer Name: " + keyboard.manufacturerName;
        }
        if (SendMessage(keyboardIncludeIdCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Device ID: " + std::to_wstring(keyboard.id);
        }
        if (SendMessage(keyboardIncludeDeviceKeyCheckbox, BM_GETCHECK, 0, 0)) {
            std::string str{ key.names.at(0) };
            line += L" Key: " + std::wstring(str.begin(), str.end());
        }
        bool addLine = false;
        if (SendMessage(keyboardKeyDownCheckbox, BM_GETCHECK, 0, 0) && state == KEYSTATE::DOWN) {
            line += L" State: DOWN"; 
            addLine = true;
        }
        if (SendMessage(keyboardKeyUpCheckbox, BM_GETCHECK, 0, 0) && state == KEYSTATE::UP) {
            line += L" State: UP";
            addLine = true;
        }
        if (addLine) {
            keyboardLogLineNumber++;
            line += L"\r\n";
            SendMessage(mouseLogText, EM_SETSEL, 0, -1);
            SendMessage(mouseLogText, EM_SETSEL, -1, -1);
            SendMessage(keyboardLogText, EM_REPLACESEL, 0, (LPARAM)line.c_str());
        }
    }
}
void mouseInterceptor(const Mouse& mouse, const KEYSTATE state, const DeviceKey& key, int x, int y) {
    if (mouseLogRunning) {
        
        std::wstring line = std::to_wstring(mouseLogLineNumber) + L":";
        if (SendMessage(mouseIncludeDeviceInterfaceNameCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Device Interface Name: " + std::wstring(mouse.deviceInterfaceName.begin(), mouse.deviceInterfaceName.end());
        }
        if (SendMessage(mouseIncludeProductNameCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Product Name: " + mouse.productName;
        }
        if (SendMessage(mouseIncludeManufacturerNameCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Manufacturer Name: " + mouse.manufacturerName;
        }
        if (SendMessage(mouseIncludeIdCheckbox, BM_GETCHECK, 0, 0)) {
            line += L" Device ID: " + std::to_wstring(mouse.id);
        }
        if (SendMessage(mouseIncludeDeviceKeyCheckbox, BM_GETCHECK, 0, 0)) {
            std::string str{ key.names.at(0) };
            line += L" Key: " + std::wstring(str.begin(), str.end());
        }
        boolean addLine = false;
        if (SendMessage(mouseKeyDownCheckbox, BM_GETCHECK, 0, 0) && state == KEYSTATE::DOWN) { 
            line += L" State: DOWN";
            addLine = true;
        }
        if (SendMessage(mouseKeyUpCheckbox, BM_GETCHECK, 0, 0) && state == KEYSTATE::UP) {
            line += L" State: UP";
            addLine = true;
        }
        if (SendMessage(mousePositionCheckbox, BM_GETCHECK, 0, 0)) {
            if (SendMessage(mouseXPositionCheckbox, BM_GETCHECK, 0, 0)) {
                line += L" X-Pos: " + std::to_wstring(x);
            }
            if (SendMessage(mouseYPositionCheckbox, BM_GETCHECK, 0, 0)) {
                line += L" Y-Pos: " + std::to_wstring(y);
            }
            addLine = true;
        }
        if (addLine) {
            mouseLogLineNumber++;
            line += L"\r\n";
            SendMessage(mouseLogText, EM_SETSEL, 0, -1);
            SendMessage(mouseLogText, EM_SETSEL, -1, -1);
            SendMessage(mouseLogText, EM_REPLACESEL, false, (LPARAM)line.c_str());
        }
    }
}
int main() {
	DeviceManager::populate();
	DeviceManager::createOrApplyMapping("mapping.mapping");

    Interceptor interceptor;
    interceptor.keyboardGlobalInterceptors.push_back(keyboardInterceptor);
    interceptor.mouseGlobalInterceptors.push_back(mouseInterceptor);
    std::thread interceptorThread([&]() {  
        interceptor.begin();
    });
    
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
    wc.hIcon = (HICON)LoadImage(wc.hInstance, MAKEINTRESOURCEW(117), IMAGE_ICON, 256, 256, LR_DEFAULTSIZE | LR_SHARED);

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
    interceptor.end();
	return 0;
}