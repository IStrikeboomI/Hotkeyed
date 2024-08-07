#pragma once
#include <vector>
#include "../script/Script.h"
#include <thread>
#include <windows/Interceptor.h>
class ScriptEngine {
private:
	std::thread interceptorThread;
	std::vector<Script> scripts;
public:
	ScriptEngine();
	void start();
	void addScript(Script& script);
};

