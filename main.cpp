#include <iostream>
#include <vector>
using namespace std;
class Animal
{
protected:
    int age;
    int x, y; // координаты
    int d;    // начальное направление
    int s;    // через сколько ходов будет поворачивать
public:
    Animal(int x, int y, int s, int d) : x(x), y(y), s(s), d(d), age(0) {}
    void move(int N, int M, int step)
    {
        if (d == 0) // север
        {
            if (y <= 0)
            {
                y += step;
                if (y == N)
                {
                    y = 0;
                }
            }
        }
        if (d == 1) // восток
        {
            if (x >= 0)
            {
                x++;
                if (y == M)
                {
                    x = 0;
                }
            }
        }
        if (d == 2) // юг
        {
            if (y <= 0)
            {
                y--;
                if (y == N)
                {
                    y = 0;
                }
            }
        }
        if (d == 3)
        {
            if (x <= 0)
            {
                x--;
                if (y == M)
                {
                    y = 0;
                }
            }
        }
    }
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }
    int getd()
    {
        return d;
    }
    int gets()
    {
        return s;
    }
    int getaged()
    {
        return age;
    }
    void change_d()
    {
        switch (d)
        {
        case 0:

            d = 1;
            break;

        case 1:

            d = 2;
            break;

        case 2:

            d = 3;
            break;

        case 3:

            d = 0;
            break;
        }
    }
    void age1()
    {
        age++;
    }
};
class Fox : public Animal
{
private:
    int food;

public:
    Fox(int x, int y, int s, int d) : Animal(x, y, s, d), food(0) {}
    ~Fox() {}
    void fooedeat()
    {
        food++;
    }
};
class Rabbit : public Animal
{
public:
    Rabbit(int x, int y, int s, int d) : Animal(x, y, s, d) {}
    ~Rabbit() {}

private:
    int step = 1;
};
class Model
{
private:
    int N, M;
    int counthod;
    vector<Fox> masF;
    vector<Rabbit> masR;
    int **mas;

public:
    void createmass()
    {
        int L = N * M;
        int **mas = (int **)malloc(L * sizeof(int));
        for (int i = 0; i < N; i++)
        {
            mas[i] = (int *)calloc(M, sizeof(*mas[i]));
        }
    }
    void addR(int x, int y, int s, int d)
    {
        masR.push_back(Rabbit(x, y, s, d));
        mas[x][y] = +1;
    }
    void addF(int x, int y, int s, int d)
    {
        masF.push_back(Fox(x, y, s, d));
        mas[x][y] = +1;
    }
    void poedanie(Fox *lisa2)
    {
        for (int i = 0; i <= masR.size(); i++)
        {
            if (masR[i].getx() == lisa2->getx())
            {
                masR.erase(masR.begin() + i);
            }
        }
    }
    void step(int step)
    {
        for (int i = 0; i <= masR.size(); i++)
        {
            masR[i].move(N, M, 1);
            masR[i].age1();
            int x = masR[i].getx();
            int y = masR[i].gety();
            int d = masR[i].getd();
            int s = masR[i].gets();
            int age = masR[i].getaged();
            if (step % s == 0)
                masR[i].change_d();
            if (age >= 10)
            {
                masR.erase(masR.begin() + i);
            }
            if (age == 5 || age == 10)
            {
                addR(x, y, s, d);
            }
        }
        for (int i = 0; i <= masF.size(); i++)
        {
            masF[i].move(N, M, 2);
            masF[i].age1();
            int x = masF[i].getx();
            int y = masF[i].gety();
            int d = masF[i].getd();
            int s = masF[i].gets();
            int age = masF[i].getaged();
            poedanie(&(masF[i]));
            if (step % s == 0)
                masF[i].change_d();
            if (age >= 15)
            {
                masF.erase(masF.begin() + i);
            }
            if (/////)
            {
                addF(x, y, s, d);
            }
        }
    }
};

int main()
{
}