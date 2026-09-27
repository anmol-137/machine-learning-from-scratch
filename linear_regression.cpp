#include<bits/stdc++.h>
using namespace std;
class LinearRegression
{
    private:
    double w;
    double b;
    double learning_rate;
    int epochs;
    public:
    LinearRegression(double lr = 0.01, int epochs = 1000)
    {
        w = 0.0;
        b = 0.0;
        learning_rate = lr;
        this->epochs = epochs;
    }
    double predict(double x)
    {
        return w*x+b;
    }
    double mse(vector<double>&x,vector<double>&y)
    {
        double total_error = 0.0;
        
        for(int i = 0;i<x.size();i++)
        {
            double prediction = predict(x[i]);
            double error = prediction-y[i];
            total_error += error*error;

        }
        return total_error/x.size();
    }
    void fit(vector<double>&x,vector<double>&y)
    {
        int n = x.size();
        for(int epoch = 0;epoch<epochs;epoch++)
        {
            double dw = 0.0;
            double db = 0.0;
            for(int i = 0;i<n;i++)
            {
                double prediction = predict(x[i]);
                double  error = prediction-y[i];
                dw+= x[i]*error;
                db+= error;
            }
            dw = (2.0/n)*dw;
            db = (2.0/n)*db;
            w = w-learning_rate*dw;
            b = b-learning_rate*db;
            if(epoch%100 == 0)
            {
                cout<<"Epoch"<<epoch<<"MSE"<<mse(x,y)<<endl;
            }
        }
    }
    void parameters()
    {
        cout<<"learned weight"<<w<<endl;
        cout<<"learned bias"<<b<<endl;
    }
};
int main()
{
    vector<double>x = {1,2,3,4,5};
    vector<double>y = {3,5,7,9,11};
    LinearRegression model(0.01,1000);
    model.fit(x,y);
    model.parameters();
    double input= 6;
    double prediction = model.predict(input);
    cout<<"\n Prediction for x "<<input<<" :"<< prediction <<endl;
    return 0;
}