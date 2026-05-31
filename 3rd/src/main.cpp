#include "../include/ClassCircularList.h"
#include <string>

/**
 * @brief Нумерация объектов выбора
 */
enum MyEnum
{
    STR = 1,
    CHR,
    DBL,
    INT,
    BOOL
};

/**
 * @brief Считывает число типа int введённое с клавиатуры
 * @return Число типа int
 */
int get_choice();

/**
 * @brief Выводит ошибку и завершает работу программы
 * @param text - текст, выводимый на экран
 */
void ERROR(const string text);

/**
 * @brief Область работы со списком
 * @param text - тип данных, участвуюший в работе списка
 */
template <typename Type>
void runList(const string text);

/**
 * @brief Считывает элемент типа type введённое с клавиатуры
 * @return Элемент типа type
 */
template <typename Type>
Type get_element();

/**
 * @brief Точка входа в программу
 * @return Если программа выполнена корректно - 0, иначе 1
 */
int main()
{
    system("chcp 1251");
    system("CLS");

    cout << "Выберите тип данных хранящихся в списке: " << endl <<
    STR << " - слова" << endl <<
    CHR << " - буквы" << endl <<
    DBL << " - вещественные числа" << endl <<
    INT << " - целые числа" << endl <<
    BOOL << " - булевые числа [0,1]" << endl;
    int choice = get_choice();

    system("CLS");

    switch (choice)
    {
        case STR:
            runList<string>("string");
            break;
        case CHR:
            runList<char>("char");
            break;
        case DBL:
            runList<double>("double");
            break;
        case INT:
            runList<int>("int");
            break;
        case BOOL:
            runList<bool>("bool");
            break;
        default:
            ERROR("Ошибка выбора");
    }

    return 0;
}

int get_choice()
{
    int number = 0;
    cin >> number;
    if (cin.fail())
    {
        ERROR("Ошибка ввода");
    }
    return number;
}

void ERROR(const string text)
{
    cerr << text;
    exit(1);
}

template <typename Type>
void runList(const string text)
{
    CircularList<Type> First;
    cin >> First;
    system("CLS");

    cout << "Исходный список: " << First;
    First.printSize(cout);

    cout << endl << "Введите элемент (c типом " << text << "), который будет добавлен в список : ";
    Type element = get_element<Type>();
    First.insert(element);
    cout << "Список после вставки элемента: " << First;
    First.printSize(cout);

    cout << endl << "Введите элемент для поиска: ";
    Type search_element = get_element<Type>();
    int index = First.search(search_element);
    if (index != -1)
        cout << "Элемент найден по индексу (от 0): " << index << endl;
    else
        cout << "Элемент не найден." << endl;

    if (index != -1)
    {
        cout << endl << "Введите новое значение для найденного элемента: ";
        Type new_element = get_element<Type>();
        First.modify(search_element, new_element);
        cout << "Список после модификации: " << First;
    }

    cout << endl << "Введите элемент для удаления по значению: ";
    Type remove_element = get_element<Type>();
    First.remove(remove_element);
    cout << "Список после удаления элемента: " << First;
    First.printSize(cout);
}

template <typename Type>
Type get_element()
{
    Type element{};
    cin >> element;
    if (cin.fail())
    {
        ERROR("Ошибка ввода");
    }
    return element;
}
