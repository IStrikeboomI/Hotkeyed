#include "ScriptEngine.h"

void ScriptEngine::keyboardInterceptor(const Keyboard& keyboard, const KEYSTATE state, const DeviceKey& key) {
	std::cout << keyboard.id << "\n";
	for (Script s : this->scripts) {
		//if () {
		//
		//}
	}
	
}
void ScriptEngine::mouseInterceptor(const Mouse& mouse, const KEYSTATE state, const DeviceKey& key, int x, int y) {
	
}
ScriptEngine::ScriptEngine() {
	using namespace std::placeholders;
	interceptor.keyboardGlobalInterceptors.push_back(std::bind(&ScriptEngine::keyboardInterceptor, this, _1, _2, _3));
	interceptor.mouseGlobalInterceptors.push_back(std::bind(&ScriptEngine::mouseInterceptor, this, _1, _2, _3,_4,_5));
}

void ScriptEngine::start() {
	std::thread interceptorThread([&] {
		std::cout << interceptor.keyboardGlobalInterceptors.size() << "\n";
		interceptor.begin();
	});
	interceptorThread.join();
}

void ScriptEngine::addScript(Script& script) {
	scripts.emplace_back(script);
}
