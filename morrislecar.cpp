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


void MorrisLecar::calc_data(const int& time){

    int steps = time * 10.;
    data = vector<pdd>(steps + 1);

    data[0].first = -10.;
    data[0].second = 0.;

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
        printf("%lf;%lf\n", (i++)*0.1, p.first);
    }
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
