#include "DataIO.h"
#include <fstream>

mat DataIO::readData(const std::string &filename)
{
    // Check if the file exists
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("File does not exist: " + filename);
    }
    file.close();

    mat data;
    data.load(filename, raw_ascii);
    return data;
}

uvec DataIO::readLabels(const std::string &filename)
{
    // Check if the file exists
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("File does not exist: " + filename);
    }
    file.close();

    uvec labels;
    labels.load(filename, raw_ascii);
    return labels;
}

void DataIO::writeLabels(const std::string &filename, const uvec &labels)
{
    // Open the file for writing
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Write the labels to the file as -1 and 1
    for (uword i = 0; i < labels.n_elem; ++i)
    {
        int label = (labels(i) == 0) ? -1 : 1;
        file << label;
        if (i != labels.n_elem - 1)
        {
            file << std::endl;
        }
    }

    // Close the file
    file.close();
}
