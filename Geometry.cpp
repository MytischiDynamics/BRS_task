#include "Geometry.h"
#include <utility>
#include <cmath>
#include <iostream>

template<typename T>
Line<T>::Line(const T x1, const T y1, const T x2, const T y2)
{
    start_pt_ = std::make_pair(x1, y1);
    stop_pt_ = std::make_pair(x2, y2);

    c_ = 1.0;
    a_ = -(c_ * (1 + y2/y1)) / (x2 - x1 * y2 / y1);
    b_ = -(a_ * x1 + c_) / y1;

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

template class Line<float>;
template class Line<double>;
template class Line<long double>;