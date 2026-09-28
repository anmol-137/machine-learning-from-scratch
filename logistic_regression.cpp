#include<bits/stdc++.h>
using namespace std;
class LogisticRegression
{
    private:
    double w;
    double b;
    double learning_rate;
    int epochs;
    double sigmoid(double z)
    {
        return 1.0/(1.0+exp(-z));
    }
    public:
    LogisticRegression(double lr = 0.01,int epochs = 1000)
    {
        w = 0.0;
        b = 0.0;
        learning_rate = lr;
        this->epochs = epochs;
    }
    double predict_probability(double x)
    {
        double z = w*x+b;
        return sigmoid(z);
    }
    int predict(double x)
    {
        double probability = predict_probability(x);
        if(probability>= 0.5)
        return 1;
        else 
        return 0;
    }
    double loss(vector<double>&x,vector<double>&y)
    {
        double total_loss = 0.0;
        int n = x.size();
        for(int i = 0;i<n;i++)
        {
            double probability = predict_probability(x[i]);
            probability = max(1e-15,min(1.0-1e-15,probability));
            total_loss+= -(y[i]*log(probability)+(1-y[i])*log(1-probability));

        }
        return total_loss/n;
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
                double probability = predict_probability(x[i]);
                double error = probability-y[i];
                dw+= x[i]*error;
                db+=  error;
            }
            dw = dw/n;
            db = db/n;
            w = w-learning_rate*dw;
            b = b-learning_rate*db;
            if(epoch%100 == 0)
            {
                cout<<"Epoch: "<<epoch<<"Loss:"<<loss(x,y)<<endl;
            }
        }
    }
    void parameters()
    {
        cout<<"\n Learned weight :" <<w<<endl;
        cout<<" learned bias:" <<b<<endl;
    }
};
int main()
{
    vector<double>x = {1,2,3,4,5,6,7,8};
    vector<double>y = {0,0,0,0,1,1,1,1};
    LogisticRegression model(0.1,1000);
    model.fit(x,y);
    model.parameters();
    double input = 7;
    double probabilty = model.predict_probability(input);
    int prediction = model.predict(input);
    cout<<"\nInput "<< input<<endl;
    cout<<"probability "<<probabilty<<endl;
    cout<<"prediction"<<prediction<<endl;
    return 0;
}