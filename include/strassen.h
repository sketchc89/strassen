#pragma once

#include <array>
#include <utility>

namespace strassen {
template <typename T, int32_t R, int32_t C>
class Mat {
    static_assert(R > 0 && C > 0, "Dimensions must be positive");

public:
    /*! @brief default constructor */
    Mat() = default;
    // rule of 5
    /*! @brief copy constructor */
    Mat(const Mat& other) = default;
    /*! @brief copy assignment */
    Mat& operator=(const Mat& other) = default;
    /*! @brief move constructor */
    Mat(Mat&& other) = default;
    /*! @brief move assignment */
    Mat& operator=(Mat&& other) = default;
    /* !@brief default destructor */
    virtual ~Mat() = default;

    template <typename _T, int32_t R2, int32_t C2>
    friend class Mat;

    template <typename _T = T, int32_t R1 = R, int32_t C1 = C, int32_t R2, int32_t C2>
    Mat<_T, R1, C2> operator*(const Mat<_T, R2, C2>& rhs);

    bool operator==(const Mat& rhs);
    bool operator!=(const Mat& rhs);

    T get(int32_t row, int32_t col) const;
    void set(int32_t row, int32_t col, T val);
    std::pair<int32_t, int32_t> dim() const noexcept;


private:
    std::array<std::array<T, C>, R> _data;
};

/*! @brief tranposes matrix
 *  @details creates a new matrix where the rows and columns are flipped such that
 *           a value previously at r, c will now be at c, r
 */
template <typename T, int32_t R, int32_t C>
static Mat<T, C, R> transpose(const Mat<T, R, C>& mat);

}  // namespace strassen


/*! @brief multiplication operator for matrices
 *  @details creates a new matrix with dimensions equal to the #rows of the first operand and the # of columns of the second operand */
// template <typename T, int32_t R1, int32_t C1, int32_t R2, int32_t C2>
// strassen::Mat<T, R1, C2> operator*(const strassen::Mat<T, R1, C1>& lhs, const strassen::Mat<T, R2, C2>& rhs);


#include <strassen.hpp>
