#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <cctype>
#include <conio.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cmath>

#define PI 3.14159265

using namespace std;
HANDLE handleConsole;

enum ConsoleColor
{
    Blue = 1,
    Green = 2,
    Red = 4,
    Yellow = 14,
    White = 15
};

string GetLine() {
    string line;
    getline(cin, line);
    cin.clear();
    return line;
}

class MyInput {

public:

    double InputData(string text) {

        string xStr = "";
        double x = 0, result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            try {
                result = stod(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!isNumber) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - не число!" << endl << endl;
            }
            else if (result <= 0) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно быть больше нуля!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max) {

        double result;

        while (true) {
            result = InputData(text);

            if (result != (int) result) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно быть целым!" << endl << endl;
            }
            else if (result < min || result > max) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно лежать в промежутке [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    

};

class MyRandom {

public:
    double MIN_RANDOM = 10, MAX_RANDOM = 1000;

    bool isRandomData() {
        cout << "Сгенерировать данные случайным образом [y/n]?" << endl;

        string answer = GetLine();

        transform(answer.begin(), answer.end(), answer.begin(), tolower);

        return answer == "y" || answer == "";
    }

    double GetRandom(int min, int max) {
        return rand() % (max - min) - min;
    }

};

class Task6 {

private:
    bool IsExistTriangle(double a, double b, double c) {

        bool res1 = a + b > c;
        bool res2 = a + c > b;
        bool res3 = b + c > a;

        return res1 && res2 && res3;
   }

    bool IsRectangularTriangle(double a, double b, double c) {

        a = a * a;
        b = b * b;
        c = c * c;

        if (a + b == c)
            return true;

        if (a + c == b)
            return true;

        if (b + c == a)
            return true;

        return false;
    }

    double RadianToDegree(double val) {
        return (val * 180) / PI;
    }

    double GetCorner(double oppoziteSide, double side1, double side2) {
        double cosOppozite = (pow(side1, 2) + pow(side2, 2) - pow(oppoziteSide, 2)) / (2 * side1 * side2);
        return RadianToDegree(acos(cosOppozite));
    }

    bool IsAcuteAngledTriangle(double a, double b, double c) {

        double cornerA = GetCorner(a, b, c);
        double cornerB = GetCorner(b, a, c);
        double cornerC = GetCorner(c, a, b);

        return cornerA < 90 && cornerB < 90 && cornerC < 90;
    }

    bool IsObtuseTriangle(double a, double b, double c) {

        double cornerA = GetCorner(a, b, c);
        double cornerB = GetCorner(b, a, c);
        double cornerC = GetCorner(c, a, b);

        return cornerA > 90 || cornerB > 90 || cornerC > 90;
    }

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << endl << "Определить, может ли быть построен треугольник по введенным длинам сторон." << endl;
        cout << "Если треугольник можно построить, то определить его тип (прямоугольный, тупоугольный или остроугольный)" << endl << endl;

        double a, b, c;

        MyRandom myRandom = *new MyRandom();

        if (myRandom.isRandomData()) {
            a = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
            b = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
            c = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
        }
        else {
            MyInput myInput = *new MyInput();

            a = myInput.InputData("Введите сторону треугольника (а): ");
            b = myInput.InputData("Введите сторону треугольника (b): ");
            c = myInput.InputData("Введите сторону треугольника (c): ");

        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << endl << "Дан треугольник со сторонами:" << endl;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl << endl;

        if (IsExistTriangle(a, b, c)) {
            SetConsoleTextAttribute(handleConsole, Green);
            cout << "Данный треугольник существует:" << endl << endl;
            SetConsoleTextAttribute(handleConsole, White);

            string view;

            if (IsRectangularTriangle(a, b, c))
                view = "прямоугольный";
            else if(IsAcuteAngledTriangle(a, b, c))
                view = "остроугольный";
            else if(IsObtuseTriangle(a, b, c))
                view = "тупоугольный";
            else {
                view = "неизвестен";
                SetConsoleTextAttribute(handleConsole, Red);
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "Вид: " << view << endl << endl;
            SetConsoleTextAttribute(handleConsole, White);
             
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "Данный треугольник не существует!" << endl << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }


    }

};

class Task16 {

private:
    string GetTimeYear(int num) {

        if (num >= 3 && num <= 5)
            return "весна";

        if (num >= 6 && num <= 8)
            return "лето";

        if (num >= 9 && num <= 11)
            return "осень";
        
        if (num == 12 || num == 1 || num == 2)
            return "зима";
        
        SetConsoleTextAttribute(handleConsole, Red);
        return "неизвестно!";
    }

public:
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        MyInput myInput = *new MyInput();
      
        SetConsoleTextAttribute(handleConsole, White);
        cout << "\nПо введенному номеру месяца определить время года" << endl;
           
        int select = myInput.InputIntData("Введите номер месяца: ", 1, 12);

        SetConsoleTextAttribute(handleConsole, Green);
        cout << "Время года: " << GetTimeYear(select) << endl;

    }
};

class Task36 {
private:
    double Min(double a, double b) {
        if (a < b) return a;
        if (a > b) return b;

        return a;
    }

    double Max(double a, double b) {
        if (a < b) return b;
        if (a > b) return a;

        return a;
    }

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "\nВычислить z = max(min(a, b), max(c, d))" << endl;

        double a, b, c, d;

        int MIN_RANDOM = -1000;
        int MAX_RANDOM = 1000;

        MyRandom myRandom = *new MyRandom();

        if (myRandom.isRandomData()) {
            a = myRandom.GetRandom(MIN_RANDOM, MAX_RANDOM);
            b = myRandom.GetRandom(MIN_RANDOM, MAX_RANDOM);
            c = myRandom.GetRandom(MIN_RANDOM, MAX_RANDOM);
            d = myRandom.GetRandom(MIN_RANDOM, MAX_RANDOM);
        }
        else {

            MyInput myInput = *new MyInput();
            a = myInput.InputData("Введите число a: ");
            b = myInput.InputData("Введите число b: ");
            c = myInput.InputData("Введите число c: ");
            d = myInput.InputData("Введите число d: ");
        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << endl << "Исходные данные:" << endl;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        cout << "d = " << d << endl << endl;

        SetConsoleTextAttribute(handleConsole, Green);

        double valMin = Min(a, b);
        cout << "min(a, b) = min(" << a << ", " << b << ") = " << valMin << endl;

        double valMax = Max(c, d);
        cout << "max(c, d) = min(" << c << ", " << d << ") = " << valMax << endl << endl;

        cout << "z = max(min(a, b), max(c, d))" << endl;
        cout << "z = max(" << valMin << ", " << valMax << ")" << endl;

        cout << "z = " << Max(valMin, valMax) << endl << endl;

    }

};

class Task46 {

private:
    double GetDeg(int h, int m, int s) {

        double sec = 0.5 / 60;

        cout << h << " * 30° + " << m << " * 0.5° + " << s << " * " << sec << "°" << endl;

        int hours = h * 30;
        double minutes = m * 0.5;
        double seconds = s * sec;

        cout << hours << "° + " << minutes << "° + " << seconds << "°" << endl;

        return hours + minutes + seconds;
    }

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "По введенному времени (часы, минуты, секунды)" << endl;
        cout << "определить угол (в градусах) между положением часовой стрелки" << endl;
        cout << "в начале суток и ее положением в указанное время." << endl << endl;

        int hour, minute, seconds;

        int MIN_RANDOM = -1000;
        int MAX_RANDOM = 1000;

        MyRandom myRandom = *new MyRandom();

        if (myRandom.isRandomData()) {
            hour = myRandom.GetRandom(0, 23);
            minute = myRandom.GetRandom(0, 59);
            seconds = myRandom.GetRandom(0, 59);
        }
        else {

            MyInput myInput = *new MyInput();
            hour = myInput.InputIntData("Часы: ", 0, 23);
            minute = myInput.InputIntData("Минуты: ", 0, 59);
            seconds = myInput.InputIntData("Секунды: ", 0, 59);
        }

        cout << endl << "1 час = 360 / 12 = 30°" << endl;
        cout << "1 минута = 30° / 60 = 0.5°" << endl;
        cout << "1 секунда = 0.5° / 60 ~ " << (0.5 / 60) << "°" << endl << endl;


        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "Исходные данные:" << endl;
        printf("%02d:%02d:%02d\n\n", hour, minute, seconds);


        SetConsoleTextAttribute(handleConsole, Green);
        cout << "Результат: " << GetDeg(hour, minute, seconds) << "°" << endl << endl;
    }
};

int main()
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");

    SetConsoleTextAttribute(handleConsole, White);

    cout << "Тема 2. Разветвляющиеся вычислительные процессы" << endl;
    cout << "Ларионов Никита Юрьевич. гр. 110з" << endl;

    bool isGo = true;
    string select;

    while (isGo)
    {
        SetConsoleTextAttribute(handleConsole, White);

        cout << "\nВведите номер задачи" << endl;
        cout << "6) Определить, может ли быть построен треугольник по введенным длинам сторон." << endl;
        cout << "Если треугольник можно построить, то определить его тип (прямоугольный, тупоугольный или остроугольный)" << endl << endl;

        cout << "16) По введенному номеру месяца определить время года" << endl << endl;

        cout << "36) Вычислить z = max(min(a, b), max(c, d))" << endl << endl;

        cout << "46) По введенному времени (часы, минуты, секунды)" << endl;
        cout << "определить угол (в градусах) между положением часовой стрелки" << endl;
        cout << "в начале суток и ее положением в указанное время." << endl << endl;


        cout << endl << "Для выхода введите \"0\": ";

        select = GetLine();

        if (select == "6") {
            Task6 task6 = *new Task6();
            task6.Init();
        }
        else if (select == "16") {
            Task16 task16 = *new Task16();
            task16.Init();
        }
        else if (select == "36") {
            Task36 task36 = *new Task36();
            task36.Init();
        }
        else if (select == "46") {
            Task46 task46 = *new Task46();
            task46.Init();
        }
        else if (select == "0") {
            isGo = false;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\nНекорректные данные!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }

    }
}

