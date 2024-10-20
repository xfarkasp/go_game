#pragma once
#include <iostream>
#include <vector>

class Row {
public:
	Row(const size_t length);

	char operator [](const size_t elementPos) const;

	char& operator [](const size_t elementPos);

	size_t size() const { return m_elements.size(); }

public:
	std::vector<char> m_elements;
};