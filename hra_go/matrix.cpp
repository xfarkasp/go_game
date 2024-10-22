#include "matrix.h"

Matrix::Matrix(size_t rows, size_t cols)
{
	for (size_t i = 0; i < rows; i++)
	{
		m_rows.push_back(Row(cols));
	}
};

Matrix::Matrix(Matrix&& other) noexcept
	: m_rows(std::move(other.m_rows)) {};

Matrix::Matrix(Matrix& other) noexcept
	: m_rows(other.m_rows) {};

Matrix& Matrix::operator=(Matrix&& other) noexcept {
	if (this != &other) {
		m_rows = std::move(other.m_rows);
	}
	return *this;
}

Matrix& Matrix::operator=(const Matrix& other) noexcept {
	if (this != &other) {
		m_rows = other.m_rows;
	}
	return *this;
}

bool Matrix::operator==(const Matrix& other) const
{
	if (this->m_rows.size() != other.m_rows.size())
	{
		return false;
	}
	for (size_t row = 0; row < this->m_rows.size(); row++)
	{
		for (size_t element = 0; element < this->m_rows[0].size(); element++)
		{
			if (this->m_rows[row][element] != other[row][element])
			{
				return false;
			}
		}
	}
	return true;
}

Row Matrix::operator [] (const size_t rowPos) const
{
	if (m_rows.size() <= rowPos)
		throw std::runtime_error("out of range");
	return m_rows[rowPos];
}

Row& Matrix::operator [] (const size_t rowPos)
{
	if (m_rows.size() <= rowPos)
		throw std::runtime_error("out of range");
	return m_rows[rowPos];
}

std::ostream& operator << (std::ostream& stream, Matrix& inputMat)
{
	for (size_t i = 0; i < inputMat.m_rows.size(); i++)
	{
		if (i == 0)
		{
			stream << "  ";
			for (size_t j = 0; j < inputMat.m_rows[0].size(); j++)
			{
				stream << j << " ";
			}
			stream << "\n";
		}
		stream << i << " ";
		for (size_t j = 0; j < inputMat.m_rows[0].size(); j++)
		{
			stream << inputMat[i][j] << " ";
		}
		stream << std::endl;
	}
	stream << std::endl;
	return stream;
}