#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;


void ways(vector<int>list, int required, int sum, int &count, int index)
{
//    if(index > list.size())
//    {
//        index = 0;
//        return;
//    }
    if(sum>required)
    {
        sum=0;
        return;
    }
    if(sum==required)
    {
        count+=1;
        sum=0;
        return;
    }
    
    while(index!=list.size())
    {
        //sum +=list[index];
        ways(list, required, sum+list[index], count, index);
        index++;
    }
    
}


int main()
{
    int required = 100;
    vector<int> coins = {10,5,25,1,50};
    
    int count=0;
    ways(coins, required, 0, count, 0);
    cout<<count<<endl;
}

//13
