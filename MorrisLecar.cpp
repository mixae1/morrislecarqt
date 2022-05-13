#include <math.h>
#include <iostream>
using namespace std;

inline double diff(const double& delta_1, const double& delta_2) {
	return delta_1 / delta_2;
}


class Model {
protected:
	const double g_Ca = 4.4;	// calcium
	const double g_K = 8.;		// 
	const double g_L = 0.2;		// leak
	//const double g_Na = -1.;

	const double C = 20.;

	const double V_Ca = 100.;
	const double V_K = 70.;
	const double V_L = 50.;

	const double V_1 = -1.;	// potential at which M_inf == 0.5
	const double V_2 = 15.;	// reciprocal of slope of voltage dependence of M_inf
	const double V_3 = 2.;	// potential at which n_inf == 0.5
	const double V_4 = 30.;	// reciprocal of slope of voltage dependence of n_inf

	const double ô = 0.05;


};

class MorrisLecar : Model{

	double I_ext;
public:
	MorrisLecar(const double& I_ext) {
		this->I_ext = I_ext;
	}

	bool is_belonged(const double& oldV, const double& V, const double& oldn, const double& n, const double& delta_t) {
		return C * diff(oldV - V, delta_t) + g_L * (V - V_L) + M_inf(V) * g_Ca * (V - V_Ca) + n_inf(V) * g_K * (V - V_K) == I_ext &&
			diff(oldn, n) == (n_inf(V) - n)/r_n(V);
	}

private:
	// fraction of open Ca++ channels
	inline double M_inf(const double& V) {
		return 0.5 * (1. + tanh((V - V_1) / V_2));
	}
	// fraction of open K+ channels
	inline double n_inf(const double& V) {
		return 0.5 * (1 + tanh((V - V_3) / V_4));
	}
	// fraction of open Ca++ channels
	inline double r_n(const double& V) {
		return 1. / ô * cosh((V - V_3) / (2. * V_4));
	}
};


int main(int argc, char* argv[]) {
	auto ML1 = new MorrisLecar(-20.);
	auto ML2 = new MorrisLecar(-27.54842);
	auto ML3 = new MorrisLecar(-30.);
	auto ML4 = new MorrisLecar(-40.);

	for (double x = 0.1; x <= 90.; x += 0.1) {
		cout << "x: " << x << "\ty: " << endl;
	}
}
