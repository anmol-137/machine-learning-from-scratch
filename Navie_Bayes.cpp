#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int>> data = {
        {0, 0, 0, 1},
        {0, 1, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0}
    };

    int numberOfFeatures = 3;
    int numberOfClasses = 2;
    int numberOfValues = 2;

    vector<int> example = {1, 1, 1};

    vector<double> score(numberOfClasses, 1.0);

    for (int c = 0; c < numberOfClasses; c++) {
        int classCount = 0;

        for (int i = 0; i < data.size(); i++) {
            if (data[i][numberOfFeatures] == c)
                classCount++;
        }

        score[c] = (double)classCount / data.size();

        for (int f = 0; f < numberOfFeatures; f++) {
            int matchingCount = 0;

            for (int i = 0; i < data.size(); i++) {
                if (data[i][numberOfFeatures] == c &&
                    data[i][f] == example[f]) {
                    matchingCount++;
                }
            }

            score[c] *= (double)(matchingCount + 1) /
                        (classCount + numberOfValues);
        }
    }

    int prediction = 0;

    for (int c = 1; c < numberOfClasses; c++) {
        if (score[c] > score[prediction])
            prediction = c;
    }

    if (prediction == 1)
        cout << "Prediction: Play outside" << endl;
    else
        cout << "Prediction: Don't play outside" << endl;

    return 0;
}