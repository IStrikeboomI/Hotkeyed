#include "ScriptEngine.h"

void keyboardInterceptor(const Keyboard& keyboard, const KEYSTATE state, const DeviceKey& key) {
	
}
void mouseInterceptor(const Mouse& mouse, const KEYSTATE state, const DeviceKey& key, int x, int y) {
	
}
ScriptEngine::ScriptEngine() {
	interceptor.keyboardGlobalInterceptors.push_back(keyboardInterceptor);
	interceptor.mouseGlobalInterceptors.push_back(mouseInterceptor);
}

void ScriptEngine::start() {
	std::thread interceptorThread([&] {
		interceptor.begin();
	});
}

void ScriptEngine::addScript(Script& script) {
	scripts.emplace_back(script);
}
