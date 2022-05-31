#include "Geometry.h"
#include <vector>

class PointSearcher {
    double tolerance_;
    int num_points_;
    Line<double> cur_line_;
    std::vector<std::pair<double, double>> mass_intersection;
    std::vector<int> intersection_hist;
    std::vector<std::vector<int>> intrsct_idx;

    std::vector<Line<double>> lines_;
    std::pair<double, double> step_vec_;

    void clean_lines(std::vector<Line<double>>& lines, int idx);
    
    public:
    PointSearcher(int num_pts);
    void set_tolerance(double val);
    std::vector<std::pair<double, double>> process(std::vector<Line<double>>&lines);
    void intersect(std::vector<Line<double>>&lines, int idx);
    void build_intersection_hist(double line_length);
};

