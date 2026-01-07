#include <string>
#include <vector>

bool InputDate(int& day, int& month, int& year, const std::string& prompt = "Введите дату (ДД ММ ГГГГ): ");
bool InputTime(int& hour, int& minute, const std::string& prompt = "Введите время (ЧЧ:ММ): ");
int InputNumber(const std::string& prompt, int min_value, int max_value);

std::string FormatWithZero(int number);

int CreatingACalendar(int month, int year);
int PrintMonthCalendar();

bool IsNumberStr(const std::string& str);

bool CheckingLeapYear(int year);
bool IsValidDate(int day, int month, int year);
bool CheckingYearMonth(const std::string& date, int& year, int& month);
bool CheckingTime(const std::string& time_str, int& hour, int& minutes);
int GetDaysInMonth(int month, int year);
void PrintDayOfWeek(int day_of_week);

int CalculateDayOfWeekZeller(int day, int month, int year);

bool FormWithSpaces(const std::string& date_str, int& day, int& month, int& year);
int ParseDateStandard(const std::string& date_str);

int SelectDateFormat();
void ProcessSpacedDate();
void ProcessStandardDate();
int CalculateDayOfWeek();

struct DateStorage {
    int day;
    int month;
    int year;
};

struct RecordStorage {
    DateStorage date;
    int hour;
    int minutes;
    std::string task;
};

int AddTaskMenu(std::vector<RecordStorage>& records);

int FindTasksByDate(const std::vector<RecordStorage>& records, int day, int month, int year);
void PrintAllTasks(const std::vector<RecordStorage>& records);
int FindTasksByDateMenu(std::vector<RecordStorage>& records);

void EditTaskDate(RecordStorage& records);
void EditTaskText(RecordStorage& records);
void EditTaskTime(RecordStorage& records);
void EditTaskMenu(std::vector<RecordStorage>& records);
void DeleteTaskMenu(std::vector<RecordStorage>& records);

void SaveTasksToFile(std::vector<RecordStorage>& records);
void LoadTasksFromFile(std::vector<RecordStorage>& records);

void SelectionSort(std::vector<RecordStorage>& records);
int CompareTasksByDate(const RecordStorage& task1, const RecordStorage& task2);
int SortTasksMenu(std::vector<RecordStorage>& records);