#include "Geometry.h"
#include "PointSearcher.h"
#include "Reader.hpp"

int main()
{
    Reader rdr("data/0-lines.txt");
    rdr.process_file();
    auto lines = rdr.get_lines();
    PointSearcher ps{lines, rdr.get_num_points()};
    ps.process();
    return 0;
}