#include "ActionRand.h"

ActionRand::ActionRand() : Action("RandInt", DataTypes::NUM, {Parameter("min",DataTypes::NUM,"Min Value",true,std::make_shared<DataTypeNumber>(DataTypeNumber(0))),
								                              Parameter("max",DataTypes::NUM, "Max Value", true,std::make_shared<DataTypeNumber>(DataTypeNumber(100)))}, "Generates a random integer between [min, max]") {
}

std::shared_ptr<DataType> ActionRand::execute(std::vector<std::shared_ptr<DataType>>& parameters) {
	BigFloat min = parameters[0]->getValue<BigFloat>();
	BigFloat max = parameters[1]->getValue<BigFloat>();
	std::random_device dev;
	std::mt19937 rng(dev());
	// distribution in range [min, max]
	std::uniform_int_distribution<std::mt19937::result_type> distribution(min.toInt(), max.toInt());

	return std::make_shared<DataTypeNumber>(distribution(rng));
}
