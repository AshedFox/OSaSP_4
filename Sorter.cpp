//
// Created by L E N O V O on 18.11.2021.
//

#include <algorithm>
#include <cmath>
#include "Sorter.h"
#include "TasksQueueProcessor.h"

std::vector<std::string> Sorter::Sort(const std::vector<std::string>& input, int threads_limit) {
    SetupParts(input, threads_limit);

    auto queue = GenerateTasksQueue();
    auto processor = new TasksQueueProcessor(queue, parts.size());

    processor->Process();
    processor->WaitAll();

    return Merge(input);
}

void Sorter::SetupParts(const std::vector<std::string>& input, int threads_limit) {
    int stringsPerThread = round((float)input.size() / threads_limit);

    while (stringsPerThread < 2 && threads_limit > 1) {
        threads_limit--;
        stringsPerThread = input.size() / threads_limit;
    }

    parts.resize(threads_limit);

    for (int i = 0; i < threads_limit; i++) {
        auto first = input.begin() + (i * stringsPerThread);
        auto last = input.begin() + (((i + 1) * stringsPerThread < input.size()) ? (i + 1) * stringsPerThread : input.size());

        parts.at(i) = std::vector<std::string>(first, last);
    }
}

TasksQueue *Sorter::GenerateTasksQueue() {
    auto queue = new TasksQueue();

    for (auto & part : parts) {
        auto task = new TasksQueue::Task(Sort, (void*)(&part));
        queue->Enqueue(task);
    }

    return queue;
}

void Sorter::Sort(void *params) {
    auto part = (std::vector<std::string>*)params;

    std::sort(part->begin(), part->end());
}

std::vector<std::string> Sorter::Merge(const std::vector<std::string>& input) {
    std::vector<int> counter(parts.size(), 0);
    std::vector<std::string> result;
    std::vector<std::string> buff;

    int resultIndex = 0;

    for(auto & part : parts) {
        buff.clear();

        int j = 0;
        int k = 0;

        while (j < part.size() && k < resultIndex) {
            if (part.at(j) <= result.at(k)) {
                buff.push_back(part.at(j++));
            }
            else {
                buff.push_back(result.at(k++));
            }
        }

        while (j < part.size()) {
            buff.push_back(part.at(j++));
        }

        while (k < resultIndex) {
            buff.push_back(result.at(k++));
        }

        result = buff;
        resultIndex += part.size();
    }

    return result;
}

