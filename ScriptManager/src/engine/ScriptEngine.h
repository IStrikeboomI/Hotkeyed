#pragma once
#include <vector>
#include "../script/Script.h"
#include <thread>
#include <windows/Interceptor.h>
#include <functional>
class ScriptEngine {
private:
	Interceptor interceptor;
	std::vector<Script> scripts;
	void keyboardInterceptor(const Keyboard& keyboard, const KEYSTATE state, const DeviceKey& key);
	void mouseInterceptor(const Mouse& mouse, const KEYSTATE state, const DeviceKey& key, int x, int y);
public:
	
	ScriptEngine();
	void start();
	void addScript(Script& script);
};

