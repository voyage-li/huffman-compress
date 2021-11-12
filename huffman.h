#pragma once
#include <bits/stdc++.h>
typedef struct HTNode
{
    long long int num;       //表示第几个元素
    long long int key;       //对应元素的值
    int weight;              //权值
    long long int parent;    //双亲
    long long int child[16]; //孩子
    friend bool operator<(HTNode a, HTNode b)
    {
        return a.weight > b.weight;
    }
} HTNode, *HuffmanTree;

bool operator>(HTNode a, HTNode b);

void init(HuffmanTree &HT, std::map<int, int> &map, std::map<int, char *> &HC, int tree_n);
void init_for_de(HuffmanTree &HT, std::map<int, int> &map, int tree_n);
void select(HuffmanTree &HT, int n);
void output_huffmantree(HuffmanTree &HT, std::map<int, int> &map);

int judge(int a);