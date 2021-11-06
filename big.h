#pragma once
#include "huffman.h"
#include "tempwindow.h"
class big
{
public:
    big();
    void decompress();
    void decompress_input();
    void decompress_output();

private:
    float size;
    int now_byte;
    char *re;
    std::string data_path;    //需要解压的文件的路径
    std::string ans_path;     //解压完成的文件路径
    std::map<int, int> map;   //需要解压的文件中不同字符的数量
    std::map<int, char *> HC; //不同字符对应的 huffman编码
    HuffmanTree HT;
};