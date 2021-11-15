#pragma once
#include "huffman.h"
#include "tempwindow.h"
class big
{
public:
    big();
    void decompress();
    bool decompress_input_output();

private:
    int select;                       //压缩单位选择
    int tree_n;                       //n元Huffman树
    float size;                       //文件大小
    int now_byte;                     //已经读取的字符数
    std::string data_path;            //需要解压的文件的路径
    std::string ans_path;             //解压完成的文件路径
    std::string type;                 //用来存储被压缩的文件的格式
    std::unordered_map<int, int> map; //需要解压的文件中不同字符的数量
    HuffmanTree HT;                   //huffman树
};