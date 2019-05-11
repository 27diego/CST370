#include <iostream>
#include <vector>
using namespace std;

int stairs(int cost, int index, vector<int> list)
{
    if(index==list.size()-1 || index == list.size())
    {
        return cost;
    }
    cost += list[index];
    
    if(index+4<list.size())
    {
        if(list[index+1] + list[index+3]<list[index+2] + list[index+4])
        {
            index+=1;
        }
        else
            index+=2;
    }
    else if(list[index+1]<list[index+2])
    {
        index+=1;
    }
    else if(list[index+1]>list[index+2])
    {
        index+=2;
    }
    
    return stairs(cost, index, list);
}

int main()
{
    vector<int> list = {7,10,15,3,11};//24
    //vector<int> list = {11,9,2,4,15,19,3,25,18,8,0,1};//48
    std::reverse(list.begin(), list.end());

    cout<<stairs(0,0,list)<<endl;
}
