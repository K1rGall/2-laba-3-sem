#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "Sequence.h"
#include <vector>
#include <algorithm>

template <class T>
class DynamicArray : public Sequence<T>
{
private:
    std::vector<T> data; // Используем std::vector вместо сырого массива

    void QuickSortHelper(int left, int right) {
        if (left < right) {
            int pivotIndex = Partition(left, right);
            QuickSortHelper(left, pivotIndex - 1);
            QuickSortHelper(pivotIndex + 1, right);
        }
    }

    int Partition(int left, int right) {
        T pivot = data[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[right]);
        return i + 1;
    }

    void MergeSortHelper(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSortHelper(left, mid);
            MergeSortHelper(mid + 1, right);
            Merge(left, mid, right);
        }
    }

    void Merge(int left, int mid, int right) {
        std::vector<T> leftArray(data.begin() + left, data.begin() + mid + 1);
        std::vector<T> rightArray(data.begin() + mid + 1, data.begin() + right + 1);

        int i = 0, j = 0, k = left;
        while (i < leftArray.size() && j < rightArray.size()) {
            if (leftArray[i] <= rightArray[j]) {
                data[k++] = leftArray[i++];
            } else {
                data[k++] = rightArray[j++];
            }
        }
        while (i < leftArray.size()) {
            data[k++] = leftArray[i++];
        }
        while (j < rightArray.size()) {
            data[k++] = rightArray[j++];
        }
    }

public:
    void QuickSort() override { QuickSortHelper(0, data.size() - 1); }
    void MergeSort() override { MergeSortHelper(0, data.size() - 1); }

    class DynamicArrayIterator : public Sequence<T>::Iterator {
    private:
        typename std::vector<T>::iterator current;

    public:
        DynamicArrayIterator(typename std::vector<T>::iterator current) : current(current) {}

        bool operator==(const typename Sequence<T>::Iterator& other) const override
        {
            const DynamicArrayIterator* otherIterator = dynamic_cast<const DynamicArrayIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename Sequence<T>::Iterator& other) const override
        {
            return !(*this == other);
        }

        T& operator*() override
        {
            return *current;
        }

        typename Sequence<T>::Iterator& operator++() override
        {
            ++current;
            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() override
    {
        return new DynamicArrayIterator(data.begin());
    }

    typename Sequence<T>::Iterator* ToEnd() override
    {
        return new DynamicArrayIterator(data.end());
    }

    DynamicArray() {}

    DynamicArray(T* items, int size) : data(items, items + size) {}

    DynamicArray(int size) : data(size) {}

    DynamicArray(DynamicArray<T>& dynamicArray) : data(dynamicArray.data) {}

    ~DynamicArray() {} // Нет необходимости в delete[] data, так как vector управляет памятью

    T& operator[](int index)
    {
        return data[index];
    }

    T& GetFirstElement() override
    {
        return data.front();
    }

    T& GetLastElement() override
    {
        return data.back();
    }

    T& GetElement(int index) override
    {
        return data.at(index);
    }

    void Swap(T& a, T& b) override
    {
        std::swap(a, b);
    }

    void Set(int index, T value) override
    {
        data[index] = value;
    }

    DynamicArray<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        return new DynamicArray<T>(data.data() + startIndex, endIndex - startIndex + 1);
    }

    int GetLength() override
    {
        return data.size();
    }

    void Append(T item) override
    {
        data.push_back(item);
    }

    void Append(T* items, int dataSize) override
    {
        data.insert(data.end(), items, items + dataSize);
    }

    void Prepend(T item) override
    {
        data.insert(data.begin(), item);
    }

    void InsertAt(T item, int index) override
    {
        data.insert(data.begin() + index, item);
    }

    void Union(Sequence<T>* dynamicArray) override
    {
        for (int i = 0; i < dynamicArray->GetLength(); i++)
        {
            Append(dynamicArray->GetElement(i));
        }
    }
};

#endif // DYNAMIC_ARRAY_H
