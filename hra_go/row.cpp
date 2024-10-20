#include "row.h"

Row::Row(const size_t length)
	:m_elements(length, '.')
{};

Row::Row(Row&& other) noexcept
	:m_elements(std::move(other.m_elements))
{};

Row::Row(const Row& other) noexcept
	:m_elements(other.m_elements)
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

Row& Row::operator=(Row&& other) noexcept {
	if (this != &other) {
		m_elements = std::move(other.m_elements);
	}
	return *this;
}

Row& Row::operator=(const Row& other) noexcept {
	if (this != &other) {
		m_elements = other.m_elements;
	}
	return *this;
}


