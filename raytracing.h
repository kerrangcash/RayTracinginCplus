#ifndef RAYTRACING_H
#define RAYTRACING_H

#include <cmath>
#include<limits>
#include<memory>
#include<random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//constraints

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//some utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.);
    static std::mt19937 genertator;
    return distribution(genertator)
}

//useful headers 

#include "ray.h"
#include "vec3.h"

#endif