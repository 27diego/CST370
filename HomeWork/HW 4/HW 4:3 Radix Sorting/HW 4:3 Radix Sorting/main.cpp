#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


void printList(vector<int> list)
{
    for(int i:list)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}

int getDigit(int num, int currDigit) {
    return (int)(num / pow(10, currDigit)) % 10;
}


vector<int> radixSort(vector<int>list, int max, int digit_place, int currentDigit)
{
    if(list[list.size()-1]==max)
    {
        return list;
    }
    
    vector<int> sorted;
    vector<vector<int>*> buckets;
    
    for(int x=0;x<10;x++)
    {
        buckets.push_back(new vector<int>());
    }
    
    for(int x=0;x<list.size(); x++)
    {
        buckets[getDigit(list[x], currentDigit)]->push_back(list[x]);
    }
    
    for(int x=0;x<10;x++)
    {
        for(int y=0;y<buckets[x]->size();y++)
        {
            sorted.push_back((*buckets[x])[y]);
        }
    }
        printList(sorted);
        return radixSort(sorted, max, digit_place, currentDigit+1);
}

int main()
{
    vector<int> list{9,87,199,15,3,214,19,26,58,2,102,23};
    
    int max = *max_element(list.begin(), list.end());
    string find_length = to_string(max);
    radixSort(list, (int)max, find_length.length(), 0);
}

 
