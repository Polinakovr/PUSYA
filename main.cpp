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
    void agerabbit()
    {
        int k = getaged();
        k++;
    }
    void agefox()
    {
        int l = getaged();
        l++;
        if (l >= 15)
        {
            // минус куни
        }
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
    void step(int step)
    {
        for (int i = 0; i <= masR.size(); i++)
        {
            masR[i].move(N, M, 1);
            masR[i].agerabbit();
            int s = masR[i].gets();
            if (step % s == 0)
                masR[i].change_d();
                if (k >= 10)
        {
            masR.erase(masR[i].());
        }
            
        }
        for (int i = 0; i <= masF.size(); i++)
        {
        }
    }
};

int main()
{
}