#ifndef SORTER_H
#define SORTER_H

#include "ISorted.h"
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class Sorter : public ISorted<T> {
private:
    // --- QuickSort Helper Function ---
    int Partition(int low, int high, Sequence<T>* sequence) {
        T point = sequence->GetElement(high);
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (sequence->GetElement(j) <= point) {
                i++;
                sequence->Swap(sequence->GetElement(i), sequence->GetElement(j));
            }
        }

        i++;
        sequence->Swap(sequence->GetElement(i), sequence->GetElement(high));
        return i;
    }
    // --- MergeSort Helper Function ---
    void Merge(int low, int middle, int high, Sequence<T>* sequence) {
        int size1 = middle - low + 1;
        int size2 = high - middle;

        DynamicArray<T> array1(size1);
        DynamicArray<T> array2(size2);
        // Copy data to temporary arrays
        for (int i = 0; i < size1; i++) {
            array1[i] = sequence->GetElement(low + i);
        }
        for (int i = 0; i < size2; i++) {
            array2[i] = sequence->GetElement(middle + 1 + i);
        }

        int i = 0, j = 0, k = low;

        // Merge arrays back into the sequence
        while (i < size1 && j < size2) {
            if (array1.GetElement(i) <= array2.GetElement(j)) {
                sequence->Set(k, array1.GetElement(i));
                i++;
            } else {
                sequence->Set(k, array2.GetElement(j));
                j++;
            }
            k++;
        }
        // Copy remaining elements
        while (i < size1) {
            sequence->Set(k, array1.GetElement(i));
            i++;
            k++;
        }
        while (j < size2) {
            sequence->Set(k, array2.GetElement(j));
            j++;
            k++;
        }
    }
    // --- Recursive QuickSort Implementation ---
    void QuickSortRecursive(int low, int high, Sequence<T>* sequence) {
        if (low < high) {
            int point = Partition(low, high, sequence);

            QuickSortRecursive(low, point - 1, sequence);
            QuickSortRecursive(point + 1, high, sequence);
        }
    }
    // --- Recursive MergeSort Implementation ---
    void MergeSortRecursive(int low, int high, Sequence<T>* sequence) {
        if (low < high) {
            int middle = low + (high - low) / 2;

            MergeSortRecursive(low, middle, sequence);
            MergeSortRecursive(middle + 1, high, sequence);

            Merge(low, middle, high, sequence);
        }
    }
public:
    // --- Public QuickSort Entry Point ---
    void QuickSort(Sequence<T>* sequence) override {
        QuickSortRecursive(0, sequence->GetLength() - 1, sequence);
    }

    // --- Public MergeSort Entry Point ---
    void MergeSort(Sequence<T>* sequence) override {
        MergeSortRecursive(0, sequence->GetLength() - 1, sequence);
    }
};

#endif
