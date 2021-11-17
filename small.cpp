#include "small.h"
#include <bits/stdc++.h>

small::small()
{
    now_byte = 0;
    char_size = 0;
}
small::~small()
{
    if (select < 6)
    {
        delete[] HC;
    }
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
        getchar();
        system("clear");
        return;
    }

    std::cout << "请选择n元huffman树(2~16):" << std::endl;
    std::cin >> tree_n;

    if (tree_n < 2 || tree_n > 16)
    {
        std::cout << "输入数据错误！" << std::endl;
        getchar();
        getchar();
        system("clear");
        return;
    }
    else
    {
        if (!compress_input())
            return;
        if (select < 7)
            compress_output();
        else
            compress_output_big();
    }

    putchar('\n');
    std::cout << "已完成文件压缩！" << std::endl;
    std::cout << "压缩文件路径：" << std::endl;
    std::cout << ans_path << std::endl;
    std::cout << "是否展示huffman树：(Enter跳过，其他字符展示)：\n";
    char c = getchar();
    if (c != '\n')
    {
        output_huffmantree(HT, map, tree_n);
        getchar();
    }
}

bool small::compress_input()
{
    std::cout << "请输入需要压缩的文件的路径(压缩后的文件会存在同路径,后缀为.dat):" << std::endl;
    getchar();
    getline(std::cin, data_path);

    //截取存储路径 截取文件格式
    int temp_len = data_path.length();
    int point_loc = 0;
    for (point_loc = temp_len - 1; point_loc > 0; point_loc--)
        if (data_path[point_loc] == '.')
            break;
    ans_path = data_path.substr(0, point_loc) + ".dat";
    type = data_path.substr(point_loc + 1, temp_len + 1 - point_loc);

    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);
    if (!infile)
    {
        std::cout << "文件打开错误！" << std::endl;
        getchar();
        return false;
    }

    system("clear");
    std::cout << "               压缩进度                  " << std::endl;
    std::cout << "正在获取文件大小..." << std::endl;

    char c;
    int every = 8 * select * 0.5; //单位 bit
    long long int tt_key = 0;     //用来记录 key
    int now_bit = 0;              //用来记录当前读入了多少个bit
    int char_now = 0;             //用来记录当前读取的字符使用到的 bit
    std::unordered_map<long long int, int> temp_map;
    while (infile.get(c))
    {
        char_size++;
        char_now = 0;
        while (char_now < 8)
        {
            while (char_now < 8)
            {
                tt_key += (long long int)(((int)c >> (7 - char_now)) & 1) << (every - 1 - now_bit);
                char_now++;
                now_bit++;
                if (now_bit == every)
                    break;
            }
            if (now_bit == every)
            {
                if (temp_map.count(tt_key) == 0)
                {
                    map[tt_key] = 1;
                    temp_map[tt_key] = 1;
                }
                else
                    temp_map[tt_key]++;
                now_bit = 0;
                tt_key = 0;
            }
        }
    }
    if (now_bit != 0)
    {
        if (temp_map.count(tt_key) == 0)
            map[tt_key] = 1;
        else
            map[tt_key]++;
    }

    infile.close();

    if (every < 28)
    {
        HC = new char *[(long long)pow(2, every)];
        init(HT, map, HC, tree_n); //生成 Huffman 树以及 Huffman 编码
    }
    else
        init_big(HT, map, HC_, tree_n);

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
    size = char_size;
    //输出文件格式 huffman树元数压缩的单位以及总字符
    outfile << type << ' ';
    outfile << tree_n << '|';
    outfile << char_size << '|';
    outfile.put(select + '0');
    outfile.put('|');

    std::cout << "开始压缩..." << std::endl;
    std::cout << "[                                        ] 0%";

    int out_for_map = 0;
    int now_bit_for_map = 1;
    long long int fre = map.size();
    for (int i = 1; i <= fre; i++)
    {
        out_for_map = 0;
        now_bit_for_map = 1;
        //换一种方式输出key
        for (int j = 0; j < select * 4; j++)
        {
            out_for_map += ((HT[i].key >> (select * 4 - j - 1)) & 1) << (8 - now_bit_for_map);
            now_bit_for_map++;
            if (now_bit_for_map == 9)
            {
                outfile.put(out_for_map);
                out_for_map = 0;
                now_bit_for_map = 1;
            }
        }
        if (select % 2 == 1)
            outfile.put(out_for_map);

        outfile << '|' << HT[i].weight;
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
                tt_key += (((int)c >> (7 - char_now)) & 1) << (every - 1 - now_bit);
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
                tt_key = 0;
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
    //输出可能没有到达8bit的最后一个字符
    if (num != 0)
        outfile.put((char)tt);
    tmp_struct = {now_byte, size};

    pthread_join(threads, NULL);

    infile.close();
    outfile.close();
}

void small::compress_output_big()
{
    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);

    std::ofstream outfile(ans_path.c_str(), std::ios::out | std::ios::binary);
    if (!outfile)
    {
        std::cout << "文件打开错误！" << std::endl;
        return;
    }
    size = char_size;
    //输出文件格式 huffman树元数压缩的单位以及总字符
    outfile << type << ' ';
    outfile << tree_n << '|';
    outfile << char_size << '|';
    outfile.put(select + '0');
    outfile.put('|');

    std::cout << "开始压缩..." << std::endl;
    std::cout << "[                                        ] 0%";

    int out_for_map = 0;
    int now_bit_for_map = 1;
    long long int fre = map.size();
    for (int i = 1; i <= fre; i++)
    {
        out_for_map = 0;
        now_bit_for_map = 1;
        //换一种方式输出key
        for (int j = 0; j < select * 4; j++)
        {
            out_for_map += ((HT[i].key >> (select * 4 - j - 1)) & 1) << (8 - now_bit_for_map);
            now_bit_for_map++;
            if (now_bit_for_map == 9)
            {
                outfile.put(out_for_map);
                out_for_map = 0;
                now_bit_for_map = 1;
            }
        }
        if (select % 2 == 1)
            outfile.put(out_for_map);

        outfile << '|' << HT[i].weight;
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

    //主要输出部分
    char c;
    int every = 8 * select * 0.5; //单位 bit
    long long int tt_key = 0;     //用来记录 key
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
                tt_key += (long long int)(((int)c >> (7 - char_now)) & 1) << (every - 1 - now_bit);
                char_now++;
                now_bit++;
                if (now_bit == every)
                    break;
            }
            if (now_bit == every)
            {
                i = 0;
                while (HC_[tt_key][i] != '\0')
                {
                    tt += (HC_[tt_key][i] - '0') << (7 - num);
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
                tt_key = 0;
            }
        }
    }
    //输出最后一个可能没有到达一个单位的字符
    if (now_bit != every && now_bit != 0)
    {
        i = 0;
        while (HC_[tt_key][i] != '\0')
        {
            tt += (HC_[tt_key][i] - '0') << (7 - num);
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
    //输出可能没有到达8bit的最后一个字符
    if (num != 0)
        outfile.put((char)tt);
    tmp_struct = {now_byte, size};

    pthread_join(threads, NULL);

    infile.close();
    outfile.close();
}