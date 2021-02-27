#include "function.h"

void job1(void* argument) { // reverse
    Data *data = (Data *) argument;
    int tmp;//, bound = (data->upper - data->lower) / 2 + data->lower;
    for(int i = data->lower; i <= data->upper; i++) {
        tmp = data->arr[i];
        data->arr[i] = data->arr[data->upper];
        data->arr[data->upper] = tmp;
        data->upper--;
    }
}
void job2(void* argument) { // minus
    Data *data = (Data *) argument;
    for(int i = data->lower; i <= data->upper; i++) {
        data->arr[i] = -data->arr[i];
    }
}
void job3(void* argument) { // double
    Data *data = (Data *) argument;
    for(int i = data->lower; i <= data->upper; i++) {
        data->arr[i] = data->arr[i]*2;
    }
}
void initTask(Task* task, void(*func)(void*),void* argument) {
    task->func = func;
    task->argument = argument;
}
void executeTasks(Task_List *task_list) {
    for(int i = 0; i < task_list->size; i++) {
        task_list->tasks[i]->func(task_list->tasks[i]->argument);
    }
}
