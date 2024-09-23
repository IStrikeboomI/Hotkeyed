#include "Action.h"

Action::Action(const std::string&& name, const std::vector<Parameter>&& parameters, const std::string& returnValue) :
	name(name),
	parameters(parameters),
	returnValue(returnValue) {

}
