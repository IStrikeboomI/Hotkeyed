#include <iostream>
#include <device/DeviceManager.h>
#include <windows/Interceptor.h>
#include "script/Script.h"
#include "engine/ScriptEngine.h"
int main() {
    ScriptEngine engine;
    Script testScript("testScript.htky");
    engine.addScript(testScript);
    engine.start();
    return 0;
}
