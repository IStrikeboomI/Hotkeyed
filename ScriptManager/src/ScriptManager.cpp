#include <iostream>
#include <device/DeviceManager.h>
#include <windows/Interceptor.h>
#include "script/Script.h"
#include "engine/ScriptEngine.h"
#include "engine/Integer.h"
int main() {
    Integer test(37948);
    std::cout << test << "\n";
    //DeviceManager::getInstance().populate();
    //Mapping mapping(std::filesystem::current_path().generic_string() + "/mapping.mapping");
    //DeviceManager::getInstance().setMapping(mapping);
    //
    //ScriptEngine engine;
    //Script testScript("testScript.htky");
    //engine.addScript(testScript);
    //engine.start();
    return 0;

}
