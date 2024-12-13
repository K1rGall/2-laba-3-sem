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

QT_USE_NAMESPACE

// Функция для генерации случайного файла
using namespace std;
template<typename T>
void TryWriteToFile(string fileNameOut, string declineWord, DynamicArray<T>* array)
{
    if (fileNameOut != declineWord)
    {
        std::cout << "Writing data to the file " << fileNameOut << std::endl;
        WriteSequenceToFile(fileNameOut, array);
    }
}
void generateRandomFile() {
    std::string fileName;
    std::cout << "Enter file name to save random data: ";
    std::cin >> fileName;

    int countNumbers;
    std::cout << "Enter the number of entries: ";
    std::cin >> countNumbers;

    GenerateRandomFile(countNumbers, fileName);
    std::cout << "Random file generated successfully.\n";
}
void generateRandomData(DynamicArray<People>& peoples, int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++) {
        peoples[i] = People();
    }
}
// Функция для сортировки с использованием QuickSort
void sortQuickSort() {
    string fileNameIn;
    string fileNameOut;
    string declineWord = "no";
    DynamicArray<People> array;
    double duration = 0;

    cout << "Write file name to sort\n";
    cin >> fileNameIn;

    cout << "Write file name to save the result (type no to don't save the result)\n";
    cin >> fileNameOut;

    std::cout << "Read data from the file " << fileNameIn << std::endl;
    ReadDynamicArrayFromFile(fileNameIn, &array);

    std::cout << "Starting sorting..." << std::endl;
    SortSequenceByQuickSort(&array, &duration);

    cout << "Sorting spend " << duration << " seconds\n";

    TryWriteToFile(fileNameOut, declineWord, &array);
}

// Функция для сортировки с использованием MergeSort
void sortMergeSort() {
    string fileNameIn;
    string fileNameOut;
    string declineWord = "no";
    DynamicArray<People> array;
    double duration = 0;

    cout << "Write file name to sort\n";
    cin >> fileNameIn;

    cout << "Write file name to save the result (type no to don't save the result)\n";
    cin >> fileNameOut;

    std::cout << "Read data from the file " << fileNameIn << std::endl;
    ReadDynamicArrayFromFile(fileNameIn, &array);

    std::cout << "Starting sorting..." << std::endl;
    SortSequenceByMergeSort(&array, &duration);

    cout << "Sorting spend " << duration << " seconds\n";

    TryWriteToFile(fileNameOut, declineWord, &array);
}
// Функция для построения графика
void PlotQuickSortGraph(std::vector<double>& x, std::vector<double>& y, QChartView* chartView) {
    QLineSeries *series = new QLineSeries();
    for (size_t i = 0; i < x.size(); i += 1) {  // Ограничиваем количество точек для улучшения производительности
        series->append(x[i], y[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("QuickSort Performance");
    chart->createDefaultAxes();

    // Настроим оси
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Number of Elements");
    axisX->setLabelFormat("%d");
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Duration (seconds)");
    axisY->setLabelFormat("%.5f");
    chart->setAxisY(axisY, series);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void PlotMergeSortGraph(std::vector<double>& x, std::vector<double>& y, QChartView* chartView) {
    QLineSeries *series = new QLineSeries();
    for (size_t i = 0; i < x.size(); i += 1) {  // Ограничиваем количество точек для улучшения производительности
        series->append(x[i], y[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("MergeSort Performance");
    chart->createDefaultAxes();

    // Настроим оси
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Number of Elements");
    axisX->setLabelFormat("%d");
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Duration (seconds)");
    axisY->setLabelFormat("%.5f");
    chart->setAxisY(axisY, series);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

// Функция для построения графика для сравнения сортировок
void PlotComparisonGraph(std::vector<double>& x, std::vector<double>& yQuickSort, std::vector<double>& yMergeSort, QChartView* chartView) {
    QLineSeries *seriesQuickSort = new QLineSeries();
    QLineSeries *seriesMergeSort = new QLineSeries();

    for (size_t i = 0; i < x.size(); i += 1) {  // Ограничиваем количество точек для улучшения производительности
        seriesQuickSort->append(x[i], yQuickSort[i]);
        seriesMergeSort->append(x[i], yMergeSort[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(seriesQuickSort);
    chart->addSeries(seriesMergeSort);

    chart->setTitle("Sorting Performance Comparison (QuickSort vs MergeSort)");
    chart->createDefaultAxes();

    // Настроим оси
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Number of Elements");
    axisX->setLabelFormat("%d");
    chart->setAxisX(axisX, seriesQuickSort);
    chart->setAxisX(axisX, seriesMergeSort);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Duration (seconds)");
    axisY->setLabelFormat("%.5f");
    chart->setAxisY(axisY, seriesQuickSort);
    chart->setAxisY(axisY, seriesMergeSort);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

// Главный класс для окна программы
class MainWindow : public QWidget
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("Sorting Application");

        QVBoxLayout *layout = new QVBoxLayout(this);

        // Кнопки для взаимодействия с пользователем
        QPushButton *btnQuickSortGraph = new QPushButton("QuickSort Graph", this);
        QPushButton *btnMergeSortGraph = new QPushButton("MergeSort Graph", this);
        QPushButton *btnCompareSorts = new QPushButton("Compare QuickSort vs MergeSort", this);

        layout->addWidget(btnQuickSortGraph);
        layout->addWidget(btnMergeSortGraph);
        layout->addWidget(btnCompareSorts);

        // Контейнер для отображения графиков
        chartView = new QChartView(this);
        layout->addWidget(chartView);

        connect(btnQuickSortGraph, &QPushButton::clicked, this, &MainWindow::plotQuickSortGraph);
        connect(btnMergeSortGraph, &QPushButton::clicked, this, &MainWindow::plotMergeSortGraph);
        connect(btnCompareSorts, &QPushButton::clicked, this, &MainWindow::plotComparisonGraph);

        setLayout(layout);
        resize(800, 600);
    }

private slots:
    void plotQuickSortGraph()
    {
        plotGraph("QuickSort");
    }

    void plotMergeSortGraph()
    {
        plotGraph("MergeSort");
    }

    void plotComparisonGraph()
    {
        compareSortingGraphs();
    }

private:
    void plotGraph(const QString& sortingMethod)
    {
        const int max = 1000000;  // 100000 элементов
        const int step = 200000;   // Шаг для увеличения количества элементов
        std::vector<double> x;
        std::vector<double> yQuickSort;
        std::vector<double> yMergeSort;

        for (int i = step; i <= max; i += step)
        {
            DynamicArray<People> peoples(i);

            // Использование нескольких потоков для генерации данных
            int half = i / 2;
            std::thread t1(generateRandomData, std::ref(peoples), 0, half);
            std::thread t2(generateRandomData, std::ref(peoples), half, i);

            // Ожидание завершения потоков
            t1.join();
            t2.join();

            double durationQuickSort;
            double durationMergeSort;

            // Сортировка QuickSort
            SortSequenceByQuickSort(&peoples, &durationQuickSort);
            x.push_back(i);
            yQuickSort.push_back(durationQuickSort);

            // Сортировка MergeSort
            SortSequenceByMergeSort(&peoples, &durationMergeSort);
            yMergeSort.push_back(durationMergeSort);
        }

        PlotComparisonGraph(x, yQuickSort, yMergeSort, chartView);
    }

    void PlotComparisonGraph(std::vector<double>& x, std::vector<double>& yQuickSort, std::vector<double>& yMergeSort, QChartView* chartView) {
        QLineSeries *seriesQuickSort = new QLineSeries();
        QLineSeries *seriesMergeSort = new QLineSeries();

        for (size_t i = 0; i < x.size(); i++) {
            seriesQuickSort->append(x[i], yQuickSort[i]);
            seriesMergeSort->append(x[i], yMergeSort[i]);
        }

        QChart *chart = new QChart();
        chart->addSeries(seriesQuickSort);
        chart->addSeries(seriesMergeSort);

        chart->setTitle("Sorting Performance Comparison (QuickSort vs MergeSort)");
        chart->createDefaultAxes();

        // Настроим оси
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("Number of Elements");
        axisX->setLabelFormat("%d");
        chart->setAxisX(axisX, seriesQuickSort);
        chart->setAxisX(axisX, seriesMergeSort);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Duration (seconds)");
        axisY->setLabelFormat("%.5f");
        chart->setAxisY(axisY, seriesQuickSort);
        chart->setAxisY(axisY, seriesMergeSort);

        chartView->setChart(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    }


    void compareSortingGraphs()
    {
        const int max = 1000000;  // Maximum number of elements for testing
        const int step = 200000;   // Step size for increasing number of elements
        std::vector<double> x;
        std::vector<double> yQuickSort;
        std::vector<double> yMergeSort;

        for (int i = step; i <= max; i += step)
        {
            DynamicArray<People> peoples(i);

            // Fill the array with random data once
            for (int j = 0; j < i; j++) {
                peoples[j] = People(); // Randomly populate the array
            }

            double durationQuickSort;
            double durationMergeSort;

            // QuickSort
            SortSequenceByQuickSort(&peoples, &durationQuickSort);

            // MergeSort
            SortSequenceByMergeSort(&peoples, &durationMergeSort);

            x.push_back(i);
            yQuickSort.push_back(durationQuickSort);
            yMergeSort.push_back(durationMergeSort);
        }

        // Plot comparison graph for both QuickSort and MergeSort
        PlotComparisonGraph(x, yQuickSort, yMergeSort, chartView);
    }
private:
    QChartView *chartView;
};

int main(int argc, char *argv[])
{
    // Консольное меню
    while (true)
    {
        std::cout << "\nSorting Application Menu:\n";
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

        if (choice < 1 || choice > 9) {
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
            case 1: {
                std::cout << "Performing QuickSort...\n";
                SortSequenceByQuickSort(&array, &durationQuickSort);
                std::cout << "QuickSort completed in " << durationQuickSort << " seconds.\n";
                break;
            }
            case 2: {
                std::cout << "Performing MergeSort...\n";
                SortSequenceByMergeSort(&array, &durationMergeSort);
                std::cout << "MergeSort completed in " << durationMergeSort << " seconds.\n";
                break;
            }
            case 3: {
                std::cout << "Performing QuickSort...\n";
                SortSequenceByQuickSort(&array, &durationQuickSort);
                std::cout << "QuickSort completed in " << durationQuickSort << " seconds.\n";

                // Перезаполняем массив случайными значениями для MergeSort
                for (int i = 0; i < numElements; i++) {
                    array[i] = People();
                }

                std::cout << "Performing MergeSort...\n";
                SortSequenceByMergeSort(&array, &durationMergeSort);
                std::cout << "MergeSort completed in " << durationMergeSort << " seconds.\n";

                std::cout << "\nComparison:\n";
                std::cout << "QuickSort: " << durationQuickSort << " seconds\n";
                std::cout << "MergeSort: " << durationMergeSort << " seconds\n";
                break;
            }
            case 4: {
                std::cout << "Launching graphical interface...\n";
                QApplication a(argc, argv);
                MainWindow w;
                w.show();
                return a.exec();
            }
            case 5: {
                generateRandomFile();
                break;
            }
            case 6: {
                sortQuickSort();
                break;
            }
            case 7: {
                sortMergeSort();
                break;
            }
            case 8: {
                std::cout << "Running all tests...\n";
                RunAllTests();  // Вызов всех тестов
                break;
            }
            case 9: {
                std::cout << "Exiting the application. Goodbye!\n";
                return 0;
            }
        }
    }
}


#include "main.moc"
