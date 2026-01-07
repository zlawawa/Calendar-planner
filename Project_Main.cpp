#include <windows.h>
#include <iostream>
#include "Project_Module.h"
#include <limits>
#include <string>

int ShowMainMenu() {
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "     Календарь + Планировщик задач    \n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "📌           Главное меню           📌\n";
    std::cout << "📆 КАЛЕНДАРЬ:\n";
    std::cout << " 1. Показать календарь месяца;\n";
    std::cout << " 2. Рассчитать день недели;\n";
    std::cout << "📃 ЗАДАЧИ:\n";
    std::cout << " 3. Добавить задачу;\n";
    std::cout << " 4. Удалить задачу;\n";
    std::cout << " 5. Редактировать задачу;\n";
    std::cout << " 6. Найти задачу по дате;\n";
    std::cout << " 7. Сортировка задач по дате;\n";
    std::cout << "💾 ФАЙЛЫ:\n";
    std::cout << " 8. Сохранить задачи в файл;\n";
    std::cout << " 9. Загрузить задачи из файла;\n";
    std::cout << "🚪 ВЫХОД:\n";
    std::cout << " 0. Выйти из программы.\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Выберите действие (0 - 9): ";
    std::string choice;
    std::getline(std::cin, choice);

    if (choice.empty()) {
        return -1;
    }
    if (choice.length() == 1) {
        char c = choice[0];
        if (c >= '0' && c <= '9') {
            return c - '0';
        }
    }
    return -1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::vector<RecordStorage> tasks;
    int choice;
    do {
        choice = ShowMainMenu();
        if (choice == -1) {
            std::cout << "❌ Неверный ввод! Пожалуйста, введите цифру от 0 до 9.\n";
            std::cout << "Нажмите, пожалуйста, Enter для продолжения...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch(choice) {
            case 0: {
                std::cout << "Завершение работы...\n";
                std::cout << "Работа завершена.\n";
                break;
            } case 1: {
                PrintMonthCalendar();
                break;
            } case 2: {
                CalculateDayOfWeek();
                break;
            } case 3: {
                AddTaskMenu(tasks);
                break;
            } case 4: {
                DeleteTaskMenu(tasks);
                break;
            } case 5: {
                EditTaskMenu(tasks);
                break;
            } case 6: {
                FindTasksByDateMenu(tasks);
                break;
            } case 7: {
                SortTasksMenu(tasks);
                break;
            } case 8: {
                SaveTasksToFile(tasks);
                break;
            } case 9: {
                LoadTasksFromFile(tasks);
                break;
            } default: {
                std::cout << "Неверный выбор! Попробуйте ещё раз.\n";
                break;
            }
        }
    } while (choice != 0);
    return 0;
}