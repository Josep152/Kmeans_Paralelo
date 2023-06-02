#ifndef POINT_H
#define POINT_H

#include <math.h>

struct Point {
    double x;
    double y;
    int cluster;
    Point () {
        x = 0;
        y = 0;
    }
    Point (double _x, double _y) {
        x = _x;
        y = _y;
    }
    double dist_Eucle (Point a) {
        return sqrt(pow(x - a.x, 2) + pow(y - a.y, 2));
    }
    void chg_cluster(int _cluster) {
        cluster = _cluster;
    }
};

#endif