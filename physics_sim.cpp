#include "physics_sim.hpp"

#include <boost/numeric/odeint.hpp>
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace boost::numeric::odeint;

System::System( double gamma, control_t &u ) : m_gam( gamma ), u_t( u ) {}

void System::setControl(const control_t &u) {
    u_t = u; // I believe this copies u to u_t, but am not sure
}

void System::operator() ( const state_t &x , state_t &dxdt , const double /* t */ )
{
    dxdt[0] = x[1];
    dxdt[1] = -x[0] - m_gam*x[1] + u_t[0];
}


Simulation::Simulation(state_t x_0)
    : control_input(constants::DIMENSION_CONTROL), x( x_0 ), system(constants::GAMMA, control_input), state_recorder(states, times)
{
    state_recorder(x, constants::t_start);      
}
void Simulation::step(control_t u,  const double t, const double dt) {
    system.setControl(u);
    stepper.do_step( system , x , t , dt );
    state_recorder(x, t+dt);
}
