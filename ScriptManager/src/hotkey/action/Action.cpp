#include "Action.h"

template <typename R, typename... P>
Action<R,P...>::Action(const std::string_view& name) :
	name(name) {

}
