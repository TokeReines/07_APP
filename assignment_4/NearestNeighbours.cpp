#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <map>
#include "armadillo.hpp"
#include "DataIO.h"

using namespace std;

// Function to compute the Euclidean distance between two data points
double computeDistance(const rowvec &point1, const rowvec &point2)
{
    return norm(point1 - point2, 2); // Euclidean norm
}

// Function to perform K Nearest Neighbor classification
int knnClassification(const mat &trainData, const uvec &trainLabels, const rowvec &testData, int k)
{
    multimap<double, int> labelDistancePairs; // Store label-distance pairs

    // Compute distances and store label-distance pairs
    for (uword i = 0; i < trainData.n_rows; i++)
    {
        double distance = computeDistance(trainData.row(i), testData);
        labelDistancePairs.insert(make_pair(distance, trainLabels(i)));
    }

    // Perform majority voting among the K nearest neighbors
    map<int, int> labelCounts;
    for (auto it = labelDistancePairs.begin(); it != labelDistancePairs.end() && k > 0; ++it, --k)
    {
        labelCounts[it->second]++;
    }

    // Find the label with the maximum count
    int maxCount = 0;
    int predictedLabel = -1;
    for (const auto &pair : labelCounts)
    {
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            predictedLabel = pair.first;
        }
    }

    return predictedLabel;
}

// Function to calculate and output the accuracy of the classification
double calculateAccuracy(const uvec &trueLabels, const uvec &predictedLabels)
{
    uvec comparison = (trueLabels == predictedLabels);
    double numCorrect = accu(comparison);
    double totalLabels = trueLabels.n_elem;
    double accuracy = (numCorrect / totalLabels) * 100.0;
    return accuracy;
}

int main()
{
    // Read the training data
    mat trainData = DataIO::readData("./data/dataX.dat");

    // Read the training labels
    uvec trainLabels = DataIO::readLabels("./data/dataY.dat");

    // Read the test data
    mat testData = DataIO::readData("./data/dataXtest.dat");

    // Perform K Nearest Neighbor classification for each test data point
    int k = 5;
    uvec predictedLabels(testData.n_rows);
    for (uword i = 0; i < testData.n_rows; i++)
    {
        predictedLabels(i) = knnClassification(trainData, trainLabels, testData.row(i), k);
    }

    // Calculate and output the accuracy
    uvec trueLabels = DataIO::readLabels("data/dataY.dat");
    trueLabels.resize(predictedLabels.size());

    double accuracy = calculateAccuracy(trueLabels, predictedLabels);
    cout << "Accuracy: " << accuracy << "%" << endl;
    cout << "Classification completed. Predicted labels saved in NN.dat." << endl;

    // Write the predicted labels to a file
    DataIO::writeLabels("NN.dat", predictedLabels);

    return 0;
}
