#include "huffman.h"

void select(HuffmanTree &HT, long long int n)
{
    //一次循环 如果简单的写两次循环 在节点太多的情况下会炸
    long long int s1 = 0, s2 = 0;
    for (long long int i = 1; i <= n; i++)
    {
        if (HT[i].parent != 0)
            continue;
        if (HT[i].weight < HT[s2].weight)
        {
            if (HT[i].weight < HT[s1].weight)
            {
                s2 = s1;
                s1 = i;
            }
            else
                s2 = i;
        }
    }
    HT[s1].parent = n + 1;
    HT[s2].parent = n + 1;
    HT[n + 1].weight = HT[s1].weight + HT[s2].weight;
    HT[n + 1].lchild = s1;
    HT[n + 1].rchild = s2;
}

void init(HuffmanTree &HT, std::map<int, int> &map, std::map<int, char *> &HC)
{
    std::cout << "正在构造Huffman树：" << std::endl;
    //初始化 huffman树
    long long int fre = map.size();
    HT = (HuffmanTree)malloc((2 * fre) * sizeof(HTNode));
    for (long long int i = 0; i < 2 * fre; i++)
    {
        HT[i].key = 0;
        HT[i].weight = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
    }
    std::map<int, int>::iterator iter;
    int index = 1;
    HT[0].weight = INT_MAX;
    for (iter = map.begin(); iter != map.end(); iter++, index++)
    {
        HT[index].key = iter->first;
        HT[index].weight = iter->second;
    }
    //构造 huffman树
    for (long long int i = fre + 1; i < 2 * fre; i++)
        select(HT, i - 1);
    //构造 huffman编码
    char *cd = (char *)malloc(fre * sizeof(char));
    cd[fre - 1] = '\0';
    for (long long int i = 1; i <= fre; i++)
    {
        long long int start = fre - 1;
        long long int j, p;
        for (j = i, p = HT[i].parent; p != 0; j = p, p = HT[p].parent)
        {
            if (HT[p].lchild == j)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        HC[HT[i].key] = (char *)malloc((fre - start) * sizeof(char));
        strcpy(HC[HT[i].key], &cd[start]);
    }
}

void init_for_de(HuffmanTree &HT, std::map<int, int> &map)
{
    std::cout << "正在构造Huffman树：" << std::endl;
    //初始化 huffman树
    long long int fre = map.size();
    HT = (HuffmanTree)malloc((2 * fre) * sizeof(HTNode));
    for (long long int i = 0; i < 2 * fre; i++)
    {
        HT[i].key = 0;
        HT[i].weight = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
    }
    std::map<int, int>::iterator iter;
    int index = 1;
    HT[0].weight = INT_MAX;
    for (iter = map.begin(); iter != map.end(); iter++, index++)
    {
        HT[index].key = iter->first;
        HT[index].weight = iter->second;
    }
    //构造 huffman树
    for (long long int i = fre + 1; i < 2 * fre; i++)
        select(HT, i - 1);
}

void output_huffmantree(HuffmanTree &HT, std::map<int, int> &map)
{
    std::cout << "Huffman树：" << std::endl;
    printf("       |  key   | weight | parent |  lch   | rch \n");
    int fre = map.size();
    for (long long int i = 1; i < 2 * fre; i++)
        printf("%6lld | %6lld | %6d | %6lld | %6lld | %6lld \n", i, HT[i].key, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
}