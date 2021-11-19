//
// Created by L E N O V O on 17.11.2021.
//

#include "TasksQueueProcessor.h"

TasksQueueProcessor::TasksQueueProcessor(TasksQueue* tasksQueue, int tasksCount) {
    threads.resize(tasksCount);

    InitializeCriticalSectionAndSpinCount(&criticalSection, 1000);

    for (auto & thread : threads) {
        thread = CreateThread(nullptr, 0, DoThreadWork, (void*)tasksQueue, CREATE_SUSPENDED, nullptr);
    }
}

TasksQueueProcessor::~TasksQueueProcessor() {
    DeleteCriticalSection(&criticalSection);
}

void TasksQueueProcessor::Process() {
    EnterCriticalSection(&criticalSection);
    for (auto & thread : threads) {
        ResumeThread(thread);
    }
    LeaveCriticalSection(&criticalSection);
}

void TasksQueueProcessor::WaitAll() {
    WaitForMultipleObjects(threads.size(), &threads.front(), TRUE, INFINITE);
}

DWORD TasksQueueProcessor::DoThreadWork(void *params) {
    TasksQueue* tasksQueue = (TasksQueue*)params;

    while (true) {
        auto task = tasksQueue->Dequeue();

        if (task == nullptr) {
            ExitThread(0);
        }

        task->func(task->params);
    }
}




