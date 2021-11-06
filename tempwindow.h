#pragma once

//该结构体用来给开辟的线程传参数
struct poss_help
{
    int now_b;
    float total;
};

void *possesion(void *threadarg);