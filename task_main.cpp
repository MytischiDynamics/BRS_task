#include "Geometry.h"
#include "PointSearcher.h"
#include "Reader.hpp"
#include <fstream>


void push_result(std::vector<std::pair<double, double>>& res)
{
    auto itstart = res.begin();
    auto itend = res.end();

    fstream outfile;
    outfile.open("result.txt", ios::out);

    for (auto it = itstart; it != itend; ++it) {
        outfile << it->first << " " << it->second << std::endl;
    }
    outfile.close();
}

int main(int argc, char**argv)
{
    //Reader rdr("data/2-lines.txt");
    Reader rdr(argv[1]);
    rdr.process_file();
    auto lines = rdr.get_lines();
    PointSearcher ps(rdr.get_num_points());
    auto pts = ps.process(lines);
    for (auto it = pts.begin(); it != pts.end(); ++it) {
        cout << "(" << it->first << "; " << it->second << ")" << std::endl;
    }
    push_result(pts);
    return 0;
}
