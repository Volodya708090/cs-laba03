#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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

// Функция для отображения заголовка SVG
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

// Функция для отображения окончания SVG
void svg_end() {
    cout << "</svg>\n";
}

// Функция для вывода текста в SVG
void svg_text(double left, double baseline, string text, int font_size) {
    cout << "<text x='" << left << "' y='" << baseline << "' font-size='" << font_size << "'>" << text << "</text>";
}

// Функция для вывода прямоугольника в SVG
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

// Функция для отображения гистограммы в формате SVG
void show_histogram_svg(const vector<size_t>& bins, int font_size) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    const double max_bin = *max_element(bins.begin(), bins.end());
    const double scaling_factor = (IMAGE_WIDTH - TEXT_WIDTH) / max_bin;

    double top = 0;
    for (size_t bin : bins) {
        const double bin_width = bin * scaling_factor;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin), font_size);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "gold", "#ffeeee");
        top += BIN_HEIGHT;
    }
    svg_end();
}

int main() {
    size_t number_count;
    cerr << "Enter the number of values: ";
    cin >> number_count;

    // Ввод чисел
    vector<size_t> bins = input_numbers(number_count);

    // Запрос размера шрифта у пользователя
    int font_size = 12;
    cerr << "Enter font size (8-32): ";
    cin >> font_size;
    while (font_size < 8 || font_size > 32) {
        cerr << "Invalid font size. Please enter a value between 8 and 32: ";
        cin >> font_size;
    }

    // Создание гистограммы
    vector<size_t> bin_counts = make_histogram(bins);

    // Отображение гистограммы в формате SVG
    show_histogram_svg(bin_counts, font_size);

    return 0;
}
