#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dimensions(vector<vector<bool>> grid)
{
    vector<vector<int>*> indexes;
    for(int i= 0; i < grid.size(); i++) {
        indexes.push_back(new vector<int>());
    }
    
    for(int x=0;x<grid.size();x++)
    {
        for(int y=0;y<grid[x].size();y++)
        {
            if(grid[x][y]==0)
            {
                indexes[x]->push_back(y);
            }
        }
    }
    
    
    for(int x=0;x<indexes.size();x++)
    {
        for(int y=0;y<indexes[x]->size();y++)
        {
            cout<<(*indexes[x])[y];
        }
        cout<<endl;
    }
    
    
    return 0;
}

int main()
{
    vector<vector<bool>> grid = {
        {0,1,0,0},
        {1,0,0,0},
        {0,0,0,0},
        {0,0,1,0}
    };
    
    cout<<dimensions(grid);
    
}
//vector<vector<bool>> grid = {
//    {0,1,0},
//    {1,0,0},
//    {0,0,1}
//};
