#pragma once

#include <array>
#include <initializer_list>
#include <ostream>
#include <utility>

namespace strassen {
template <typename T, int32_t R, int32_t C>
class Mat {
    static_assert(R > 0 && C > 0, "Dimensions must be positive");

public:
    /*! @brief default constructor, zero initializes */
    Mat();
    /*! @brief initialize with 2d initializer list
     *  @code
     *  strassen::Mat<int32_t, 2, 2> mat{{1, 2}, {3, 4}};
     *  @endcode
     */
    Mat(std::initializer_list<std::initializer_list<T>> l);

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

    /* @brief friend matrix with different template parameters
     * @details used to allow member functions to directly access _data rather than
     *          use getters, for example when multiplying
     */
    template <typename _T, int32_t R2, int32_t C2>
    friend class Mat;

    /*! @brief matrix multiplication
     *  @details compile time check for invalid multiplication.
     *           only allows for same type multiplication since it's ambiguous how to cast
     */
    template <typename _T = T, int32_t R1 = R, int32_t C1 = C, int32_t R2, int32_t C2>
    Mat<_T, R1, C2> operator*(const Mat<_T, R2, C2>& rhs);
    /*! @brief values in matrix are exactly equal to one another */
    bool operator==(const Mat& rhs);
    /*! @brief values in matrix are not exactly equal to one another */
    bool operator!=(const Mat& rhs);
    /*! @brief gets the value stored at row and column */
    T get(int32_t row, int32_t col) const;
    /*! @brief sets the row and column given to val */
    void set(int32_t row, int32_t col, T val);
    /*! @brief returns number of rows and columns as a pair */
    std::pair<int32_t, int32_t> dim() const noexcept;

    /*! @brief tranposes matrix
     *  @details creates a new matrix where the rows and columns are flipped such that
     *           a value previously at r, c will now be at c, r
     */
    Mat<T, C, R> transpose();


private:
    std::array<std::array<T, C>, R> _data;
};

}  // namespace strassen

template <typename T, int32_t R, int32_t C>
std::ostream& operator<<(std::ostream& os, const strassen::Mat<T, R, C>& mat);


// implementation of class
#include <strassen.hpp>
