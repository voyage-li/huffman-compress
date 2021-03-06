#pragma once
#include "huffman.h"
#include "tempwindow.h"
class small
{
public:
    small();
    ~small();
    void compress();
    bool compress_input();
    void compress_output();
    void compress_output_big();

private:
    clock_t begin_time, end_time;
    int select;                                    //压缩单位选择
    int tree_n;                                    // n元Huffman树
    float size;                                    //文件大小
    int char_size;                                 //防止读取出现错误
    int now_byte;                                  //当前读取到的的文件位数
    std::string data_path;                         //需要压缩的文件的路径
    std::string ans_path;                          //需要存储的完成压缩的路径
    std::string type;                              //用来存储被压缩的文件的格式
    std::map<long long int, int> map;              //需要压缩的文件中不同字符的数量
    std::unordered_map<long long int, char *> HC_; //不同字符对应的 huffman编码
    char **HC;                                     //小数据量用数组
    HuffmanTree HT;                                // huffman树
};