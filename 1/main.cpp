#include "Triangle.h"

/**
 * @brief Считывает значения введённые с клавиатуры, преобразуя их в "точку"
 * @return Точку, с переданными ей значениями
 */
const Point getPoint(void);

/**
 * @brief Точка входа в программу
 * @return Возвращает ноль, если программа выполнена корректно, иначе единицу
 */
int main(void)
{
    system("chcp 1251");
    system("CLS");

    cout << "Внимание! Точка H ищется для высоты AH, опущенной из ПЕРВОЙ точки (A)." << endl;
    cout << "Введите координату первой точки (A) в формате (x,y): ";
    Point A = getPoint();
    cout << "Введите координату второй точки (B) в формате (x,y): ";
    Point B = getPoint();
    cout << "Введите координату третьей точки (C) в формате (x,y): ";
    Point C = getPoint();

    Triangle Tr(A, B, C);
    Point H = Tr.getAltitudePointH();

    cout << endl << endl;
    cout << "Координаты точки H высоты AH: (" << H.getX() << ", " << H.getY() << ")" << endl;
    cout << "Площадь треугольника: " << Tr.getArea() << endl;

    return 0;
}

const Point getPoint(void)
{
    double x = 0;
    double y = 0;
    cin >> x >> y;
    if (cin.fail())
    {
        cout << "Ошибка ввода!";
        exit(1);
    }
    Point A(x, y);
    return A;
}
