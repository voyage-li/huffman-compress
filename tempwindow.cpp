#include "tempwindow.h"
#include <bits/stdc++.h>

void *possesion(void *threadarg)
{
    while (1)
    {
        struct poss_help *p = (struct poss_help *)threadarg;
        int now_byte = p->now_b;
        float size = p->total;

        if (now_byte % 100 != 1)
            continue;
        int temp = 40 * (now_byte / size);
        int temp_n = 40 - temp;
        putchar('\r');
        putchar('[');
        while (temp--)
            putchar('#');
        while (temp_n--)
            putchar(' ');
        std::cout << "]  " << (int)(100 * (now_byte / size)) << "%  ";
        if ((100 * (now_byte / size)) > 99)
            break;
    }
    pthread_exit(NULL);
}