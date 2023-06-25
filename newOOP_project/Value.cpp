#include "Value.h"
#include "Pair.h"
#include "Vector.hpp"
#include <iostream>
#include <fstream>

void Value::printTabs(std::ostream& os, unsigned tabsCount) const
{
	for (size_t i = 0; i < tabsCount; i++)
		os << "  ";
}