#include <stdlib.h>
#include <iostream>
#include "Utilities.h"

namespace Utilities
{
	CharSequence::CharSequence(char* items)
	{
		this->items = items;
	}

	CharSequence::CharSequence(std::string items)
	{
		this->items = items.c_str();
	}

	size_t CharSequence::length()
	{
		return strlen(this->items);
	}

	std::string CharSequence::toString()
	{
		return std::string(this->items);
	}

	std::string CharSequence::join(std::string separator)
	{
		std::string result;

		result += *this->items;

		for (unsigned int i = 1; i < length(); ++i)
		{
			result += separator;
			result += this->items[i];
		}

		return result;
	}

	char CharSequence::operator[](size_t i)
	{
		if (i >= length())
		{
			// TODO Throw exception instead
			std::cout << "ERROR: Index out of bounds";
			return this->items[0];
		}

		return this->items[i];
	}
}