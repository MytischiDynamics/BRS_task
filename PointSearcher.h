#include "Geometry.h"
#include <vector>

class PointSearcher {
    std::vector<Line<double>> lines_;
    int num_points_;
    double* x_;
    public:
    PointSearcher(std::vector<Line<double>> l, int num_points);
    //void set_lines(const std::vector<Line<double>> &lines, const int num_points);
    void gen_init_pos(double x_min, double x_max, double y_min, double y_max);
    void process();
};

