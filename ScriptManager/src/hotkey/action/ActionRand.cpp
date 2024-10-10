#include "ActionRand.h"

ActionRand::ActionRand() : Action("Rand", {Parameter(ParameterType::INT,"min","Min value",true),Parameter(ParameterType::INT,"max","Max value",true)}) {
}

std::any ActionRand::execute(std::map<Parameter, std::any>& params) {
	BigInt min = std::any_cast<BigInt>(getParam("min",params));
	BigInt max = std::any_cast<BigInt>(getParam("max", params));
	std::random_device dev;
	std::mt19937 rng(dev());
	// distribution in range [min, max]
	std::uniform_int_distribution<std::mt19937::result_type> distribution(min.to_int(), max.to_int());

	return static_cast<BigInt>(distribution(rng));
}
