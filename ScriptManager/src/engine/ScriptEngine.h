#pragma once
#include <vector>
#include "../script/Script.h"
#include <thread>
#include <windows/Interceptor.h>
class ScriptEngine {
private:
	Interceptor interceptor;
	std::vector<Script> scripts;
public:
	ScriptEngine();
	void start();
	void addScript(Script& script);
};

