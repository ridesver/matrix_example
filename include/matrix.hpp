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
template <typename T> matrix_t<T>::matrix_t( matrix_t const & other )
{
	    elements_= new T *[other.rows()];
	    for (size_t i = 0; i < other.rows(); ++i) 
	    {
			elements_[i] = new T[other.collumns()];
			for (size_t j = 0; j < other.collumns(); ++j)
				elements_[i][j] = other.elements_[i][j];
	    }
		
	    rows_ = other.rows();
            collumns_=other.collumns();
}
template <typename T> matrix_t<T> & matrix_t<T>::operator =( matrix_t const & other )
{   
	if (this!=&other)
	{
           if(elements_!=nullptr){
	           for (size_t i = 0; i < rows_; ++i)
		      delete[] elements_[i];
               delete[] elements_;
        }
            elements_ = new T *[other.rows()];
	    for (size_t i = 0; i < other.rows(); ++i) 
	    {
			elements_[i] = new T[other.collumns()];
			for (size_t j = 0; j < other.collumns(); ++j)
				elements_[i][j] = other.elements_[i][j];
	    }
	    rows_ = other.rows();
            collumns_ = other.collumns();
        }
	return *this;
}
template <typename T> matrix_t<T>::~matrix_t()
{
	if(elements_!=nullptr){
          for (size_t i = 0; i < rows_; ++i)
              delete[] elements_[i];
           delete[] elements_;
        }
}
template <typename T> size_t matrix_t<T>::rows() const
{
    return rows_;
}
template <typename T> size_t matrix_t<T>::collumns() const
{
    return collumns_;
}
template <typename T> matrix_t<T> matrix_t<T>::operator +( matrix_t const & other ) const
{
       if(collumns_ != other.collumns() || rows_ != other.rows()
	  {throw "wrong matrix";}
	matrix_t result;
	result.elements_= new T*[rows_];
	for (size_t i = 0; i < rows_; ++i) 
	  {
		result.elements_[i] = new T[collumns_];
	   	for (size_t j = 0; j < collumns_; ++j)
			result.elements_[i][j] = elements_[i][j]+other.elements_[i][j];
	}
	
        result.rows_=rows_;
        result.collumns_=collumns_;
	return result;
}
template <typename T> matrix_t<T> matrix_t<T>::operator -( matrix_t const & other ) const
{
        if(collumns_ != other.collumns() || rows_ != other.rows())
	{throw "wrong matrix";}
        matrix_t result;
	result.elements_= new T*[rows_];
	for (size_t i = 0; i < rows_; ++i) 
	{
		result.elements_[i] = new T[collumns_];
	   	for (size_t j = 0; j < collumns_; ++j)
			result.elements_[i][j] = elements_[i][j]-other.elements_[i][j];
	}
        result.rows_=rows_;
        result.collumns_=collumns_;
	return result;
}
template <typename T> matrix_t<T> matrix_t<T>::operator *( matrix_t const & other ) const
{
        if(collumns_ != other.rows())
	{throw  "wrong matrix"; }
        matrix_t result;
	result.elements_=new T*[rows_];
        for (size_t i = 0; i < rows_; i++)
	{
                result.elements_[i]=new T[other.collumns()];
		for (size_t j = 0; j < other.collumns(); j++) 
		{
			float y = 0;
			for (size_t z = 0; z < collumns_; z++)
				y += elements_[i][z] * other.elements_[z][j];
			result.elements_[i][j] = y;
		}
        }  
    
        result.rows_=rows_;
        result.collumns_=other.collumns_;
	return result;
}
template <typename T> matrix_t<T> & matrix_t<T>::operator -=( matrix_t const & other )
{  
     if(collumns_ != other.collumns() || rows_ != other.rows())
     {throw "wrong matrix";}
	for (size_t i = 0; i < rows_; ++i) 
	{	
	   	for (size_t j = 0; j < collumns_; ++j)
			elements_[i][j] = elements_[i][j]-other.elements_[i][j];
	}
	return *this;
}
template <typename T> matrix_t<T> & matrix_t<T>::operator +=( matrix_t const & other )
{
	  if(collumns_ != other.collumns() || rows_ != other.rows())
	  {throw "wrong matrix";}
	  for (size_t i = 0; i < rows_; ++i) 
	  {	
	   	for (size_t j = 0; j < collumns_; ++j) 
		{elements_[i][j] = elements_[i][j]+other.elements_[i][j]; }
	  }
	return *this;
}
template <typename T> matrix_t<T> & matrix_t<T>::operator *=( matrix_t const & other )
{
	*this=*this * other;
	return *this;
}
template <typename T> istream & matrix_t<T>::read( istream & stream )
{
    size_t rows;
    size_t collumns;
    char symbol;
    
    bool success = true;
    if( stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns ) 
    {
        T ** elements = new T*[ rows ];
        for(size_t i = 0; success && i < rows; ++i ) 
	{
            elements[ i ] = new T[ collumns ];
            for(size_t j = 0; j < collumns; ++j ) 
	    {
                if( !( stream >> elements[ i ][ j ] ) ) 
		{
                    success = false;
                    break;
                }
            }
        }
        
        if( success ) 
	{
            for( size_t i = 0; i < rows_; ++i )
                delete [] elements_[ i ];
            delete [] elements_;
            
            rows_ = rows;
            collumns_ = collumns;
            elements_ = elements;
        }
        else 
	{
            for(size_t i = 0; i < rows; ++i )
                delete [] elements[ i ];
            delete [] elements;
        }
    }
    else {success = false;}
   
    if( !success )
        stream.setstate( ios_base::failbit );
    
return stream;
}
template <typename T> ostream & matrix_t<T>::write(ostream & stream ) const
{
    stream << rows_ << ", " << collumns_;
    for( size_t i = 0; i < rows_; ++i ) 
    {
        stream << '\n';
        for( size_t j = 0; j < collumns_; ++j ) 
	{
            stream << elements_[ i ][ j ];
            if( j != rows_ - 1 ) 
                stream << ' ';
        }
    }
    
	return stream;
}
