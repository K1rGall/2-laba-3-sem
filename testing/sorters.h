#ifndef SORTERS_H
#define SORTERS_H

#include "ISorted.h"
#include "timesorters.h"

template <typename T>
class QuickSort : public ISorted<T> {
public:
    void Sort(Sequence<T>* seq) override {
        double duration = 0;
        SortSequenceByQuickSort(seq, &duration);
    }
};

template <typename T>
class MergeSort : public ISorted<T> {
public:
    void Sort(Sequence<T>* seq) override {
        double duration = 0;
        SortSequenceByMergeSort(seq, &duration);
    }
};

#endif // SORTERS_H
