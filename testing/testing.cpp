#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "timesorters.h"
#include "Sequence.h"
#include <cassert>

template<typename T>
void TestSorter(void (*sortFunc)(Sequence<T>*), Sequence<T>* sequence, T* expectedArray, int size) {
    sortFunc(sequence);
    for (int i = 0; i < size; i++) {
        assert(sequence->GetElement(i) == expectedArray[i]);
    }
}
template<typename T>
void QuickSort(Sequence<T>* sequence)
{
    double duration = 0;
    SortSequenceByQuickSort(sequence, &duration);
}

template<typename T>
void MergeSort(Sequence<T>* sequence)
{
    double duration = 0;
    SortSequenceByMergeSort(sequence, &duration);
}

void ConstructorTests() {
    int array[] = { 1, 2, 3, 4 };
    int size = 4;

    DynamicArray<int> dynamicArray(array, size);

    for (int i = 0; i < size; i++) {
        if (dynamicArray.GetElement(i) != array[i]) {
            std::cout << "Constructor test failed at index " << i << std::endl;
        }
        //else{
            //std::cout << "Passed" << i << std::endl;}
    }

    DynamicArray<int> dynamicArray1(size);

    for (int i = 0; i < size; i++) {
        if (dynamicArray1.GetElement(i) != 0) {  // assuming default value 0 for new elements
            std::cout << "Constructor test failed at index " << i << " for dynamicArray1" << std::endl;
        }
        //else{
        //std::cout << "Passed" << i << std::endl;}
    }

    DynamicArray<int> dynamicArray2(dynamicArray);

    for (int i = 0; i < size; i++) {
        if (dynamicArray2.GetElement(i) != array[i]) {
            std::cout << "Copy constructor test failed at index " << i << std::endl;
        }
        //else{
        //std::cout << "Passed" << i << std::endl;}
    }
}

void CopyConstructorTests() {
    int array[] = { 1, 2, 3, 4 };
    int size = 4;

    DynamicArray<int> dynamicArray1(array, size);
    DynamicArray<int> dynamicArray2 = dynamicArray1;

    for (int i = 0; i < size; i++) {
        if (dynamicArray1.GetElement(i) != array[i] || dynamicArray2.GetElement(i) != array[i]) {
            std::cout << "Copy constructor test failed at index " << i << std::endl;
        }
        //else{
        //std::cout << "Passed" << i << std::endl;}
    }
}

void GetElementsTests() {
    int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = 10;

    DynamicArray<int> dynamicArray(array, size);

    for (int i = 0; i < size; i++) {
        if (dynamicArray.GetElement(i) != array[i]) {
            std::cout << "Get element test failed at index " << i << std::endl;
        }
    }

    if (dynamicArray.GetFirstElement() != array[0]) {
        std::cout << "First element test failed" << std::endl;
    }

    if (dynamicArray.GetLastElement() != array[size - 1]) {
        std::cout << "Last element test failed" << std::endl;
    }
}

void AppendTest() {
    int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int size = 9;
    int number = 9;

    DynamicArray<int> dynamicArray(array, size);
    dynamicArray.Append(number);

    for (int i = 0; i < size; i++) {
        if (dynamicArray.GetElement(i) != array[i]) {
            std::cout << "Append test failed at index " << i << std::endl;
        }
    }

    if (dynamicArray.GetElement(size) != number) {
        std::cout << "Append test failed for last element" << std::endl;
    }

    if (dynamicArray.GetLength() != (size + 1)) {
        std::cout << "Append test failed for length" << std::endl;
    }
}

void PrependTest() {
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = 9;
    int number = 0;

    DynamicArray<int> dynamicArray(array, size);
    dynamicArray.Prepend(number);

    for (int i = 0; i < size; i++) {
        if (dynamicArray.GetElement(i + 1) != array[i]) {
            std::cout << "Prepend test failed at index " << i << std::endl;
        }
    }

    if (dynamicArray.GetElement(0) != number) {
        std::cout << "Prepend test failed for first element" << std::endl;
    }

    if (dynamicArray.GetLength() != (size + 1)) {
        std::cout << "Prepend test failed for length" << std::endl;
    }
}

void InsertAtTest() {
    int array[] = { 0, 1, 2, 3, 5, 6, 7, 8, 9 };
    int size = 9;
    int number = 4;
    int index = 4;

    DynamicArray<int> dynamicArray(array, size);
    dynamicArray.InsertAt(number, index);

    for (int i = 0; i < index; i++) {
        if (dynamicArray.GetElement(i) != array[i]) {
            std::cout << "InsertAt test failed at index " << i << std::endl;
        }
    }

    if (dynamicArray.GetElement(index) != number) {
        std::cout << "InsertAt test failed for inserted element" << std::endl;
    }

    for (int i = index + 1; i < dynamicArray.GetLength(); i++) {
        if (dynamicArray.GetElement(i) != array[i - 1]) {
            std::cout << "InsertAt test failed at index " << i << std::endl;
        }
    }

    if (dynamicArray.GetLength() != (size + 1)) {
        std::cout << "InsertAt test failed for length" << std::endl;
    }
}
void LinkedConstructorTests() {
    int array[] = {1, 2, 3, 4};
    int size = 4;

    LinkedList<int> list(array, size);

    for (int i = 0; i < size; i++) {
        if (list.GetElement(i) != array[i]) {
            std::cout << "Constructor test failed at index " << i << std::endl;
        }
    }

    LinkedList<int> list1(list);

    for (int i = 0; i < size; i++) {
        if (list1.GetElement(i) != array[i]) {
            std::cout << "Copy constructor test failed at index " << i << std::endl;
        }
    }
}

void LinkedGetElementsTests() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = 10;

    LinkedList<int> list(array, size);

    for (int i = 0; i < size; i++) {
        if (list.GetElement(i) != array[i]) {
            std::cout << "Get element test failed at index " << i << std::endl;
        }
    }

    if (list.GetFirstElement() != array[0]) {
        std::cout << "First element test failed" << std::endl;
    }

    if (list.GetLastElement() != array[size - 1]) {
        std::cout << "Last element test failed" << std::endl;
    }
}

void LinkedGetSubsequencesTests() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = 10;

    LinkedList<int> list(array, size);

    LinkedList<int>* subsequence = list.GetSubsequence(0, size);

    if (list.GetLength() != subsequence->GetLength()) {
        std::cout << "Get subsequence length test failed" << std::endl;
    }

    for (int i = 0; i < size; i++) {
        if (list.GetElement(i) != subsequence->GetElement(i)) {
            std::cout << "Get subsequence element test failed at index " << i << std::endl;
        }
    }

    subsequence = list.GetSubsequence(0, 4 * size);

    if (list.GetLength() != subsequence->GetLength()) {
        std::cout << "Get subsequence larger than list test failed" << std::endl;
    }

    for (int i = 0; i < size; i++) {
        if (list.GetElement(i) != subsequence->GetElement(i)) {
            std::cout << "Get subsequence larger than list element test failed at index " << i << std::endl;
        }
    }

    int sliceCount = 2;

    subsequence = list.GetSubsequence(sliceCount, size - sliceCount);

    if (size - 2 * sliceCount + 1 != subsequence->GetLength()) {
        std::cout << "Subsequence slice count test failed" << std::endl;
    }

    for (int i = 0; i < size - sliceCount - 1; i++) {
        if (list.GetElement(i + sliceCount) != subsequence->GetElement(i)) {
            std::cout << "Subsequence slice content test failed at index " << i << std::endl;
        }
    }

    int index = 3;

    subsequence = list.GetSubsequence(index, index);

    if (subsequence->GetLength() != 1) {
        std::cout << "Get subsequence of length 1 failed" << std::endl;
    }

    if (list.GetElement(index) != subsequence->GetElement(0)) {
        std::cout << "Subsequence single element mismatch test failed" << std::endl;
    }
}

void LinkedGetLengthTests() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = 10;

    LinkedList<int> list(array, size);

    if (list.GetLength() != size) {
        std::cout << "Get length test failed" << std::endl;
    }
}

void LinkedAppendTest() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int size = 9;
    int number = 9;

    LinkedList<int> list(array, size);
    list.Append(number);

    for (int i = 0; i < size; i++) {
        if (list.GetElement(i) != array[i]) {
            std::cout << "Append test failed at index " << i << std::endl;
        }
    }

    if (list.GetElement(size) != number) {
        std::cout << "Append test failed for last element" << std::endl;
    }

    if (list.GetLength() != (size + 1)) {
        std::cout << "Append test failed for length" << std::endl;
    }
}

void LinkedPrependTest() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = 9;
    int number = 0;

    LinkedList<int> list(array, size);
    list.Prepend(number);

    for (int i = 0; i < size; i++) {
        if (list.GetElement(i + 1) != array[i]) {
            std::cout << "Prepend test failed at index " << i << std::endl;
        }
    }

    if (list.GetElement(0) != number) {
        std::cout << "Prepend test failed for first element" << std::endl;
    }

    if (list.GetLength() != (size + 1)) {
        std::cout << "Prepend test failed for length" << std::endl;
    }
}

void LinkedInsertAtTest() {
    int array[] = {0, 1, 2, 3, 5, 6, 7, 8, 9};
    int size = 9;
    int number = 4;
    int index = 4;

    LinkedList<int> list(array, size);
    list.InsertAt(number, index);

    for (int i = 0; i < index; i++) {
        if (list.GetElement(i) != array[i]) {
            std::cout << "InsertAt test failed at index " << i << std::endl;
        }
    }

    if (list.GetElement(index) != number) {
        std::cout << "InsertAt test failed for inserted element" << std::endl;
    }

    for (int i = index + 1; i < list.GetLength(); i++) {
        if (list.GetElement(i) != array[i - 1]) {
            std::cout << "InsertAt test failed at index " << i << std::endl;
        }
    }

    if (list.GetLength() != (size + 1)) {
        std::cout << "InsertAt test failed for length" << std::endl;
    }
}

void LinkedUnionTest() {
    int array1[] = {0, 1, 2, 3, 5};
    int array2[] = {6, 7, 8, 9};
    int size1 = 5;
    int size2 = 4;

    LinkedList<int> list1(array1, size1);
    LinkedList<int> list2(array2, size2);

    list1.Union(&list2);

    for (int i = 0; i < size1; i++) {
        if (list1.GetElement(i) != array1[i]) {
            std::cout << "Union test failed at index " << i << std::endl;
        }
    }

    for (int i = size1; i < size1 + size2; i++) {
        if (list1.GetElement(i) != array2[i - size1]) {
            std::cout << "Union test failed at index " << i << std::endl;
        }
    }
}


void SortingTests() {
    int array1[] = {5, 3, 1, 8, 9, 2, 34, -7};
    int sortedArray1[] = {-7, 1, 2, 3, 5, 8, 9, 34};
    int size1 = 8;

    DynamicArray<int> dynamicArray1(array1, size1);
    TestSorter(QuickSort<int>, &dynamicArray1, sortedArray1, size1);
    TestSorter(MergeSort<int>, &dynamicArray1, sortedArray1, size1);

    int array2[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int sortedArray2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size2 = 8;

    DynamicArray<int> dynamicArray2(array2, size2);
    TestSorter(QuickSort<int>, &dynamicArray2, sortedArray2, size2);
    TestSorter(MergeSort<int>, &dynamicArray2, sortedArray2, size2);

    int array3[] = {1, 2, 3, 5, 4, 6, 7, 8};
    int sortedArray3[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size3 = 8;

    DynamicArray<int> dynamicArray3(array3, size3);
    TestSorter(QuickSort<int>, &dynamicArray3, sortedArray3, size3);
    TestSorter(MergeSort<int>, &dynamicArray3, sortedArray3, size3);

    int array4[] = {1};
    int sortedArray4[] = {1};
    int size4 = 1;

    DynamicArray<int> dynamicArray4(array4, size4);
    TestSorter(QuickSort<int>, &dynamicArray4, sortedArray4, size4);
    TestSorter(MergeSort<int>, &dynamicArray4, sortedArray4, size4);

    int size5 = 10000;
    DynamicArray<int> dynamicArray5(0);
    for (int i = 0; i < size5; i++) {
        dynamicArray5.Append(rand());
    }

    QuickSort(&dynamicArray5);
    for (int i = 0; i < size5 - 1; i++) {
        assert(dynamicArray5.GetElement(i) <= dynamicArray5.GetElement(i + 1));
    }

    for (int i = 0; i < size5; i++) {
        dynamicArray5.Append(rand());
    }
    MergeSort(&dynamicArray5);
    for (int i = 0; i < size5 - 1; i++) {
        assert(dynamicArray5.GetElement(i) <= dynamicArray5.GetElement(i + 1));
    }
}

void RunAllTests() {
    std::cout << "Running Constructor Tests...\n";
    ConstructorTests();
    std::cout << "Running Copy Constructor Tests...\n";
    CopyConstructorTests();
    std::cout << "Running Get Elements Tests...\n";
    GetElementsTests();
    std::cout << "Running Append Tests...\n";
    AppendTest();
    std::cout << "Running Prepend Tests...\n";
    PrependTest();
    std::cout << "Running InsertAt Tests...\n";
    InsertAtTest();
    std::cout << "Running Linked Constructor Tests...\n";
    LinkedConstructorTests();
    std::cout << "Running Linked Get Elements Tests...\n";
    LinkedGetElementsTests();
    std::cout << "Running Linked Get Subsequences Tests...\n";
    LinkedGetSubsequencesTests();
    std::cout << "Running Linked Get Length Tests...\n";
    LinkedGetLengthTests();
    std::cout << "Running Linked Append Tests...\n";
    LinkedAppendTest();
    std::cout << "Running Linked Prepend Tests...\n";
    LinkedPrependTest();
    std::cout << "Running Linked InsertAt Tests...\n";
    LinkedInsertAtTest();
    std::cout << "Running Linked Union Tests...\n";
    LinkedUnionTest();
    std::cout << "Running Sorting Tests...\n";
    SortingTests();
    std::cout << "All tests completed!\n";
}





