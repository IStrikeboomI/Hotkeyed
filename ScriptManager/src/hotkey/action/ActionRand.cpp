#include "ActionRand.h"

ActionRand::ActionRand() : Action("Rand", {Parameter(ParameterType::NUM,"min","Min value",true),Parameter(ParameterType::NUM,"max","Max value",true)}) {
}

std::any ActionRand::execute(std::map<Parameter, std::any>& params) {
	BigFloat min = std::any_cast<BigFloat>(getParam("min",params));
	BigFloat max = std::any_cast<BigFloat>(getParam("max", params));
	std::random_device dev;
	std::mt19937 rng(dev());
	// distribution in range [min, max]
	std::uniform_int_distribution<std::mt19937::result_type> distribution(min.toInt(), max.toInt());

	return static_cast<BigFloat>(distribution(rng));
}
