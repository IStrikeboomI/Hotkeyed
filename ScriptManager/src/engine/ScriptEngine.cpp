#include "ScriptEngine.h"

void ScriptEngine::keyboardInterceptor(const Keyboard& keyboard, const KEYSTATE state, const DeviceKey& key) {
	std::cout << keyboard.id << "\n";
	for (Script s : scripts) {
		for (Hotkey h : s.hotkeys) {
			for (Key k : h.keys) {
				if (k.key.value == key.value && k.isDeviceIdValid(keyboard.id)) {
					bool allKeysDown = true;
					for (Key kk : h.keys) {
						if (interceptor.activeKeyStates.isKeyBeingUsed(kk) != 0) {
							allKeysDown = false;
						}
					}
					if (allKeysDown) {
						std::cout << "hotkey activated" << "\n";
					}
				}
			}
		}
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
		interceptor.begin();
	});
	interceptorThread.join();
	for (Script s : scripts) {
		
	}
}

void ScriptEngine::addScript(Script& script) {
	scripts.emplace_back(script);
}
