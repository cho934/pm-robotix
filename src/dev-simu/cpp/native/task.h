#ifdef SIMU
#ifndef TASK_H
#define TASK_H

#define RT_TASK int

extern "C"
{
    int rt_task_create(int*, const char*, int, int, int);

    void rt_task_start(int*, void(*)(void*), void*);

    void rt_task_delete(int*);
}

#endif
#endif
