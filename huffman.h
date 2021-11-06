#pragma once
#include <bits/stdc++.h>
typedef struct HTNode
{
    char key;
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

void init(HuffmanTree &HT, std::map<int, int> &map, std::map<int, char *> &HC, char *&re);
void select(HuffmanTree &HT, int n);