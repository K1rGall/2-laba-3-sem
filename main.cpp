#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QInputDialog>
#include <QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <vector>
#include <iostream>
#include "testing/AllAboutFiles.h"
#include "testing/Person.h"
#include "testing/DynamicArray.h"
#include "testing/timesorters.h"
#include "testing/testing.h"
#include <thread>
#include <random>
#include <algorithm>
#include "testing/sorters.h"


QT_USE_NAMESPACE

using namespace std;

void SortLargeFile() {
    std::string inputFile, outputFile;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;

    int chunkSize;
    std::cout << "Enter max chunk size (number of records per chunk): ";
    std::cin >> chunkSize;

    std::cout << "Sorting large file...\n";
    ExternalSort(inputFile, outputFile, chunkSize);
    std::cout << "Sorting completed. Sorted data saved to " << outputFile << std::endl;
}

// Функция для генерации случайного файла
template<typename T>
void TryWriteToFile(string FileNameOut, string DeclineWord, DynamicArray<T>* Array)
{
    if (FileNameOut != DeclineWord)
    {
        std::cout << "Writing data to the file " << FileNameOut << std::endl;
        WriteSequenceToFile(FileNameOut, Array);
    }
}

void GenerateRandomFile() {
    std::string FileName;
    std::cout << "Enter file name to save random data: ";
    std::cin >> FileName;

    int CountNumbers;
    std::cout << "Enter the number of entries: ";
    std::cin >> CountNumbers;

    GenerateRandomFile(CountNumbers, FileName);
    std::cout << "Random file generated successfully.\n";
}

void GenerateRandomData(DynamicArray<People>& Peoples, int StartIndex, int EndIndex) {
    for (int i = StartIndex; i < EndIndex; i++) {
        Peoples[i] = People();
    }
}

// Функция для сортировки с использованием QuickSort
void SortQuickSort() {
    std::string FileNameIn;
    std::string FileNameOut;
    std::string DeclineWord = "no";
    DynamicArray<People> Array;

    std::cout << "Write file name to sort\n";
    std::cin >> FileNameIn;

    std::cout << "Write file name to save the result (type no to don't save the result)\n";
    std::cin >> FileNameOut;

    std::cout << "Read data from the file " << FileNameIn << std::endl;
    ReadDynamicArrayFromFile(FileNameIn, &Array);

    std::cout << "Starting sorting using QuickSort..." << std::endl;

    QuickSort<People> quickSorter;
    quickSorter.Sort(&Array);

    std::cout << "Sorting completed." << std::endl;

    TryWriteToFile(FileNameOut, DeclineWord, &Array);
}

void SortMergeSort() {
    std::string FileNameIn;
    std::string FileNameOut;
    std::string DeclineWord = "no";
    DynamicArray<People> Array;

    std::cout << "Write file name to sort\n";
    std::cin >> FileNameIn;

    std::cout << "Write file name to save the result (type no to don't save the result)\n";
    std::cin >> FileNameOut;

    std::cout << "Read data from the file " << FileNameIn << std::endl;
    ReadDynamicArrayFromFile(FileNameIn, &Array);

    std::cout << "Starting sorting using MergeSort..." << std::endl;

    MergeSort<People> mergeSorter;
    mergeSorter.Sort(&Array);

    std::cout << "Sorting completed." << std::endl;

    TryWriteToFile(FileNameOut, DeclineWord, &Array);
}

// Функция для построения графика
void PlotQuickSortGraph(std::vector<double>& X, std::vector<double>& Y, QChartView* ChartView) {
    QLineSeries *Series = new QLineSeries();
    for (size_t i = 0; i < X.size(); i++) {
        Series->append(X[i], Y[i]);
    }

    QChart *Chart = new QChart();
    Chart->addSeries(Series);
    Chart->setTitle("QuickSort Performance");
    Chart->createDefaultAxes();

    // Настроим оси
    QValueAxis *AxisX = new QValueAxis();
    AxisX->setTitleText("Number of Elements");
    AxisX->setLabelFormat("%d");
    Chart->setAxisX(AxisX, Series);

    QValueAxis *AxisY = new QValueAxis();
    AxisY->setTitleText("Duration (seconds)");
    AxisY->setLabelFormat("%.5f");
    Chart->setAxisY(AxisY, Series);

    ChartView->setChart(Chart);
    ChartView->setRenderHint(QPainter::Antialiasing);
}

void PlotMergeSortGraph(std::vector<double>& X, std::vector<double>& Y, QChartView* ChartView) {
    QLineSeries *Series = new QLineSeries();
    for (size_t i = 0; i < X.size(); i++) {
        Series->append(X[i], Y[i]);
    }

    QChart *Chart = new QChart();
    Chart->addSeries(Series);
    Chart->setTitle("MergeSort Performance");
    Chart->createDefaultAxes();

    // Настроим оси
    QValueAxis *AxisX = new QValueAxis();
    AxisX->setTitleText("Number of Elements");
    AxisX->setLabelFormat("%d");
    Chart->setAxisX(AxisX, Series);

    QValueAxis *AxisY = new QValueAxis();
    AxisY->setTitleText("Duration (seconds)");
    AxisY->setLabelFormat("%.5f");
    Chart->setAxisY(AxisY, Series);

    ChartView->setChart(Chart);
    ChartView->setRenderHint(QPainter::Antialiasing);
}

// Функция для построения графика для сравнения сортировок
void PlotComparisonGraph(std::vector<double>& X, std::vector<double>& YQuickSort, std::vector<double>& YMergeSort, QChartView* ChartView) {
    QLineSeries *SeriesQuickSort = new QLineSeries();
    QLineSeries *SeriesMergeSort = new QLineSeries();

    for (size_t i = 0; i < X.size(); i++) {
        SeriesQuickSort->append(X[i], YQuickSort[i]);
        SeriesMergeSort->append(X[i], YMergeSort[i]);
    }

    QChart *Chart = new QChart();
    Chart->addSeries(SeriesQuickSort);
    Chart->addSeries(SeriesMergeSort);

    Chart->setTitle("Sorting Performance Comparison (QuickSort vs MergeSort)");
    Chart->createDefaultAxes();

    // Настроим оси
    QValueAxis *AxisX = new QValueAxis();
    AxisX->setTitleText("Number of Elements");
    AxisX->setLabelFormat("%d");
    Chart->setAxisX(AxisX, SeriesQuickSort);
    Chart->setAxisX(AxisX, SeriesMergeSort);

    QValueAxis *AxisY = new QValueAxis();
    AxisY->setTitleText("Duration (seconds)");
    AxisY->setLabelFormat("%.5f");
    Chart->setAxisY(AxisY, SeriesQuickSort);
    Chart->setAxisY(AxisY, SeriesMergeSort);

    ChartView->setChart(Chart);
    ChartView->setRenderHint(QPainter::Antialiasing);
}

// Главный класс для окна программы
class MainWindow : public QWidget
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("Sorting Application");

        QVBoxLayout *Layout = new QVBoxLayout(this);

        // Кнопки для взаимодействия с пользователем
        QPushButton *BtnQuickSortGraph = new QPushButton("QuickSort Graph", this);
        QPushButton *BtnMergeSortGraph = new QPushButton("MergeSort Graph", this);
        QPushButton *BtnCompareSorts = new QPushButton("Compare QuickSort vs MergeSort", this);

        Layout->addWidget(BtnQuickSortGraph);
        Layout->addWidget(BtnMergeSortGraph);
        Layout->addWidget(BtnCompareSorts);

        // Контейнер для отображения графиков
        ChartView = new QChartView(this);
        Layout->addWidget(ChartView);

        connect(BtnQuickSortGraph, &QPushButton::clicked, this, &MainWindow::PlotQuickSortGraph);
        connect(BtnMergeSortGraph, &QPushButton::clicked, this, &MainWindow::PlotMergeSortGraph);
        connect(BtnCompareSorts, &QPushButton::clicked, this, &MainWindow::PlotComparisonGraph);

        setLayout(Layout);
        resize(800, 600);
    }

private slots:
    void PlotQuickSortGraph()
    {
        PlotGraph("QuickSort");
    }

    void PlotMergeSortGraph()
    {
        PlotGraph("MergeSort");
    }

    void PlotComparisonGraph()
    {
        CompareSortingGraphs();
    }

private:
    void PlotGraph(const QString& SortingMethod)
    {
        const int Max = 1000000;  // 1000000 элементов
        const int Step = 200000;   // Шаг для увеличения количества элементов
        std::vector<double> X;
        std::vector<double> YQuickSort;
        std::vector<double> YMergeSort;

        for (int i = Step; i <= Max; i += Step)
        {
            DynamicArray<People> Peoples(i);

            // Использование нескольких потоков для генерации данных
            int Half = i / 2;
            std::thread T1(GenerateRandomData, std::ref(Peoples), 0, Half);
            std::thread T2(GenerateRandomData, std::ref(Peoples), Half, i);

            // Ожидание завершения потоков
            T1.join();
            T2.join();

            // Создание объектов сортировщиков
            QuickSort<People> quickSorter;
            MergeSort<People> mergeSorter;

            // Сортировка QuickSort
            auto startQuick = std::chrono::high_resolution_clock::now();
            quickSorter.Sort(&Peoples);
            auto endQuick = std::chrono::high_resolution_clock::now();
            double DurationQuickSort = std::chrono::duration<double>(endQuick - startQuick).count();

            X.push_back(i);
            YQuickSort.push_back(DurationQuickSort);

            // Сортировка MergeSort
            auto startMerge = std::chrono::high_resolution_clock::now();
            mergeSorter.Sort(&Peoples);
            auto endMerge = std::chrono::high_resolution_clock::now();
            double DurationMergeSort = std::chrono::duration<double>(endMerge - startMerge).count();

            YMergeSort.push_back(DurationMergeSort);
        }

        ::PlotComparisonGraph(X, YQuickSort, YMergeSort, ChartView);
    }

    void CompareSortingGraphs()
    {
        const int Max = 1000000;  // Maximum number of elements for testing
        const int Step = 200000;   // Step size for increasing number of elements
        std::vector<double> X;
        std::vector<double> YQuickSort;
        std::vector<double> YMergeSort;

        for (int i = 0; i <= Max; i += Step)
        {
            DynamicArray<People> Peoples(i);

            // Заполнение массива случайными данными
            for (int j = 0; j < i; j++) {
                Peoples[j] = People(); // Заполняем массив случайными значениями
            }

            // Создаем объекты сортировщиков
            QuickSort<People> quickSorter;
            MergeSort<People> mergeSorter;

            // Измерение времени для QuickSort
            auto startQuick = std::chrono::high_resolution_clock::now();
            quickSorter.Sort(&Peoples);
            auto endQuick = std::chrono::high_resolution_clock::now();
            double DurationQuickSort = std::chrono::duration<double>(endQuick - startQuick).count();

            // Измерение времени для MergeSort
            auto startMerge = std::chrono::high_resolution_clock::now();
            mergeSorter.Sort(&Peoples);
            auto endMerge = std::chrono::high_resolution_clock::now();
            double DurationMergeSort = std::chrono::duration<double>(endMerge - startMerge).count();

            // Запись данных для построения графиков
            X.push_back(i);
            YQuickSort.push_back(DurationQuickSort);
            YMergeSort.push_back(DurationMergeSort);
        }

        // Построение графика для сравнения двух сортировок
        ::PlotComparisonGraph(X, YQuickSort, YMergeSort, ChartView);
    }

private:
    QChartView *ChartView;
};

int main(int argc, char *argv[])
{
    // Консольное меню
    while (true)
    {
        std::cout << "\nSorting Application Menu:\n";
        std::cout << "0. Sort a large file\n";
        std::cout << "1. Perform QuickSort\n";
        std::cout << "2. Perform MergeSort\n";
        std::cout << "3. Compare QuickSort and MergeSort\n";
        std::cout << "4. Launch Graphical Interface\n";
        std::cout << "5. Generate Random File\n";
        std::cout << "6. Sort file with QuickSort\n";
        std::cout << "7. Sort file with MergeSort\n";
        std::cout << "8. Run All Tests\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 9: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice < 0 || choice > 9) {
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        int numElements = 0;
        if (choice >= 1 && choice <= 3) {
            std::cout << "Enter the number of elements: ";
            while (!(std::cin >> numElements) || numElements <= 0) {
                std::cout << "Invalid input. Please enter a positive number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        DynamicArray<People> array(numElements);
        for (int i = 0; i < numElements; i++) {
            array[i] = People(); // Заполняем массив случайными значениями
        }

        double durationQuickSort, durationMergeSort;

        switch (choice)
        {
            case 0:
                SortLargeFile();
                break;
            case 1: {
                std::cout << "Performing QuickSort...\n";

                // Создаем объект сортировщика
                QuickSort<People> quickSorter;

                // Измеряем время выполнения
                auto startQuick = std::chrono::high_resolution_clock::now();
                quickSorter.Sort(&array);
                auto endQuick = std::chrono::high_resolution_clock::now();

                double durationQuickSort = std::chrono::duration<double>(endQuick - startQuick).count();

                std::cout << "QuickSort completed in " << durationQuickSort << " seconds.\n";
                break;
            }

            case 2: {
                std::cout << "Performing MergeSort...\n";

                // Создаем объект сортировщика
                MergeSort<People> mergeSorter;

                // Измеряем время выполнения
                auto startMerge = std::chrono::high_resolution_clock::now();
                mergeSorter.Sort(&array);
                auto endMerge = std::chrono::high_resolution_clock::now();

                double durationMergeSort = std::chrono::duration<double>(endMerge - startMerge).count();

                std::cout << "MergeSort completed in " << durationMergeSort << " seconds.\n";
                break;
            }
            case 3: {
                std::cout << "Performing QuickSort...\n";

                // Создаем объект сортировщика QuickSort
                QuickSort<People> quickSorter;

                // Измеряем время выполнения QuickSort
                auto startQuick = std::chrono::high_resolution_clock::now();
                quickSorter.Sort(&array);
                auto endQuick = std::chrono::high_resolution_clock::now();

                double durationQuickSort = std::chrono::duration<double>(endQuick - startQuick).count();

                std::cout << "QuickSort completed in " << durationQuickSort << " seconds.\n";

                // Перезаполняем массив случайными значениями перед MergeSort
                for (int i = 0; i < numElements; i++) {
                    array[i] = People();
                }

                std::cout << "Performing MergeSort...\n";

                // Создаем объект сортировщика MergeSort
                MergeSort<People> mergeSorter;

                // Измеряем время выполнения MergeSort
                auto startMerge = std::chrono::high_resolution_clock::now();
                mergeSorter.Sort(&array);
                auto endMerge = std::chrono::high_resolution_clock::now();

                double durationMergeSort = std::chrono::duration<double>(endMerge - startMerge).count();

                std::cout << "MergeSort completed in " << durationMergeSort << " seconds.\n";

                std::cout << "\nComparison:\n";
                std::cout << "QuickSort: " << durationQuickSort << " seconds\n";
                std::cout << "MergeSort: " << durationMergeSort << " seconds\n";
                break;
            }
            case 4: {
                QApplication a(argc, argv);
                MainWindow w;
                w.show();
                a.exec();
                break;
            }
            case 5:
                GenerateRandomFile();
                break;
            case 6:
                SortQuickSort();
                break;
            case 7:
                SortMergeSort();
                break;
            case 8:
                RunAllTests();
                break;
            case 9:
                return 0;
        }
    }

    return 0;
}
#include "main.moc"