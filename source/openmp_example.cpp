// OpenMP header
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>    //medir tiempo

#include "cluster.h"

int main(int argc, char* argv[])
{
    int nthreads, tid;
    double x, y;
    int i = 0;
    unsigned t0, t1;            //variables para medir el tiempo de ejecucion en secuencial
    double start, finish;       //variables para medir el tiempo de ejecucion en paralelo
    vector<Point> my_points;
    
    fstream newfile;
    newfile.open("../puntos_2_bloques.txt",ios::in); //open a file to perform read operation using file object
    string line;
    stringstream linestream;

    while (getline(newfile, line))
    {
        stringstream linestream;
        linestream << line;
        linestream >> x >> y;
        //cout << x << " - " << y << endl;
        Point a (x,y);
        my_points.push_back(a);
    }
    newfile.close();

    start = omp_get_wtime();
    //t0=clock();                   //Secuencial
    k_means(my_points, 2);          //Mandamos los puntos para a la funcion k means
    //t1 = clock();                 //Secuencial
    finish = omp_get_wtime();

    //double time = (double(t1-t0)/CLOCKS_PER_SEC);     //Secuencial
    //cout << "Execution Time: " << time << endl;       //Secuencial
    printf("Elapsed time = %e seconds\n", finish - start);

    ofstream file;            		//Abrimos un file, donde almacenaremos el map
    string nombre = "points_cluster_2";
    string direccion = "D://Programacion//EDA//Thisone//Kmeans_Paralelo//cmake_parallel//";
    direccion.append(nombre);
    direccion.append(".csv");
    file.open(direccion, ios::out);

    file << 'x' << ',' << 'y' << ',' << "color" << endl;

    for (int i = 0; i < my_points.size(); i++) {
        file << my_points[i].x << "," << my_points[i].y << "," << my_points[i].cluster << endl;
    }
    file.close();   //Se cierra el file

    return 0;
}
