//
// Created by L E N O V O on 17.11.2021.
//

#ifndef LAB4_TASKSQUEUEPROCESSOR_H
#define LAB4_TASKSQUEUEPROCESSOR_H


#include <vector>
#include "TasksQueue.h"

class TasksQueueProcessor {
public:
    TasksQueueProcessor(TasksQueue* tasksQueue, int tasksCount);
    ~TasksQueueProcessor();
    void Process();
    void WaitAll();

private:
    std::vector<HANDLE> threads;
    CRITICAL_SECTION criticalSection;
    static DWORD DoThreadWork(void* params);
};


#endif //LAB4_TASKSQUEUEPROCESSOR_H
