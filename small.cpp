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
        while (1)
        {
            while (char_now < 8)
            {
                tt_key += ((int)c) & (1 << (7 - char_now));
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
            if (char_now == 8)
                break;
        }
    }

    infile.close();
    init(HT, map, HC, re);
    return true;
}

void small::compress_output()
{
    // std::ofstream testfile("/home/voyage/code/yasuo/source/test_.dat");
    // std::ofstream testfile8("/home/voyage/code/yasuo/source/test8.dat");

    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);

    std::ofstream outfile(ans_path, std::ios::out | std::ios::binary);
    if (!outfile)
    {
        std::cout << "文件打开错误！" << std::endl;
        return;
    }

    int fre = map.size();
    for (int i = 1; i <= fre; i++)
    {
        outfile.put(HT[i].key);
        outfile.put('|');
        outfile << HT[i].weight;

        // testfile << (int)HT[i].key << ' ' << HT[i].key << ' ' << HC[HT[i].key] << '\n';
        // testfile8 << (int)HT[i].key << ' ' << HT[i].key << ' ' << HC[HT[i].key] << '\n';

        if (i != fre)
            outfile.put('|');
    }
    outfile.put('-');
    char c;
    int num = 0;
    int i = 0;
    int tt = 0;

    // int num_0 = 0, num_8 = 0;
    std::cout << "开始压缩..." << std::endl;
    std::cout << "[                                        ] 0%";

    pthread_t threads;
    poss_help tmp_struct;
    tmp_struct = {now_byte, size};
    pthread_create(&threads, NULL, possesion, (void *)&tmp_struct);

    while (1)
    {
        infile.get(c);
        now_byte++;
        i = 0;
        while (HC[c][i] != '\0')
        {
            tt += (HC[c][i] - '0') << (7 - num);

            // testfile8.put(HC[c][i]);
            // testfile.put(HC[c][i]);

            i++;
            num++;
            if (num == 8)
            {
                outfile.put((char)tt);
                num = 0;
                tt = 0;

                // num_8++;
                // // testfile8.put(' ');
                // if (num_8 % 10 == 0)
                //     testfile8.put('\n');
            }
        }

        tmp_struct = {now_byte, size};
        if (now_byte == size)
            break;
        // if (now_byte % 100 == 1)
        //     feature(now_byte, size);
        // num_0++;
        // testfile.put(' ');
        // if (num_0 % 10 == 0)
        //     testfile.put('\n');
    }

    i = 0;
    while (re[i] != '\0')
    {
        tt += (re[i] - '0') << (7 - num);

        // testfile8.put(re[i]);
        // testfile.put(re[i]);

        i++;
        num++;
        if (num == 8)
        {
            outfile.put(tt);
            num = 0;
            tt = 0;
        }
    }

    std::cout << '\r' << "[########################################] 100%  ";
    // << std::setprecision(4) << size / pow(2, 20) << "MB/" << size / pow(2, 20) << "MB"
    // testfile.put(' ');

    outfile.put(tt);
    infile.close();
    outfile.close();
    // testfile8.close();
    // testfile.close();
}