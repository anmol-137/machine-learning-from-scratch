#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<vector<double>> data = {
        {1,1,0},
        {1.5,2,0},
        {3,4,1},
        {3.5,5,1}
    };
    double x =2,y = 2.5;
    int k = 3;
    vector<double> distances;
    for(int i = 0;i<data.size();i++)
    {
        double dx = x-data[i][0];
        double dy = y-data[i][0];
        double distance = sqrt(dx*dx+dy*dy);
        distances.push_back(distance);
    }
    int count0 = 0;
    int count1 = 0;
    for(int n = 0;n<k;n++)
    {
        int nearest =0;
        for(int i = 1;i<distances.size();i++)
        {
            if(distances[i]<distances[nearest])
            {
                nearest = i;
            }

        }
        if(data[nearest][2] == 0)
        count0++;
        else
        count1++;
        distances[nearest] = 999999;
    }
    if(count0>count1)
    cout<< "predicted class : 0";
    else
    cout<<"predicted class:1";
    return 0;

}