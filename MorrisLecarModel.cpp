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
	const double g_L = 0.2;		// leak

	const double C = 20.;		// capacity of membrane

	const double V_Ca = 100.;
	const double V_K = 70.;
	const double V_L = 50.;

	const double V_1 = -1.;	// potential at which M_inf == 0.5
	const double V_2 = 15.;	// reciprocal of slope of voltage dependence of M_inf
	const double V_3 = 2.;	// potential at which n_inf == 0.5
	const double V_4 = 30.;	// reciprocal of slope of voltage dependence of n_inf

	const double phi = 0.066;
	double I_ext;

	vector<pdd> data; // an array for V and n relationships

public:
	MorrisLecar(const double& I_ext) {
		this->I_ext = I_ext;
	}

	double get_dV(const double& V, const double& N) {
		return (I_ext - (g_L * (V - V_L)) - (g_Ca * M_inf(V) * (V - V_Ca)) - (g_K * N * (V - V_K))) / C;
	}
	double get_dN(const double& V, const double& N) {
		return (N_inf(V) - N) * r_N(V);
	}

	void calc_data(const double& time = 30.){
		data = vector<pdd>(time * 10);
		int steps = time * 10.;
		double delta_i = (time - 0) / steps;
		data[0].first = -30.;
		data[0].second = 0.;
		double leftV = get_dV(data[0].first, data[0].second);
		double leftN = get_dN(data[0].first, data[0].second);
		for(int i = 1; i <= steps; i++){
			double rightV = get_dV(data[i - 1].first, data[i - 1].second);
			double rightN = get_dN(data[i - 1].first, data[i - 1].second);
			data[i].first = data[i - 1].first + (((leftV + rightV) / 2.) * delta_i);
			data[i].second = data[i - 1].second + (((leftN + rightN) / 2.) * delta_i);
		}
	}

	void print_data(){
		int i = 0;
		for(const auto& p : data){
			//printf("[%d]\tV: %lf,\tN: %lf\n", i++, data[i - 1].first, data[i - 1].second);
			//printf("%lf;%lf\n", p.first, p.second);
			printf("%lf;%lf\n", (i++)*0.1, p.first);
		}
	}

private:
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
		return phi * cosh((V - V_3) / V_4 / 2.);
	}
};

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

int main(int argc, char* argv[]) {
	MorrisLecar* ML = new MorrisLecar(60.);
	ML->calc_data();
	ML->print_data();
}
