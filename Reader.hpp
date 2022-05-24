#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "Geometry.h"

using namespace std;

class Reader {
    fstream in_file_;
    int num_lines_;
    int num_pts_;
    std::vector<Line<double>> lines_;

    public:
    explicit Reader(string fname);
    void process_file();
    int get_num_lines() const;
    int get_num_points() const;
    const std::vector<Line<double>>& get_lines() const;
};

Reader::Reader(string fname)
{
    /*!TODO: catch exception if file doesn't exist*/
    in_file_.open(fname, ios::in);
}

void Reader::process_file()
{
    in_file_ >> num_lines_;
    std::cout << num_lines_ << " lines" << std::endl;
    in_file_ >> num_pts_;
    std::cout << num_pts_ << " points" << std::endl;
    
    double x1, y1, x2, y2;
    
    for(int line_idx = 0; line_idx < num_lines_; line_idx++) {
        in_file_ >> x1;
        in_file_ >> y1;
        in_file_ >> x2;
        in_file_ >> y2;
        lines_.push_back(Line<double>{x1, y1, x2, y2});
    }
}

int Reader::get_num_lines() const
{
    return num_lines_;
}

int Reader::get_num_points() const
{
    return num_pts_;
}

const std::vector<Line<double>> &Reader::get_lines() const
{
    return lines_;
}