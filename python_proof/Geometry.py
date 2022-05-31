import numpy as np
from scipy.special import huber


class Line:
    def __init__(self):
        self.a = 1.0
        self.b = 1.0
        self.c = 1.0
        self.start_pt = np.ones((2,))
        self.end_pt = np.ones((2,))

    def __init__(self, x1, y1, x2, y2):
        self.start_pt = np.array([x1, y1])
        self.end_pt = np.array([x2, y2])
        self.c = 1.0

        if y1 == y2:
            self.c = -y1
            self.a = 0.0
            self.b = 1.0
        elif x1 == x2:
            self.c = -x1
            self.a = 1.0
            self.b = 0.0
        elif y2 * x1 - y1 * x2 != 0.0:
            if x1 != 0.0:
                self.c = 1.0
                self.b = self.c * (x2 - x1) / (y2 * x1 - y1 * x2)
                self.a = -((self.b * y1 + self.c) / x1)
            elif y1 != 0.0:
                self.c = 1.0
                self.a = self.c * (y2 - y1) / (x2 * y1 - x1 * y2)
                self.b = -(self.a * x1 + self.c) / y1
        else:
            self.c = 0.0
            self.a = 1.0
            self.b = -x2 / y2

        self.normalize()

    def normalize(self):
        k = 1 / np.sqrt(self.a * self.a + self.b * self.b)
        self.a = self.a * k
        self.b = self.b * k
        self.c = self.c * k

    def rescale(self, coef):
        self.start_pt *= coef
        self.end_pt *= coef

    def dist_to_pt(self, x, y):
        return np.abs(self.a * x + self.b * y + self.c)

    def intersect(self, other):
        x_ret = 0.0
        y_ret = 0.0

        a1 = self.a
        b1 = self.b
        c1 = self.c

        a2 = other.a
        b2 = other.b
        c2 = other.c

        if (a1 == a2) and (b1 == b2):
            x_ret = None
            y_ret = None
        elif b1 != 0.0:
            x_ret = (b2 * c1 - c2 * b1) / (a2 * b1 - b2 * a1)
            y_ret = -(c1 + a1 * x_ret) / b1
        elif a1 != 0.0:
            y_ret = (a2 * c1 - a1 * c2) / (b2 * a1 - a2 * b1)
            x_ret = -(b1 * y_ret + c1) / a1

        return np.array([x_ret, y_ret])


class LineSet:
    def __init__(self):
        self.data = []

    def rescale(self, coef):
        for line in self.data:
            line.rescale(coef)

    def append(self, l):
        self.data.append(l)

    def total_dist_sq(self, x, y):
        res = 0.0
        for l in self.data:
            cur_dist = l.dist_to_pt(x, y)
            res += cur_dist * cur_dist
        return res

    def total_dist_nl(self, x, y):
        res = 0.0
        for l in self.data:
            cur_dist = l.dist_to_pt(x, y)
            if cur_dist <= 2.0:
                res += cur_dist
        return res

    def total_dist(self, x, y):
        res = 0.0
        for l in self.data:
            cur_dist = l.dist_to_pt(x, y)
            res += cur_dist
        return res

    def intersect(self, line):
        intersections = []
        for l in self.data:
            intersections.append(l.intersect(line))
        return intersections


if __name__ == "__main__":
    l1 = Line(-1.0, 0.0, 1.0, 0.0)
    print(l1.dist_to_pt(0.0, 10.0))

    l2 = Line(0.0, 0.0, 1.0, 1.0)
    print(l2.dist_to_pt(0.0, 10.0))
