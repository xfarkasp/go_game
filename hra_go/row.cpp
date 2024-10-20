#include "row.h"

Row::Row(const size_t length)
	:m_elements(length, '.')
{};

char Row::operator [](const size_t elementPos) const
{
	if (m_elements.size() <= elementPos)
		throw std::runtime_error("out of range");
	return m_elements[elementPos];
}

char& Row::operator [](const size_t elementPos)
{
	if (m_elements.size() <= elementPos)
		throw std::runtime_error("out of range");
	return m_elements[elementPos];
}


