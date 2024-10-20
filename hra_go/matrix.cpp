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

Matrix& Matrix::operator=(Matrix&& other) noexcept {
	if (this != &other) {
		m_rows = std::move(other.m_rows);
	}
	return *this;
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

