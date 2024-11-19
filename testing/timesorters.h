#ifndef Timesorters_H
#define Timesorters_H

#include <chrono>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "sorters.h"

template<typename T>
void SortSequenceByQuickSort(Sequence<T>* array, double* durationSorting)
{
    Sorter<T> sorter;
    auto start = std::chrono::high_resolution_clock::now();
    sorter.QuickSort(array);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    *durationSorting = duration.count();
}

template<typename T>
void SortSequenceByMergeSort(Sequence<T>* array, double* durationSorting)
{
    Sorter<T> sorter;
    auto start = std::chrono::high_resolution_clock::now();
    sorter.MergeSort(array);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    *durationSorting = duration.count();
}
#endif