#include "physics_sim.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>


int main() {
    control_t u(constants::DIMENSION_CONTROL);
    state_t x_0(constants::DIMENSION_STATE_SPACE);

    x_0[0] = 2.0;
    x_0[1] = 0.0;

    Simulation sim(x_0);
    const double t_end = 10.0;
    for( double t = constants::t_start ; t < t_end ; t+= constants::DELTA_T ) {
        u[0] = 0;
        sim.step(u, t, constants::DELTA_T);
    }

    std::ofstream outfile;
    outfile.open ("data.txt");
    
    for( size_t i=0; i<=t_end/constants::DELTA_T; i++ ) {
       outfile << sim.times[i] << ';' << sim.states[i][0] << ';' << sim.states[i][1] << std::endl;
    }
    outfile.close();
}
