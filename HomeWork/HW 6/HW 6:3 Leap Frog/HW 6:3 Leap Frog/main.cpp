#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

int leaps(int index, int counter, vector<int>pads)
{
    if(index>pads.size()-1)
        return counter;
    if(pads[index]==0)
    {
        if(index<=1)
        {
            counter = -1;
            return counter;
        }
        else
            index -=1;
    }
    index += pads[index];
    return leaps(index, counter+1, pads);
}

int main()
{
    //vector<int> list = {1,3,5,8,9,2,6,7,6,8,9};//3
    //vector<int> list = {1,0,10,5,11,3}; //-1
    //vector<int> list = {1,3,5,8,9,2,6,7,6,8,9};  //3
    vector<int> list = {1,4,3,2,2,0,9,5,10,8};  //4
    
    
    int index = 0;
    int counter = 0;
    
    cout << leaps(index, counter, list)<<endl;
    
    
    //notes
    //make a sorted list with the values max
    
    
}
