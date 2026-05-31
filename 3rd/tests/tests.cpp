#include <gtest/gtest.h>
#include "../include/ClassCircularList.h"

/**
 * @brief Тест конструкторов
 */
TEST(ClassCircularList, TestConstructors)
{
    CircularList<int> Zero;
    EXPECT_TRUE(Zero.isEmpty());
    EXPECT_EQ(Zero.printSize(), 0);

    CircularList<int> One{ 1, 2, 3 };
    EXPECT_EQ(One.printSize(), 3);
    EXPECT_EQ(One[0], 1);
    EXPECT_EQ(One[1], 2);
    EXPECT_EQ(One[2], 3);

    list<int> a = { 2, 3, 4 };
    CircularList<int> Two(a);
    EXPECT_EQ(Two.printSize(), 3);
    EXPECT_EQ(Two[0], 2);
    EXPECT_EQ(Two[1], 3);
    EXPECT_EQ(Two[2], 4);

    CircularList<int> Three(Two);
    EXPECT_EQ(Three.printSize(), 3);
    EXPECT_EQ(Three[0], 2);
    EXPECT_EQ(Three[1], 3);
    EXPECT_EQ(Three[2], 4);

    CircularList<int> Original{ 5, 10 };
    CircularList<int> Moved(move(Original));
    EXPECT_EQ(Original.printSize(), 0);
    EXPECT_TRUE(Original.isEmpty());
    EXPECT_EQ(Moved.printSize(), 2);
    EXPECT_EQ(Moved[0], 5);
    EXPECT_EQ(Moved[1], 10);
}

/**
 * @brief Тест оператора индекса
 */
TEST(ClassCircularList, Index_Operator)
{
    CircularList<int> One;
    EXPECT_EXIT(One[20], ::testing::ExitedWithCode(1), "Выход за границы списка");

    CircularList<int> Two{ 5, 7, 10, 9 };
    EXPECT_EQ(Two[2], 10);
}

/**
 * @brief Тест операторов сравнения
 */
TEST(ClassCircularList, EQ_Operators)
{
    CircularList<int> One{ 1, 2, 3, 4, 5 };
    CircularList<int> Two{ 1, 2, 3, 4, 5 };
    CircularList<int> Three{ 1, 2, 3, 4 };
    EXPECT_TRUE(One == Two);
    EXPECT_TRUE(One != Three);
    EXPECT_FALSE(One == Three);
}

/**
 * @brief Тест операторов присваивания
 */
TEST(ClassCircularList, Assign_Operators)
{
    CircularList<int> One;
    CircularList<int> Two{ 1, 2, 3 };
    One = Two;
    EXPECT_EQ(One.printSize(), 3);
    EXPECT_EQ(One[0], 1);
    EXPECT_EQ(One[1], 2);
    EXPECT_EQ(One[2], 3);
}

/**
 * @brief Тест функций вставки, удаления, поиска и модификации
 */
TEST(ClassCircularList, Functional)
{
    CircularList<int> First{ 1, 2, 10 };

    First.remove(2);
    EXPECT_EQ(First.printSize(), 2);
    EXPECT_EQ(First[0], 1);
    EXPECT_EQ(First[1], 10);

    First.insert(50);
    EXPECT_EQ(First.printSize(), 3);
    EXPECT_EQ(First[2], 50);

    EXPECT_EQ(First.search(10), 1);
    EXPECT_EQ(First.search(99), -1);

    First.modify(10, 20);
    EXPECT_EQ(First[1], 20);
}

/**
 * @brief Тест операторов ввода и вывода
 */
TEST(ClassCircularList, IO_Operators)
{
    system("chcp 1251");
    stringstream input("2 10 20");
    CircularList<int> One;
    input >> One;

    EXPECT_EQ(One.printSize(), 2);
    EXPECT_EQ(One[0], 10);
    EXPECT_EQ(One[1], 20);

    stringstream output;
    output << One;
    EXPECT_EQ(output.str(), "{10, 20}\n");
}
