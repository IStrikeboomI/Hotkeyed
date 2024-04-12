#pragma once
#include <Windows.h>
#include <Ntddkbd.h>
#include <Hidsdi.h>
#include <stdexcept>
#include <iostream>
#include "../device/DeviceManager.h"

#pragma comment (lib,"Hid.lib")
//This class intercepts keyboard messages and sets up other needed
class Interceptor {
public:
	Interceptor();
};

