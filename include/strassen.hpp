/*! implements strassen.h DO NOT include directly */

#include <cassert>

namespace strassen {

template <typename T, int32_t R, int32_t C>
template <typename _T, int32_t R1, int32_t C1, int32_t R2, int32_t C2>
Mat<_T, R1, C2> Mat<T, R, C>::operator*(const Mat<_T, R2, C2>& rhs) {
    static_assert(C1 == R2, "Matrix operands are invalid for multiplication.");

    Mat<T, R1, C2> res;
    for (int32_t i = 0; i < R1; ++i) {
        for (int32_t j = 0; j < C2; ++j) {
            for (int32_t k = 0; k < C1; ++k) {
                res._data[i][j] += _data[i][k] * rhs._data[k][j];
            }
        }
    }
    return res;
}

template <typename T, int32_t R, int32_t C>
bool Mat<T, R, C>::operator==(const Mat<T, R, C>& rhs) {
    for (int32_t row = 0; row < R; ++row) {
        for (int32_t col = 0; col < C; ++col) {
            if (_data[row][col] != rhs._data[row][col]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T, int32_t R, int32_t C>
bool Mat<T, R, C>::operator!=(const Mat<T, R, C>& rhs) {
    return !operator==(rhs);
}

template <typename T, int32_t R, int32_t C>
std::ostream& operator<<(std::ostream& os, const strassen::Mat<T, R, C>& mat) {
    for (int32_t row = 0; row < R; ++row) {
        for (int32_t col = 0; col < C; ++col) {
            os << mat.get(row, col) << ',';
        }
        os << '\n';
    }
    return os;
}

template <typename T, int32_t R, int32_t C>
Mat<T, R, C>::Mat()
        : _data{} {}

template <typename T, int32_t R, int32_t C>
Mat<T, R, C>::Mat(std::initializer_list<std::initializer_list<T>> l) {
    assert(l.size() == R && begin(l)->size() == C);
    auto lIt = begin(l);
    auto aIt = begin(_data);
    for (; lIt != end(l) && aIt != end(_data); ++lIt, ++aIt) {
        std::copy(lIt->begin(), lIt->end(), aIt->begin());
    }
}

template <typename T, int32_t R, int32_t C>
T Mat<T, R, C>::get(int32_t row, int32_t col) const {
    assert(row >= 0 && row < R && col >= 0 && col < C);
    return _data[row][col];
}

template <typename T, int32_t R, int32_t C>
void Mat<T, R, C>::set(int32_t row, int32_t col, T val) {
    assert(row >= 0 && row < R && col >= 0 && col < C);
    _data[row][col] = val;
}

template <typename T, int32_t R, int32_t C>
std::pair<int32_t, int32_t> Mat<T, R, C>::dim() const noexcept {
    return std::make_pair(R, C);
}

template <typename T, int32_t R, int32_t C>
Mat<T, C, R> Mat<T, R, C>::transpose() {
    Mat<T, C, R> res;
    for (int32_t row = 0; row < R; ++row) {
        for (int32_t col = 0; col < C; ++col) {
            res._data[col][row] = _data[row][col];
        }
    }
    return res;
}

}  // namespace strassen
