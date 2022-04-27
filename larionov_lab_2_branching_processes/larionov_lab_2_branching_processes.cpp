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
                cout << endl << xStr + " - �� �����!" << endl << endl;
            }
            else if (result <= 0) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ���� ������ ����!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max) {

        int result = 0;

        while (true) {
            result = InputData(text);

            if ((int)result != result) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ���� �����!" << endl << endl;
            }
            else if (result < min || result > max) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ������ � ���������� [" << min << "; " << max << "]!" << endl << endl;
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
        cout << "������������� ������ ��������� ������� [y/n]?" << endl;

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

        bool res1 = a + b == c;
        bool res2 = a + c == b;
        bool res3 = b + c == a;

        return res1 && res2 && res3;
    }

    double RadianToDegree(double val) {
        return (val * 180) / PI;
    }

    double GetCorner(double oppoziteSide, double side1, double side2) {
        double cosOppozite = (pow(side1, 2) + pow(side2, 2) - pow(oppoziteSide, 2)) / (2 * side1 * side2);
        return RadianToDegree(acos(cosOppozite));
    }

    bool IsAcuteAngledTriangle(double a, double b, double c) {

        if (a == b && b == c && a == c) //��� ������� �����
            return true;

        double cornerA = GetCorner(a, b, c);
        double cornerB = GetCorner(b, a, c);
        double cornerC = GetCorner(c, a, b);

        //��� ������� ������
        if (a != b && b != c && a != c) { 
            if (cornerA < 90 && cornerB < 90 && cornerC < 90)
                return true;
        }

        //=========================��������������===========================
        bool res1 = a == b && a > c;
        bool res2 = a == c && a > b;
        bool res3 = b == c && b > a;

        if (a == b && cornerC < 90)
            return true;

        if (a == c && cornerB < 90)
            return true;

        if (c == b && cornerA < 90)
            return true;

        return false;
    }

    bool IsObtuseTriangle(double a, double b, double c) {

        //=========================��������������===========================
        double cornerA = GetCorner(a, b, c);
        double cornerB = GetCorner(b, a, c);
        double cornerC = GetCorner(c, a, b);

        if (a == b && cornerC > 90)
            return true;

        if (a == c && cornerB > 90)
            return true;

        if (c == b && cornerA > 90)
            return true;

        //��� ������� ������
        if (a != b && b != c && a != c) {

            if (cornerA > 90 && (cornerB > 90 || cornerC > 90))
                return true;

            if (cornerB > 90 && (cornerA > 90 || cornerC > 90))
                return true;

            if (cornerC > 90 && (cornerA > 90 || cornerB > 90))
                return true;
        }

        return false;
    }

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "����������, ����� �� ���� �������� ����������� �� ��������� ������ ������." << endl;
        cout << "���� ����������� ����� ���������, �� ���������� ��� ��� (�������������, ������������ ��� �������������)" << endl << endl;

        double a, b, c;

        MyRandom myRandom = *new MyRandom();

        if (myRandom.isRandomData()) {
            a = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
            b = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
            c = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
        }
        else {
            MyInput myInput = *new MyInput();

            a = myInput.InputData("������� ������� ������������ (�): ");
            b = myInput.InputData("������� ������� ������������ (b): ");
            c = myInput.InputData("������� ������� ������������ (c): ");

        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << endl << "��� ����������� �� ���������:" << endl;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl << endl;

        if (IsExistTriangle(a, b, c)) {
            SetConsoleTextAttribute(handleConsole, Green);
            cout << "������ ����������� ����������:" << endl << endl;
            SetConsoleTextAttribute(handleConsole, White);

            string view;

            if (IsRectangularTriangle(a, b, c))
                view = "�������������";
            else if(IsAcuteAngledTriangle(a, b, c))
                view = "�������������";
            else if(IsObtuseTriangle(a, b, c))
                view = "������������";
            else {
                view = "����������";
                SetConsoleTextAttribute(handleConsole, Red);
            }

            cout << "���: " << view << endl << endl;
            SetConsoleTextAttribute(handleConsole, White);
             
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "������ ����������� �� ����������!" << endl << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }


    }

};

class Task16 {

private:
    string GetTimeYear(int num) {

        if (num >= 3 && num <= 5)
            return "�����";

        if (num >= 6 && num <= 8)
            return "����";

        if (num >= 9 && num <= 11)
            return "�����";
        
        if (num == 12 || num == 1 || num == 2)
            return "����";
        
        SetConsoleTextAttribute(handleConsole, Red);
        return "����������!";
    }

public:
    void Init() {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        MyInput myInput = *new MyInput();
      
        SetConsoleTextAttribute(handleConsole, White);
        cout << "\n�� ���������� ������ ������ ���������� ����� ����" << endl;
           
        int select = myInput.InputIntData("������� ����� ������: ", 1, 12);

        SetConsoleTextAttribute(handleConsole, Green);
        cout << "����� ����: " << GetTimeYear(select) << endl;

    }
};

int main()
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");

    SetConsoleTextAttribute(handleConsole, White);

    cout << "���� 2. ��������������� �������������� ��������" << endl;
    cout << "�������� ������ �������. ��. 110�" << endl;

    bool isGo = true;
    string select;

    while (isGo)
    {
        SetConsoleTextAttribute(handleConsole, White);

        cout << "\n������� ����� ������" << endl;
        cout << "6) ����������, ����� �� ���� �������� ����������� �� ��������� ������ ������." << endl;
        cout << "���� ����������� ����� ���������, �� ���������� ��� ��� (�������������, ������������ ��� �������������)" << endl << endl;

        cout << "16) �� ���������� ������ ������ ���������� ����� ����" << endl;
        cout << "��� ������ ������� \"0\": ";

        select = GetLine();

        if (select == "6") {
            Task6 task6 = *new Task6();
            task6.Init();
        }
        else if (select == "16") {
            Task16 task16 = *new Task16();
            task16.Init();
        }
        else if (select == "0") {
            isGo = false;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\n������������ ������!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }

    }
}

