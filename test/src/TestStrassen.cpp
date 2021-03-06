#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <strassen.h>

// template <typename T, int32_t R, int32_t C>
// using strassen::Mat;

namespace testing {

using namespace strassen;
using namespace ::testing;  // gtest namespace

TEST(Initialization, Initializes) {
    Mat<float, 2, 1> floatMat;
    Mat<double, 1, 1> doubleMat;
    Mat<int32_t, 1, 2> intMat;

    SUCCEED();
}

TEST(Initialization, BigMatrices) {
    Mat<double, 1'000, 1'000> bigMat;

    SUCCEED();
}

// TEST(Initialization, InitializerList) {
//     Mat<double, 3, 3> mat{{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};
//     ASSERT_THAT(mat.get(0, 0), DoubleEq(1.1));
//     ASSERT_THAT(mat.get(2, 2), DoubleEq(9.9));
// }

TEST(Multiplication, Multiplies) {
    Mat<double, 4, 2> lhs;
    Mat<double, 2, 5> rhs;

    auto res = lhs * rhs;

    SUCCEED();
}

TEST(Multiplies, DimensionsValid) {
    constexpr int32_t ROW = 4;
    constexpr int32_t COL = 5;
    Mat<double, 4, 2> lhs;
    Mat<double, 2, 5> rhs;

    auto res = lhs * rhs;
    auto dim = res.dim();

    ASSERT_THAT(dim.first, Eq(ROW));
    ASSERT_THAT(dim.second, Eq(COL));
}

/* Correctly doesn't compile
TEST(Multiplies, DifferentTypes) {
    constexpr int32_t ROW = 4;
    constexpr int32_t COL = 5;
    Mat<double, 4, 2> lhs;
    Mat<float, 2, 5> rhs;

    auto res = lhs * rhs;
    FAIL();
}
*/

/* Correctly doesn't compile
TEST(Multiplies, DimensionsInvalid) {
    Mat<double, 4, 2> lhs;
    Mat<double, 3, 5> rhs;

    auto res = lhs * rhs;
    FAIL();
}
*/

class MatFixture : public Test {
public:
    void SetUp() override {
        lhs.set(0, 0, 1);
        lhs.set(1, 0, 2);
        lhs.set(2, 0, 3);
        rhs.set(0, 0, 4);
        rhs.set(0, 1, 5);
    }

protected:
    constexpr static int32_t ROW = 3;
    constexpr static int32_t COL = 2;
    constexpr static int32_t MID = 1;
    Mat<int32_t, ROW, MID> lhs;
    Mat<int32_t, MID, COL> rhs;
};

TEST_F(MatFixture, Multiplies) {
    auto res = lhs * rhs;

    EXPECT_THAT(res.get(0, 0), Eq(4));
    EXPECT_THAT(res.get(0, 1), Eq(5));
    EXPECT_THAT(res.get(1, 0), Eq(8));
    EXPECT_THAT(res.get(1, 1), Eq(10));
    EXPECT_THAT(res.get(2, 0), Eq(12));
    EXPECT_THAT(res.get(2, 1), Eq(15));
}

TEST_F(MatFixture, TransposesDimensions) {
    auto res = lhs.transpose();

    auto dim = res.dim();

    EXPECT_THAT(dim.first, Eq(MID));
    EXPECT_THAT(dim.second, Eq(ROW));
}

TEST_F(MatFixture, TransposesValues) {
    auto res = lhs.transpose();

    EXPECT_THAT(res.get(0, 0), Eq(1));
    EXPECT_THAT(res.get(0, 1), Eq(2));
    EXPECT_THAT(res.get(0, 2), Eq(3));
}

TEST(Access, SetsAndGets) {
    double val = 123.456;
    Mat<double, 2, 2> mat;

    mat.set(0, 0, val);
    ASSERT_THAT(mat.get(0, 0), DoubleEq(val));
}

TEST(Operators, Equality) {
    Mat<int32_t, 2, 2> m{{1, 2}, {3, 4}}, n{{1, 2}, {3, 4}};
    EXPECT_TRUE(m == n);
}

TEST(Operators, Inequality) {
    Mat<int32_t, 2, 2> m{{1, 2}, {3, 4}}, n{{1, 2}, {3, 4}};
    EXPECT_FALSE(m != n);
}

TEST(Operators, Ostream) {
    Mat<int32_t, 2, 2> m{{1, 2}, {3, 4}};
    std::cerr << m;
    SUCCEED();
}

TEST(ReadMe, Runs) {
    strassen::Mat<double, 3, 2> lhs{{1.1, 2.2},  //
                                    {3.3, 4.4},
                                    {5.5, 6.6}};
    strassen::Mat<double, 2, 4> rhs{{11.11, 22.22, 33.33, 44.44},  //
                                    {55.55, 66.66, 77.77, 88.88}};
    strassen::Mat<double, 3, 4> expected{{134.431, 171.094, 207.757, 244.42},  //
                                         {281.083, 366.63, 452.177, 537.724},
                                         {427.735, 562.166, 696.597, 831.028}};
    auto res = lhs * rhs;
    for (int32_t r = 0; r < 3; ++r) {
        for (int32_t c = 0; c < 4; ++c) {
            // doubles can be slightly off and haven't written approx equality function
            EXPECT_THAT(res.get(r, c), DoubleEq(expected.get(r, c)));
        }
    }
    std::cerr << "Values are\n" << res;
    EXPECT_THAT(res.dim().first, Eq(3));
    EXPECT_THAT(res.dim().second, Eq(4));
    std::cerr << "Dimensions are (" << res.dim().first << ',' << res.dim().second << ")\n";

    auto tres = res.transpose();
    EXPECT_THAT(tres.dim().first, Eq(4));
    EXPECT_THAT(tres.dim().second, Eq(3));
    std::cerr << "Dimensions are (" << tres.dim().first << ',' << tres.dim().second << ")\n";
    SUCCEED();
}

}  // namespace testing
