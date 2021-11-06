#include "huffman.h"

void select(HuffmanTree &HT, int n)
{
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent != 0)
            continue;
        if (HT[s1].weight > HT[i].weight)
            s1 = i;
    }
    HT[s1].parent = n + 1;
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent != 0)
            continue;
        if (HT[s2].weight > HT[i].weight)
            s2 = i;
    }
    HT[s2].parent = n + 1;
    HT[n + 1].weight = HT[s1].weight + HT[s2].weight;
    HT[n + 1].lchild = s1;
    HT[n + 1].rchild = s2;
}

void init(HuffmanTree &HT, std::map<char, int> &map, std::map<char, char *> &HC, char *&re)
{
    int fre = map.size();
    fre++;
    HT = (HuffmanTree)malloc((2 * fre) * sizeof(HTNode));
    for (int i = 0; i < 2 * fre; i++)
    {
        HT[i].key = ' ';
        HT[i].weight = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
    }
    std::map<char, int>::iterator iter;
    int index = 1;
    HT[0].weight = INT_MAX;
    for (iter = map.begin(); iter != map.end(); iter++, index++)
    {
        HT[index].key = iter->first;
        HT[index].weight = iter->second;
    }
    for (int i = fre + 1; i < 2 * fre; i++)
        select(HT, i - 1);
    char *cd = (char *)malloc(fre * sizeof(char));
    cd[fre - 1] = '\0';
    for (int i = 1; i <= fre; i++)
    {
        int start = fre - 1;
        int j, p;
        for (j = i, p = HT[i].parent; p != 0; j = p, p = HT[p].parent)
        {
            if (HT[p].lchild == j)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        if (i != fre)
        {
            HC[HT[i].key] = (char *)malloc((fre - start) * sizeof(char));
            strcpy(HC[HT[i].key], &cd[start]);
        }
        else
        {
            re = &cd[start];
        }
    }
}