#include "tempwindow.h"
#include <bits/stdc++.h>

void *possesion(void *threadarg)
{
    while (1)
    {
        struct poss_help *p = (struct poss_help *)threadarg;
        int now_byte = p->now_b;
        float size = p->total;
        int temp = 40 * (now_byte / size);
        int temp_n = 40 - temp;
        putchar('\r');
        putchar('[');
        for (int i = 0; i < temp; i++)
            putchar('#');
        for (int i = 0; i < temp_n; i++)
            putchar(' ');
        std::cout << "] " << (int)(100 * (now_byte / size)) << "%  ";
        if ((100 * (now_byte / size)) > 99)
        {
            putchar('\r');
            putchar('[');
            for (int i = 0; i < 40; i++)
                putchar('#');
            std::cout << "] 100%";
            break;
        }
        //不敢写100 因为字节可能计算失误 可能会导致进度条最后跳一下 不过问题应该不是很大
    }
    pthread_exit(NULL);
}
