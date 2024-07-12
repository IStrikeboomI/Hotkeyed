#include "DeviceKeys.h"

namespace DeviceKeys {
	std::set<DeviceKey> DeviceKeys::keys {
		DeviceKey(0, {"NONE"}),
		DeviceKey(VK_LBUTTON,{"LButton","Left Key", "Left Click"}),
		DeviceKey(VK_RBUTTON,{"RButton","Right Key", "Right Click"}),
		DeviceKey(VK_MBUTTON,{"MButton","Middle Mouse", "Middle Click"}),
		DeviceKey(VK_BACK, { "Backspace","Back"}),
		DeviceKey(VK_TAB, { "Tab"}),
		DeviceKey(VK_CLEAR, { "Clear" }),
		DeviceKey(VK_RETURN, { "Enter", "Return"}),
		DeviceKey(VK_SHIFT, { "Shift"}),
		DeviceKey(VK_LSHIFT, { "Left Shift", "LShift"}),
		DeviceKey(VK_RSHIFT, { "Right Shift", "RShift"}),
		DeviceKey(VK_CONTROL, { "Control", "CTRL" }),
		DeviceKey(VK_LCONTROL, { "Left Control", "LCTRL" }),
		DeviceKey(VK_RCONTROL, { "Right Control", "RCTRL" }),
		DeviceKey(VK_MENU, { "Alt", "Menu" }),
		DeviceKey(VK_LMENU, { "Left Alt", "Left Menu", "LMENU", "LALT" }),
		DeviceKey(VK_RMENU, { "Right Alt", "Right Menu", "RMENU", "RALT" }),
		DeviceKey(VK_PAUSE, { "Pause"}),
		DeviceKey(VK_CAPITAL, { "Caps Lock", "Capital"}),
		DeviceKey(VK_ESCAPE, { "Escape", "ESC" }),
		DeviceKey(VK_SPACE, { "Spacebar", "Space" }),
		DeviceKey(VK_PRIOR, { "Page Up", "PGUP" }),
		DeviceKey(VK_NEXT, { "Page Down", "PGDN" }),
		DeviceKey(VK_END, { "End" }),
		DeviceKey(VK_HOME, { "Home" }),
		DeviceKey(VK_LEFT, { "Left Arrow", "Left"}),
		DeviceKey(VK_RIGHT, { "Right Arrow", "Right" }),
		DeviceKey(VK_UP, { "Up Arrow", "Up" }),
		DeviceKey(VK_DOWN, { "Down Arrow", "Down" }),
		DeviceKey(VK_SELECT, { "Select"}),
		DeviceKey(VK_SNAPSHOT, { "Printscreen", "Print screen", "PRTSC" }),
		DeviceKey(VK_INSERT, { "Insert", "INS"}),
		DeviceKey(VK_DELETE, { "Delete", "DEL" }),
		DeviceKey(0x30, { "0", "Zero" }),
		DeviceKey(0x31, { "1", "One" }),
		DeviceKey(0x32, { "2", "Two" }),
		DeviceKey(0x33, { "3", "Three" }),
		DeviceKey(0x34, { "4", "Four" }),
		DeviceKey(0x35, { "5", "Five" }),
		DeviceKey(0x36, { "6", "Six" }),
		DeviceKey(0x37, { "7", "Seven" }),
		DeviceKey(0x38, { "8", "Eight" }),
		DeviceKey(0x39, { "9", "Nine" }),
		DeviceKey(0x41, { "A" }),
		DeviceKey(0x42, { "B" }),
		DeviceKey(0x43, { "C" }),
		DeviceKey(0x44, { "D" }),
		DeviceKey(0x45, { "E" }),
		DeviceKey(0x46, { "F" }),
		DeviceKey(0x47, { "G" }),
		DeviceKey(0x48, { "H" }),
		DeviceKey(0x49, { "I" }),
		DeviceKey(0x4a, { "J" }),
		DeviceKey(0x4b, { "K" }),
		DeviceKey(0x4c, { "L" }),
		DeviceKey(0x4d, { "M" }),
		DeviceKey(0x4e, { "N" }),
		DeviceKey(0x4f, { "O" }),
		DeviceKey(0x50, { "P" }),
		DeviceKey(0x51, { "Q" }),
		DeviceKey(0x52, { "R" }),
		DeviceKey(0x53, { "S" }),
		DeviceKey(0x54, { "T" }),
		DeviceKey(0x55, { "U" }),
		DeviceKey(0x56, { "V" }),
		DeviceKey(0x57, { "W" }),
		DeviceKey(0x58, { "X" }),
		DeviceKey(0x59, { "Y" }),
		DeviceKey(0x5A, { "Z" }),
		DeviceKey(VK_LWIN, { "Left Windows", "LWIN"}),
		DeviceKey(VK_RWIN, { "Right Windows", "RWIN" }),
		DeviceKey(VK_NUMPAD0, {"Numpad 0"}),
		DeviceKey(VK_NUMPAD1, { "Numpad 1" }),
		DeviceKey(VK_NUMPAD2, { "Numpad 2" }),
		DeviceKey(VK_NUMPAD3, { "Numpad 3" }),
		DeviceKey(VK_NUMPAD4, { "Numpad 4" }),
		DeviceKey(VK_NUMPAD5, { "Numpad 5" }),
		DeviceKey(VK_NUMPAD6, { "Numpad 6" }),
		DeviceKey(VK_NUMPAD7, { "Numpad 7" }),
		DeviceKey(VK_NUMPAD8, {"Numpad 8" }),
		DeviceKey(VK_NUMPAD9, { "Numpad 9" }),
		DeviceKey(VK_MULTIPLY, { "Multiply", "Times"}),
		DeviceKey(VK_ADD, { "Add", "Plus", "Sum"}),
		DeviceKey(VK_SEPARATOR, { "Separator" }),
		DeviceKey(VK_SUBTRACT, { "Subtract", "Minus"}),
		DeviceKey(VK_DECIMAL, { "Decimal", "Dot"}),
		DeviceKey(VK_DIVIDE, { "Divide", "Division"}),
		DeviceKey(VK_F1, { "F1" }),
		DeviceKey(VK_F2, { "F2" }),
		DeviceKey(VK_F3, { "F3" }),
		DeviceKey(VK_F4, { "F4" }),
		DeviceKey(VK_F5, { "F5" }),
		DeviceKey(VK_F6, { "F6" }),
		DeviceKey(VK_F7, { "F7" }),
		DeviceKey(VK_F8, { "F8" }),
		DeviceKey(VK_F9, { "F9" }),
		DeviceKey(VK_F10, { "F10" }),
		DeviceKey(VK_F11, { "F11" }),
		DeviceKey(VK_F12, { "F12" }),
		DeviceKey(VK_F13, { "F13" }),
		DeviceKey(VK_F14, { "F14" }),
		DeviceKey(VK_F15, { "F15" }),
		DeviceKey(VK_F16, { "F16" }),
		DeviceKey(VK_F17, { "F17" }),
		DeviceKey(VK_F18, { "F18" }),
		DeviceKey(VK_F19, { "F19" }),
		DeviceKey(VK_F20, { "F20" }),
		DeviceKey(VK_F21, { "F21" }),
		DeviceKey(VK_F22, { "F22" }),
		DeviceKey(VK_F23, { "F23" }),
		DeviceKey(VK_F24, { "F24" }),
		DeviceKey(VK_NUMLOCK, { "Num Lock", "Numlock", "Number Lock", "Number", "NUM"}),
		DeviceKey(VK_SCROLL, { "Scroll Lock", "Scroll", "SCRLK"}),
		DeviceKey(VK_VOLUME_MUTE, { "Mute" }),
		DeviceKey(VK_VOLUME_UP, { "Volume Up" }),
		DeviceKey(VK_VOLUME_DOWN, { "Volume Down" }),
		DeviceKey(VK_MEDIA_STOP, { "Media Stop", "Stop"}),
		DeviceKey(VK_MEDIA_STOP, { "Media Play/Pause"}),
		DeviceKey(VK_OEM_1, { ";", ":", "Semicolon", "Semi-colon", "Colon"}),
		DeviceKey(VK_OEM_PLUS, { "=", "+", "Equal", "Plus"}),
		DeviceKey(VK_OEM_COMMA, { ",", "Comma"}),
		DeviceKey(VK_OEM_MINUS, { "-", "Minus" }),
		DeviceKey(VK_OEM_PERIOD, { ".", "Period" }),
		DeviceKey(VK_OEM_2, { "/", "?", "Forward Slash", "Question", "Question Mark"}),
		DeviceKey(VK_OEM_5, { "\\", "Back Slash" }),
		DeviceKey(VK_OEM_3, { "`", "~", "Grave", "Tilde"}),
		DeviceKey(VK_OEM_4, { "[", "Left Bracket", "Left Braces", "Left Brace", "Left Curly Bracket"}),
		DeviceKey(VK_OEM_6, { "]", "Right Bracket", "Right Braces", "Right Brace", "Right Curly Bracket" }),
		DeviceKey(VK_OEM_7, { "'", "\"", "Quotation", "Quotation Mark"}),
		DeviceKey(VK_PLAY, { "Play" }),
		DeviceKey(VK_ZOOM, { "Zoom" })
	};
}