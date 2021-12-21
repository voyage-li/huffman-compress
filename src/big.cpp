#include "big.h"
#include <bits/stdc++.h>

big::big()
{
    now_byte = 0; //刚开始有两个字符代表压缩位数以及'|'(区分正文)
}
void big::decompress()
{
    if (!decompress_input_output())
        return;
    std::cout << "\n已完成文件解压！" << std::endl;
    std::cout << "解压文件路径：" << std::endl;
    std::cout << ans_path << std::endl;
    end_time = clock();
    double total_time = double(end_time - begin_time) / CLOCKS_PER_SEC;
    std::cout << "解压用时: " << total_time << "s" << std::endl;
    getchar();
}
bool big::decompress_input_output()
{
    std::cout << "请输入需要解压的文件的路径(解压文件会存在相同的目录):" << std::endl;
    getchar();
    getline(std::cin, data_path);

    begin_time = clock();

    std::ifstream infile(data_path.c_str(), std::ios::in | std::ios::binary);

    if (!infile)
    {
        std::cout << "文件打开错误！" << std::endl;
        getchar();
        return false;
    }

    system("clear");
    std::cout << "               解压进度                  " << std::endl;
    std::cout << "正在扫描文件......" << std::endl;

    char tmp;
    int num;
    long long int fff;
    int char_size;

    //假设这里我是成功开了一个多线程

    infile >> type;             //获取解压文件格式
    infile >> tree_n >> tmp;    //获取 Huffman树元数
    infile >> char_size >> tmp; //获取压缩基本符号单元
    infile >> select >> tmp;    //获取压缩基本符号单元
    int every = select * 4;

    size = char_size;

    while (1)
    {
        fff = 0;
        char c;
        int now_get_bit = 0;
        for (int i = 0; i < (select + 1) / 2; i++)
        {
            infile.get(c);
            for (int j = 0; j < 8; j++)
            {
                fff += (long long int)(((int)c >> (7 - j)) & 1) << (every - 1 - now_get_bit);
                now_get_bit++;
            }
        }
        infile >> tmp >> num;
        map[fff] = num;
        infile.get(tmp);

        if (tmp != '|')
            break;
    }

    int temp_len = data_path.length();
    int point_loc = 0;
    for (point_loc = temp_len - 1; point_loc > 0; point_loc--)
        if (data_path[point_loc] == '.')
            break;
    ans_path = data_path.substr(0, point_loc) + "_." + type;

    std::ofstream outfile(ans_path.c_str(), std::ios::out | std::ios::binary);
    if (map.size() == 1)
    {
        std::cout << "开始解压..." << std::endl;
        char ans[select * 4];
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < select * 4; i++)
            ans[i] = ((fff & (1 << (select * 4 - 1 - i))) >> (select * 4 - 1 - i)) + '0';
        int out_put = 0;
        int num_now = 0;
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < select * 4; j++)
            {
                out_put += (ans[j] - '0') << (7 - num_now);
                num_now++;
                if (num_now == 8)
                {
                    outfile.put(out_put);
                    out_put = 0;
                    num_now = 0;
                }
            }
        }
        std::cout << "[########################################] 100%";
        infile.close();
        outfile.close();
        return true;
    }

    init_for_de(HT, map, tree_n);

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
    int root_loc;
    int now;
    int now_bit = 0; //记录当前输出字符到的bit
    int out_tmp = 0; //用来记录输出的字符
    int wei = judge(tree_n);
    int wei_now = 0;
    int switch_child = 0;

    for (root_loc = 1; root_loc < 2 * fre; root_loc++)
    {
        if (HT[root_loc].parent == 0)
            break;
    }

    now = root_loc;

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
            switch_child += (ans[index] - '0') << (wei - 1 - wei_now);
            wei_now++;
            if (wei == wei_now)
            {
                wei_now = 0;
                now = HT[now].child[switch_child];
                switch_child = 0;
            }
            index++;

            if (HT[now].child[0] == 0)
            {
                //获取对应权值对应的 bit位
                int int_to_char = HT[now].key;
                char ans_[every + 1];
                ans_[every] = '\0';
                for (int j = 0; j < every; j++)
                    ans_[j] = ((int_to_char >> (every - 1 - j)) & 1) + '0';

                int j = 0;
                while (ans_[j] != '\0')
                {
                    now_bit++;
                    out_tmp += (ans_[j] - '0') << (8 - now_bit);
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
                now = root_loc;
            }
            if (index == 8 || char_size == 0)
                break;
        }
        if (char_size == 0)
            break;
    }
    tmp_struct = {now_byte, size};
    infile.close();
    outfile.close();

    pthread_join(threads, NULL);

    return true;
}