#include <iostream>
#include <vector>
using namespace std;


class MaxHeap{
    vector<int> list;
    
public:
    int maxLookup()
    {
        return list[0];
    }
    int extractMax()
    {
        swap(0, list.size()-1);
        int temp = list[list.size()-1];
        list.pop_back();
        heapifyDown(0);
        return temp;
    }
    void deletion(int val)
    {
        swap(val, list.size()-1);
        list.pop_back();
        heapifyDown(val);
    }
    void insert(int val)
    {
        list.push_back(val);
        heapifyUp(list.size()-1);
        print();
    }
    int size()
    {
        return list.size();
    }
    bool empty() { return size() == 0;}
    void print() {
        cout<<"------------------"<<endl;
        for (auto n : list) {
            cout << n << endl;
        }
         cout<<"------------------"<<endl;
    }
    int pop() { return extractMax();}
    void push(int val) { insert(val);}
    vector<int> getData() { return list;}
private:
    void heapifyUp(int idx)
    {
        if (idx > 0) {
            int parent = (idx - 1) / 2;
           if(list[idx]>list[parent])
           {
               swap(parent, idx);
               heapifyUp(parent);
           }
        }
    }
    void heapifyDown(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int mini = i;
        
        if(list[left]>list[mini])
        {
            mini = left;
        }
        if(list[right]>list[mini])
        {
            mini = right;
        }
        if(mini!=i)
        {
            swap(mini, i);
            heapifyDown(mini);
        }
    }
    void swap(int i, int j)
    {
        int temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }
};


int main()
{
    MaxHeap max;
    
    cout<<max.size()<<endl;
    max.insert(5);
    cout<<max.maxLookup()<<endl;
    max.insert(18);
    cout<<max.maxLookup()<<endl;
    max.insert(3);
    cout<<max.maxLookup()<<endl;
    max.insert(12);
    max.insert(19);
    cout<<max.maxLookup()<<endl;
    max.extractMax();
    cout<<max.maxLookup()<<endl;
    max.insert(25);
    max.insert(6);
    max.insert(1);
    cout<<max.size()<<endl;
    max.extractMax();
    max.extractMax();
    max.extractMax();
    cout<<max.size()<<endl;
    max.deletion(1);
    max.deletion(1);
    max.deletion(0);
    cout<<max.size()<<endl;
    cout<<max.maxLookup()<<endl;
    
    
    
}

/*
 0
 5
 18
 18
 19
 18
 7
 4
 1
 1
 */
