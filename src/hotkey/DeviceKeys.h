#pragma once
#include <string>
#include <set>
#include <functional>
#include <Windows.h>
#include <Winuser.h>
#include <cctype>
#include <algorithm>
#include <string_view>
#include <memory>

#include "DeviceKey.h"

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace DeviceKeys {
	extern std::set<std::shared_ptr<DeviceKey>> keys;
	//Helper function to add and create DeviceKey at same time
	static const DeviceKey& add(const DeviceKey&& key) {
		keys.insert(std::make_shared<DeviceKey>(key));
		return key;
	}
	static const DeviceKey NONE = add(DeviceKey(0, {"NONE"}));
	//Mouse Keys
	static const DeviceKey LBUTTON = add(DeviceKey(VK_LBUTTON,{"LButton","Left Key", "Left Click"}));
	static const DeviceKey RBUTTON = add(DeviceKey(VK_RBUTTON,{"RButton","Right Key", "Right Click"}));
	static const DeviceKey MBUTTON = add(DeviceKey(VK_MBUTTON,{"MButton","Middle Mouse", "Middle Click"}));
	//Keyboard Keys
	static const DeviceKey BACKSPACE = add(DeviceKey(VK_BACK, { "Backspace","Back"}));
	//static const DeviceKey TAB = add(DeviceKey(VK_TAB, { "Tab"}));
	//static const DeviceKey CLEAR = add(DeviceKey(VK_CLEAR, { "Clear" }));
	//static const DeviceKey ENTER = add(DeviceKey(VK_RETURN, { "Enter", "Return"}));
	//static const DeviceKey SHIFT = add(DeviceKey(VK_SHIFT, { "Shift"}));
	//static const DeviceKey LSHIFT = add(DeviceKey(VK_LSHIFT, { "Left Shift", "LShift"}));
	//static const DeviceKey RSHIFT = add(DeviceKey(VK_RSHIFT, { "Right Shift", "RShift"}));
	//static const DeviceKey CONTROL = add(DeviceKey(VK_CONTROL, { "Control", "CTRL" }));
	//static const DeviceKey LCONTROL = add(DeviceKey(VK_LCONTROL, { "Left Control", "LCTRL" }));
	//static const DeviceKey RCONTROL = add(DeviceKey(VK_RCONTROL, { "Right Control", "RCTRL" }));
	//static const DeviceKey ALT = add(DeviceKey(VK_MENU, { "Alt", "Menu" }));
	//static const DeviceKey LALT = add(DeviceKey(VK_LMENU, { "Left Alt", "Left Menu", "LMENU", "LALT" }));
	//static const DeviceKey RALT = add(DeviceKey(VK_RMENU, { "Right Alt", "Right Menu", "RMENU", "RALT" }));
	//static const DeviceKey PAUSE = add(DeviceKey(VK_PAUSE, { "Pause"}));
	//static const DeviceKey CAPSLOCK = add(DeviceKey(VK_CAPITAL, { "Caps Lock", "Capital"}));
	//static const DeviceKey ESCAPE = add(DeviceKey(VK_ESCAPE, { "Escape", "ESC" }));
	//static const DeviceKey SPACE = add(DeviceKey(VK_SPACE, { "Spacebar", "Space" }));
	//static const DeviceKey PAGEUP = add(DeviceKey(VK_PRIOR, { "Page Up", "PGUP" }));
	//static const DeviceKey PAGEDOWN = add(DeviceKey(VK_NEXT, { "Page Down", "PGDN" }));
	//static const DeviceKey END = add(DeviceKey(VK_END, { "END" }));
	//static const DeviceKey HOME = add(DeviceKey(VK_HOME, { "HOME" }));
	//static const DeviceKey LEFT = add(DeviceKey(VK_LEFT, { "Left Arrow", "Left"}));
	//static const DeviceKey RIGHT = add(DeviceKey(VK_RIGHT, { "Right Arrow", "Right" }));
	//static const DeviceKey UP = add(DeviceKey(VK_UP, { "Up Arrow", "Up" }));
	//static const DeviceKey DOWN = add(DeviceKey(VK_DOWN, { "Down Arrow", "Down" }));
	//static const DeviceKey SELECT = add(DeviceKey(VK_SELECT, { "Select"}));
	//static const DeviceKey PRINTSCREEN = add(DeviceKey(VK_SNAPSHOT, { "Printscreen", "Print screen", "PRTSC" }));
	//static const DeviceKey INSERT = add(DeviceKey(VK_INSERT, { "Insert", "INS"}));
	//static const DeviceKey DEL = add(DeviceKey(VK_DELETE, { "Delete", "DEL" }));
	//static const DeviceKey ZERO = add(DeviceKey(0x30, { "0" "Zero" }));
	//static const DeviceKey ONE = add(DeviceKey(0x31, { "1", "One" }));
	//static const DeviceKey TWO = add(DeviceKey(0x32, { "2", "Two" }));
	//static const DeviceKey THREE = add(DeviceKey(0x33, { "3", "Three" }));
	//static const DeviceKey FOUR = add(DeviceKey(0x34, { "4", "Four" }));
	//static const DeviceKey FIVE = add(DeviceKey(0x35, { "5", "Five" }));
	//static const DeviceKey SIX = add(DeviceKey(0x36, { "6", "Six" }));
	//static const DeviceKey SEVEN = add(DeviceKey(0x37, { "7", "Seven" }));
	//static const DeviceKey EIGHT = add(DeviceKey(0x38, { "8", "Eight" }));
	//static const DeviceKey NINE = add(DeviceKey(0x39, { "9", "Nine" }));
	//static const DeviceKey A = add(DeviceKey(0x41, { "A" }));
	//static const DeviceKey B = add(DeviceKey(0x42, { "B" }));
	//static const DeviceKey C = add(DeviceKey(0x43, { "C" }));
	//static const DeviceKey D = add(DeviceKey(0x44, { "D" }));
	//static const DeviceKey E = add(DeviceKey(0x45, { "E" }));
	//static const DeviceKey F = add(DeviceKey(0x46, { "F" }));
	//static const DeviceKey G = add(DeviceKey(0x47, { "G" }));
	//static const DeviceKey H = add(DeviceKey(0x48, { "H" }));
	//static const DeviceKey I = add(DeviceKey(0x49, { "I" }));
	//static const DeviceKey J = add(DeviceKey(0x4a, { "J" }));
	//static const DeviceKey K = add(DeviceKey(0x4b, { "K" }));
	//static const DeviceKey L = add(DeviceKey(0x4c, { "L" }));
	//static const DeviceKey M = add(DeviceKey(0x4d, { "M" }));
	//static const DeviceKey N = add(DeviceKey(0x4e, { "N" }));
	//static const DeviceKey O = add(DeviceKey(0x4f, { "O" }));
	//static const DeviceKey P = add(DeviceKey(0x50, { "P" }));
	//static const DeviceKey Q = add(DeviceKey(0x51, { "Q" }));
	//static const DeviceKey R = add(DeviceKey(0x52, { "R" }));
	//static const DeviceKey S = add(DeviceKey(0x53, { "S" }));
	//static const DeviceKey T = add(DeviceKey(0x54, { "T" }));
	//static const DeviceKey U = add(DeviceKey(0x55, { "U" }));
	//static const DeviceKey V = add(DeviceKey(0x56, { "V" }));
	//static const DeviceKey W = add(DeviceKey(0x57, { "W" }));
	//static const DeviceKey X = add(DeviceKey(0x58, { "X" }));
	//static const DeviceKey Y = add(DeviceKey(0x59, { "Y" }));
	//static const DeviceKey Z = add(DeviceKey(0x5A, { "Z" }));
	//static const DeviceKey LWIN = add(DeviceKey(VK_LWIN, { "Left Windows", "LWIN"}));
	//static const DeviceKey RWIN = add(DeviceKey(VK_RWIN, { "Right Windows", "RWIN" }));
	//static const DeviceKey NUMPAD_ZERO = add(DeviceKey(VK_NUMPAD0, {"Numpad 0"}));
	//static const DeviceKey NUMPAD_ONE = add(DeviceKey(VK_NUMPAD1, { "Numpad 1" }));
	//static const DeviceKey NUMPAD_TWO = add(DeviceKey(VK_NUMPAD2, { "Numpad 2" }));
	//static const DeviceKey NUMPAD_THREE = add(DeviceKey(VK_NUMPAD3, { "Numpad 3" }));
	//static const DeviceKey NUMPAD_FOUR = add(DeviceKey(VK_NUMPAD4, { "Numpad 4" }));
	//static const DeviceKey NUMPAD_FIVE = add(DeviceKey(VK_NUMPAD5, { "Numpad 5" }));
	//static const DeviceKey NUMPAD_SIX = add(DeviceKey(VK_NUMPAD6, { "Numpad 6" }));
	//static const DeviceKey NUMPAD_SEVEN = add(DeviceKey(VK_NUMPAD7, { "Numpad 7" }));
	//static const DeviceKey NUMPAD_EIGHT = add(DeviceKey(VK_NUMPAD8, {"Numpad 8" }));
	//static const DeviceKey NUMPAD_NINE = add(DeviceKey(VK_NUMPAD9, { "Numpad 9" }));
	//static const DeviceKey MULTIPLY = add(DeviceKey(VK_MULTIPLY, { "Multiply", "Times"}));
	//static const DeviceKey ADD = add(DeviceKey(VK_ADD, { "Add", "Plus", "Sum"}));
	//static const DeviceKey SEPARATOR = add(DeviceKey(VK_SEPARATOR, { "Separator" }));
	//static const DeviceKey SUBTRACT = add(DeviceKey(VK_SUBTRACT, { "Subtract", "Minus"}));
	//static const DeviceKey DECIMAL = add(DeviceKey(VK_DECIMAL, { "Decimal", "Dot"}));
	//static const DeviceKey DIVIDE = add(DeviceKey(VK_DIVIDE, { "Divide", "Division"}));
	//static const DeviceKey F1 = add(DeviceKey(VK_F1, { "F1" }));
	//static const DeviceKey F2 = add(DeviceKey(VK_F2, { "F2" }));
	//static const DeviceKey F3 = add(DeviceKey(VK_F3, { "F3" }));
	//static const DeviceKey F4 = add(DeviceKey(VK_F4, { "F4" }));
	//static const DeviceKey F5 = add(DeviceKey(VK_F5, { "F5" }));
	//static const DeviceKey F6 = add(DeviceKey(VK_F6, { "F6" }));
	//static const DeviceKey F7 = add(DeviceKey(VK_F7, { "F7" }));
	//static const DeviceKey F8 = add(DeviceKey(VK_F8, { "F8" }));
	//static const DeviceKey F9 = add(DeviceKey(VK_F9, { "F9" }));
	//static const DeviceKey F10 = add(DeviceKey(VK_F10, { "F10" }));
	//static const DeviceKey F11 = add(DeviceKey(VK_F11, { "F11" }));
	//static const DeviceKey F12 = add(DeviceKey(VK_F12, { "F12" }));
	//static const DeviceKey F13 = add(DeviceKey(VK_F13, { "F13" }));
	//static const DeviceKey F14 = add(DeviceKey(VK_F14, { "F14" }));
	//static const DeviceKey F15 = add(DeviceKey(VK_F15, { "F15" }));
	//static const DeviceKey F16 = add(DeviceKey(VK_F16, { "F16" }));
	//static const DeviceKey F17 = add(DeviceKey(VK_F17, { "F17" }));
	//static const DeviceKey F18 = add(DeviceKey(VK_F18, { "F18" }));
	//static const DeviceKey F19 = add(DeviceKey(VK_F19, { "F19" }));
	//static const DeviceKey F20 = add(DeviceKey(VK_F20, { "F20" }));
	//static const DeviceKey F21 = add(DeviceKey(VK_F21, { "F21" }));
	//static const DeviceKey F22 = add(DeviceKey(VK_F22, { "F22" }));
	//static const DeviceKey F23 = add(DeviceKey(VK_F23, { "F23" }));
	//static const DeviceKey F24 = add(DeviceKey(VK_F24, { "F24" }));
	//static const DeviceKey NUMLOCK = add(DeviceKey(VK_NUMLOCK, { "Num Lock", "Numlock", "Number Lock", "Number", "NUM"}));
	//static const DeviceKey SCROLL_LOCK = add(DeviceKey(VK_SCROLL, { "Scroll Lock", "Scroll", "SCRLK"}));
	//static const DeviceKey MUTE = add(DeviceKey(VK_VOLUME_MUTE, { "Mute" }));
	//static const DeviceKey VOLUME_UP = add(DeviceKey(VK_VOLUME_UP, { "Volume Up" }));
	//static const DeviceKey VOLUME_DOWN = add(DeviceKey(VK_VOLUME_DOWN, { "Volume Down" }));
	//static const DeviceKey MEDIA_STOP = add(DeviceKey(VK_MEDIA_STOP, { "Media Stop", "Stop"}));
	//static const DeviceKey MEDIA_PLAY_PAUSE = add(DeviceKey(VK_MEDIA_STOP, { "Media Play/Pause"}));
	//static const DeviceKey SEMICOLON = add(DeviceKey(VK_OEM_1, { ";", ":", "Semicolon", "Semi-colon", "Colon"}));
	//static const DeviceKey EQUAL = add(DeviceKey(VK_OEM_PLUS, { "=", "+", "Equal", "Plus"}));
	//static const DeviceKey COMMA = add(DeviceKey(VK_OEM_COMMA, { ",", "Comma"}));
	//static const DeviceKey MINUS = add(DeviceKey(VK_OEM_MINUS, { "-", "Minus" }));
	//static const DeviceKey PERIOD = add(DeviceKey(VK_OEM_PERIOD, { "-", "Minus" }));
	//static const DeviceKey FORWARD_SLASH = add(DeviceKey(VK_OEM_2, { "/", "?", "Forward Slash", "Question", "Question Mark"}));
	//static const DeviceKey BACK_SLASH = add(DeviceKey(VK_OEM_5, { "\\", "Back Slash" }));
	//static const DeviceKey GRAVE = add(DeviceKey(VK_OEM_3, { "`", "~", "Grave", "Tilde"}));
	//static const DeviceKey LEFT_BRACKET = add(DeviceKey(VK_OEM_4, { "[", "{", "Left Bracket", "Left Braces", "Left Brace", "Left Curly Bracket"}));
	//static const DeviceKey RIGHT_BRACKET = add(DeviceKey(VK_OEM_4, { "]", "}", "Right Bracket", "Right Braces", "Right Brace", "Right Curly Bracket" }));
	//static const DeviceKey QUOTATION = add(DeviceKey(VK_OEM_4, { "'", "\"", "Quotation", "Quotation Mark"}));
	//static const DeviceKey PLAY = add(DeviceKey(VK_PLAY, { "Play" }));
	//static const DeviceKey ZOOM = add(DeviceKey(VK_ZOOM, { "Zoom" }));

	//Gets device key by case insensitive search 
	static const DeviceKey& getByName(const std::string& name) {
		for (std::shared_ptr<const DeviceKey> key : keys) {
			for (std::string_view n : key->names) {
				if (std::ranges::equal(std::string_view(name), n, [](auto a, auto b) {return std::tolower(a) == std::tolower(b); })) {
					return *key;
				}
			}
		}
		return **keys.begin();
	}
	static const DeviceKey& getByVKey(const int vKey) {
		for (std::shared_ptr<const DeviceKey> key : keys) {
			if (vKey == key->value) {
				return* key;
			}
		}
		return **keys.begin();
	}
}