#pragma once
#include "huffman.h"
#include "tempwindow.h"
class small
{
public:
    small();
    void compress();
    bool compress_input();
    void compress_output();

private:
    int data_len;
    int select;
    float size;
    int now_byte;
    char *re;
    std::string data_path;     //需要压缩的文件的路径
    std::string ans_path;      //需要存储的完成压缩的路径
    std::map<char, int> map;   //需要压缩的文件中不同字符的数量
    std::map<char, char *> HC; //不同字符对应的 huffman编码
    HuffmanTree HT;
};