#include "big.h"
#include <bits/stdc++.h>

big::big()
{
    now_byte = 0;
}
void big::decompress()
{
    decompress_input();
    // decompress_output();
    std::cout << "\n已完成文件解压！" << std::endl;
    std::cout << "解压文件路径：" << std::endl;
    std::cout << ans_path << std::endl;
    getchar();
}
void big::decompress_input()
{
    std::cout << "请输入需要解压的文件的路径:" << std::endl;
    getchar();
    getline(std::cin, data_path);
    std::cout << "请输入解压文件存储路径:" << std::endl;
    getline(std::cin, ans_path);

    system("clear");
    std::cout << "               解压进度                  " << std::endl;
    std::cout << "正在获取文件大小..." << std::endl;

    std::ifstream tempfile(data_path.c_str(), std::ios::in | std::ios::binary);
    tempfile.seekg(0, std::ios::end);
    size = tempfile.tellg();
    tempfile.close();

    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);
    std::ofstream outfile(ans_path.c_str(), std::ios::out | std::ios::binary);
    if (!infile)
    {
        std::cout << "文件打开错误！" << std::endl;
        return;
    }
    char c, tmp;
    int num;

    std::cout << "开始解压..." << std::endl;
    std::cout << "[                                        ] 0%";

    pthread_t threads;
    poss_help tmp_struct;
    tmp_struct = {now_byte, size};
    pthread_create(&threads, NULL, possesion, (void *)&tmp_struct);

    while (1)
    {
        now_byte += 2;

        infile.get(c);
        infile.get(tmp);
        infile >> num;
        map[c] = num;

        int loc = 0;
        while (num != 0)
        {
            num /= 10;
            loc++;
        }
        now_byte += loc;

        infile.get(c);

        now_byte++;

        if (c != '|')
            break;

        tmp_struct = {now_byte, size};
    }

    init(HT, map, HC, re);

    char ans[8];
    int index = 0;
    int flag = 0;
    int fre = map.size() + 1;
    int now = 2 * fre - 1;
    while (1)
    {
        now_byte++;
        infile.get(c);
        int tt = c;
        index = 0;
        for (int i = 7; i >= 0; i--)
            ans[index++] = ((tt >> i) & 1) + '0';
        index = 0;
        while (1)
        {
            if (ans[index] == '0')
                now = HT[now].lchild;
            else
                now = HT[now].rchild;
            index++;
            if (HT[now].lchild == 0)
            {
                if (now != fre)
                {
                    // if (HT[now].key == '\n')
                    //     putchar('\n');
                    outfile.put(HT[now].key);
                    // putchar('\n');
                    now = 2 * fre - 1;
                }
                else
                    flag = 1;
            }
            if (flag == 1 || index == 8)
                break;
        }
        if (flag == 1)
            break;

        tmp_struct = {now_byte, size};
    }
    std::cout << '\r' << "[########################################] 100%  ";
    infile.close();
    outfile.close();
}
void big::decompress_output()
{
}