#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include "morrislecar.h"

using namespace std;


void MorrisLecar::calc_data(){

    int steps = (int)(time * accuracy);
    data = vector<pdd>(steps + 1);

    data[0].first = V0;
    data[0].second = N0;

    double delta_i = (time - 0.) / steps;
    double leftV = get_dV(data[0].first, data[0].second);
    double leftN = get_dN(data[0].first, data[0].second);

    for(int i = 1; i <= steps; i++){
        double rightV = get_dV(data[i - 1].first, data[i - 1].second);
        double rightN = get_dN(data[i - 1].first, data[i - 1].second);
        data[i].first = data[i - 1].first + (((leftV + rightV) / 2.) * delta_i);
        data[i].second = data[i - 1].second + (((leftN + rightN) / 2.) * delta_i);
        leftV = rightV;
        leftN = rightN;
    }
}

void MorrisLecar::print_data(){
    int i = 0;
    for(const auto& p : data){
        //printf("[%d]\tV: %lf,\tN: %lf\n", i++, data[i - 1].first, data[i - 1].second);
        //printf("%lf;%lf\n", p.first, p.second);
        printf("%lf;%lf\n", (i++)/accuracy, p.first);
    }
}

void MorrisLecar::load_values(const vector<double>& values){
    this->V_Ca = values[0];
    this->V_K = values[1];
    this->V_L = values[2];
    this->V_1 = values[3];
    this->V_2 = values[4];
    this->V_3 = values[5];
    this->V_4 = values[6];
    this->g_Ca = values[7];
    this->g_K = values[8];
    this->g_L = values[9];
    this->C = values[10];
    this->phi = values[11];
    this->I_ext = values[12];
    this->time = values[13];
    this->accuracy = values[14];
    this->V0 = values[15];
    this->N0 = values[16];
}

void MorrisLecar::set_default(){
    this->V_Ca = _V_Ca;
    this->V_K = _V_K;
    this->V_L = _V_L;
    this->V_1 = _V_1;
    this->V_2 = _V_2;
    this->V_3 = _V_3;
    this->V_4 = _V_4;
    this->g_Ca = _g_Ca;
    this->g_K = _g_K;
    this->g_L = _g_L;
    this->C = _C;
    this->phi = _phi;
    this->I_ext = _I_ext;
    this->time = _time;
    this->accuracy = _accuracy;
    this->V0 = _V0;
    this->N0 = _N0;
}

void integral(vector<double>& dest, double(*f)(double), const double& lower_bound, const double& upper_bound, const int& steps){
	dest = vector<double>(steps + 1);
	double delta_i = (upper_bound - lower_bound) / steps; 
	double left = f(lower_bound);
	dest[0] = 0;
	for (int i = 1; i <= steps; i++) {
		double right = f(lower_bound + i * delta_i);
		dest[i] = dest[i - 1] + (((left + right) / 2.) * delta_i);
		left = right;
	}
	//dest[steps] = dest[steps-1] + (((left + f(upper_bound)) / 2.) * delta_i);
}
