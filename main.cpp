#include <bits/stdc++.h>
#include "huffman.h"
#include "small.h"
#include "big.h"
#include "tempwindow.h"
int main()
{
    while (1)
    {
        system("clear");
        std::cout << "请选择压缩或者解压：" << std::endl;
        std::cout << "1. 压缩" << std::endl;
        std::cout << "2. 解压" << std::endl;
        std::cout << "3. 退出" << std::endl;
        int tmp;
        std::cin >> tmp;
        if (tmp == 1)
        {
            small a;
            a.compress();
        }
        else if (tmp == 2)
        {
            big a;
            a.decompress();
        }
        else if (tmp == 3)
            break;
        else
            std::cout << "无效输入" << std::endl;
    }
    return 0;
}