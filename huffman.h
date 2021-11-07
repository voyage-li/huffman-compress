#pragma once
#include <bits/stdc++.h>
typedef struct HTNode
{
    long long int key;
    int weight;
    long long int parent, lchild, rchild;
} HTNode, *HuffmanTree;

void init(HuffmanTree &HT, std::map<int, int> &map, std::map<int, char *> &HC);
void init_for_de(HuffmanTree &HT, std::map<int, int> &map);
void select(HuffmanTree &HT, int n);
void output_huffmantree(HuffmanTree &HT, std::map<int, int> &map);