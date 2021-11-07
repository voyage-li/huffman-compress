#include "big.h"
#include <bits/stdc++.h>

big::big()
{
    now_byte = 0; //刚开始有两个字符代表压缩位数以及'|'(区分正文)
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

    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);
    std::ofstream outfile(ans_path.c_str(), std::ios::out | std::ios::binary);
    if (!infile)
    {
        std::cout << "文件打开错误！" << std::endl;
        return;
    }

    char tmp;
    int num;
    int fff;
    int char_size;

    //假设这里我是成功开了一个多线程

    infile >> char_size >> tmp; //获取压缩基本符号单元
    infile >> select >> tmp;    //获取压缩基本符号单元
    int every = select * 4;

    size = char_size;

    while (1)
    {
        infile >> fff >> tmp >> num;
        map[fff] = num;

        infile.get(tmp);

        if (tmp != '|')
            break;
    }

    init_for_de(HT, map);

    std::cout << "开始解压..." << std::endl;
    std::cout << "[                                        ] 0%";

    pthread_t threads;
    poss_help tmp_struct;
    tmp_struct = {now_byte, size};
    pthread_create(&threads, NULL, possesion, (void *)&tmp_struct);

    char ans[8];
    char c;
    int index = 0;
    int fre = map.size();
    int now = 2 * fre - 1;
    int now_bit = 0; //记录当前输出字符到的bit
    int out_tmp = 0; //用来记录输出的字符
    while (1)
    {
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
                //获取对应权值对应的 bit位
                int int_to_char = HT[now].key;
                char ans[every + 1];
                ans[every] = '\0';
                for (int j = 0; j < every; j++)
                    ans[j] = ((int_to_char >> (every - 1 - j)) & 1) + '0';

                int j = 0;
                while (ans[j] != '\0')
                {
                    now_bit++;
                    out_tmp += (ans[j] - '0') << (8 - now_bit);
                    if (now_bit == 8)
                    {
                        char_size--;
                        outfile.put(out_tmp);
                        now_byte++;
                        tmp_struct = {now_byte, size};
                        out_tmp = 0;
                        now_bit = 0;
                    }
                    j++;
                    if (char_size == 0)
                        break;
                }
                now = 2 * fre - 1;
            }
            if (index == 8 || char_size == 0)
                break;
        }
        if (char_size == 0)
            break;
    }

    std::cout << '\r' << "[########################################] 100%  ";
    infile.close();
    outfile.close();
}
void big::decompress_output()
{
}