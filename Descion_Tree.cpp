#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>

using namespace std;

// --------------------------------------------------
// Node of the Decision Tree
// --------------------------------------------------

struct Node {
    bool isLeaf;

    int prediction;       // Class if this is a leaf

    int featureIndex;     // Which feature to split on
    double threshold;     // Value used for splitting

    Node* left;
    Node* right;

    Node() {
        isLeaf = false;
        prediction = -1;
        featureIndex = -1;
        threshold = 0;

        left = nullptr;
        right = nullptr;
    }
};


// --------------------------------------------------
// Decision Tree Class
// --------------------------------------------------

class DecisionTree {

private:

    int maxDepth;


    // --------------------------------------------------
    // Find the majority class
    // --------------------------------------------------

    int majorityClass(const vector<int>& y) {

        map<int, int> frequency;

        for (int label : y) {
            frequency[label]++;
        }

        int bestClass = -1;
        int bestCount = 0;

        for (auto& p : frequency) {

            if (p.second > bestCount) {
                bestCount = p.second;
                bestClass = p.first;
            }
        }

        return bestClass;
    }


    // --------------------------------------------------
    // Calculate Gini Impurity
    // --------------------------------------------------

    double gini(const vector<int>& y) {

        if (y.empty())
            return 0;

        map<int, int> frequency;

        for (int label : y) {
            frequency[label]++;
        }

        double impurity = 1.0;

        int n = y.size();

        for (auto& p : frequency) {

            double probability =
                (double)p.second / n;

            impurity -= probability * probability;
        }

        return impurity;
    }


    // --------------------------------------------------
    // Split dataset
    // --------------------------------------------------

    void split(
        const vector<vector<double>>& X,
        const vector<int>& y,
        int feature,
        double threshold,
        vector<vector<double>>& leftX,
        vector<int>& leftY,
        vector<vector<double>>& rightX,
        vector<int>& rightY
    ) {

        for (int i = 0; i < X.size(); i++) {

            if (X[i][feature] <= threshold) {

                leftX.push_back(X[i]);
                leftY.push_back(y[i]);

            }
            else {

                rightX.push_back(X[i]);
                rightY.push_back(y[i]);
            }
        }
    }


    // --------------------------------------------------
    // Find the best split
    // --------------------------------------------------

    void bestSplit(
        const vector<vector<double>>& X,
        const vector<int>& y,
        int& bestFeature,
        double& bestThreshold
    ) {

        double bestGini =
            numeric_limits<double>::infinity();

        bestFeature = -1;
        bestThreshold = 0;


        int numberOfFeatures = X[0].size();


        // Try every feature
        for (int feature = 0;
             feature < numberOfFeatures;
             feature++) {


            // Try every possible threshold
            for (int i = 0; i < X.size(); i++) {

                double threshold = X[i][feature];


                vector<vector<double>> leftX;
                vector<int> leftY;

                vector<vector<double>> rightX;
                vector<int> rightY;


                split(
                    X,
                    y,
                    feature,
                    threshold,
                    leftX,
                    leftY,
                    rightX,
                    rightY
                );


                // Ignore useless split
                if (leftY.empty() || rightY.empty())
                    continue;


                // Weighted Gini

                double leftGini = gini(leftY);
                double rightGini = gini(rightY);


                double weightedGini =
                    ((double)leftY.size() / y.size())
                    * leftGini
                    +
                    ((double)rightY.size() / y.size())
                    * rightGini;


                // Is this the best split?
                if (weightedGini < bestGini) {

                    bestGini = weightedGini;

                    bestFeature = feature;

                    bestThreshold = threshold;
                }
            }
        }
    }


    // --------------------------------------------------
    // Recursively build tree
    // --------------------------------------------------

    Node* buildTree(
        const vector<vector<double>>& X,
        const vector<int>& y,
        int depth
    ) {

        Node* node = new Node();


        // --------------------------------------------
        // Stopping condition 1:
        // All samples belong to same class
        // --------------------------------------------

        bool sameClass = true;

        for (int label : y) {

            if (label != y[0]) {

                sameClass = false;
                break;
            }
        }


        if (sameClass) {

            node->isLeaf = true;
            node->prediction = y[0];

            return node;
        }


        // --------------------------------------------
        // Stopping condition 2:
        // Maximum depth reached
        // --------------------------------------------

        if (depth >= maxDepth) {

            node->isLeaf = true;

            node->prediction =
                majorityClass(y);

            return node;
        }


        // --------------------------------------------
        // Find best split
        // --------------------------------------------

        int bestFeature;

        double bestThreshold;


        bestSplit(
            X,
            y,
            bestFeature,
            bestThreshold
        );


        // --------------------------------------------
        // No useful split
        // --------------------------------------------

        if (bestFeature == -1) {

            node->isLeaf = true;

            node->prediction =
                majorityClass(y);

            return node;
        }


        // --------------------------------------------
        // Store split information
        // --------------------------------------------

        node->featureIndex = bestFeature;

        node->threshold = bestThreshold;


        // --------------------------------------------
        // Create left and right datasets
        // --------------------------------------------

        vector<vector<double>> leftX;
        vector<int> leftY;

        vector<vector<double>> rightX;
        vector<int> rightY;


        split(
            X,
            y,
            bestFeature,
            bestThreshold,
            leftX,
            leftY,
            rightX,
            rightY
        );


        // --------------------------------------------
        // Recursively build left subtree
        // --------------------------------------------

        node->left =
            buildTree(leftX, leftY, depth + 1);


        // --------------------------------------------
        // Recursively build right subtree
        // --------------------------------------------

        node->right =
            buildTree(rightX, rightY, depth + 1);


        return node;
    }


    // --------------------------------------------------
    // Prediction for one sample
    // --------------------------------------------------

    int predictSample(
        Node* node,
        const vector<double>& sample
    ) {

        // We reached a leaf
        if (node->isLeaf) {

            return node->prediction;
        }


        // Go left
        if (sample[node->featureIndex]
            <= node->threshold) {

            return predictSample(
                node->left,
                sample
            );
        }


        // Go right
        return predictSample(
            node->right,
            sample
        );
    }


public:

    // --------------------------------------------------
    // Constructor
    // --------------------------------------------------

    DecisionTree(int depth = 3) {

        maxDepth = depth;
    }


    // --------------------------------------------------
    // Train
    // --------------------------------------------------

    Node* train(
        const vector<vector<double>>& X,
        const vector<int>& y
    ) {

        return buildTree(X, y, 0);
    }


    // --------------------------------------------------
    // Predict
    // --------------------------------------------------

    int predict(
        Node* root,
        const vector<double>& sample
    ) {

        return predictSample(root, sample);
    }
};


// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main() {

    // -----------------------------------------------
    // Dataset
    //
    // Feature 0 = Study Hours
    // Feature 1 = Attendance
    //
    // Target:
    // 0 = Fail
    // 1 = Pass
    // -----------------------------------------------

    vector<vector<double>> X = {

        {1, 40},
        {2, 50},
        {3, 60},
        {4, 70},
        {5, 80},
        {6, 90}
    };


    vector<int> y = {

        0,
        0,
        1,
        1,
        1,
        1
    };


    // -----------------------------------------------
    // Create Decision Tree
    // -----------------------------------------------

    DecisionTree tree(3);


    // -----------------------------------------------
    // Train
    // -----------------------------------------------

    Node* root =
        tree.train(X, y);


    // -----------------------------------------------
    // Test sample
    //
    // Study Hours = 2.5
    // Attendance = 55
    // -----------------------------------------------

    vector<double> student = {

        2.5,
        55
    };


    int prediction =
        tree.predict(root, student);


    // -----------------------------------------------
    // Print result
    // -----------------------------------------------

    if (prediction == 1)
        cout << "Pass" << endl;

    else
        cout << "Fail" << endl;


    return 0;
}