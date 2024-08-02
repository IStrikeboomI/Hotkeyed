#pragma once
#include <vector>
#include "../script/Script.h"
#include <windows/Interceptor.h>
class ScriptEngine {
private:
	std::vector<Script> scripts;
public:
	ScriptEngine();
	void start();
	void addScript(Script& script);
};

