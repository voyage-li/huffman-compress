#pragma once
#include <bits/stdc++.h>
typedef struct HTNode
{
    int key;
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

void init(HuffmanTree &HT, std::map<int, int> &map, std::map<int, char *> &HC);
void select(HuffmanTree &HT, int n);
void output_huffmantree(HuffmanTree &HT, std::map<int, int> &map);