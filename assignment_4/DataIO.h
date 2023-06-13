#ifndef DATAIO_H
#define DATAIO_H

#include "armadillo.hpp"

using namespace arma;

class DataIO {
public:
    static mat readData(const std::string& filename);
    static vec readLabels(const std::string& filename);
    static void writeLabels(const std::string& filename, const vec& labels);
};

#endif // DATAIO_H
