#ifndef ISORTED_H
#define ISORTED_H

#include "Sequence.h"

template <typename T>
class ISorted {
public:
    virtual void Sort(Sequence<T>* seq) = 0;
    virtual ~ISorted() {}
};

#endif // ISORTED_H
