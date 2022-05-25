#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;
using namespace sf;

static int width = 1280; //Ширина экрана
static int height = 720; //Высота экрана

int choice = 0; //Номер функции
double parameter = 1; //Параметр функции

double function(double x) { //Функция, по которой построится график
    switch (choice) {
    case 0: { //Линейная функция
        return parameter*x;
        break;
    }
    case 1: { //Прямая, параллельная оси X
        return parameter;
        break;
    }
    case 2: { //Парабола
        return x * x;
        break;
    }
    case 3: { //Гипербола
        return 1 / x;
        break;
    }
    case 4: { //Степенная функция
        return pow(x, parameter);
        break;
    }
    case 5: { //Показательная функция
        return pow(parameter, x);
        break;
    }
    case 6: { //Синусоида
        return sin(x);
        break;
    }
    case 7: { //Острая синусоида
        return asin(sin(x));
        break;
    }
    case 8: { //Успокаивающаяся синусоида
        return sin(1 / x);
        break;
    }
    case 9: { //Сердце
        return (sqrt(cos(x)) * cos(300 * x) + sqrt(abs(x))) * pow((4 - x * x), 0.01);
        break;
    }
    case 10: { //Горы
        return cos(3 * x * 3.14) / 2 + cos(9 * x * 3.14) / 4 + cos(27 * x * 3.14) / 8 + cos(81 * x * 3.14) / 16;
        break;
    }
    case 11: { //Звуковая волна
        return x * sin(x) * sin(1000000 * x);
        break;
    }
    }
}

int screenX(double minx, double x, double scale) { //Функция перехода от реальных координат к экранным по X
    return (x - minx) * scale;
}

int screenY(double maxy, double y, double scale) { //Фукнция перехода от реальных координат к экранным по Y
    return (maxy - y) * scale;
}

bool nancheck(double y) { //Проверка на неопределённость
    if (y >= 0 || y < 0) {
        return false;
    }
    else {
        return true;
    }
}

bool infcheck(double y) { //Проверка на бесконечность
    if (abs(y) > numeric_limits<int>::max()) {
        return true;
    }
    else {
        return false;
    }
}

bool norm(double y) { //Проверка на нормальность
    return !infcheck(y) && !nancheck(y);
}

int main()
{
    int x1 = 0; //Координата x первой точки
    int y1 = 0; //Координата y первой точки
    int x2 = 0; //Координата x второй точки
    int y2 = 0; //Координата y второй точки
    double xx = 0; //Реальная координата по X
    double yy = 0; //Реальная координата по Y

    double minx; //Минимальное значение x
    double maxx; //Максимальное значение x


    double scaleX; //Pixels per 1 //Масштаб оси x
    double scaleY; //Pixels per 1 //Масштаб оси y

    //vector <double> bad;

    cout << "List of functions: " << endl; //Список функций
    cout << "(0) Linear function" << endl;
    cout << "(1) X axis parallel" << endl;
    cout << "(2) Parabola" << endl;
    cout << "(3) Hyberbole" << endl;
    cout << "(4) Power function" << endl;
    cout << "(5) Exponential function" << endl;
    cout << "(6) Sinusoid" << endl;
    cout << "(7) Sharp sinus" << endl;
    cout << "(8) Calming sinus" << endl;
    cout << "(9) Heart" << endl;
    cout << "(10) Mountain" << endl;
    cout << "(11) Sound wave" << endl;
    cout << endl;

    cout << "Choose function type: "; //Выбор функции
    cin >> choice;

    if (choice == 1 || choice == 4 || choice == 5) { //Ввод параметра при необходимости
        cout << "Input parameter for function: ";
        cin >> parameter;
    }

    if (choice != 11 && choice != 10 && choice != 9) { //Ввод крайних значений аргумента при необходимости
        cout << "Input minimum X value: ";
        cin >> minx;
        cout << "Input maximum X value: ";
        cin >> maxx;
    }
    else {
        switch (choice) { //Установка рекомендуемых значений для некоторых функций
        case 9: {
            minx = -2;
            maxx = 2;
            break;
        }
        case 10: {
            minx = -1;
            maxx = 1;
            break;
        }
        case 11: {
            minx = -10;
            maxx = 10;
            break;
        }
        }
    }

    double miny = function(minx); //Минимальное значние функции
    double maxy = function(maxx); //Максимальное значение функции
    
    if (!(maxx > minx)) { //Ошиька ввода крайних значений аргумента
        cout << "Error: maximum value of X must be more than minimum value of X" << endl;
    } 
    else if(choice < 0 || choice > 11) { //Ошибка ввода номера функции
        cout << "Error: wrong function number" << endl;
    }
    else {

        scaleX = width / abs(maxx - minx); //Масштаб по x

        for (double x = minx; x <= maxx; x+= 1 / scaleX) { //Определение минимума и максимума функции
            if (function(x) < miny) miny = function(x);
            if (function(x) > maxy) maxy = function(x);
        }

        if (norm(miny) && nancheck(maxy)) { //Перебор всех комбинаций типов минимального и максимального значений функций с нормализацией значений
            maxy = 1;
        }
        else if (norm(miny) && infcheck(maxy)) {
            maxy = abs(miny);
        }
        else if (nancheck(miny) && norm(maxy)) {
            miny = -1;
        }
        else if (nancheck(miny) && nancheck(maxy)) {
            miny = -1;
            maxy = 1;
        }
        else if (nancheck(miny) && infcheck(maxy)) {
            miny = 1;
            maxy = 100;
        }
        else if (infcheck(miny) && norm(maxy)) {
            miny = -maxy;
        }
        else if (infcheck(miny) && nancheck(maxy)) {
            miny = -100;
            maxy = 1;
        }
        else if (infcheck(miny) && infcheck(maxy)) {
            miny = -100;
            maxy = 100;
        }

        miny = round(miny); //Округление
        maxy = round(maxy);

        scaleY = height / (maxy - miny); //Масштаб по Y

        double fxmin = minx; //Разделение минимумов и максимумов на функциональные и осевые
        double fxmax = maxx;
        double fymin = miny;
        double fymax = maxy;

        if (minx > 0 && maxx > 0) { //Автоматическая корректировка и подгон минимумов и максимумов под окно
            minx = -1;
            scaleX = width / abs(maxx - minx);
        }
        else if (minx < 0 && maxx < 0) {
            maxx = 1;
            scaleX = width / abs(maxx - minx);
        }

        if (miny > 0 && maxy > 0) {
            miny = -1;
            scaleY = height / abs(maxy - miny);
        }
        else if (miny < 0 && maxy < 0) {
            maxy = 1;
            scaleY = height / abs(maxy - miny);
        }

        if (miny == 0) {
            miny = -1;
            scaleY = height / abs(maxy - miny);
        }

        if (maxy == 0) {
            maxy = 1;
            scaleY = height / abs(maxy - miny);
        }

        fymin -= 1;
        fymax += 1;

        miny -= 1;
        maxy += 1;

        scaleY = height / abs(maxy - miny); //Пересчёт масштаба по y

        vector <double> xp; //Вектор точек на оси x
        vector <double> yp; //Вектор точек на оси y

        int rangeX; //Диапазон по x
        int rangeY; //Диапазон по y

        rangeX = maxx - minx;
        rangeY = maxy - miny;

        int dx = 0; //Максимальная степень 10 по x
        int dy = 0; //Максимальная степень 10 по y

        while (rangeX != 0) {
            rangeX /= 10;
            dx++;
        }

        while (rangeY != 0) {
            rangeY /= 10;
            dy++;
        }

        dx--;
        dy--;

        for (double i = minx; i <= maxx; i += pow(10, dx) / 5) { //Расчёт значений точек на оси x
            double d = i;
            if (abs(d) < 0.0000000001) d = 0;

            xp.push_back(d);
        }

        for (double i = miny; i <= maxy; i += pow(10, dy) / 2) { //Расчёт значений точек на оси y
            double d = i;
            if (abs(d) < 0.0000000001) d = 0;

            yp.push_back(d);
        }

        RenderWindow window(VideoMode(width, height), "Graph"); //Инициализация окна

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear();

            Vertex ox[] = //Ось x
            {
                Vertex(Vector2f(0,screenY(maxy, 0, scaleY))),
                Vertex(Vector2f(width, screenY(maxy, 0, scaleY)))
            };

            Vertex oy[] = //Ось y
            {
                Vertex(Vector2f(screenX(minx, 0, scaleX), height)),
                Vertex(Vector2f(screenX(minx, 0, scaleX), 0))
            };

            window.draw(ox, 2, Lines); //Отрисовка осей
            window.draw(oy, 2, Lines);

            x1 = screenX(fxmin, fxmin, scaleX); //Первая точка отрезка
            y1 = screenY(fymax, round(function(fxmin)), scaleY);

            bool wasbad = false; //Была ли предыдущая точка выколотой

            for (xx = fxmin + 1 / scaleX; xx <= fxmax; xx += 1 / scaleX) { //Проход по всем значениям аргумента
                yy = function(xx); //Реальное значений функции

                x2 = screenX(fxmin, xx, scaleX); //Вторая точка отрезка
                y2 = screenY(fymax, yy, scaleY);

                Vertex graph[] = { //Отрезок
                    Vertex(Vector2f(x1, y1)),
                    Vertex(Vector2f(x2, y2))
                };

                if (!wasbad && norm(function(xx))) { //Если не было и нет выколотой точки, то отрсиовать отрезок
                    window.draw(graph, 2, Lines);
                }
                
                x1 = x2; //Обновить координаты первой точки
                y1 = y2;

                if (norm(function(xx))) { //Является ли эта точка выколотой
                    wasbad = false;
                }
                else {
                    wasbad = true;
                }
            }

            for (int i = 0; i < xp.size(); i++) { //Инициализация штрихов на оси x
                Vertex point[] = {
                    Vertex(Vector2f(screenX(minx, xp[i], scaleX), screenY(maxy, 0, scaleY) - 5)),
                    Vertex(Vector2f(screenX(minx, xp[i], scaleX), screenY(maxy, 0, scaleY) + 5))
                };
                window.draw(point, 2, Lines); //Отрисовка штрихов
            }

            for (int i = 0; i < yp.size(); i++) { //Инициалиация штрихов на оси y
                Vertex point[] = {
                    Vertex(Vector2f(screenX(minx, 0, scaleX) - 5, screenY(maxy, yp[i], scaleY))),
                    Vertex(Vector2f(screenX(minx, 0, scaleX) + 5, screenY(maxy, yp[i], scaleY))),
                };
                window.draw(point, 2, Lines); //Отрисовка штрихов
            }

            Font font; //Загрузка шрифта
            if (!font.loadFromFile("arial.ttf")) {
                cout << "Font loading error" << endl;
            }

            for (int i = 0; i < xp.size(); i++) { //Определение координат точек и отрисовка текстов с координатами по оси x
                string s;
                if (xp[i] - round(xp[i]) == 0) {
                    s = to_string((int)xp[i]);
                }
                else {
                    s = to_string(xp[i]);
                }

                Text text(s, font, 14);
                text.setFillColor(Color::White);
                text.setPosition(screenX(minx, xp[i], scaleX), screenY(maxy, 0, scaleY) + 10);
                window.draw(text);
            }

            for (int i = 0; i < yp.size(); i++) { //Определение координат точек и отрисовка текстов с координатами по оси y
                string s;
                if (yp[i] - round(yp[i]) == 0) {
                    s = to_string((int)yp[i]);
                }
                else {
                    s = to_string(yp[i]);
                }

                Text text(s, font, 14);
                text.setFillColor(Color::White);
                text.setPosition(screenX(minx, 0, scaleX) + 6, screenY(maxy, yp[i], scaleY));
                window.draw(text);
            }

            window.display(); //Отобразить изменения в окне
        }
    }
    return 0;
}
