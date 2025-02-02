#ifndef TIMESORTERS_H
#define TIMESORTERS_H

#include "Sequence.h"
#include <chrono>

template <typename T>
void SortSequenceByQuickSort(Sequence<T>* sequence, double* duration) {
    auto start = std::chrono::high_resolution_clock::now();
    sequence->QuickSort();
    auto end = std::chrono::high_resolution_clock::now();
    *duration = std::chrono::duration<double>(end - start).count();
}

template <typename T>
void SortSequenceByMergeSort(Sequence<T>* sequence, double* duration) {
    auto start = std::chrono::high_resolution_clock::now();
    sequence->MergeSort();
    auto end = std::chrono::high_resolution_clock::now();
    *duration = std::chrono::duration<double>(end - start).count();
}

#endif // TIMESORTERS_H