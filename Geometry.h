#pragma once

#include <utility>

template<typename T>
class Line {
    public:
    std::pair<T, T> start_pt_, stop_pt_;
    //should be private but currently like that...

    T a_;
    T b_;
    T c_;

    void normalize();

    public:
    Line();
    explicit Line(const T x1, const T y1, const T x2, const T y2);
    T calc_dist( std::pair<T, T> &pt);
    T calc_squared_dist( std::pair<T, T> &pt);
    std::pair<T, T> intersect(Line<T>& other);
    T get_length() const;
};