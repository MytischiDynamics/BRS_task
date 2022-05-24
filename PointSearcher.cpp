#include "PointSearcher.h"
#include "ceres/ceres.h"
#include <vector>
#include <random>
#include "Geometry.h"

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;

struct CostFunctor {
    CostFunctor(const std::vector<Line<double>> &l, const int num_pts) {
        l_ = l;
        num_pts_ = num_pts;
    }

    template <typename T>
    bool operator()(const T* const x, T* residual) const {
        auto l_it_stop = l_.end();
        double resid = 0.0;
        residual[0] = 0.0 + x[0] - x[0];
        
        for(auto l_it = l_.begin(); l_it != l_it_stop; ++l_it) {
            for(int pt_idx = 0; pt_idx < num_pts_; pt_idx++) {
                //resid += l_it->calc_dist(std::make_pair(x[2 * pt_idx], x[2 * pt_idx + 1]));
                auto signed_dist = l_it->a_*x[2 * pt_idx] + l_it->b_*x[2 * pt_idx + 1] + l_it->c_;
                residual[0] += signed_dist * signed_dist;
            }
        }
        //residual[0] = std::move(resid) - x[0] + x[0];
        return true;
    }

    private:
    std::vector<Line<double>> l_;
    int num_pts_;
};


/*!TODO: add scaling ranges from -1.0 to 1.0 to exploite double type density*/
PointSearcher::PointSearcher(std::vector<Line<double>> l, int num_points)
{
    lines_ = l;
    num_points_ = num_points;
    gen_init_pos(-1000.0, 1000.0, -1000.0, 1000.0);
}

void PointSearcher::gen_init_pos(double x_min, double x_max, double y_min, double y_max)
{
    x_ = new double[num_points_ * 2];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(x_min, x_max);
    std::uniform_real_distribution<> dis_y(y_min, y_max);
    for(int i = 0; i < num_points_; i++) {
        x_[2 * i] = dis_x(gen);
        x_[2 * i + 1] = dis_y(gen);
    }
    std::cout << "start point x: " << x_[0] << std::endl;
}

void PointSearcher::process()
{
    Problem problem;

    //Here we should provide Jacobian matrix since Ceres doesn't support
    //runtime defined size of x
    //The "3" in template parameter is not correct here
    CostFunction* cost_function =
        new AutoDiffCostFunction<CostFunctor, 1, 3>(new CostFunctor{lines_, num_points_});
    problem.AddResidualBlock(cost_function, nullptr, x_);
    Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    Solver::Summary summary;
    Solve(options, &problem, &summary);
    std::cout << summary.BriefReport() << "\n";
    // std::cout << "x : " << initial_x << " -> " << x << "\n";
}