#include "small.h"
#include <bits/stdc++.h>

small::small()
{
    now_byte = 0;
}

void small::compress()
{
    std::cout << "请选择压缩的基本单元:" << std::endl;
    std::cout << "1. 0.5字节   2. 1.0字节" << std::endl;
    std::cout << "3. 1.5字节   4. 2.0字节" << std::endl;
    std::cout << "5. 2.5字节   6. 3.0字节" << std::endl;
    std::cout << "7. 3.5字节   8. 4.0字节" << std::endl;
    std::cin >> select;

    if (select < 1 || select > 8)
    {
        std::cout << "输入数据错误！" << std::endl;
        getchar();
        system("clear");
        return;
    }
    else
    {
        if (!compress_input())
            return;
        compress_output();
    }

    std::cout << "\n已完成文件压缩！" << std::endl;
    std::cout << "压缩文件路径：" << std::endl;
    std::cout << ans_path << std::endl;
    output_huffmantree(HT, map);
    getchar();
}

bool small::compress_input()
{
    std::cout << "请输入需要压缩的文件的路径:" << std::endl;
    getchar();
    getline(std::cin, data_path);
    std::cout << "请输入压缩文件存储路径:" << std::endl;
    getline(std::cin, ans_path);

    system("clear");
    std::cout << "               压缩进度                  " << std::endl;
    std::cout << "正在获取文件大小..." << std::endl;

    std::ifstream tempfile(data_path.c_str(), std::ios::in | std::ios::binary);
    if (!tempfile)
    {
        std::cout << "文件打开错误！" << std::endl;
        return false;
    }
    tempfile.seekg(0, std::ios::end);
    size = tempfile.tellg();
    tempfile.close();

    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);

    char c;
    int every = 8 * select * 0.5; //单位 bit
    int tt_key = 0;               //用来记录 key
    int now_bit = 0;              //用来记录当前读入了多少个bit
    int char_now = 0;             //用来记录当前读取的字符使用到的 bit
    while (infile.get(c))
    {
        char_now = 0;
        while (char_now < 8)
        {
            while (char_now < 8)
            {
                tt_key += ((int)c) & (1 << (every - 1 - char_now));
                char_now++;
                now_bit++;
                if (now_bit == every)
                    break;
            }
            if (now_bit == every)
            {
                if (map.count(tt_key) == 0)
                    map[tt_key] = 1;
                else
                    map[tt_key]++;
                now_bit = 0;
            }
        }
    }
    if (now_bit != 0)
    {
        more_bits = every - now_bit; //文件不够长 末尾补0 记录补的位数
        if (map.count(tt_key) == 0)
            map[tt_key] = 1;
        else
            map[tt_key]++;
    }

    EOF_loc = pow(2, every) - 1;
    map[EOF_loc] = 1; //记录EOF

    infile.close();

    init(HT, map, HC); //生成 Huffman 树以及 Huffman 编码

    return true;
}

void small::compress_output()
{
    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);

    std::ofstream outfile(ans_path.c_str(), std::ios::out | std::ios::binary);
    if (!outfile)
    {
        std::cout << "文件打开错误！" << std::endl;
        return;
    }

    //输出压缩的单位
    outfile.put(select + '0');
    outfile.put('|');

    int fre = map.size();
    for (int i = 1; i <= fre; i++)
    {
        outfile << HT[i].key << '|' << HT[i].weight;
        if (i != fre)
            outfile.put('|');
    }

    outfile.put('-');

    int num = 0;
    int i = 0;
    int tt = 0;

    //应该是开了一个线程用来记录进度 但是我不知道是不是成功了 但是运行效果和我预想的一样
    //那我们就不妨假设它是成功的！
    pthread_t threads;
    poss_help tmp_struct;
    tmp_struct = {now_byte, size};
    pthread_create(&threads, NULL, possesion, (void *)&tmp_struct);

    // int num_0 = 0, num_8 = 0;
    std::cout << "开始压缩..." << std::endl;
    std::cout << "[                                        ] 0%";

    //主要输出部分
    char c;
    int every = 8 * select * 0.5; //单位 bit
    int tt_key = 0;               //用来记录 key
    int now_bit = 0;              //用来记录当前读入了多少个bit
    int char_now = 0;             //用来记录当前读取的字符使用到的 bit
    while (infile.get(c))
    {
        now_byte++;
        char_now = 0;
        while (char_now < 8)
        {
            while (char_now < 8)
            {
                tt_key += ((int)c) & (1 << (every - 1 - char_now));
                char_now++;
                now_bit++;
                if (now_bit == every)
                    break;
            }
            if (now_bit == every)
            {
                i = 0;
                while (HC[tt_key][i] != '\0')
                {
                    tt += (HC[tt_key][i] - '0') << (7 - num);
                    i++;
                    num++;
                    if (num == 8)
                    {
                        outfile.put((char)tt);
                        num = 0;
                        tt = 0;
                    }
                }
                tmp_struct = {now_byte, size}; //实时更新当前的进度
                now_bit = 0;
            }
        }
    }
    //输出最后一个可能没有到达一个单位的字符
    if (now_bit != every && now_bit != 0)
    {
        i = 0;
        while (HC[tt_key][i] != '\0')
        {
            tt += (HC[tt_key][i] - '0') << (7 - num);
            i++;
            num++;
            if (num == 8)
            {
                outfile.put((char)tt);
                num = 0;
                tt = 0;
            }
        }
    }

    i = 0;
    while (HC[EOF_loc][i] != '\0')
    {
        tt += (HC[EOF_loc][i] - '0') << (7 - num);
        i++;
        num++;
        if (num == 8)
        {
            outfile.put(tt);
            num = 0;
            tt = 0;
        }
    }
    //输出可能没有到达8bit的最后一个字符
    if (num != 0)
        outfile.put((char)tt);

    std::cout << '\r' << "[########################################] 100%  ";

    infile.close();
    outfile.close();
}