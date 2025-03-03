#include "ActionRand.h"

ActionRand::ActionRand() : Action("RandInt", DataTypes::INTEGER, {Parameter("min",DataTypes::INTEGER,"Min Value",true,DataTypeInteger(0)),
								                              Parameter("max",DataTypes::INTEGER, "Max Value", true,DataTypeInteger(100))}, "Generates a random integer between [min, max]", CATEGORY_MATH) {
}

std::shared_ptr<DataType> ActionRand::execute(std::vector<std::shared_ptr<DataType>>& parameters) {
	int min = parameters[0]->getData<DataTypeInteger>()->value;
	int max = parameters[1]->getData<DataTypeInteger>()->value;

	std::random_device dev;
	std::mt19937 rng(dev());
	// distribution in range [min, max]
	std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);

	return std::make_shared<DataTypeInteger>(distribution(rng));
}
