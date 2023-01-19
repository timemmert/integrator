#pragma once

#include <cstdio>
#include <iostream>
#include <boost/numeric/odeint.hpp>

typedef std::vector< double > state_t;
typedef std::vector< double > control_t;

namespace constants {
    const size_t DIMENSION_STATE_SPACE = 2;
    const size_t DIMENSION_CONTROL = 1;
    const double DELTA_T = 0.01;
    const double GAMMA = 0.2;
    const double t_start = 0.0;
}


struct push_back_state_and_time {
    std::vector< state_t > &m_states;
    std::vector< double > &m_times;

    // constructor for struct, initializes member variables with the arguments
    push_back_state_and_time( std::vector< state_t > &states , std::vector< double > &times ) : m_states( states ) , m_times( times ) { }

    // overloads the call operator () -> The struct becomes callable
    void operator()( const state_t &x , double t )
    {
        m_states.push_back( x );
        m_times.push_back( t );
    }
};

class System {
    double m_gam;
    control_t &u_t;
public:
    System( double gamma, control_t &u );
    void setControl(const control_t &u);
    void operator() ( const state_t &x , state_t &dxdt , const double /* t */ );
};

class Simulation {
    state_t x;
    control_t control_input;
    System system;
    push_back_state_and_time state_recorder;
    boost::numeric::odeint::runge_kutta4< state_t > stepper;
public:
    std::vector< state_t > states;
    std::vector< double > times;
    Simulation(state_t x_0);
    void step(control_t u,  const double t, const double dt);
};
