# 使用`huffman`树 实现压缩软件

> 本程序在 linux 环境下测试运行 没有测试 windows 平台的兼容性

#### 实现的功能

1. 压缩任意格式的文件(虽然不知道这算不算压缩 甚至变大了)
2. 解压指定路径的文件(无损)
3. 选择压缩的基本单元
4. 可以选择使用多元`huffman`树进行压缩
5. 3，4 项同时使用

#### 实现思路

1. 压缩
   1. 以二进制格式打开文件 统计每一种符号单元出现的次数
   2. 以出现的次数作为权重 构造`huffman`树
   3. 根据构造出的`huffman`树求得`huffman`编码
   4. 再次扫描文件 将符号单元转变成 huffman 编码输出
2. 解压
   1. 获取压缩文件头部的相关信息
   2. 用相同的方式构造'huffman'树与'huffman'编码
   3. 扫描压缩文件，将文件转换为原来的形式输出

#### 不同文件的具体功能

1. **`main.cpp`**
   - 主函数部分 相当于消息循环
2. **`small.h`和`small.cpp`**
   ```c++
   public:
   small();//初始化
   void compress();//调用
   bool compress_input();//读取
   void compress_output();//输出
   private:
   int select; //压缩单位选择
   int tree_n; //n 元 Huffman 树
   float size; //文件大小
   int char_size; //防止读取出现错误 再自己计算 一下总字符 后期应该可以删掉
   int now_byte; //当前读取到的的文件位数
   std::string data_path; //需要压缩的文件的路径
   std::string ans_path; //需要存储的完成压缩的路径
   std::string type; //用来存储被压缩的文件的格式
   std::map<int, int> map; //需要压缩的文件中不同字符的数量
   std::map<int, char *> HC; //不同字符对应的 huffman 编码
   HuffmanTree HT; //huffman 树
   ```
   - **具体的思路**
    ```c
    ```
3. **`big.h`和`big.cpp`**
   ```c++
    public:
        big();
        void decompress();
        void decompress_input();
        void decompress_output();

    private:
        int select;               //压缩单位选择
        int tree_n;               //n元Huffman树
        float size;               //文件大小
        int now_byte;             //已经读取的字符数
        std::string data_path;    //需要解压的文件的路径
        std::string ans_path;     //解压完成的文件路径
        std::string type;         //用来存储被压缩的文件的格式
        std::map<int, int> map;   //需要解压的文件中不同字符的数量
        std::map<int, char *> HC; //不同字符对应的 huffman编码
        HuffmanTree HT;           //huffman树
    ```
    - **具体的思路**
    ```c
    ```
4. **`huffman.h`和`huffman.cpp`**
    ```c++
    typedef struct HTNode
    {
        long long int num;       //表示第几个元素
        long long int key;       //对应元素的值
        int weight;              //权值
        long long int parent;    //双亲
        long long int child[16]; //孩子
        friend bool operator<(HTNode a, HTNode b)
        {
            return a.weight > b.weight;
        }
    } HTNode, *HuffmanTree;
    bool operator>(HTNode a, HTNode b);
    void init(HuffmanTree &HT, std::map<int, int> & map, std::map<int, char *> &HC, int tree_n);
    void init_for_de(HuffmanTree &HT,std::map<int, int> &map, int tree_n);
    void select(HuffmanTree &HT, int n);
    void output_huffmantree(HuffmanTree &HT, std::map<int, int> &map, int tree_n);
    int judge(int a);
    ```
    - **具体的思路**
    ```c
    ```
5. **`tempwindow.h`和`tempwindow.cpp`**
    ```c++
    struct poss_help
    {
        int now_b;
        float total;
    };
    void *possesion(void *threadarg);
    ```
    - **具体的思路**
    ```c
    ```
#### 一些思考
- ~~暂时没有~~