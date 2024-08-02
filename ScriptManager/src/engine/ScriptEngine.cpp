#include "ScriptEngine.h"

ScriptEngine::ScriptEngine() {
}

void ScriptEngine::start() {
}

void ScriptEngine::addScript(Script& script) {
	scripts.emplace_back(script);
}
