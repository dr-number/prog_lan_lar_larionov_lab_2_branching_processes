#include <iostream>
#include <Windows.h>
#include <random>
#include <regex>

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

string RoundStr(float var, int after = 2) {

    string s = to_string(var);
    int size = s.size();

    string result = "";
    bool isAfter = false;
    int afterCount = 0;

    for (int i = 0; i < size; ++i) {

        if (afterCount == after)
            break;

        if (isAfter)
            ++afterCount;

        if (!isAfter && s[i] == ',')
            isAfter = true;

        result += s[i];

    }

    return result;
}

float Round(float var)
{
    // 37.66666 * 100 = 3766.66
    // 3766.66 + .5 = 3767.16 для значения округления

    // затем вводим тип int в значение 3767
    // затем делим на 100, поэтому значение преобразуется в 37,67

    float value = (int)(var * 100 + .5);
    return stod(RoundStr((float)value / 100));

}

class MyInput {

public:
    bool isDouble(string str) {
        return regex_match(str, regex("^[-]?[0-9]*?,?[0-9]*"));
    }

    bool isNum(string str) {
        return regex_match(str, regex("^[-]?[0-9]*"));
    }

    double InputData(string text, int min, int max, int defaultValue = -1) {

        string xStr = "";
        double result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            if (xStr == "" && defaultValue != -1)
                return defaultValue;


            try {
                result = stod(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!(isNumber && isDouble(xStr))) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - не число!" << endl << endl;
            }
            else if (result > max || result < min) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно лежать в промежутке [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max, int defaultValue = -1) {

        string xStr = "";
        double result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            if (xStr == "" && defaultValue != -1)
                return defaultValue;


            try {
                result = stod(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!(isNumber && isNum(xStr))) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - не число!" << endl << endl;
            }
            else if (result > max || result < min) {
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
    static const int MIN_RANDOM = 10, MAX_RANDOM = 1000;

    bool isRandomData() {
        cout << "Сгенерировать данные случайным образом [y/n]?" << endl;

        string answer = GetLine();

        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        return answer == "y" || answer == "";
    }

    double GetRandom(int min, int max) {

        random_device random_device; // Источник энтропии.
        mt19937 generator(random_device()); // Генератор случайных чисел.

        // (Здесь берется одно инициализирующее значение, можно брать больше)
        uniform_int_distribution<> distribution(min, max); // Равномерное распределение [min, max]

        return distribution(generator);

        //return rand() % (max - min) - min;
        //return rand() % max + min;
    }

};

class MyGeometry {
public:
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
};

class Task6 {

private:
    const int MIN = MyRandom::MIN_RANDOM;
    const int MAX = MyRandom::MAX_RANDOM;

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << endl << "Определить, может ли быть построен треугольник по введенным длинам сторон." << endl;
        cout << "Если треугольник можно построить, то определить его тип (прямоугольный, тупоугольный или остроугольный)" << endl << endl;

        double a, b, c;

        MyRandom myRandom = *new MyRandom();

        if (myRandom.isRandomData()) {
            a = myRandom.GetRandom(MIN, MAX);
            b = myRandom.GetRandom(MIN, MAX);
            c = myRandom.GetRandom(MIN, MAX);
        }
        else {
            MyInput myInput = *new MyInput();

            a = myInput.InputData("Введите сторону треугольника (а): ", MIN, MAX);
            b = myInput.InputData("Введите сторону треугольника (b): ", MIN, MAX);
            c = myInput.InputData("Введите сторону треугольника (c): ", MIN, MAX);

        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << endl << "Дан треугольник со сторонами:" << endl;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl << endl;

        MyGeometry myGeometry = *new MyGeometry();

        if (myGeometry.IsExistTriangle(a, b, c)) {
            SetConsoleTextAttribute(handleConsole, Green);
            cout << "Данный треугольник существует:" << endl << endl;
            SetConsoleTextAttribute(handleConsole, White);

            string view;

            if (myGeometry.IsRectangularTriangle(a, b, c))
                view = "прямоугольный";
            else if(myGeometry.IsAcuteAngledTriangle(a, b, c))
                view = "остроугольный";
            else if(myGeometry.IsObtuseTriangle(a, b, c))
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

class Task26 {
private:
    const int MIN = 10;
    const int MAX = 100;

    void PrintData(string type, string data) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, Yellow);

        cout << type << " ";

        SetConsoleTextAttribute(handleConsole, Green);
        cout << data << endl;
    }

    double getRSemiPerimeter(double a, double b, double c) {

        string sA = RoundStr(a);
        string sB = RoundStr(b);
        string sC = RoundStr(c);

        double sumABC = Round(a + b + c);
        string sSumABC = RoundStr(sumABC);

        double p = Round(sumABC / 2);
        string sP = RoundStr(p);

        cout << "p = (a + b + c) / 2" << endl;
        cout << "p = (" << a << " + " << b << " + " << c << ") / 2" << endl;
        cout << "p = " << sumABC << " / 2" << endl;
        cout << "p = " << p << endl << endl;

        double ABC = Round(a * b * c);
        string sABC = RoundStr(ABC);

        double PA = Round(p - a);
        double PB = Round(p - b);
        double PC = Round(p - c);
       
        double underRoot = Round(p * PA * PB * PC);
        double noRoot = Round(sqrt(underRoot));

        double divider = Round(noRoot * 4);
        double result = Round(ABC / divider);

        cout << "r = (a * b * c) / (4 * Корень из (p * (p - a) * (p - b) * (p - c))" << endl;
        cout << "r = (" << sA << " * " << sB << " * " << sC << ") / (4 * Корень из(" << sP  << " * (" << sP << " - " << sA <<") * (" << sP << " - " << sB << ") * (" << sP << " - " << sC << "))" << endl;
        cout << "r = " << sABC << " / (4 * Корень из(" << sP << " * " << RoundStr(PA) << " * " << RoundStr(PB) << " * " << RoundStr(PC) << "))" << endl;
        cout << "r = " << sABC << " / (4 * Корень из " << RoundStr(underRoot) << ")" << endl;
        cout << "r = " << sABC << " / (4 * " << RoundStr(noRoot) << ")" << endl;
        cout << "r = " << sABC << " / " << RoundStr(divider) << ")" << endl;
        cout << "r = " << RoundStr(result) << endl;

        return result;
    }
public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "Определить, из круга какого наименьшего радиуса можно вырезать треугольник со сторонами a, b, c." << endl;
        cout << "Указание: пусть c – большая из сторон треугольника" << endl << endl;

        double a, b, c;
        bool isGo = true;

        MyRandom myRandom = *new MyRandom();
        MyGeometry myGeometry = *new MyGeometry();

        if (myRandom.isRandomData()) {

            while (isGo) {
                c = myRandom.GetRandom(MIN, MAX);

                a = myRandom.GetRandom(MIN, c - 1);
                b = myRandom.GetRandom(MIN, c - 1);

                isGo = !myGeometry.IsExistTriangle(a, b, c);
            }
        }
        else {

            MyInput myInput = *new MyInput();

            while (isGo) {
                c = myInput.InputData("Введите сторону c: ", MIN, MAX);

                a = myInput.InputData("Введите сторону a: ", MIN, c - 1);
                b = myInput.InputData("Введите сторону b: ", MIN, c - 1);

                if (!myGeometry.IsExistTriangle(a, b, c)) {
                    SetConsoleTextAttribute(handleConsole, Red);
                    cout << "Данный треугольник не существует!" << endl << endl;
                    SetConsoleTextAttribute(handleConsole, White);
                }
                else
                    isGo = false;
            }   
        }

        double cornerC = myGeometry.GetCorner(c, a, b);

        a = Round(a);
        b = Round(b);
        c = Round(c);

        cornerC = Round(cornerC);

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "\nДан треугольник со сторонами:" << endl;

        PrintData("a: ", RoundStr(a));
        PrintData("b: ", RoundStr(b));
        PrintData("c: ", RoundStr(c));

        PrintData("Угол С: ", RoundStr(cornerC));

        SetConsoleTextAttribute(handleConsole, White);

        cout << "\nТ.к угол С - ";
        

        if (cornerC > 90) {
            cout << "тупой" << endl;
            cout << "=> сторона \"c\" совпадает с диаметром круга" << endl;

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "d = c" << endl;
            cout << "r = c/2" << endl;

            cout << "r = " << RoundStr(c) << "/2" << endl;
            cout << "r = " << RoundStr(c/2) << endl;
        }
        else {

            if (cornerC < 90)
                cout << "острый";
            else
                cout << "прямой";

            cout << endl << endl;

            getRSemiPerimeter(a, b, c);
        }


    }
};

class Task36 {
private:
    const int MIN = -1000;
    const int MAX = 1000;

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

        MyRandom myRandom = *new MyRandom();

        if (myRandom.isRandomData()) {
            a = myRandom.GetRandom(MIN, MAX);
            b = myRandom.GetRandom(MIN, MAX);
            c = myRandom.GetRandom(MIN, MAX);
            d = myRandom.GetRandom(MIN, MAX);
        }
        else {

            MyInput myInput = *new MyInput();
            a = myInput.InputData("Введите число a: ", MIN, MAX);
            b = myInput.InputData("Введите число b: ", MIN, MAX);
            c = myInput.InputData("Введите число c: ", MIN, MAX);
            d = myInput.InputData("Введите число d: ", MIN, MAX);
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

        cout << "26) Определить, из круга какого наименьшего радиуса можно вырезать треугольник со сторонами a, b, c." << endl;
        cout << "Указание: пусть c – большая из сторон треугольника" << endl << endl;

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
        else if (select == "26") {
            Task26 task26 = *new Task26();
            task26.Init();
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

