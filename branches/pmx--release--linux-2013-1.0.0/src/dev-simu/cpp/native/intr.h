#ifdef SIMU
#ifndef INTR_H
#define INTR_H

#define RT_INTR int

extern "C"
{
    #define TM_INFINITE 0

    int rt_intr_enable(int*);

    int rt_intr_wait(int*, int);

    int rt_intr_create(int*, const char*, int, int);

    void rt_intr_delete(int*);
}

#endif
#endif
