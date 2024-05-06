#pragma once
#include <Windows.h>
#include <Ntddkbd.h>
#include <Hidsdi.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <functional>
#include "../device/DeviceManager.h"
#include "../hotkey/Key.h"

#pragma comment (lib,"Hid.lib")
//This class intercepts keyboard messages and sets up other needed
class Interceptor {
private:
	WNDCLASS wc;
	void handleInput(const MSG& msg);
public:
	std::vector<std::function<void(const Keyboard& keyboard,const KEYSTATE state, const DeviceKey& key)>> keyboardGlobalInterceptors;
	Interceptor();

	void begin();
};
