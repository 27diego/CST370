#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

struct TrieNode{
    bool isWord;
    vector<TrieNode*> letters;
    
public:
    TrieNode()
    {
        letters = vector<TrieNode*>(26, nullptr);
    }
};

int getIndex(char c)
{
    return (int)c - (int)'a';
}


class Trie{
    TrieNode* root;
    
public:
    Trie()
    {
        root = new TrieNode();
    }
    
    void insert(string word)
    {
        TrieNode* current = root;
        int index = 0;
        
        for(int x = word.length()-1; x>=0;x--)
        {
            index = getIndex(word[x]);
            if(current->letters[index]==nullptr)
            {
                current->letters[index] = new TrieNode();
            }
            current = current->letters[index];
        }
        current->isWord = true;
    }
    
    void DFS(TrieNode* node, string word)
    {
        if(node->isWord && word!="")
        {
            string temp="";
            for(int x=word.size()-1;x>=0;x--)
            {
                temp.push_back(word[x]);
            }
            std::cout.width(6); std::cout << std::right << temp << '\n';
        }
        for(int x=0;x<node->letters.size();x++)
        {
            if(node->letters[x])
            {
                word.push_back(x+(int)'a');
                DFS(node->letters[x], word);
                word.pop_back();
            }
        }
    }
    
    void alphabetical()
    {
        DFS(root, "");
    }
    
    
};


int main()
{
    Trie* trie = new Trie();
    vector<string> names;
    string input = "";
    for(int x=0;x<5;x++)
    {
        cout<<"Enter name: "<<endl;
        cin>>input;
        names.push_back(input);
    }
    
    for(auto name : names)
    {
        trie->insert(name);
    }
    
    trie->alphabetical();
    
}

//int main()
//{
//    Trie* trie = new Trie();
//
//    vector<string> names{"apple", "banana", "grape", "kiwi", "pear", "airplane", "bicycle", "boat", "car"};
//
//    for(auto name : names)
//    {
//        trie->insert(name);
//    }
//
//    trie->alphabetical();
//
//}
