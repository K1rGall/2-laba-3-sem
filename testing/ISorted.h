#ifndef ISORTED_H
#define ISORTED_H
#include "Sequence.h"

template <class T>
class ISorted {
public:
    virtual void QuickSort(Sequence<T>* seq) = 0;
    virtual void MergeSort(Sequence<T>* seq) = 0;
    virtual ~ISorted() {}
};

#endif