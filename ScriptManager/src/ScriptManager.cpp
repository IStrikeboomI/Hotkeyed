#include <iostream>
#include <device/DeviceManager.h>
#include <windows/Interceptor.h>
#include "script/Script.h"
#include "engine/ScriptEngine.h"
int main() {
    DeviceManager::getInstance().populate();
    Mapping mapping(std::filesystem::current_path().generic_string() + "/mapping.mapping");
    DeviceManager::getInstance().setMapping(mapping);

    ScriptEngine engine;
    Script testScript("testScript.htky");
    engine.addScript(testScript);
    //engine.start();
    //ask for the grades using a while loop and store grade in a double called grade
    //then do grades.push_back(grade); or whatever the grades vector is called
    return 0;

}
