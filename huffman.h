#pragma once
#include <bits/stdc++.h>
typedef struct HTNode
{
    char key;
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

void init(HuffmanTree &HT, std::map<char, int> &map, std::map<char, char *> &HC, char *&re);
void select(HuffmanTree &HT, int n);