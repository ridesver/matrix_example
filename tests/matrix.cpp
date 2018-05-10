#include <catch.hpp>
#include <sstream>
#include "matrix.hpp"

using namespace std;

TEST_CASE("creating matrix")
{
	matrix_t<int> matrix;
	REQUIRE(matrix.rows() == 0);
	REQUIRE(matrix.collumns() == 0);
}

TEST_CASE("reading matrix")
{
	string input{
		"3, 3\n"
		"1 1 1\n"
		"2 2 2\n"
		"3 3 3" };
	matrix_t<int> matrix;
	istringstream istream{ input };

	REQUIRE(matrix.read(istream));
	REQUIRE(matrix.rows() == 3);
	REQUIRE(matrix.collumns() == 3);

	ostringstream ostream;
	matrix.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("operator =")
{
	string input1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	string input2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	matrix_t<int> matrix_1, matrix_2;

	istringstream istream1{ input1 };
	REQUIRE(matrix_1.read(istream1));

	istringstream istream2{ input2 };
	REQUIRE(matrix_2.read(istream2));

	matrix_1 = matrix_2;
	ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input2 == ostream.str());

}
TEST_CASE("operator +")
{
	string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	string input{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };


	matrix_t<int> matrix_1, matrix_2;
	istringstream istream1{ input_1 };
	istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));
	REQUIRE_NOTHROW(matrix_1 = matrix_1 + matrix_2);

	ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("operator -")
{
	string input_1{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };
	string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	string input{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };


	matrix_t<int> matrix_1, matrix_2;
	istringstream istream1{ input_1 };
	istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));
	REQUIRE_NOTHROW(matrix_1 = matrix_1 - matrix_2);

	ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}
TEST_CASE("operator *")
{
	string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	string input{
		"3, 3\n"
		"6 6 6\n"
		"6 6 6\n"
		"6 6 6" };


	matrix_t<int> matrix_1, matrix_2;
	istringstream istream1{ input_1 };
	istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));
	REQUIRE_NOTHROW(matrix_1 *= matrix_2);

	ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("operator +=")
{
	string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	string input{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };


	matrix_t<int> matrix_1, matrix_2;
	istringstream istream1{ input_1 };
	istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));
	REQUIRE_NOTHROW(matrix_1 += matrix_2);

	ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("operator -=")
{
	string input_1{
		"3, 3\n"
		"3 3 3\n"
		"3 3 3\n"
		"3 3 3" };
	string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	string input{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };


	matrix_t<int> matrix_1, matrix_2;
	istringstream istream1{ input_1 };
	istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));
	REQUIRE_NOTHROW(matrix_1 -= matrix_2);

	ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("operator *=")
{
	string input_1{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	string input_2{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	string input{
		"3, 3\n"
		"6 6 6\n"
		"6 6 6\n"
		"6 6 6" };


	matrix_t<int> matrix_1, matrix_2;
	istringstream istream1{ input_1 };
	istringstream istream2{ input_2 };
	REQUIRE(matrix_1.read(istream1));
	REQUIRE(matrix_2.read(istream2));

	matrix_1 *= matrix_2;
	ostringstream ostream;
	matrix_1.write(ostream);

	REQUIRE(input == ostream.str());
}

TEST_CASE("typetests") {
	string input{
		"3, 3\n"
		"1 1 1\n"
		"2 2 2\n"
		"3 3 3" };

	matrix_t<int> matrix;
	matrix_t<float> matrix1;
	matrix_t<double> matrix2;
	istringstream istream{ input };
	istringstream istream1{ input };
	istringstream istream2{ input };

	REQUIRE(matrix.read(istream));
	REQUIRE(matrix.rows() == 3);
	REQUIRE(matrix.collumns() == 3);
	REQUIRE(matrix1.read(istream1));
	REQUIRE(matrix1.rows() == 3);
	REQUIRE(matrix1.collumns() == 3);
	REQUIRE(matrix2.read(istream2));
	REQUIRE(matrix2.rows() == 3);
	REQUIRE(matrix2.collumns() == 3);

	ostringstream ostream;
	matrix.write(ostream);
	ostream << '\n';
	matrix1.write(ostream);
	ostream << '\n';
	matrix2.write(ostream);

	REQUIRE(input + '\n' + input + '\n' + input == ostream.str());
}
