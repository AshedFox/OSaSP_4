//
// Created by L E N O V O on 17.11.2021.
//

#include "TasksQueue.h"

TasksQueue::TasksQueue() {
    InitializeCriticalSectionAndSpinCount(&criticalSection, 1000);
    front = nullptr;
    back = nullptr;
}

TasksQueue::~TasksQueue() {
    EnterCriticalSection(&criticalSection);
    while(!IsEmpty()) {
        Dequeue();
    }
    LeaveCriticalSection(&criticalSection);

    DeleteCriticalSection(&criticalSection);
}

void TasksQueue::Enqueue(TasksQueue::Task *task) {
    EnterCriticalSection(&criticalSection);
    if (!front) {
        front = new Node(task);
        back = front;
    }
    else {
        back->next = new Node(task);
        back = back->next;
    }
    LeaveCriticalSection(&criticalSection);
}

TasksQueue::Task *TasksQueue::Dequeue() {
    EnterCriticalSection(&criticalSection);

    Task* result = nullptr;
    if (front != nullptr) {
        result = front->task;

        auto curr = front;

        if(front == back) {
            front = nullptr;
            back = nullptr;
        }
        else {
            front = front->next;
        }

        delete curr;
    }

    LeaveCriticalSection(&criticalSection);

    return result;
}

bool TasksQueue::IsEmpty() {
    return front == nullptr && back == nullptr;
}

TasksQueue::Node *TasksQueue::GetFront() {
    return front;
}

TasksQueue::Node *TasksQueue::GetBack() {
    return back;
}
