#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;
using namespace sf;

static int width = 1280;
static int height = 720;

int choice = 0;
double parameter = 1;

double function(double x) {
    switch (choice) {
    case 0: { //Линейная функция
        return parameter*x;
        break;
    }
    case 1: { //Параллельная оси X
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
    case 4: { //Степенная
        return pow(x, parameter);
        break;
    }
    case 5: { //Показательная
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
    case 11: { //Звуковые волны
        return x * sin(x) * sin(1000000 * x);
        break;
    }
    }
}

int screenX(double minx, double x, double scale) {
    return (x - minx) * scale;
}

int screenY(double maxy, double y, double scale) {
    return (maxy - y) * scale;
}

bool nancheck(double y) {
    if (y >= 0 || y < 0) {
        return false;
    }
    else {
        return true;
    }
}

bool infcheck(double y) {
    if (abs(y) > numeric_limits<int>::max()) {
        return true;
    }
    else {
        return false;
    }
}

bool norm(double y) {
    return !infcheck(y) && !nancheck(y);
}

int main()
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    double xx = 0;
    double yy = 0;

    double minx;
    double maxx;  


    double scaleX; //Pixels per 1
    double scaleY; //Pixels per 1

    vector <double> bad;

    cout << "List of functions: " << endl;
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

    cout << "Choose function type: ";
    cin >> choice;

    if (choice == 1 || choice == 4 || choice == 5) {
        cout << "Input parameter for function: ";
        cin >> parameter;
    }

    if (choice != 11 && choice != 10 && choice != 9) {
        cout << "Input minimum X value: ";
        cin >> minx;
        cout << "Input maximum X value: ";
        cin >> maxx;
    }
    else {
        switch (choice) {
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

    double miny = function(minx);
    double maxy = function(maxx);
    
    if (!(maxx > minx)) {
        cout << "Error: maximum value of X must be more than minimum value of X" << endl;
    } 
    else if(choice < 0 || choice > 11) {
        cout << "Error: wrong function number" << endl;
    }
    else {

        scaleX = width / abs(maxx - minx);

        for (double x = minx; x <= maxx; x+= 1 / scaleX) {
            if (function(x) < miny) miny = function(x);
            if (function(x) > maxy) maxy = function(x);
        }

        if (norm(miny) && nancheck(maxy)) {
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

        miny = round(miny);
        maxy = round(maxy);

        scaleY = height / (maxy - miny);

        double fxmin = minx;
        double fxmax = maxx;
        double fymin = miny;
        double fymax = maxy;

        if (minx > 0 && maxx > 0) {
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

        scaleY = height / abs(maxy - miny);

        vector <double> xp;
        vector <double> yp;

        int rangeX;
        int rangeY;

        rangeX = maxx - minx;
        rangeY = maxy - miny;

        int dx = 0;
        int dy = 0;

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

        for (double i = minx; i <= maxx; i += pow(10, dx) / 5) {
            double d = i;
            if (abs(d) < 0.0000000001) d = 0;

            xp.push_back(d);
        }

        for (double i = miny; i <= maxy; i += pow(10, dy) / 2) {
            double d = i;
            if (abs(d) < 0.0000000001) d = 0;

            yp.push_back(d);
        }

        RenderWindow window(VideoMode(width, height), "Graph");

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear();

            Vertex ox[] =
            {
                Vertex(Vector2f(0,screenY(maxy, 0, scaleY))),
                Vertex(Vector2f(width, screenY(maxy, 0, scaleY)))
            };

            Vertex oy[] =
            {
                Vertex(Vector2f(screenX(minx, 0, scaleX), height)),
                Vertex(Vector2f(screenX(minx, 0, scaleX), 0))
            };

            window.draw(ox, 2, Lines);
            window.draw(oy, 2, Lines);

            x1 = screenX(fxmin, fxmin, scaleX);
            y1 = screenY(fymax, round(function(fxmin)), scaleY);

            bool wasbad = false;

            for (xx = fxmin + 1 / scaleX; xx <= fxmax; xx += 1 / scaleX) {
                yy = function(xx);

                x2 = screenX(fxmin, xx, scaleX);
                y2 = screenY(fymax, yy, scaleY);

                Vertex graph[] = {
                    Vertex(Vector2f(x1, y1)),
                    Vertex(Vector2f(x2, y2))
                };

                if (!wasbad && norm(function(xx))) {
                    window.draw(graph, 2, Lines);
                }
                
                x1 = x2;
                y1 = y2;

                if (norm(function(xx))) {
                    wasbad = false;
                }
                else {
                    wasbad = true;
                }
            }

            for (int i = 0; i < xp.size(); i++) {
                Vertex point[] = {
                    Vertex(Vector2f(screenX(minx, xp[i], scaleX), screenY(maxy, 0, scaleY) - 5)),
                    Vertex(Vector2f(screenX(minx, xp[i], scaleX), screenY(maxy, 0, scaleY) + 5))
                };
                window.draw(point, 2, Lines);
            }

            for (int i = 0; i < yp.size(); i++) {
                Vertex point[] = {
                    Vertex(Vector2f(screenX(minx, 0, scaleX) - 5, screenY(maxy, yp[i], scaleY))),
                    Vertex(Vector2f(screenX(minx, 0, scaleX) + 5, screenY(maxy, yp[i], scaleY))),
                };
                window.draw(point, 2, Lines);
            }

            Font font;
            if (!font.loadFromFile("arial.ttf")) {
                cout << "Font loading error" << endl;
            }

            for (int i = 0; i < xp.size(); i++) {
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

            for (int i = 0; i < yp.size(); i++) {
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

            window.display();
        }
    }
    return 0;
}