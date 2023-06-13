#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <map>
#include "armadillo.hpp"

using namespace arma;

mat readData(const std::string &filename)
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

vec readLabels(const std::string &filename)
{
    // Check if the file exists
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("File does not exist: " + filename);
    }
    file.close();

    vec labels;
    labels.load(filename, raw_ascii);
    return labels;
}

void writeLabels(const std::string &filename, const vec &labels)
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
        file << labels(i);
        if (i != labels.n_elem - 1)
        {
            file << std::endl;
        }
    }

    // Close the file
    file.close();
}

using namespace std;

// Function to compute the Euclidean distance between two data points
double computeDistance(const rowvec &point1, const rowvec &point2)
{
    return norm(point1 - point2, 2); // Euclidean norm
}

// Pure Armadillo function to perform K Nearest Neighbor classification
int knnClassification(const mat &trainData, const vec &trainLabels, const rowvec &testData, int k) {
    // Calculate the Euclidean distance between each training data point and the test data
    mat diff = trainData.each_row() - testData;
    vec dists = sqrt(sum(square(diff), 1));

    // Find the indices of the k nearest neighbors
    uvec indices = sort_index(dists);

    // Get the labels of the k nearest neighbors
    vec nearestLabels = trainLabels.elem(indices.head(k));

    // Count the number of -1 and 1 labels
    int countNeg = 0;
    int countPos = 0;
    for (int i = 0; i < k; i++) {
        if (nearestLabels(i) == -1) {
            countNeg++;
        } else if (nearestLabels(i) == 1) {
            countPos++;
        }
    }

    // Return the label with the maximum count
    return (countNeg > countPos) ? -1 : 1;
}

// Function to perform K Nearest Neighbor classification
// int knnClassification(const mat &trainData, const vec &trainLabels, const rowvec &testData, int k)
// {
//     multimap<double, int> labelDistancePairs; // Store distance-label pairs

//     // Compute distances and store distance-label pairs
//     for (uword i = 0; i < trainData.n_rows; i++)
//     {
//         double distance = computeDistance(trainData.row(i), testData);
//         labelDistancePairs.insert(make_pair(distance, trainLabels(i)));
//     }

//     // Perform majority voting among the K nearest neighbors
//     map<int, int> labelCounts; // {label: count}
//     for (auto it = labelDistancePairs.begin(); it != labelDistancePairs.end() && k > 0; ++it, --k)
//     {
//         labelCounts[it->second]++;
//     }


//     // labelCounts = {1: 2, -1: 3}
//     // Find the label with the maximum count
//     int maxCount = 0;
//     int predictedLabel = -1;
//     cout <<  "\n----" << endl;
//     for (const auto &pair : labelCounts)
//     {
//         cout << pair.first << " " << pair.second << endl;
//         if (pair.second > maxCount)
//         {
//             maxCount = pair.second;
//             predictedLabel = pair.first;
//         }
//     }

//     return predictedLabel;
// }

// Function to calculate and output the accuracy of the classification
double calculateAccuracy(const vec &trueLabels, const vec &predictedLabels)
{
    double numCorrect = accu(trueLabels == predictedLabels);
    double totalLabels = trueLabels.n_elem;
    double accuracy = (numCorrect / totalLabels) * 100.0;
    return accuracy;
}

int main()
{
    // Read the training data
    mat trainData = readData("dataX.dat");

    // Read the training labels
    vec trainLabels = readLabels("dataY.dat");

    // Read the test data
    mat testData = readData("dataXtest.dat");

    // Perform K Nearest Neighbor classification for each test data point
    int k = 5;
    vec predictedLabels(testData.n_rows);
    for (uword i = 0; i < testData.n_rows; i++) 
    {
        predictedLabels(i) = knnClassification(trainData, trainLabels, testData.row(i), k);
    }

    // Calculate and output the accuracy
    // vec trueLabels = readLabels("dataYtest_knn.dat");

    // double accuracy = calculateAccuracy(trueLabels, predictedLabels);
    // cout << "Accuracy: " << accuracy << "%" << endl;
    // cout << "Classification completed. Predicted labels saved in NN.dat." << endl;

    // Write the predicted labels to a file
    writeLabels("NN.dat", predictedLabels);

    return 0;
}
