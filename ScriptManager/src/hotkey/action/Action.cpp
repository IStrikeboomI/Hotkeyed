#include "Action.h"

template <Parameter R, Parameter... P>
Action<R,P...>::Action(const std::string_view& name) :
	name(name) {

}
