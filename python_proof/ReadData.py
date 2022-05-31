import numpy as np
from Geometry import Line, LineSet
import matplotlib.pyplot as plt
from matplotlib import collections as mc


class DataReader:
    def __init__(self):
        self.fname = "data//1-lines.txt"
        self.lines = LineSet()
        self.num_pts = 1
        self.num_lines = 1

    def set_fname(self, fname):
        self.fname = fname

    def read_file(self):
        f = open(self.fname)
        lines = f.readlines()
        for l_idx, line in enumerate(lines):
            val_strs = line.split(" ")
            if l_idx == 0:
                self.num_lines = int(val_strs[0])
                self.num_pts = int(val_strs[1])
            else:
                self.lines.append(Line(np.double(val_strs[0]), np.double(val_strs[1]), np.double(val_strs[2]), np.double(val_strs[3])))

    def draw(self):
        lines = []
        for l in self.lines.data:
            lines.append([(l.start_pt[0], l.start_pt[1]), (l.end_pt[0], l.end_pt[1])])

        lc = mc.LineCollection(lines, linewidths=1)
        return lc


if __name__ == "__main__":
    dr = DataReader()
    dr.set_fname("data//1-lines.txt")
    dr.read_file()
    coll = dr.draw()
    fig, ax = plt.subplots()
    ax.add_collection(coll)
    plt.autoscale()
    plt.show()
