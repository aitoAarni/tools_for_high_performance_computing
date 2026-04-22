#include <mpi.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

#define d  1.0
#define k2 1.0
#define k3 0.1
#define xsc 2.35

using namespace std;

ofstream fcoord;
string coord_file="coords.dat";

void accel(int nat, int i, double *u, double *a, double box, vector<double>& x) {
    int j, k;
    double dxl, dxr;
    
    j = i - 1; if (j < 0) j = nat - 1;
    k = i + 1; if (k >= nat) k = 0;
    
    dxl = x[i] - x[j];
    dxr = x[k] - x[i];
    if (dxl < -box / 2.0) dxl += box;
    if (dxl >= box / 2.0) dxl -= box;
    if (dxr < -box / 2.0) dxr += box;
    if (dxr >= box / 2.0) dxr -= box;
    dxl -= d;
    dxr -= d;

    *u = (k2 * (dxl * dxl + dxr * dxr) + k3 * (dxl * dxl * dxl + dxr * dxr * dxr)) / 2.0;
    *a = -(2.0 * k2 * (dxl - dxr) + 3.0 * k3 * (dxl * dxl - dxr * dxr));
}


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    
    int numprocs, myid;
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    vector<double> x, v, v0, a, ep, ek;
    double dt, vsc, box;
    int nat, maxt, eout, coout;
    int i, n;

    if (argc < 5 || argc > 7) {
        if (myid == 0) cerr << "usage: mpirun -np X ./md1d_mpi nat dt maxt vsc [eout [coout]]\n";
        MPI_Finalize();
        return 1;
    }
    
    coout = 0;
    eout = 1;
    nat = atoi(argv[1]);
    dt = atof(argv[2]);
    maxt = atoi(argv[3]);
    vsc = atof(argv[4]);
    if (argc > 5) eout = atoi(argv[5]);
    if (argc > 6) coout = atoi(argv[6]);

    int nlocal = nat / numprocs;
    int start_idx = myid * nlocal;
    int end_idx = start_idx + nlocal - 1;

    x = vector<double>(nat, 0.0);
    v = vector<double>(nat, 0.0);
    v0 = vector<double>(nat, 0.0);
    a = vector<double>(nat, 0.0);
    ep = vector<double>(nat, 0.0);
    ek = vector<double>(nat, 0.0);

    box = nat;
    srand(12345);
    for (i = 0; i < nat; i++) {
        x[i] = i;
        double rn = (double)rand() / RAND_MAX;
        v[i] = vsc * (rn - 0.5);
    }

    MPI_Comm comm1d;
    int dims[1] = {numprocs};
    int periods[1] = {1};
    MPI_Cart_create(MPI_COMM_WORLD, 1, dims, periods, 1, &comm1d);
    
    MPI_Comm_rank(comm1d, &myid); 
    
    int left_id, right_id;
    MPI_Cart_shift(comm1d, 0, 1, &left_id, &right_id);

    int left_ghost = (start_idx - 1 + nat) % nat;
    int right_ghost = (end_idx + 1) % nat;

    MPI_Barrier(comm1d);
    double t0 = MPI_Wtime();

    for (n = 0; n < maxt; n++) {
        
        for (i = start_idx; i <= end_idx; i++) v0[i] = v[i];

        MPI_Sendrecv(&x[start_idx], 1, MPI_DOUBLE, left_id, 0,
                     &x[right_ghost], 1, MPI_DOUBLE, right_id, 0,
                     comm1d, MPI_STATUS_IGNORE);

        MPI_Sendrecv(&x[end_idx], 1, MPI_DOUBLE, right_id, 1,
                     &x[left_ghost], 1, MPI_DOUBLE, left_id, 1,
                     comm1d, MPI_STATUS_IGNORE);
        
        for (i = start_idx; i <= end_idx; i++)
            accel(nat, i, &ep[i], &a[i], box, x);
        
        for (i = start_idx; i <= end_idx; i++) {
            v[i] = v[i] + dt * a[i];
            x[i] = x[i] + dt * v[i];
            
            if (x[i] < 0.0) x[i] = x[i] + box;
            if (x[i] >= box) x[i] = x[i] - box;
            
            double vave = (v0[i] + v[i]) / 2.0;
            ek[i] = 1.0 / 2.0 * vave * vave;
        }

        if (eout > 0 && n % eout == 0) {
            double local_epsum = accumulate(ep.begin() + start_idx, ep.begin() + end_idx + 1, 0.0);
            double local_eksum = accumulate(ek.begin() + start_idx, ek.begin() + end_idx + 1, 0.0);
            
            double global_epsum = 0.0;
            double global_eksum = 0.0;

            MPI_Reduce(&local_epsum, &global_epsum, 1, MPI_DOUBLE, MPI_SUM, 0, comm1d);
            MPI_Reduce(&local_eksum, &global_eksum, 1, MPI_DOUBLE, MPI_SUM, 0, comm1d);

            if (myid == 0) {
                printf("%20.10g %20.10g %20.10g %20.10g\n", dt * n, global_epsum + global_eksum, global_epsum, global_eksum);
            }
        }
    }
    
    MPI_Barrier(comm1d);
    double t1 = MPI_Wtime();
    
    if (myid == 0) {
        printf("Wall clock time: %f seconds\n", t1 - t0);
    }

    MPI_Finalize();
    return 0;
}