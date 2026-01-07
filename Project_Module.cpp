#include <iostream>
#include "Project_Module.h"
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <fstream>

bool InputDate(int& day, int& month, int& year, const std::string& prompt) {
    std::string date_str;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, date_str);
        if (FormWithSpaces(date_str, day, month, year)) {
            return true;
        }
    }
    return false;
}

bool InputTime(int& hour, int& minute, const std::string& prompt) {
    std::string time_str;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, time_str);
        if (CheckingTime(time_str, hour, minute)) {
            return true;
        }
    }
    return false;
}

int InputNumber(const std::string& prompt, int min_value, int max_value) {
    std::string input;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Ошибка: пустой ввод!\n";
            continue;
        }
        bool all_digits = true;
        for (char c : input) {
            if (c < '0' || c > '9') {
                all_digits = false;
                break;
            }
        }
        if (!all_digits) {
            std::cout << "Ошибка: введите число!\n";
            continue;
        }
        int number = 0;
        for (char c : input) {
            number = number * 10 + (c - '0');
        }
        if (number < min_value || number > max_value) {
            std::cout << "Ошибка: число должно быть от " << min_value << " до " << max_value << "!\n";
            continue;
        }
        return number;
    }
}

int CreatingACalendar(int month, int year) {
    int first_day_of_the_month = CalculateDayOfWeekZeller(1, month, year);
    int days_in_month = GetDaysInMonth(month, year);
    std::string MonthNames[] = {
        "Январь", "Февраль", "Март", "Апрель", 
        "Май", "Июнь", "Июль", "Август", 
        "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
    };
    std::string DayNames[] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    if (!IsValidDate(1, month, year)) {
        return -1;
    }
    std::cout << "\n 📆  " << MonthNames[month - 1] << " " << year << " 📆\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~\n ";
    for (int i = 0; i < 7; i++) {
        std::cout << std::setw(3) << DayNames[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < first_day_of_the_month; i++) {
        std::cout << std::setw(3) << " ";
    }
    for (int day = 1; day <= days_in_month; day++) {
        std::cout << std::setw(3) << day;
        if ((first_day_of_the_month + day) % 7 == 0) {
            std::cout << "\n";
        }
    }
    std::cout << "\n\n";
    return 0;
}

int PrintMonthCalendar() {
    std::cout << "\n--ПОКАЗАТЬ КАЛЕНДАРЬ МЕСЯЦА--\n";

    std::cout << "📅 Введите год и месяц (ГГГГ ММ): ";
    int year, month;
    while (true) {
        std::string date_str;
        std::getline(std::cin, date_str);
        if (CheckingYearMonth(date_str, year, month)) {
            break;
        }
        std::cout << "Неверный формат! Попробуйте ещё раз (ГГГГ ММ): ";
    }
    return CreatingACalendar(month, year);
}

bool CheckingYearMonth(const std::string& date, int& year, int& month) {
    if (date.empty()) {
        std::cout << "Ошибка: пустой ввод!\n";
        return false;
    }
    bool has_digits = false;
    for (char c : date) {
        if (std::isdigit(c)) {
            has_digits = true;
        } else if (c != ' ') {
            std::cout << "Ошибка: неверный символ в дате! Используйте только цифры и пробелы.\n";
            return false;
        }
    }
    if (!has_digits) {
        std::cout << "Ошибка: неверный формат!\n";
        return false;
    }
    std::vector<std::string> numbers;
    std::string current_number;
    for (char c : date) {
        if (c == ' ') {
            if (!current_number.empty()) {
                numbers.push_back(current_number);
                current_number.clear();
            }
        } else {
            current_number += c;
        }
    }
    if (!current_number.empty()) {
        numbers.push_back(current_number);
    }
    if (numbers.size() != 2) {
        std::cout << "Ошибка: нужно ровно два числа (год и месяц)!\n";
        return false;
    }
    for (std::string part: numbers) {
        for (char c : part) {
            if (!std::isdigit(c)) {
                std::cout << "Ошибка: неверный формат числа!\n";
                return false;
            }
        }
    }
    year = std::stoi(numbers[0]), month = std::stoi(numbers[1]);
    return IsValidDate(1, month, year);
}

std::string FormatWithZero(int number) {
    if (number < 10) {
        return "0" + std::to_string(number);
    }
    return std::to_string(number);
}

bool IsNumberStr(const std::string& str) {
    if (str.empty()) { 
        return false;
    }
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

int SelectDateFormat() {
    std::string choice;

    while (true) {
        std::cout << "📅 Выберите формат ввода даты:\n";
        std::cout << "1. Через пробел - (ДД ММ ГГГГ);\n";
        std::cout << "2. В стандартной форме - (ДД.ММ.ГГГГ или ДД/ММ/ГГГГ);\n";
        std::cout << "0. Возврат в главное меню.\n";
        std::cout << "Выберите (0 - 2): ";
        std::getline(std::cin, choice);

        if (choice.empty()) {
            std::cout << "Ошибка: пустой ввод!\n";
            continue;
        } 
        if (choice.length() != 1) {
            std::cout << "Ошибка: введите одну цифру!\n";
            continue;
        }
        char c = choice[0];
        if (c >= '0' && c <= '2') {
            return c - '0';
        } else {
            std::cout << "Ошибка: введите цифру от 0 до 2!\n";
        }
    }
}

bool CheckingLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int GetDaysInMonth(int month, int year) {
    if (month == 2) {
        return CheckingLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

bool IsValidDate(int day, int month, int year) {
    bool has_error = false;
    if (year < 1600 || year > 2150) {
        std::cout << "Ошибка: некорректно введён год!\n";
        has_error = true;
    } if (month < 1 || month > 12) {
        std::cout << "Ошибка: месяц должен быть от 1 до 12!\n";
        has_error = true;
    } if (day < 1) {
        std::cout << "Ошибка: день не может быть меньше 1!\n";
        has_error = true;
    }
    int days_in_month = GetDaysInMonth(month, year);
    if (day > days_in_month) {
        std::cout << "Ошибка: некорректное число дней в месяце!\n";
        has_error = true;
    }
    return !has_error;
}

void PrintDayOfWeek(int day_of_week) {
    if (day_of_week == -1) {
        return;
    }
    switch(day_of_week) {
        case 0: {
            std::cout << "Понедельник\n";
            break;
        } case 1: {
            std::cout << "Вторник\n";
            break;
        } case 2: {
            std::cout << "Среда\n";
            break;
        } case 3: {
            std::cout << "Четверг\n";
            break;
        } case 4: {
            std::cout << "Пятница\n";
            break;
        } case 5: {
            std::cout << "Суббота\n";
            break;
        } case 6: {
            std::cout << "Воскресенье\n";
            break;
        } default: {
            std::cout << "Ошибка: неизвестный код дня недели\n";
            break;
        }
    }
}

/* алгоритм Зеллера для расчета дня недели (используется полная классическая формула)
если месяц - январь\февраль, то меняем цифру месяца на 13(янв.)\14(февр.), а год уменьшаем на 1
остальные месяцы: 3 - март, 4 - апрель, ..., 13 - январь, 14 - февраль (год не меняем)
год_в_столетии = год % 100, столетие = год / 100
формула: день_недели = (день + 13 * (месяц + 1) / 5 + год_в_столетии + год_в_столетии / 4 + столетие / 4 + 5 * столетие) mod(%) 7
результат: 0 - сб, 1 - вс, 2 - пн, ..., 6 - пт
в конце функции преобразуем в обычный формат: 0 - пн, 1 - вт, ..., 6 - вс */
int CalculateDayOfWeekZeller(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int century = year / 100;
    int year_in_a_century = year % 100;
    int day_of_week = (day + ((13 * (month + 1)) / 5) + year_in_a_century + (year_in_a_century / 4) + (century / 4) + (5 * century)) % 7;
    return (day_of_week + 5) % 7;
}

bool FormWithSpaces(const std::string& date_str, int& day, int& month, int& year) {
    if (date_str.empty()) {
        std::cout << "Ошибка: неверный формат даты!\n";
        return false;
    }
    bool has_digits = false;
    for (char c : date_str) {
        if (std::isdigit(c)) {
            has_digits = true;
        } else if (c != ' ') {
            std::cout << "Ошибка: неверный символ в дате! Используйте только цифры и пробелы.\n";
            return false;
        }
    }
    if (!has_digits) {
        std::cout << "Ошибка: неверный формат даты!\n";
        return false;
    }
    std::vector<std::string> numbers;
    std::string current_number;
    for (char c : date_str) {
        if (c == ' ') {
            if (!current_number.empty()) {
                numbers.push_back(current_number);
                current_number.clear();
            }
        } else {
            current_number += c;
        }
    }
    if (!current_number.empty()) {
        numbers.push_back(current_number);
    }
    if (numbers.size() != 3) {
        std::cout << "Ошибка: неверный формат даты! Нужно ровно три числа.\n";
        return false;
    }
    day = std::stoi(numbers[0]);
    month = std::stoi(numbers[1]);
    year = std::stoi(numbers[2]);
    return IsValidDate(day, month, year);
}

/* функция ParseDateStandard() разбивает даты в форматах (дд.мм.гггг и дд/мм/гггг)
алгоритм:   1. заменяем "." и "/" на пробел
            2. разбиваем строку на чила
            3. проверяем числа на корректность написания
            4. возвращаем день недели или -1 при ошибке */
int ParseDateStandard(const std::string& date_str) {
    if (date_str.empty()) {
        std::cout << "Ошибка: неверный формат даты!\n";
        return -1;
    }
    for (char c : date_str) {
        if (!(std::isdigit(c)) && c != '.' && c != '/') {
            std::cout << "Ошибка: неверный формат даты!\n";
            return -1;
        }
    }
    std::string temp_var = date_str;
    for (char& c : temp_var) {
        if (c == '.' || c == '/') {
            c = ' ';
        }
    }
    std::vector<int> numbers;
    std::string current_number;
    for (char c : temp_var) {
        if (c == ' ') {
            if (!current_number.empty()) {
                if (!IsNumberStr(current_number)) {
                    std::cout << "Ошибка: неверный формат числа!\n";
                    return -1;
                }
                numbers.push_back(std::stoi(current_number));
                current_number.clear();
            }
        } else if (std::isdigit(c)) {
            current_number += c;
        }
    }
    if (!current_number.empty()) {
        if (!IsNumberStr(current_number)) {
            std::cout << "Ошибка: неверный формат числа!\n";
            return -1;
        }
        numbers.push_back(std::stoi(current_number));
    } 
    if (numbers.size() != 3) {
        std::cout << "Ошибка: неверный формат даты!\n";
        return -1;
    } 
    int day = numbers[0], month = numbers[1], year = numbers[2];
    if (!IsValidDate(day, month, year)) {
        return -1;
    }
    return CalculateDayOfWeekZeller(day, month, year);
}

void ProcessSpacedDate() {
    std::cout << "📅 Введите дату - (ДД ММ ГГГГ): ";

    while (true) {
        int day, month, year;
        std::string date_str;
        std::getline(std::cin, date_str);
        if (FormWithSpaces(date_str, day, month, year)) {
            int day_of_week = CalculateDayOfWeekZeller(day, month, year);
            std::cout << "\n" << FormatWithZero(day) << "." 
                              << FormatWithZero(month) << "."  
                              << FormatWithZero(year) << " - ";
            PrintDayOfWeek(day_of_week);
            break;
        }
        std::cout << "Неверный формат! Попробуйте ещё раз (ДД ММ ГГГГ): ";
    }
}

void ProcessStandardDate() {
    std::cout << "📅 Введите дату - (ДД.ММ.ГГГГ или ДД/ММ/ГГГГ): ";

    while (true) {
        std::string date_str;
        std::getline(std::cin, date_str);
        int day_of_week = ParseDateStandard(date_str);
        if (day_of_week != -1) {
            std::cout << "\n" << date_str << " - ";
            PrintDayOfWeek(day_of_week);
            break;
        }
        std::cout << "Неверный формат! Попробуйте ещё раз (ДД.ММ.ГГГГ или ДД/ММ/ГГГГ): ";
    }
}

int CalculateDayOfWeek() {
    std::cout << "\n--РАССЧИТАТЬ ДЕНЬ НЕДЕЛИ--\n";

    while (true) {
        int choice = SelectDateFormat();
        switch (choice) {
            case 1: {
                ProcessSpacedDate();
                break;
            } case 2: {
                ProcessStandardDate();
                break;
            } case 0: {
                std::cout << "Возврат в главное меню...\n";
                return 0;
            } default: {
                std::cout << "Ошибка: неверный выбор формата!\n";
                continue;
            }
        }
        std::cout << "\nХотите рассчитать ещё один день? (0 - нет, 1 - да): ";
        std::string continue_choice;
        std::getline(std::cin, continue_choice);
        if (continue_choice.empty() || continue_choice[0] != '1') {
            std::cout << "Возврат в главное меню...\n";
            break;
        }
        std::cout << "\n";
    }
    return 0;
}

bool CheckingTime(const std::string& time_str, int& hour, int& minutes) {
    if (time_str.size() != 5 || time_str[2] != ':') {
        std::cout << "Ошибка: неверный формат времени!\n";
        return false;
    }
    for (int i = 0; i < 5; i++) {
        if (i == 2) {
            continue;
        }
        if (!std::isdigit(time_str[i])) {
            std::cout << "Ошибка: неверный символ во времени!\n";
            return false;
        }
    }
    hour = (time_str[0] - '0') * 10 + (time_str[1] - '0');
    minutes = (time_str[3] - '0') * 10 + (time_str[4] - '0');
    if (hour < 0 || hour > 23) {
        std::cout << "Ошибка: некорректно введено время (часы)!\n";
        return false;
    }
    if (minutes < 0 || minutes > 59) {
        std::cout << "Ошибка: некорректно введено время (минуты)!\n";
        return false;
    }
    return true;
}

int AddTaskMenu(std::vector<RecordStorage>& records) {
    std::cout << "--ДОБАВИТЬ НОВУЮ ЗАДАЧУ--\n";

    RecordStorage record;
    InputDate(record.date.day, record.date.month, record.date.year, "📅 Укажите дату выполнения задачи (ДД ММ ГГГГ): ");
    InputTime(record.hour, record.minutes, "🕔 Укажите время выполнения задачи (ЧЧ:ММ): ");

    std::cout << "📄 Укажите описание задачи: ";
    std::getline(std::cin, record.task);

    records.push_back(record);
    std::cout << "Задача успешно добавлена!\n";
    return 0;
}

int FindTasksByDate(const std::vector<RecordStorage>& records, int day, int month, int year) {
    int count_records = 0;
    std::cout << "\n--------------------------------------\n";
    std::cout << "Задачи на " << day << "." << month << "." << year << ":\n";
    std::cout << "--------------------------------------\n";
    for (int i = 0; i < records.size(); i++) {
        if (records[i].date.day == day && records[i].date.month == month && records[i].date.year == year) { 
            count_records++;
            std::cout << "-(" << count_records << ")- " 
                      << FormatWithZero(records[i].hour) << ":" << FormatWithZero(records[i].minutes) 
                      << " | " << records[i].task << "\n";
        }
    }
    if (count_records == 0) {
        std::cout << "На этот день задач нет.\n";
        std::cout << "--------------------------------------\nВозврат в главное меню...\n";
    } else {
        std::cout << "--------------------------------------\nВозврат в главное меню...\n";
    }
    return count_records;
}

int FindTasksByDateMenu(std::vector<RecordStorage>& records) {
    std::cout << "\n--ПОИСК ЗАДАЧ ПО ДАТЕ--\n";
    if (records.empty()) {
        std::cout << "Список задач пуст!\nВозврат в главное меню...\n";
        return -1;
    }
    int day, month, year;
    InputDate(day, month, year, "📅 Для просмотра задач введите дату (ДД ММ ГГГГ): ");
    return FindTasksByDate(records, day, month, year);
}

void PrintAllTasks(const std::vector<RecordStorage>& records) {
    if (records.empty()) {
        std::cout << "\n--------------------------------------\n";
        std::cout << "Задач нет.\n";
        std::cout << "--------------------------------------\n\n";
        return;
    }
    std::cout << "\n--------------------------------------\n";
    std::cout << "Все задачи: \n";
    for (int i = 0; i < records.size(); i++) {
        std::cout << "-(" << i + 1 << ")- (" 
                  << FormatWithZero(records[i].date.day) << "." << FormatWithZero(records[i].date.month) << "." << FormatWithZero(records[i].date.year) 
                  << " " << FormatWithZero(records[i].hour) << ":" << FormatWithZero(records[i].minutes) 
                  << ") | " << records[i].task << "\n";
    }
    std::cout << "--------------------------------------\n\n";
}

int ChangeData() {
    std::string choice;

    while (true) {
        std::cout << "⁉️  Что вы хотите изменить? ⁉️\n";
        std::cout << "1. Дату задачи;\n";
        std::cout << "2. Время задачи;\n";
        std::cout << "3. Описание задачи (текст);\n";
        std::cout << "4. Всё сразу\n";
        std::cout << "0. Ничего (отмена).\n";
        std::cout << "Выберите (0 - 4): ";
        std::getline(std::cin, choice);

        if (choice.empty()) {
            std::cout << "Ошибка: пустой ввод!\n";
            continue;
        } if (choice.length() != 1) {
            std::cout << "Ошибка: введите ровно одну цифру!\n";
            continue;
        }
        char c = choice[0];
        if (c >= '0' && c <= '4') {
            return c - '0';
        } else {
            std::cout << "Ошибка: введите цифру от 0 до 4!\n";
        }
    }
}

void EditTaskDate(RecordStorage& records) {
    InputDate(records.date.day, records.date.month, records.date.year, "📅 Введите новую дату задачи (ДД ММ ГГГГ): ");
}

void EditTaskText(RecordStorage& records) {
    std::cout << "Введите новый текст задачи: ";
    std::getline(std::cin, records.task);
}

void EditTaskTime(RecordStorage& records) {
    InputTime(records.hour, records.minutes, "🕔 Введите новое время для выполнения задачи (ЧЧ:ММ): ");
}

void EditTaskMenu(std::vector<RecordStorage>& records) {
    std::cout << "\n--РЕДАКТИРОВАТЬ ЗАДАЧУ--\n";

    if (records.empty()) {
        std::cout << "Список задач пуст!\nВозврат в главное меню...\n";
        return;
    }
    PrintAllTasks(records);

    int day, month, year;
    std::string date_str;
    std::cout << "📅 Введите дату для редактирования задачи (ДД ММ ГГГГ): ";

    while (true) {
        std::getline(std::cin, date_str);
        if (FormWithSpaces(date_str, day, month, year)) {
            break;
        }
        std::cout << "Ошибка: неверный формат! Попробуйте ещё раз (ДД ММ ГГГГ): ";
    }
    std::vector<int> indices;
    for (int i = 0; i < records.size(); i++) {
        if (records[i].date.day == day && records[i].date.month == month && records[i].date.year == year) {
            indices.push_back(i);
        }
    }
    if (indices.empty()) {
        std::cout << "Задач на " << FormatWithZero(day) << "." << FormatWithZero(month) << "." << FormatWithZero(year) << " не найдено.\nВозврат в главное меню...\n";
        return;
    }
    std::cout << "\n--------------------------------------\n";
    std::cout << "Задачи на " << FormatWithZero(day) << "." << FormatWithZero(month) << "." << FormatWithZero(year) << ":";
    std::cout << "\n--------------------------------------\n";
    for (int i = 0; i < indices.size(); i++) {
        std::cout << "-(" << i + 1 << ")- (" 
                  << FormatWithZero(records[indices[i]].hour) << ":" << FormatWithZero(records[indices[i]].minutes) << ") | " 
                  << records[indices[i]].task << "\n";
    }
    std::cout << "--------------------------------------\n";

    int choice = InputNumber("Выберите номер задачи для изменения (0 - отмена): ", 0, indices.size());
    int real_index = indices[choice - 1];
    if (choice == 0) {
        std::cout << "Редактирование отменено.\nВозврат в главное меню...\n";
        return;
    }

    std::cout << "\n💭 Текущие данные задачи: 💭\n";
    std::cout << "📅 Дата: " << FormatWithZero(records[real_index].date.day) << "." 
                              << FormatWithZero(records[real_index].date.month) << "." 
                              << FormatWithZero(records[real_index].date.year) << "\n";

    std::cout << "🕔 Время: " << FormatWithZero(records[real_index].hour) << ":" << FormatWithZero(records[real_index].minutes) << "\n";
    std::cout << "📄 Задача: " << records[real_index].task << "\n\n";
    
    int choice_menu;
    choice_menu = ChangeData();
    switch (choice_menu) {
        case 1: {
            EditTaskDate(records[real_index]);
            std::cout << "\nДанные обновлены!\nВозврат в главное меню...\n";
            break;
        } case 2: {
            EditTaskTime(records[real_index]);
            std::cout << "\nДанные обновлены!\nВозврат в главное меню...\n";
            break;
        } case 3: {
            EditTaskText(records[real_index]);
            std::cout << "\nДанные обновлены!\nВозврат в главное меню...\n";
            break;
        } case 4: {
            EditTaskDate(records[real_index]);
            EditTaskTime(records[real_index]);
            EditTaskText(records[real_index]);
            std::cout << "\nДанные обновлены!\nВозврат в главное меню...\n";
            break;
        } case 0: {
            std::cout << "Изменение отменено.\nВозврат в главное меню...\n";
            return;
        } default: {
            std::cout << "Неверный выбор!\n";
            return;
        }
    }
}

void DeleteTaskMenu(std::vector<RecordStorage>& records) {
    std::cout << "\n--УДАЛИТЬ ЗАДАЧУ--\n";

    if (records.empty()) {
        std::cout << "Список задач пуст!\nВозврат в главное меню...\n";
        return;
    }
    PrintAllTasks(records);

    int index = InputNumber("Введите номер задачи, которую хотите удалить: ", 1, records.size());
    records.erase(records.begin() + (index - 1));
    std::cout << "Удаление прошло успешно!\n";

    PrintAllTasks(records);
}

void SaveTasksToFile(std::vector<RecordStorage>& records) {
    std::cout << "--СОХРАНИТЬ ЗАДАЧИ В ФАЙЛ--\n"; 

    std::string file_name;
    std::cout << "📁 Введите имя файла (по умолчанию: FinalListOfEntries.txt): ";
    std::getline(std::cin, file_name);
    if (file_name.empty()) { file_name = "FinalListOfEntries.txt"; }
    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cout << "Ошибка: не получилось открыть файл - " << file_name << " !\nВозврат в главное меню...\n";
        return;
    }
    for (int i = 0; i < records.size(); i++) {
        file << FormatWithZero(records[i].date.day) << "." << FormatWithZero(records[i].date.month) << "." << FormatWithZero(records[i].date.year) << " " 
             << FormatWithZero(records[i].hour) << ":" << FormatWithZero(records[i].minutes) << " " 
             << records[i].task << "\n";
    }
    file.close();
    std::cout << "Задачи успешно сохранены в файл " << file_name << "!\nВозврат в главное меню...\n";
}

/* функция LoadTasksFromFile() загружает задачи из файла.txt 
формат строки в файле - дд.мм.гггг чч:мм задача
алгоритм:   1. читаем файл построчно
            2. для каждой строки: разбиваем дату (до first space), разбиваем время (между first and second space), остальное > описание задачи
            3. проверяем числа на корректность написания
            4. добавляем в вектор задач
в случае ошибок формата - пропускаем строку с предупреждением о некорректности */
void LoadTasksFromFile(std::vector<RecordStorage>& records) {
    std::cout << "--ЗАГРУЗИТЬ ЗАДАЧИ ИЗ ФАЙЛА--\n"; 

    std::string file_name;
    std::cout << "📁 Введите имя файла (по умолчанию: OriginalListOfEntries.txt): ";
    std::getline(std::cin, file_name);
    if (file_name.empty()) { file_name = "OriginalListOfEntries.txt"; }
    std::ifstream file(file_name, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Ошибка: не получилось открыть файл - " << file_name << " !\nВозврат в главное меню...\n";
        return;
    }

    // records.clear();

    std::string line;
    bool has_error = false;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        RecordStorage record;
        int space1 = line.find(' ');
        if (space1 == std::string::npos) {
            has_error = true;
            continue;
        }
        std::string date_part_str = line.substr(0, space1);
        int dot1 = date_part_str.find('.'), dot2 = date_part_str.find('.', dot1 + 1);
        if (dot1 == std::string::npos || dot2 == std::string::npos) {
            has_error = true;
            continue;
        }

        record.date.day = std::stoi(date_part_str.substr(0, dot1));
        record.date.month = std::stoi(date_part_str.substr(dot1 + 1, dot2 - dot1 - 1));
        record.date.year = std::stoi(date_part_str.substr(dot2 + 1));

        int space2 = line.find(' ', space1 + 1);
        if (space2 == std::string::npos) {
            has_error = true;
            continue;
        }

        std::string time_part_str = line.substr(space1 + 1, space2 - space1 - 1);
        int colon = time_part_str.find(':');

        if (colon == std::string::npos) {
            has_error = true;
            continue;
        }

        record.hour = std::stoi(time_part_str.substr(0, colon));
        record.minutes = std::stoi(time_part_str.substr(colon + 1));
        record.task = line.substr(space2 + 1);

        if (IsValidDate(record.date.day, record.date.month, record.date.year) && record.hour >= 0 && record.hour < 24 && record.minutes >= 0 && record.minutes < 60) {
            records.push_back(record);
        } else {
            has_error = true;
        }
    }
    file.close();

    if (records.empty()) {
        std::cout << "Файл пуст или не содержит корректных задач.\n";
        if (has_error) {
            std::cout << "Некоторые задачи пропущены из-за некорректного формата!\n";
        }
    } else {
        std::cout << "Задачи успешно загружены из файла!\n";
        if (has_error) {
            std::cout << "Некоторые задачи пропущены из-за некорректного формата!\n";
        }
    }
    std::cout << "Возврат в главное меню...\n";
}

/* функция SelectionSort() сортирует (методом простого выбора) задачи по дате и времени
алгоритм:   1. в цикле проходим по всем элементам
            2. для каждой позиции ищем мин. элемент в оставшейся части
            3. меняем местами текущий элемент с найденным мин.
сложность: О(n^2) для малого кол-ва задач сойдёт */
void SelectionSort(std::vector<RecordStorage>& records) {
    int size = records.size();
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (CompareTasksByDate(records[j], records[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(records[i], records[min_index]);
        }
    }
}

/* функция CompareTasksByDate() сравнивает данные двух задач (год -> месяц -> день -> часы -> минуты) для сортировки
возвращает:     1, если task1 > task2
                -1, если task1 < task2
                0, если task1 == task2 */
int CompareTasksByDate(const RecordStorage& task1, const RecordStorage& task2) {
    if (task1.date.year != task2.date.year) {
        return (task1.date.year < task2.date.year) ? -1 : 1;
    } if (task1.date.month != task2.date.month) {
        return (task1.date.month < task2.date.month) ? -1 : 1;
    } if (task1.date.day != task2.date.day) {
        return (task1.date.day < task2.date.day) ? -1 : 1;
    } if (task1.hour != task2.hour) {
        return (task1.hour < task2.hour) ? -1 : 1;
    } if (task1.minutes != task2.minutes) {
        return (task1.minutes < task2.minutes) ? -1 : 1;
    }
    return 0;
}

int SortTasksMenu(std::vector<RecordStorage>& records) {
    std::cout << "\n--СОРТИРОВКА ЗАДАЧ ПО ДАТЕ--\n";

    if (records.empty()) {
        std::cout << "Нет задач для сортировки!\nВозврат в главное меню...\n";
        return 0;
    }

    std::cout << "\nЗадачи до сортировки: \n";
    PrintAllTasks(records);

    SelectionSort(records);

    std::cout << "\nЗадачи после сортировки: \n";
    PrintAllTasks(records);

    std::cout << "Сортировка прошла успешно!\nВозврат в главное меню...\n";
    return 0;
}