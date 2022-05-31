#include "PointSearcher.h"
#include "Geometry.h"
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <iostream>

PointSearcher::PointSearcher(int num_pts)
{
    num_points_ = num_pts;
    tolerance_ = 10.0;
}

//Intersect all lines in vector with line at idx
//line[idx] will be removed from verctor
//Result is in this->mass_intersection
void PointSearcher::intersect(std::vector<Line<double>>&lines, int idx)
{
    mass_intersection.clear();
    
    Line cur_line = lines[idx];
    lines.erase(lines.begin() + idx);

    //Fill intersections data
    auto it_begin = lines.begin();
    auto it_end = lines.end();
    for (auto it = it_begin; it != it_end; ++it) {
        mass_intersection.push_back(it->intersect(cur_line));
    }
}

void PointSearcher::build_intersection_hist(double line_length)
{
    int num_bins = int(std::ceil(line_length / tolerance_));
    intersection_hist = std::vector<int>(num_bins, 0);
    //intrsct_idx.resize(num_bins, std::vector<int>(1));
    intrsct_idx = std::vector<std::vector<int>>(num_bins, std::vector<int>(0));

    auto intrsct_start = mass_intersection.begin();
    auto intrsct_end = mass_intersection.end();

    for (auto it = intrsct_start; it != intrsct_end; ++it) {
        int cur_bin = int(Line(it->first, it->second, cur_line_.start_pt_.first, cur_line_.start_pt_.second).get_length() / tolerance_);
        if ((cur_bin < num_bins) && (cur_bin >= 0)) {
            intersection_hist[cur_bin]++;
            intrsct_idx[cur_bin].push_back(it - intrsct_start);
        }
    }
}

void PointSearcher::clean_lines(std::vector<Line<double>>& lines, int idx)
{
    std::sort(intrsct_idx[idx].begin(), intrsct_idx[idx].end(), std::greater<int>());
    auto ibegin = intrsct_idx[idx].begin();
    auto iend = intrsct_idx[idx].end();

    for(auto iit = ibegin; iit != iend; ++iit) {
        //std::cout << "Removing " << *iit << std::endl;
        lines.erase(lines.begin() + *iit);
        //std::cout << lines.size() << std::endl;
    }
}

std::vector<std::pair<double, double>> PointSearcher::process(std::vector<Line<double>>& lines)
{
    std::vector<std::pair<double, double>> result_pts;
    int cur_progress = 0;

    std::cout << num_points_ << " " << lines.size() << std::endl;
    while ((cur_progress != num_points_) && (lines.size() > 1)) {
        //std::cout<< "here!" << std::endl;
        cur_line_ = lines[0];
        double cur_line_length = cur_line_.get_length();
        step_vec_.first = (cur_line_.stop_pt_.first - cur_line_.start_pt_.first) / cur_line_length * tolerance_;
        step_vec_.second = (cur_line_.stop_pt_.second - cur_line_.start_pt_.second) / cur_line_length * tolerance_;
        intersect(lines, 0);
        build_intersection_hist(cur_line_length);
        auto max_it = std::max_element(intersection_hist.begin(), intersection_hist.end());
        int max_idx = max_it - intersection_hist.begin();
        result_pts.push_back(std::make_pair(cur_line_.start_pt_.first + max_idx * step_vec_.first,
                                            cur_line_.start_pt_.second + max_idx * step_vec_.second));
        clean_lines(lines, max_idx);
        cur_progress++;
        //std::cout << lines.size() << " lines lost" << std::endl;
    }
    return result_pts;
}