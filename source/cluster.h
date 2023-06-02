#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   //time
#include <map>      //map
#include <utility>  //pair
#include <cmath>    //valor absoluto

#include <omp.h>    //openMP    /////////////////////////////////////////////////////

#include "point.h"

using namespace std;

void act_centroides(vector<Point>& _curr_clusters, vector<Point>& _last_clusters, int cant_k) {
    for (int i = 0; i < cant_k; i++) {
        _last_clusters[i] = _curr_clusters[i];
    }
}

bool stop_cluster(vector<Point>& _curr_clusters, vector<Point>& _last_clusters, int cant_k){
    for (int i = 0; i < cant_k; i++){
        if (abs(_curr_clusters[i].x - _last_clusters[i].x) > 0.1) {
            act_centroides(_curr_clusters, _last_clusters, cant_k);
            return false;
        }
        if (abs(_curr_clusters[i].y - _last_clusters[i].y) > 0.1) {
            act_centroides(_curr_clusters, _last_clusters, cant_k);
            return false;
        }
    }
    return true;
}

void k_means(vector<Point>& _points, int cant_k) {
    srand( time(NULL) );

    vector<Point> curr_clusters(cant_k);
    vector<Point> last_clusters(cant_k);

    for (int i = 0; i < cant_k; i++) {                      //Inicializamos los clusters, con la etiqueta que llevaran
        curr_clusters[i].x = ((double)(rand() % 40000)/10000);
        curr_clusters[i].y = ((double)(rand() % 40000)/10000);
        curr_clusters[i].chg_cluster(i);
        last_clusters[i] = curr_clusters[i];
    }

    do {
        map<int,pair<pair<double,double>,int>> means;
        double dist_min = 0;
        int i, j;

#       pragma omp parallel for num_threads(8) \
            default(none) shared(_points, last_clusters, curr_clusters, cant_k, means) private(i, j, dist_min)
        for (i = 0; i < _points.size(); i++) {
            dist_min = _points[i].dist_Eucle(curr_clusters[0]);
            _points[i].chg_cluster(curr_clusters[0].cluster);
            for (j = 1; j < cant_k; j++) {
                if (_points[i].dist_Eucle(curr_clusters[j]) < dist_min){
                    _points[i].chg_cluster(curr_clusters[j].cluster);
                    dist_min = _points[i].dist_Eucle(curr_clusters[j]);
                }
            }
#           pragma omp critical
            means[_points[i].cluster].first.first += _points[i].x;
            means[_points[i].cluster].first.second += _points[i].y;
            means[_points[i].cluster].second++;
        }
        for (int i = 0; i < cant_k; i++) {
            curr_clusters[i].x = (means[i].first.first)/(means[i].second);
            curr_clusters[i].y = (means[i].first.second)/(means[i].second);
        }
    } while(!stop_cluster(curr_clusters, last_clusters, cant_k));

    cout << "\nPrinting clusters -> \n";
    for (int i = 0; i < cant_k; i++) {
        cout << last_clusters[i].x << ' ' << last_clusters[i].y << endl; 
    }
}


#endif