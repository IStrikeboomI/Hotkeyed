#include <iostream>
#include <device/DeviceManager.h>
#include <windows/Interceptor.h>
#include "script/Script.h"
#include "engine/ScriptEngine.h"
#include "hotkey/parameter/Parameter.h"
#include "hotkey/datatype/DataTypeNumber.h"
int main() {
    BigFloat f("-3479768509280387935095304798.426879");
    std::cout << f << "\n";
    std::vector<std::unique_ptr<Parameter>> dt;
    Parameter p = Parameter::Parameter<DataTypeNumber>("test", "test", false);

    DeviceManager::getInstance().populate();
    Mapping mapping(std::filesystem::current_path().generic_string() + "/mapping.mapping");
    DeviceManager::getInstance().setMapping(mapping);
    
    ScriptEngine engine;
    Script testScript("testScript.htky");
    engine.addScript(testScript);
    //engine.start();
    return 0;

}
