#pragma once
#include <iostream>
#include <initializer_list>
#include <list>

using namespace std;

/**
 * @brief Класс Циклический двусвязный список
 */
template<typename Type>
class CircularList
{
private:
    /**
     * @brief Структура узла списка
     */
    struct Node
    {
        Type data;
        Node* next;
        Node* prev;
        Node(Type val) : data(val), next(nullptr), prev(nullptr) {}
    };

    /**
     * @param head - указатель на начало списка
     */
    Node* head;

    /**
     * @param count - количество элементов в списке
     */
    size_t count;

    /**
     * @brief Выводит ошибку и завершает работу программы
     * @param text - текст, выводимый на экран
     */
    void ERROR(const string text) const
    {
        cerr << text;
        exit(1);
    }

public:
    /**
     * @brief Конструктор класса по-умолчанию, задаёт пустой список
     */
    CircularList(void) : head(nullptr), count(0) {}

    /**
     * @brief Конструктор класса, задаёт список по заданному массиву данных
     * @tparam other - массив данных определённого типа
     */
    CircularList(initializer_list<Type> other) : head(nullptr), count(0)
    {
        for (const auto& value : other)
        {
            insert(value);
        }
    }

    /**
     * @brief Конструктор класса, задаёт список по переданному массиву данных std::list
     * @tparam other - массив данных определённого типа
     */
    CircularList(list<Type>& other) : head(nullptr), count(0)
    {
        for (const auto& value : other)
        {
            insert(value);
        }
    }

    /**
     * @brief Конструктор класса, задаёт список по переданному списку (копирование)
     * @tparam other - переданный список
     */
    CircularList(const CircularList& other) : head(nullptr), count(0)
    {
        if (other.head)
        {
            Node* current = other.head;
            for (size_t i = 0; i < other.count; i++)
            {
                insert(current->data);
                current = current->next;
            }
        }
    }

    /**
     * @brief Конструктор класса, задаёт список по ссылке на список (перемещение)
     * @tparam other - ссылка на переданный список
     */
    CircularList(CircularList&& other) : head(other.head), count(other.count)
    {
        other.head = nullptr;
        other.count = 0;
    }

    /**
     * @brief Добавление элемента в конец списка
     * @param object - объект добавляемый в список
     */
    void insert(const Type& object)
    {
        Node* newNode = new Node(object);
        if (!head)
        {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else
        {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        count++;
    }

    /**
     * @brief Удаление элемента из списка по значению
     * @param object - удаляемый объект
     */
    void remove(const Type& object)
    {
        if (!head)
        {
            cout << "Список пуст, удаление не выполнено" << endl;
            return;
        }

        Node* current = head;
        for (size_t i = 0; i < count; i++)
        {
            if (current->data == object)
            {
                if (count == 1)
                {
                    delete current;
                    head = nullptr;
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    if (current == head)
                    {
                        head = current->next;
                    }
                    delete current;
                }
                count--;
                return;
            }
            current = current->next;
        }
        cout << "Элемент не найден для удаления" << endl;
    }

    /**
     * @brief Поиск элемента по значению
     * @param object - искомый объект
     * @return Индекс элемента (от 0), или -1 если не найден
     */
    int search(const Type& object) const
    {
        if (!head) return -1;
        Node* current = head;
        for (size_t i = 0; i < count; i++)
        {
            if (current->data == object)
                return i;
            current = current->next;
        }
        return -1;
    }

    /**
     * @brief Модификация элемента по значению
     * @param old_object - старое значение
     * @param new_object - новое значение
     */
    void modify(const Type& old_object, const Type& new_object)
    {
        if (!head) return;
        Node* current = head;
        for (size_t i = 0; i < count; i++)
        {
            if (current->data == old_object)
            {
                current->data = new_object;
                return;
            }
            current = current->next;
        }
        cout << "Элемент для модификации не найден" << endl;
    }

    /**
     * @brief Проверка списка на пустоту
     * @return true если пуст, false если есть элементы
     */
    bool isEmpty() const
    {
        return count == 0;
    }

    /**
     * @brief Вывод размера списка (как число)
     * @return Число - размер списка
     */
    size_t printSize() const
    {
        return count;
    }

    /**
     * @brief Вывод размера списка (как текст)
     * @param os - поток вывода
     * @return поток вывода
     */
    ostream& printSize(ostream& os) const
    {
        if (count == 0)
        {
            os << "Список пуст!" << endl;
        }
        else
        {
            os << "Размер списка: " << count << endl;
        }

        return os;
    }

    /**
     * @brief Оператор присваивания списка (копирование)
     * @param other - другой список
     * @return Список
     */
    CircularList& operator = (const CircularList& other)
    {
        if (this != &other)
        {
            while (!isEmpty()) remove(head->data);

            if (other.head)
            {
                Node* current = other.head;
                for (size_t i = 0; i < other.count; i++)
                {
                    insert(current->data);
                    current = current->next;
                }
            }
        }
        return *this;
    }

    /**
     * @brief Оператор присваивания списка (перемещение)
     * @param other - ссылка на другой список
     * @return Список
     */
    CircularList& operator = (CircularList&& other)
    {
        if (this != &other)
        {
            while (!isEmpty()) remove(head->data);

            head = other.head;
            count = other.count;

            other.head = nullptr;
            other.count = 0;
        }
        return *this;
    }

    /**
     * @brief Оператор сравнения списков
     * @param other - другой список
     * @return true или false
     */
    bool operator == (const CircularList& other) const
    {
        if (count != other.count)
            return false;

        Node* current1 = head;
        Node* current2 = other.head;
        for (size_t i = 0; i < count; i++)
        {
            if (current1->data != current2->data)
                return false;
            current1 = current1->next;
            current2 = current2->next;
        }

        return true;
    }

    /**
     * @brief Оператор сравнения списков (неравенство)
     * @param other - другой список
     * @return true или false
     */
    bool operator != (const CircularList& other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Оператор, показывающий n-й элемент списка
     * @param index - индекс элемента, который будет показан
     * @return n-й элемент списка
     */
    Type& operator [] (const size_t index) const
    {
        if (index < count)
        {
            Node* current = head;
            for (size_t i = 0; i < index; i++)
            {
                current = current->next;
            }
            return current->data;
        }
        ERROR("Выход за границы списка");
    }

    /**
     * @brief Оператор вывода списка в поток вывода
     * @param os - поток вывода
     * @param other - список
     * @return Список, сериализованный в строку
     */
    friend ostream& operator << (ostream& os, const CircularList& other)
    {
        os << "{";
        if (other.head)
        {
            Node* current = other.head;
            for (size_t i = 0; i < other.count; i++)
            {
                os << current->data;
                if (i != other.count - 1)
                {
                    os << ", ";
                }
                current = current->next;
            }
        }
        os << "}" << endl;
        return os;
    }

    /**
     * @brief Оператор ввода элементов списка
     * @param is - поток ввода
     * @param list_obj - список
     */
    friend istream& operator>>(istream& is, CircularList& list_obj)
    {
        size_t elements_count = 0;
        cout << "Введите количество элементов в списке: ";
        is >> elements_count;

        if (is.fail() || elements_count < 0)
        {
            list_obj.ERROR("Ошибка ввода");
        }

        while (!list_obj.isEmpty()) list_obj.remove(list_obj.head->data);

        if (elements_count > 0)
        {
            for (size_t i = 0; i < elements_count; ++i)
            {
                Type val;
                cout << "Введите " << i + 1 << " элемент списка: ";
                is >> val;

                if (is.fail())
                {
                    list_obj.ERROR("Ошибка ввода");
                }
                list_obj.insert(val);
            }
        }

        return is;
    }

    /**
     * @brief Деструктор класса по-умолчанию
     */
    ~CircularList()
    {
        while (!isEmpty())
        {
            remove(head->data);
        }
    }
};
