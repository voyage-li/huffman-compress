#include "huffman.h"

void init(HuffmanTree &HT, std::map<int, int> &map, std::unordered_map<int, char *> &HC, int tree_n)
{
    std::cout << "正在构造Huffman树：" << std::endl;
    //初始化 huffman树
    long long int fre = map.size();
    HT = new HTNode[2 * fre];
    for (long long int i = 0; i < 2 * fre; i++)
    {
        HT[i].num = i;
        HT[i].key = 0;
        HT[i].weight = 0;
        for (int j = 0; j < tree_n; j++)
            HT[i].child[j] = 0;
        HT[i].parent = 0;
    }
    int index = 1;
    HT[0].weight = INT_MAX;
    for (auto iter : map)
    {
        HT[index].key = iter.first;
        HT[index].weight = iter.second;
        index++;
    }

    //使用优先队列构造huffman树
    std::priority_queue<HTNode> ans;
    for (int i = 1; i <= fre; i++)
        ans.push(HT[i]);

    if (tree_n != 2)
    {
        int blank;
        if (fre % (tree_n - 1) == 0)
            blank = 1;
        else
            blank = tree_n - fre % (tree_n - 1);
        if (blank != tree_n - 1)
        {
            HuffmanTree Tree_blank = new HTNode;
            Tree_blank->key = 0;
            Tree_blank->parent = 0;
            Tree_blank->weight = 0;
            for (int j = 0; j < tree_n; j++)
                Tree_blank->child[j] = 0;
            for (int i = 0; i < blank; i++)
            {
                Tree_blank->num = fre + i + 1;
                ans.push(*Tree_blank);
            }
        }
    }

    //要从加了0之后开始计算 即修正fre

    for (long long int now = fre + 1; now < 2 * fre; now++)
    {
        int now_weight = 0;
        for (int i = 0; i < tree_n; i++)
        {
            HTNode temp_Node = ans.top();
            HT[temp_Node.num].parent = now;
            HT[now].child[i] = temp_Node.num;
            now_weight += temp_Node.weight;
            ans.pop();
        }
        HT[now].weight = now_weight;
        if (ans.empty())
            break;
        ans.push(HT[now]);
    }

    //构造 huffman编码
    char *cd = (char *)malloc(fre * sizeof(char));
    cd[fre - 1] = '\0';
    for (long long int i = 1; i <= fre; i++)
    {
        long long int start = fre - 1;
        long long int j, p;
        for (j = i, p = HT[i].parent; p != 0; j = p, p = HT[p].parent)
        {
            int index = 0;
            while (HT[p].child[index] != j)
                index++;
            int wei = judge(tree_n);
            for (int i = 0; i <= wei - 1; i++)
                cd[--start] = ((index >> i) & 1) + '0';
        }
        HC[HT[i].key] = (char *)malloc((fre - start) * sizeof(char));
        strcpy(HC[HT[i].key], &cd[start]);
    }
}
void init_for_de(HuffmanTree &HT, std::map<int, int> &map, int tree_n)
{
    std::cout << "正在构造Huffman树：" << std::endl;
    //初始化 huffman树
    long long int fre = map.size();
    HT = new HTNode[2 * fre];
    for (long long int i = 0; i < 2 * fre; i++)
    {
        HT[i].num = i;
        HT[i].key = 0;
        HT[i].weight = 0;
        for (int j = 0; j < tree_n; j++)
            HT[i].child[j] = 0;
        HT[i].parent = 0;
    }
    int index = 1;
    HT[0].weight = INT_MAX;
    for (auto iter : map)
    {
        HT[index].key = iter.first;
        HT[index].weight = iter.second;
        index++;
    }

    //使用优先队列构造huffman树
    std::priority_queue<HTNode> ans;
    for (int i = 1; i <= fre; i++)
        ans.push(HT[i]);

    if (tree_n != 2)
    {
        int blank;
        if (fre % (tree_n - 1) == 0)
            blank = 1;
        else
            blank = tree_n - fre % (tree_n - 1);
        if (blank != tree_n - 1)
        {
            HuffmanTree Tree_blank = new HTNode;
            Tree_blank->key = 0;
            Tree_blank->parent = 0;
            Tree_blank->weight = 0;
            for (int j = 0; j < tree_n; j++)
                Tree_blank->child[j] = 0;
            for (int i = 0; i < blank; i++)
            {
                Tree_blank->num = fre + i + 1;
                ans.push(*Tree_blank);
            }
        }
    }

    for (long long int now = fre + 1; now < 2 * fre; now++)
    {
        int now_weight = 0;
        for (int i = 0; i < tree_n; i++)
        {
            HTNode temp_Node = ans.top();
            HT[temp_Node.num].parent = now;
            HT[now].child[i] = temp_Node.num;
            now_weight += temp_Node.weight;
            ans.pop();
        }
        HT[now].weight = now_weight;
        if (ans.empty())
            break;
        ans.push(HT[now]);
    }
}

void output_huffmantree(HuffmanTree &HT, std::map<int, int> &map, int tree_n)
{
    std::cout << "Huffman树：" << std::endl;
    printf("       |  key   | weight | parent |  ch\n");
    int fre = map.size();
    for (long long int i = 1; i < 2 * fre; i++)
    {
        printf("%6lld | %6lld | %6d | %6lld ", i, HT[i].key, HT[i].weight, HT[i].parent);
        for (int j = 0; j < tree_n; j++)
            printf("| %6lld ", HT[i].child[j]);
        putchar('\n');
        if (HT[i].parent == 0)
            break;
    }
}

int judge(int a) //判断编码
{
    if (a <= 2)
        return 1;
    else if (a > 2 && a <= 4)
        return 2;
    else if (a > 4 && a <= 8)
        return 3;
    else
        return 4;
}