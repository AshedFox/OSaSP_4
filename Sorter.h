//
// Created by L E N O V O on 18.11.2021.
//

#ifndef LAB4_SORTER_H
#define LAB4_SORTER_H

#include "vector"
#include "string"
#include "TasksQueue.h"

class Sorter {
public:
    std::vector<std::string> Sort(const std::vector<std::string>& input, int threads_limit);
private:
    std::vector<std::vector<std::string>> parts;

    void SetupParts(const std::vector<std::string>& input, int threads_limit);
    TasksQueue *GenerateTasksQueue();
    static void Sort(void* params);
    std::vector<std::string> Merge(const std::vector<std::string>& input);
};


#endif //LAB4_SORTER_H
