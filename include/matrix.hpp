#include <iostream>
using namespace std;

template <typename T> class matrix_t 
{
	private:
	T ** elements_;
	size_t rows_;
	size_t collumns_;
	public:
	matrix_t();
	matrix_t(matrix_t const & other);
	matrix_t & operator =(matrix_t const & other);
	~matrix_t();

	size_t rows() const;
	size_t collumns() const;

	matrix_t operator +(matrix_t const & other) const;
	matrix_t operator -(matrix_t const & other) const;
	matrix_t operator *(matrix_t const & other) const;

	matrix_t & operator -=(matrix_t const & other);
	matrix_t & operator +=(matrix_t const & other);
	matrix_t & operator *=(matrix_t const & other);

	istream & read(istream & stream);
	ostream & write(ostream  & stream) const;
};

template <typename T> matrix_t<T>::matrix_t() : elements_{ nullptr }, rows_{ 0 }, collumns_{ 0 }
{
}

template <typename T> matrix_t<T>::matrix_t(matrix_t const & other)
{
	rows_ = other.rows();
	collumns_ = other.collumns();
	elements_ = new T *[other.rows()];
	for (size_t i = 0; i < other.rows(); ++i) {
		elements_[i] = new T[other.collumns()];
		for (size_t j = 0; j < other.collumns(); ++j) {
			elements_[i][j] = other.elements_[i][j];
		}
	}
}

template <typename T> matrix_t<T> & matrix_t<T>::operator =(matrix_t const & other)
{
	if (this != &other) {
		for (size_t i = 0; i < rows_; ++i) {
			delete[] elements_[i];
		}
		delete[] elements_;

		elements_ = new T *[other.rows()];
		for (size_t i = 0; i < other.rows(); ++i) {
			elements_[i] = new T[other.collumns()];
			for (size_t j = 0; j < other.collumns(); ++j) {
				elements_[i][j] = other.elements_[i][j];
			}
		}
		rows_ = other.rows();
		collumns_ = other.collumns();
	}
	return *this;
}

template <typename T> matrix_t<T>::~matrix_t()
{
	for (size_t i = 0; i < rows_; ++i) {
		delete[] elements_[i];
	}
	delete[] elements_;
}

template <typename T> size_t matrix_t<T>::rows() const
{
	return rows_;
}

template <typename T> size_t matrix_t<T>::collumns() const
{
	return collumns_;
}

template <typename T> matrix_t<T> matrix_t<T>::operator +(matrix_t const & other) const
{
	if (rows_ != other.rows_ || collumns_ != other.collumns_) {
		throw exception("Error: columns and/or rows mismatch");
	}
	matrix_t result;
	result.rows_ = rows_;
	result.collumns_ = collumns_;
	result.elements_ = new T *[rows_];
	for (size_t i = 0; i < rows_; ++i) {
		result.elements_[i] = new T[collumns_];
		for (size_t j = 0; j < collumns_; ++j) {
			result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
		}
	}
	return result;
}

template <typename T> matrix_t<T> matrix_t<T>::operator -(matrix_t const & other) const
{
	if (rows_ != other.rows_ || collumns_ != other.collumns_) {
		throw exception("Error: columns and/or rows mismatch");
	}
	matrix_t result;
	result.rows_ = rows_;
	result.collumns_ = collumns_;
	result.elements_ = new T *[rows_];
	for (std::size_t i = 0; i < rows_; ++i) {
		result.elements_[i] = new T[collumns_];
		for (std::size_t j = 0; j < collumns_; ++j) {
			result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
		}
	}
	return result;
}

template <typename T> matrix_t<T> matrix_t<T>::operator *(matrix_t const & other) const
{
	if (collumns_ != other.rows_) {
		throw exception("Error: columns != rows");
	}
	matrix_t result;
	result.rows_ = rows_;
	result.collumns_ = other.collumns_;
	result.elements_ = new T *[rows_];
	for (size_t i = 0; i < rows_; i++) {
		result.elements_[i] = new T [other.collumns()];
		for (size_t j = 0; j < other.collumns(); j++) {
			T temp = 0;
			for (size_t k = 0; k < collumns_; k++) {
				temp += elements_[i][k] * other.elements_[k][j];
			}
			result.elements_[i][j] = temp;
		}
	}
	return result;
}

template <typename T> matrix_t<T> & matrix_t<T>::operator -=(matrix_t const & other)
{
	if (rows_ != other.rows_ || collumns_ != other.collumns_) {
		throw exception("Error: columns and/or rows mismatch");
	}
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < collumns_; ++j) {
			elements_[i][j] = elements_[i][j] - other.elements_[i][j];
		}
	}
	return *this;
}

template <typename T> matrix_t<T> & matrix_t<T>::operator +=(matrix_t const & other)
{
	if (rows_ != other.rows_ || collumns_ != other.collumns_) {
		throw exception("Error: columns and/or rows mismatch");
	}
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < collumns_; ++j) {
			elements_[i][j] = elements_[i][j] + other.elements_[i][j];
		}
	}
	return *this;
}

template <typename T> matrix_t<T> & matrix_t<T>::operator *=(matrix_t const & other)
{
	if (collumns_ != other.rows_) {
		throw exception("Error: columns != rows");
	}
	matrix_t result;
	result.rows_ = rows_;
	result.collumns_ = other.collumns_;
	result.elements_ = new T *[rows_];
	for (size_t i = 0; i < rows_; i++) {
		result.elements_[i] = new T[other.collumns()];
		for (size_t j = 0; j < other.collumns(); j++) {
			T temp = 0;
			for (size_t k = 0; k < collumns_; k++) {
				temp += elements_[i][k] * other.elements_[k][j];
			}
			result.elements_[i][j] = temp;
		}
	}
	for (size_t i = 0; i < rows_; i++) {
		for (size_t j = 0; j < other.collumns(); j++) {
			elements_[i][j] = result.elements_[i][j];
		}
	}
	return *this;
}

template <typename T> istream & matrix_t<T>::read(istream & stream)
{
	size_t rows;
	size_t collumns;
	char symbol;
	bool success = true;
	if (stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns) {
		T ** elements = new T *[rows];
		for (size_t i = 0; success && i < rows; ++i) {
			elements[i] = new T[collumns];
			for (size_t j = 0; j < collumns; ++j) {
				if (!(stream >> elements[i][j])) {
					success = false;
					break;
				}
			}
		}

		if (success) {
			for (size_t i = 0; i < rows_; ++i) {
				delete[] elements_[i];
			}
			delete[] elements_;

			rows_ = rows;
			collumns_ = collumns;
			elements_ = elements;
		}
		else {
			for (size_t i = 0; i < rows; ++i) {
				delete[] elements[i];
			}
			delete[] elements;
		}
	}
	else {
		throw exception("Error: incorrect matrix");
	}
	return stream;
}

template <typename T> ostream & matrix_t<T>::write(ostream & stream) const
{
	stream << rows_ << ", " << collumns_;
	for (size_t i = 0; i < rows_; ++i) {
		stream << '\n';
		for (size_t j = 0; j < collumns_; ++j) {
			stream << elements_[i][j];
			if (j != rows_ - 1) {
				stream << ' ';
			}
		}
	}

	return stream;
}
