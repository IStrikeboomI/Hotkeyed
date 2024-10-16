#include <iostream>
#include <device/DeviceManager.h>
#include <windows/Interceptor.h>
#include "script/Script.h"
#include "engine/ScriptEngine.h"
int main() {
    BigFloat f("-3479768509280387935095304798.426879");
    std::cout << f << "\n";
    ParameterNum n("","");
    DeviceManager::getInstance().populate();
    Mapping mapping(std::filesystem::current_path().generic_string() + "/mapping.mapping");
    DeviceManager::getInstance().setMapping(mapping);
    
    ScriptEngine engine;
    Script testScript("testScript.htky");
    engine.addScript(testScript);
    //engine.start();
    return 0;

}
