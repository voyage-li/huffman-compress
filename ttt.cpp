#include <bits/stdc++.h>
typedef struct TTT
{
    long long int num;       //表示第几个元素
    long long int key;       //对应元素的值
    int weight;              //权值
    long long int parent;    //双亲
    long long int child[16]; //孩子
    friend bool operator<(TTT a, TTT b)
    {
        return a.weight > b.weight;
    }
} TTT;

int main()
{
    std::priority_queue<TTT> s;
    int w;
    std::cin >> w;
    while (w >= 0)
    {
        struct TTT a;
        std::cin >> a.weight;
        s.push(a);
        std::cin >> w;
    }
    while (!s.empty())
    {
        std::cout << s.top().weight << '|';
        s.pop();
    }
    return 0;
}