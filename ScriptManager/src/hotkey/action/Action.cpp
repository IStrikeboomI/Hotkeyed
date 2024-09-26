#include "Action.h"

Action::Action(const std::string_view& name, const std::vector<Parameter>&& parameters, const std::string_view& returnValue) :
	name(name),
	parameters(parameters),
	returnValue(returnValue) {

}
