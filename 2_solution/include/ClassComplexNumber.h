#pragma once

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Класс "Комплексное число"
 */
class ComplexNumber
{
private:
    /**
     * @param real - действительная часть
     */
    double real;

    /**
     * @param imag - мнимая часть
     */
    double imag;

public:
    /**
     * @brief Базовый конструктор класса
     * @param real - действительная часть (по-умолчанию 0)
     * @param imag - мнимая часть (по-умолчанию 0)
     */
    ComplexNumber(const double real = 0.0, const double imag = 0.0);

    /**
     * @brief Получает действительную часть
     * @return Действительная часть
     */
    double getReal() const;

    /**
     * @brief Получает мнимую часть
     * @return Мнимая часть
     */
    double getImag() const;

    /**
     * @brief Оператор сложения двух комплексных чисел
     */
    ComplexNumber operator + (const ComplexNumber& other) const;

    /**
     * @brief Оператор сложения комплексного и вещественного числа
     */
    ComplexNumber operator + (const double value) const;

    /**
     * @brief Оператор вычитания двух комплексных чисел
     */
    ComplexNumber operator - (const ComplexNumber& other) const;

    /**
     * @brief Оператор умножения двух комплексных чисел
     */
    ComplexNumber operator * (const ComplexNumber& other) const;

    /**
     * @brief Оператор деления двух комплексных чисел
     */
    ComplexNumber operator / (const ComplexNumber& other) const;

    /**
     * @brief Оператор проверки на равенство
     */
    bool operator == (const ComplexNumber& other) const;

    /**
     * @brief Оператор проверки на неравенство
     */
    bool operator != (const ComplexNumber& other) const;

    /**
     * @brief Метод нахождения комплексно-сопряженного числа
     * @return Комплексно-сопряженное число
     */
    ComplexNumber getConjugate() const;

    /**
     * @brief Представление в алгебраической форме
     * @return Строка вида a + bi
     */
    string toAlgebraicString() const;

    /**
     * @brief Представление в тригонометрической форме
     * @return Строка вида r(cos(phi) + i*sin(phi))
     */
    string toTrigonometricString() const;

    /**
     * @brief Представление в экспоненциальной форме
     * @return Строка вида r * e^(i*phi)
     */
    string toExponentialString() const;

    /**
     * @brief Оператор сложения вещественного и комплексного числа
     */
    friend ComplexNumber operator + (const double value, const ComplexNumber& c);

    /**
     * @brief Оператор вывода для комплексного числа
     */
    friend ostream& operator << (ostream& os, const ComplexNumber& c);

    /**
     * @brief Оператор ввода для комплексного числа
     */
    friend istream& operator >> (istream& is, ComplexNumber& c);
};
