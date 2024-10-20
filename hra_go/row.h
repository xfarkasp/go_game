#pragma once
#include <iostream>
#include <vector>

class Row {
public:
	Row(const size_t length);
	Row(Row&& other) noexcept;
	Row(const Row& other) noexcept;
	char operator [](const size_t elementPos) const;

	char& operator [](const size_t elementPos);

	Row& operator=(Row&& other) noexcept;
	Row& operator=(const Row& other) noexcept;

	size_t size() const { return m_elements.size(); }

public:
	std::vector<char> m_elements;
};