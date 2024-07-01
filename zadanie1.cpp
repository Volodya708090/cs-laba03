#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Функция для ввода чисел
vector<size_t> input_numbers(size_t number_count) {
    vector<size_t> bins(number_count);
    cerr << "Enter the values:" << endl;
    for (size_t i = 0; i < number_count; ++i) {
        cin >> bins[i];
    }
    return bins;
}

// Функция для создания гистограммы
vector<size_t> make_histogram(const vector<size_t>& numbers) {
    vector<size_t> bin_counts;
    size_t bin_sum = 0;
    for (size_t count : numbers) {
        bin_sum += count;
        bin_counts.push_back(bin_sum);
    }
    return bin_counts;
}

// Функция для отображения гистограммы
void show_histogram_text(const vector<size_t>& bin_counts) {
    for (size_t count : bin_counts) {
        cout << setw(3) << count << "|";
        for (size_t i = 0; i < count; ++i) {
            cout << '*';
        }
        cout << endl;
    }
}

int main() {
    size_t number_count;
    cerr << "Enter the number of values: ";
    cin >> number_count;

    // Ввод чисел
    vector<size_t> bins = input_numbers(number_count);

    // Создание гистограммы
    vector<size_t> bin_counts = make_histogram(bins);

    // Отображение гистограммы
    show_histogram_text(bin_counts);

    return 0;
}
