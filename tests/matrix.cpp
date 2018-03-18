#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}
TEST_CASE("=")
{
	std::string input1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	std::string input2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	matrix_t matrix_1, matrix_2;

	std::istringstream istream1{ input1 };
	REQUIRE(matrix_1.read(istream1));

	std::istringstream istream2{ input2 };
	REQUIRE(matrix_2.read(istream2));

	matrix_1 = matrix_2;
	std::ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input2 == ostream.str());

}
TEST_CASE("Add")
{
	std::string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	std::string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string input{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };


	matrix_t matrix_1, matrix_2;
	std::istringstream istream1{ input_1 };
	std::istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));

	std::ostringstream ostream;
	(matrix_1 + matrix_2).write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("Sub")
{
	std::string input_1{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };
	std::string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string input{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };


	matrix_t matrix_1, matrix_2;
	std::istringstream istream1{ input_1 };
	std::istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));

	std::ostringstream ostream;
	(matrix_1 - matrix_2).write(ostream);

	REQUIRE(input == ostream.str());
}
TEST_CASE("Mul")
{
	std::string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	std::string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string input{
		"3, 3\n"
		"6 6 6\n"
		"6 6 6\n"
		"6 6 6" };


	matrix_t matrix_1, matrix_2;
	std::istringstream istream1{ input_1 };
	std::istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));

	std::ostringstream ostream;
	(matrix_1 * matrix_2).write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("+=")
{
	std::string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	std::string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string input{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };


	matrix_t matrix_1, matrix_2;
	std::istringstream istream1{ input_1 };
	std::istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));

	matrix_1 += matrix_2;
	std::ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("-=")
{
	std::string input_1{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };
	std::string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string input{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };


	matrix_t matrix_1, matrix_2;
	std::istringstream istream1{ input_1 };
	std::istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));

	matrix_1 -= matrix_2;
	std::ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("*=")
{
	std::string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	std::string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string input{
		"3, 3\n"
		"6 6 6\n"
		"6 6 6\n"
		"6 6 6" };


	matrix_t matrix_1, matrix_2;
	std::istringstream istream1{ input_1 };
	std::istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));

	matrix_1 *= matrix_2;
	std::ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}
TEST_CASE("=")
{
	std::string input1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	std::string input2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	matrix_t matrix_1, matrix_2;

	std::istringstream istream1{ input1 };
	REQUIRE(matrix_1.read(istream1));

	std::istringstream istream2{ input2 };
	REQUIRE(matrix_2.read(istream2));

	matrix_1 = matrix_2;
	std::ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input2 == ostream.str());
}
