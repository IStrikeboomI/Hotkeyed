#include "Action.h"

Action::Action(const std::string&& name, const std::vector<Parameter>&& parameters) :
	name(name),
	parameters(parameters) {

}
