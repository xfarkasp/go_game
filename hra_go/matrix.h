#pragma once
#include <iostream>
#include <vector>
#include "row.h"
class Matrix
{
public:
	Matrix(size_t rows, size_t cols);

	Matrix(Matrix&& other) noexcept;
	Matrix(Matrix& other) noexcept;

	Matrix& operator=(Matrix&& other) noexcept;
	Matrix& operator=(const Matrix& other) noexcept;
	bool operator==(const Matrix& other) const;

	Row operator [] (const size_t rowPos) const;

	Row& operator [] (const size_t rowPos);

	friend std::ostream& operator << (std::ostream& stream, Matrix& inputMat);

public:
	std::vector<Row> m_rows;
};