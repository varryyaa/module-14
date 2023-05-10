#include <iostream>
#include "trie.h"

using namespace std;

Trie::Trie()
{
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        _root.children[i] = nullptr;
    }
    _root.isEndOfWord = false;
}

Trie::~Trie()
{
    clean();
}

TrieNode* Trie::getNewNode(void)
{
    struct TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        pNode->children[i] = nullptr;
    }
    return pNode;
}

void Trie::cleanInner(const TrieNode* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (pNode->children[i] != nullptr)
        {
            cleanInner(pNode->children[i]);
        }
    }
    if (pNode == &_root)
    {
        return;
    }
    delete pNode;
    pNode = nullptr;
}

bool Trie::isEmpty(TrieNode* pNode)
{
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (pNode->children[i] != nullptr)
        {
            return false;
        }
    }
    return true;
}

void Trie::insertKey(const string& key)
{
    TrieNode* node = &_root;

    for (int i = 0; i < key.length(); ++i)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
        {
            node->children[index] = getNewNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

void Trie::clean(void)
{
    cleanInner(&_root);
}

bool Trie::searchKey(const string& key, bool printFlag)
{
    TrieNode* pNode = &_root;

    for (int i = 0; i < key.length(); ++i)
    {
        int index = key[i] - 'a';
        if (pNode->children[index] == nullptr)
        {
            return false;
        }
        pNode = pNode->children[index];
    }

    if (printFlag == true)
    {
        string postfix;
        printVariants(pNode, key, postfix);
        return true;
    }
    return (pNode != nullptr && pNode->isEndOfWord);
}

void Trie::removeKey(const string& key)
{
    removeInner(&_root, key);
}

TrieNode* Trie::removeInner(TrieNode* root, string key, int depth)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (depth == key.size())
    {
        if (root->isEndOfWord)
        {
            root->isEndOfWord = false;
        }

        if (isEmpty(root))
        {
            delete (root);
            root = nullptr;
        }
        return root;
    }

    int index = key.at(depth) - 'a';
    root->children[index] = removeInner(root->children[index], key, depth + 1);

    if (isEmpty(root) && root->isEndOfWord == false)
    {
        delete (root);
        root = nullptr;
    }
    return root;
}

void Trie::printVariants(const TrieNode* pNode, const string& pre, string& post)
{
    if (pNode->isEndOfWord == true)
    {
        std::cout << pre + post << std::endl;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (pNode->children[i] != nullptr)
        {
            post += i + 'a';
            printVariants(pNode->children[i], pre, post);
        }
    }
    post = post.substr(0, post.length() - 1);
}