#ifndef SORTER_H
#define SORTER_H

#include "ISorted.h"
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class Sorter : public ISorted<T> {
private:
    // Вспомогательный буфер для MergeSort
    DynamicArray<T>* buffer;

    // --- MergeSort Helper Function ---
    void Merge(int low, int middle, int high, Sequence<T>* sequence) {
        int i = low;
        int j = middle + 1;
        int k = low;

        // Копирование текущего диапазона в буфер
        for (int idx = low; idx <= high; ++idx) {
            buffer->Set(idx, sequence->GetElement(idx));
        }

        // Слияние двух частей из буфера обратно в sequence
        while (i <= middle && j <= high) {
            if (buffer->GetElement(i) <= buffer->GetElement(j)) {
                sequence->Set(k++, buffer->GetElement(i++));
            } else {
                sequence->Set(k++, buffer->GetElement(j++));
            }
        }

        // Копирование оставшихся элементов
        while (i <= middle) {
            sequence->Set(k++, buffer->GetElement(i++));
        }
        while (j <= high) {
            sequence->Set(k++, buffer->GetElement(j++));
        }
    }

    // --- Recursive MergeSort Implementation ---
    void MergeSortRecursive(int low, int high, Sequence<T>* sequence) {
        if (high - low <= 10) {
            // Для малых подмассивов используем сортировку вставками
            for (int i = low + 1; i <= high; ++i) {
                T key = sequence->GetElement(i);
                int j = i - 1;
                while (j >= low && sequence->GetElement(j) > key) {
                    sequence->Set(j + 1, sequence->GetElement(j));
                    j--;
                }
                sequence->Set(j + 1, key);
            }
        } else if (low < high) {
            int middle = low + (high - low) / 2;

            MergeSortRecursive(low, middle, sequence);
            MergeSortRecursive(middle + 1, high, sequence);

            // Проверка на упорядоченность перед слиянием
            if (sequence->GetElement(middle) > sequence->GetElement(middle + 1)) {
                Merge(low, middle, high, sequence);
            }
        }
    }

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

    // --- Recursive QuickSort Implementation ---
    void QuickSortRecursive(int low, int high, Sequence<T>* sequence) {
        if (low < high) {
            int point = Partition(low, high, sequence);

            QuickSortRecursive(low, point - 1, sequence);
            QuickSortRecursive(point + 1, high, sequence);
        }
    }

public:
    // --- Public QuickSort Entry Point ---
    void QuickSort(Sequence<T>* sequence) override {
        QuickSortRecursive(0, sequence->GetLength() - 1, sequence);
    }

    // --- Public MergeSort Entry Point ---
    void MergeSort(Sequence<T>* sequence) override {
        int n = sequence->GetLength();
        buffer = new DynamicArray<T>(n); // Инициализация буфера
        MergeSortRecursive(0, n - 1, sequence);
        delete buffer; // Очистка буфера
    }
};

#endif
