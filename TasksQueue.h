//
// Created by L E N O V O on 17.11.2021.
//

#ifndef LAB4_TASKSQUEUE_H
#define LAB4_TASKSQUEUE_H

#include "windows.h"

class TasksQueue {
public:
    struct Task {
        void (*func)(void*);
        void* params;

        Task(void (*_func)(void*), void* _params): func(_func), params(_params) {}
    };
    struct Node {
        Task* task;
        Node* next;

        Node(Task* _task): task(_task), next(nullptr) {}
    };

private:
    Node* front;
    Node* back;
    CRITICAL_SECTION criticalSection;

public:
    TasksQueue();
    ~TasksQueue();

    Node* GetFront();
    Node* GetBack();
    void Enqueue(Task* task);
    Task* Dequeue();
    bool IsEmpty();
};


#endif //LAB4_TASKSQUEUE_H
