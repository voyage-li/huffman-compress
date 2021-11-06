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
    int EOF_loc;              //map中用来表示 EOF的 key
    int select;               //压缩单位选择
    int more_bits;            //由于压缩单位不同 因此扩展的位数
    float size;               //文件大小
    int now_byte;             //当前读取到的的文件位数
    std::string data_path;    //需要压缩的文件的路径
    std::string ans_path;     //需要存储的完成压缩的路径
    std::map<int, int> map;   //需要压缩的文件中不同字符的数量
    std::map<int, char *> HC; //不同字符对应的 huffman编码
    HuffmanTree HT;
};