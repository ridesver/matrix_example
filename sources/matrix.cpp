#include "matrix.hpp"

matrix_t::matrix_t() : elements_{ nullptr }, rows_{ 0 }, collumns_{ 0 }
{
}

matrix_t::matrix_t(matrix_t const & other)
{
	rows_ = other.rows();
	columns_ = other.columns();
	elements_ = new float *[other.rows()];
	for (std::size_t i = 0; i < other.rows(); ++i) 
	{
		elements_[i] = new float[other.columns()];
		for (std::size_t j = 0; j < other.columns(); ++j)
			elements_[i][j] = other.elements_[i][j];
	}
}

matrix_t & matrix_t::operator =(matrix_t const & other)
{
	if (this != &other) {
		for (std::size_t i = 0; i < rows_; ++i)
			delete[] elements_[i];
		delete[] elements_;

		elements_ = new float *[other.rows()];
		for (std::size_t i = 0; i < other.rows(); ++i) 
		{
			elements_[i] = new float[other.columns()];
			for (std::size_t j = 0; j < other.columns(); ++j)
				elements_[i][j] = other.elements_[i][j];
		}
		rows_ = other.rows();
		columns_ = other.columns();
	}
	return *this;
}

matrix_t::~matrix_t()
{
	for (std::size_t i = 0; i < rows_; ++i)
		delete[] elements_[i];
	delete[] elements_;
}

std::size_t matrix_t::rows() const
{
	return rows_;
}

std::size_t matrix_t::columns() const
{
	return columns_;
}

matrix_t matrix_t::operator +(matrix_t const & other) const
{
	matrix_t result;
	result.rows_ = rows_;
	result.columns_ = columns_;
	result.elements_ = new float *[rows_];
	for (std::size_t i = 0; i < rows_; ++i) 
	{
		result.elements_[i] = new float[columns_];
		for (std::size_t j = 0; j < columns_; ++j)
			result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
	}
	return result;
}

matrix_t matrix_t::operator -(matrix_t const & other) const
{
	matrix_t result;
	result.rows_ = rows_;
	result.columns_ = columns_;
	result.elements_ = new float *[rows_];
	for (std::size_t i = 0; i < rows_; ++i) 
	{
		result.elements_[i] = new float[columns_];
		for (std::size_t j = 0; j < columns_; ++j)
			result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
	}
	return result;
}

matrix_t matrix_t::operator *(matrix_t const & other) const
{
	matrix_t result;
	result.rows_ = rows_;
	result.columns_ = other.columns_;
	result.elements_ = new float *[rows_];
	for (std::size_t i = 0; i < rows_; i++) {
		result.elements_[i] = new float[other.columns()];
		for (std::size_t j = 0; j < other.columns(); j++) 
		{
			float temp = 0;
			for (std::size_t k = 0; k < columns_; k++)
				temp += elements_[i][k] * other.elements_[k][j];
			result.elements_[i][j] = temp;
		}
	}
	return result;
}

matrix_t & matrix_t::operator -=(matrix_t const & other)
{
	for (std::size_t i = 0; i < rows_; ++i) 
	{
		for (std::size_t j = 0; j < columns_; ++j)
			elements_[i][j] = elements_[i][j] - other.elements_[i][j];
	}
	return *this;
}

matrix_t & matrix_t::operator +=(matrix_t const & other)
{
	for (std::size_t i = 0; i < rows_; ++i) 
	{
		for (std::size_t j = 0; j < columns_; ++j)
			elements_[i][j] = elements_[i][j] + other.elements_[i][j];
	}
	return *this;
}

matrix_t & matrix_t::operator *=(matrix_t const & other)
{
	matrix_t result;
	result.rows_ = rows_;
	result.columns_ = other.columns_;
	result.elements_ = new float *[rows_];
	for (std::size_t i = 0; i < rows_; i++) 
	{
		result.elements_[i] = new float[other.columns()];
		for (std::size_t j = 0; j < other.columns(); j++) 
		{
			float temp = 0;
			for (std::size_t k = 0; k < columns_; k++) 
				temp += elements_[i][k] * other.elements_[k][j];
			result.elements_[i][j] = temp;
		}
	}
	for (std::size_t i = 0; i < rows_; i++) 
	{
		for (std::size_t j = 0; j < other.columns(); j++)
			elements_[i][j] = result.elements_[i][j];
	}
	return *this;
}

std::istream & matrix_t::read(std::istream & stream)
{
	std::size_t rows;
	std::size_t columns;
	char symbol;

	bool success = true;
	if (stream >> rows && stream >> symbol && symbol == ',' && stream >> columns) 
	{
		float ** elements = new float *[rows];
		for (std::size_t i = 0; success && i < rows; ++i) 
		{
			elements[i] = new float[columns];
			for (std::size_t j = 0; j < columns; ++j) 
			{
				if (!(stream >> elements[i][j])) 
				{
					success = false;
					break;
				}
			}
		}

		if (success) 
		{
			for (std::size_t i = 0; i < rows_; ++i) 
				delete[] elements_[i];
			delete[] elements_;

			rows_ = rows;
			columns_ = columns;
			elements_ = elements;
		}
		else 
		{
			for (std::size_t i = 0; i < rows; ++i)
				delete[] elements[i];
			delete[] elements;
		}
	}
	else {success = false;}

	if (!success) {stream.setstate(std::ios_base::failbit);}

	return stream;
}

std::ostream & matrix_t::write(std::ostream & stream) const
{
	stream << rows_ << ", " << columns_;
	for (std::size_t i = 0; i < rows_; ++i) 
	{
		stream << '\n';
		for (std::size_t j = 0; j < columns_; ++j) 
		{
			stream << elements_[i][j];
			if (j != rows_ - 1)
				stream << ' ';
		}
	}
	return stream;
}
