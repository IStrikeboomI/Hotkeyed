#include "ActionRand.h"

ActionRand::ActionRand() : Action("Rand", {Parameter(ParameterType::INT,"min","Min value",true),Parameter(ParameterType::INT,"max","Max value",true)}) {
}

std::any ActionRand::execute(std::map<Parameter, std::any>& params) {
	int min = std::any_cast<int>(getParam("min",params));
	int max = std::any_cast<int>(getParam("max", params));
	std::random_device dev;
	std::mt19937 rng(dev());
	// distribution in range [min, max]
	std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);

	return static_cast<int>(distribution(rng));
}
