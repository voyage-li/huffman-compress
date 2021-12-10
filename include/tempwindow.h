#pragma once

//该结构体用来给开辟的线程传参数
//假设我写的是对的 至少运行结果看起来还可以

struct poss_help
{
    int now_b;
    float total;
};

void *possesion(void *threadarg);