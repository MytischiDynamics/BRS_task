#include "Geometry.h"
#include <utility>
#include <cmath>
#include <iostream>

template<typename T>
Line<T>::Line()
{
    start_pt_ = std::make_pair<T, T>(0.0, 0.0);
    stop_pt_ = std::make_pair<T, T>(1.0, 1.0);

    c_ = 0.0;
    a_ = -1.0;
    b_ = 1.0;
}

template<typename T>
Line<T>::Line(const T x1, const T y1, const T x2, const T y2)
{
    start_pt_ = std::make_pair(x1, y1);
    stop_pt_ = std::make_pair(x2, y2);

    c_ = 1.0;
    if (y1 == y2) {
        c_ = -y1;
        a_ = 0.0;
        b_ = 1.0;
    } else if (x1 == x2) {
        c_ = -x1;
        a_ = 1.0;
        b_ = 0.0;
    } else if (y2 * x1 - y1 * x2 != 0.0) {
        if (x1 != 0.0) {
            c_ = 1.0;
            b_ = c_ * (x2 - x1) / (y2 * x1 - y1 * x2);
            a_ = -((b_ * y1 + c_) / x1);
        } else if (y1 != 0.0) {
            c_ = 1.0;
            a_ = c_ * (y2 - y1) / (x2 * y1 - x1 * y2);
            b_ = -(a_ * x1 + c_) / y1;
        }
    } else {
        c_ = 0.0;
        a_ = 1.0;
        b_ = -x2 / y2;
    }

    normalize();
}

template<typename T>
void Line<T>::normalize()
{
    T k = 1.0 / std::sqrt(a_ * a_ + b_ * b_);
    a_ *= k;
    b_ *= k;
    c_ *= k;
}

template <typename T>
T Line<T>::calc_dist(std::pair<T, T> &pt)
{
    std::cout << std::abs(a_ * pt.first + b_ * pt.second + c_) << std::endl;
    return std::abs(a_ * pt.first + b_ * pt.second + c_);
}

template <typename T>
T Line<T>::calc_squared_dist(std::pair<T, T> &pt)
{
    T dist = a_ * pt.first + b_ * pt.second + c_;
    return dist * dist;
}

template <typename T>
std::pair<T, T> Line<T>::intersect(Line<T>& other)
{
    T x_ret = 0.0;
    T y_ret = 0.0;

    T a1 = a_;
    T b1 = b_;
    T c1 = c_;

    T a2 = other.a_;
    T b2 = other.b_;
    T c2 = other.c_;

    //std::cout << "Intersecting " << a1 << " " << b1 << " " << c1 << " and " << a2 << " " << b2 << " " << c2 << std::endl;

    if ((a1 == a2) && (b1 == b2)) {
        /*far point that cannot fall inside line*/
        x_ret = 1000000.0;
        y_ret = 1000000.0;
    } else if (b1 != 0.0) {
        x_ret = (b2 * c1 - c2 * b1) / (a2 * b1 - b2 * a1);
        y_ret = -(c1 + a1 * x_ret) / b1;
    } else if (a1 != 0.0) {
        y_ret = (a2 * c1 - a1 * c2) / (b2 * a1 - a2 * b1);
        x_ret = -(b1 * y_ret + c1) / a1;
    }

    //std::cout << "Result (" << x_ret << ", " << y_ret << ")" << std::endl;
    return std::make_pair(x_ret, y_ret);
}

template <typename T>
T Line<T>::get_length() const
{
    T delta_x = start_pt_.first - stop_pt_.first;
    T delta_y = start_pt_.second - stop_pt_.second;
    return std::sqrt(delta_x * delta_x + delta_y * delta_y);
}

template class Line<float>;
template class Line<double>;
template class Line<long double>;