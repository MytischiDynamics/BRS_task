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
    T calc_dist(const std::pair<T, T> &pt) const;
    T calc_squared_dist(const std::pair<T, T> &pt) const;
    std::pair<T, T> intersect(const Line<T>& other) const;
    T get_length() const;
};