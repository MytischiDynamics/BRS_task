from ReadData import DataReader
from Geometry import Line, LineSet
import numpy as np


def find_pts(lines):
    line_step = 10.0
    while len(lines.data) > 3:
        cur_line = lines.data[0]
        lines.data.remove(cur_line)
        intersections = lines.intersect(cur_line)

        cur_length = np.linalg.norm(cur_line.end_pt - cur_line.start_pt)
        num_bins = int(np.ceil(cur_length / 10.0))
        histogram = np.zeros((num_bins,), dtype=int)
        indices = []
        for i in range(num_bins):
            indices.append([])

        step_vec = (cur_line.end_pt - cur_line.start_pt) / cur_length * line_step

        for pt_idx, pt in enumerate(intersections):
            cur_bin = int(np.linalg.norm(cur_line.start_pt - pt) / line_step)
            if (cur_bin < num_bins) and (cur_bin >= 0):
                histogram[cur_bin] += 1
                indices[cur_bin].append(pt_idx)

        best_bin = np.argmax(histogram)
        print("Intersection: " + str(cur_line.start_pt + best_bin * step_vec))
        print(str(histogram[best_bin]) + " lines we can find here")
        for idx in sorted(indices[best_bin], reverse=True):
            del lines.data[idx]

        print(str(len(lines.data)) + " lines lost")


if __name__ == "__main__":
    dr = DataReader()
    dr.set_fname("data//2-lines.txt")
    dr.read_file()

    find_pts(dr.lines)
