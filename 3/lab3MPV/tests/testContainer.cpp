#include "Matrix.h"
#include "catch2/catch_all.hpp"

TEST_CASE("Matrix constructors") {
    SECTION("listInit") {
    Matrix<int> matrix{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
    Matrix<int> matrix7 = matrix;
        REQUIRE(matrix.size() == 4);
        REQUIRE(matrix[0][0] == 4);
        Matrix<int> matrix2 = matrix;
        Matrix<int> matrix4(matrix);
        Matrix<int> matrix3 = std::move(matrix);
        Matrix<char> matrix5{3, 2};
        REQUIRE(matrix2.size() == 4);
        REQUIRE(matrix2[0][0] == 4);
        REQUIRE(matrix3.size()==4);
        REQUIRE(matrix3[0][0] == 4);
        REQUIRE(matrix4.size()==4);
        REQUIRE(matrix4[0][0] == 4);
        REQUIRE(matrix5.size()==6);
        Matrix<int>matrix8{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
        matrix8 = std::move(matrix7);
        REQUIRE(matrix8.size() == 4);
        Matrix<int> matrix9{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
        matrix9 = matrix3;
        REQUIRE(matrix9.size() == 4);


    }
    SECTION("rows&cols" ) {
        Matrix<int> matrix{2, 2};
        REQUIRE(matrix.width()==2);
        REQUIRE(matrix.height()==2);
        int s =matrix.max_size();
        REQUIRE(s==matrix.max_size());
    }
    SECTION("default" ) {
        Matrix<int> matrix;
        REQUIRE(matrix.empty());
    }
    SECTION("prekoli") {
        std::vector<int> prekoli{4, 1, 2, 3};
        Matrix<int> matrix{2, 2 , prekoli.begin(), prekoli.end()};
        REQUIRE(matrix.size()==4);
        REQUIRE(matrix[0][0] == 4);
    }
    SECTION("def") {
        size_t s=2;
        size_t f=2;
        Matrix<int> matrix{s, f};
        REQUIRE(matrix.size()==s*f);
    }
}
TEST_CASE("operators") {
    SECTION("resize") {
        Matrix<int> matrix{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
        REQUIRE(matrix.size() == 4);
        matrix.resize(4, 2);
        REQUIRE(matrix.size() == 8);
    }
    SECTION("swap") {
        Matrix<int> matrix{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
        Matrix<int> matrix2 = {2, 2, std::initializer_list<int>{1, 4, 2, 3}};
        matrix.swap(matrix2);
        REQUIRE(matrix[0][0] == 1);
        swap(matrix, matrix2);
        REQUIRE(matrix[0][0] == 4);
    }
    SECTION("==") {
        Matrix<int> matrix{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
        Matrix<int> matrix2 = {2, 2, std::initializer_list<int>{4, 1, 2, 3}};
        REQUIRE(matrix == matrix2);
    }
    SECTION("data") {
        Matrix<int> matrix{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
        const Matrix<int> matrix2{2, 2, std::initializer_list<int>{4, 1, 2, 3}};

        auto data = matrix.data();
        auto data2 = matrix2.data();
        REQUIRE(matrix2[0][0]==4);
        REQUIRE(true);
    }
}
TEST_CASE("iterators") {
    Matrix<int> matrix{2, 2, std::initializer_list<int>{4, 1, 2, 3}};
    SECTION("iterators begin/end") {
        auto it = matrix.cbegin();
        auto it2 = matrix.cend();
        REQUIRE(*it == 4);
        REQUIRE(it2 == matrix.cend());
        auto it3 = matrix.begin();
        auto it4 = matrix.end();
        REQUIRE(*it3 == 4);
    }

    SECTION("itera inc") {
        auto it = matrix.begin();
        REQUIRE(*(++it)==1);
        REQUIRE(*(it++)==1);
    }
    SECTION("iterators dec") {
        auto it = matrix.begin();
        it++;
        REQUIRE(*(--it)==4);
        it++;
        REQUIRE(*(it--)==1);
    }
    SECTION("iterators +=-") {
        auto it = matrix.begin();
        it+=2;
        REQUIRE(*(it)==2);
        it-=1;
        REQUIRE(*(it)==1);
    }
    SECTION("+") {
        auto it = matrix.begin();
        auto it2= it + 1;
        REQUIRE(*(it2)==1);
        auto it3 = 1+it2;
        REQUIRE(*(it3)==2);
    }
    SECTION("-") {
        auto it = matrix.begin();
        it++;
        REQUIRE(*(it-1)==4);
    }
    SECTION("[]") {
        auto it = matrix.begin();
        REQUIRE(it[2]==2);
    }
    SECTION("<=>") {
        auto it = matrix.begin();
        auto it2 = matrix.begin();
        it2++;
        REQUIRE(it2>it);
    }
    SECTION("->") {
        auto it = matrix.begin();
        auto a= it.operator->();
        REQUIRE(*a==4);
    }
    SECTION("") {
        auto it = matrix.begin();
        auto it2 = matrix.begin();
        REQUIRE(it==it2);
    }
    SECTION("pprisvoiva") {
        MatrixIterator<int, true> it = matrix.begin();
        auto it2 = matrix.begin();
        it2++;
        it = it2;
        REQUIRE(*it==1);
    }
    SECTION("constr") {
        MatrixIterator<int, false> it = matrix.begin();
        MatrixIterator<int,true > it2 = it;
        REQUIRE(*it2==4);
    }

}
