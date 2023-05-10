#pragma once
#include <string>
using namespace std;
const int ALPHABET_SIZE = 26;

struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

class Trie
{
public:
    Trie();
    ~Trie();

    void insertKey(const string& key);
    void clean(void);
    bool searchKey(const string& key, bool printFlag);
    void removeKey(const string& key);

private:
    TrieNode _root;

    TrieNode* getNewNode(void);
    void cleanInner(const TrieNode* pNode);
    bool isEmpty(TrieNode* pNode);
    TrieNode* removeInner(TrieNode* root, string key, int depth = 0);
    void printVariants(const TrieNode* pNode, const string& pre, string& post);
};