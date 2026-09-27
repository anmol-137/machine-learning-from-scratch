# Machine Learning From Scratch

A collection of fundamental Machine Learning algorithms implemented **from scratch in C++**, without using NumPy, scikit-learn, TensorFlow, PyTorch, or other Machine Learning libraries.

The goal of this repository is to understand the **mathematics, logic, and internal working** of Machine Learning algorithms by implementing them manually.

---

## 🎯 Objective

This project focuses on understanding how Machine Learning algorithms work internally rather than relying on pre-built implementations.

Each algorithm is implemented step-by-step, covering concepts such as:

* Mathematical foundations
* Cost and loss functions
* Gradient Descent
* Parameter optimization
* Model training
* Prediction
* Evaluation
* Core Machine Learning concepts

---

## 🛠️ Technologies

* **Language:** C++
* **Compiler:** g++
* **Libraries:** C++ Standard Library

No specialized Machine Learning or numerical-computing libraries are used.

---

## 🚫 No ML / Numerical Libraries

This repository does not use:

* NumPy
* scikit-learn
* TensorFlow
* PyTorch
* Eigen
* Armadillo
* Other Machine Learning frameworks

All mathematical operations and algorithmic logic are implemented manually using C++.

---

## 📚 Algorithms

### Supervised Learning

* Linear Regression
* Logistic Regression
* K-Nearest Neighbors (KNN)
* Naive Bayes
* Decision Tree

### Unsupervised Learning

* K-Means Clustering
* Principal Component Analysis (PCA)

### Neural Networks

* Perceptron
* Neural Network
* Backpropagation

---

## 📂 Project Structure

```text
machine-learning-from-scratch/
│
├── README.md
│
├── linear_regression/
│   └── linear_regression.cpp
│
├── logistic_regression/
│   └── logistic_regression.cpp
│
├── knn/
│   └── knn.cpp
│
├── kmeans/
│   └── kmeans.cpp
│
├── decision_tree/
│   └── decision_tree.cpp
│
└── neural_network/
    └── neural_network.cpp
```

The repository will grow as additional algorithms are implemented.

---

## ⚙️ Setup and Run

### Prerequisites

Install a C++ compiler such as **g++**.

Check your installation:

```bash
g++ --version
```

### Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/machine-learning-from-scratch.git
```

Navigate into the repository:

```bash
cd machine-learning-from-scratch
```

### Compile an Algorithm

For example, to compile Linear Regression:

```bash
cd linear_regression
g++ linear_regression.cpp -o linear_regression
```

### Run

**Windows:**

```bash
.\linear_regression.exe
```

**Linux/macOS:**

```bash
./linear_regression
```

The same process can be followed for other algorithms.

---

## 🧠 Implementation Philosophy

Each algorithm follows a general process:

```text
Understand the Mathematics
          ↓
Design the Algorithm
          ↓
Implement in C++
          ↓
Train / Process Data
          ↓
Generate Predictions
          ↓
Evaluate Results
          ↓
Understand the Internals
```

The emphasis is on **understanding and implementation**, not simply obtaining a working prediction.

---

## 📈 Learning Goals

Through this project, I aim to develop a deeper understanding of:

* Linear and logistic models
* Optimization algorithms
* Gradient Descent
* Loss functions
* Probability
* Classification
* Regression
* Clustering
* Decision Trees
* Neural Networks
* Backpropagation
* Machine Learning mathematics
* Efficient C++ implementation

---

## 🚀 Future Expansion

The repository will gradually expand with additional Machine Learning algorithms, optimization techniques, neural networks, and eventually selected Deep Learning concepts.

---

## 📌 Disclaimer

This is primarily a **learning and educational project** created to understand the internal mechanics of Machine Learning algorithms through manual implementation.

---

**Built from scratch. Built to understand.**
