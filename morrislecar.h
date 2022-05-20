#ifndef MORRISLECAR_H
#define MORRISLECAR_H

#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

#define pdd pair<double, double>

inline double div(const double& delta_1, const double& delta_2) {
    return delta_1/delta_2;
}

class MorrisLecar {
    const double g_Ca = 4.4;	// calcium
    const double g_K = 8.;		// potassium
    const double g_L = 2;		// leak

    const double C = 1.;		// capacity of membrane

    const double V_Ca = 120.;
    const double V_K = -84.;
    const double V_L = -60.;

    const double V_1 = -1.2;	// potential at which M_inf == 0.5
    const double V_2 = 18.;	// reciprocal of slope of voltage dependence of M_inf
    const double V_3 = 12.;	// potential at which n_inf == 0.5
    const double V_4 = 30.;	// reciprocal of slope of voltage dependence of n_inf

    const double phi = 0.04;
    double I_ext;

    vector<pdd> data; // an array for V and n relationships

public:
    MorrisLecar(const double& I_ext) {
        this->I_ext = I_ext;
    }
    void calc_data(const int& time = 30);

    void print_data();

    inline const vector<pdd>& get_data(){
        return data;
    }

private:

    inline double get_dV(const double& V, const double& N){
        return (I_ext - (g_L * (V - V_L)) - (g_Ca * M_inf(V) * (V - V_Ca)) - (g_K * N * (V - V_K))) / C;
    }
    inline double get_dN(const double& V, const double& N){
        return (N_inf(V) - N) / r_N(V);
    }

    // fraction of open Ca++ channels
    inline double M_inf(const double& V) {
        return 0.5 * (1. + tanh((V - V_1) / V_2));
    }
    // fraction of open K+ channels
    inline double N_inf(const double& V) {
        return 0.5 * (1 + tanh((V - V_3) / V_4));
    }
    // fraction of open Ca++ channels
    inline double r_N(const double& V) {
        return 1./(phi * cosh((V - V_3) / V_4 / 2.));
    }
};

void integral(vector<double>& dest, double(*f)(double), const double& lower_bound, const double& upper_bound, const int& steps);

#endif // MORRISLECAR_H
