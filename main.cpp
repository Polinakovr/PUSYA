#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
class Animal
{
protected:
    int x;
    int y; // координаты
    int s;
    int d;
    int age; // через сколько ходов будет поворачивать
public:
    Animal(int x, int y, int s, int d) : x(x), y(y), s(s), d(d), age(0) {}
    ~Animal() {}
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

    void lisichkapokyshala()
    {
        food++;
    }
    void edacirdik()
    {
        food = 0;
    }
    int getzayacsdox()
    {
        return food;
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
    Model(int N, int M, int counthod) : N(N), M(M), counthod(counthod) {}
    ~Model() {}
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
    }
    void addF(int x, int y, int s, int d)
    {
        masF.push_back(Fox(x, y, s, d));
    }
    void poedanie(Fox *lisa2)
    {
        int k = masR.size();
        for (int i = 0; i <= k; i++)
        {
            if (masR[i].getx() == lisa2->getx())
            {
                if (masR[i].gety() == lisa2->gety())
                {
                    masR.erase(masR.begin() + i);
                    lisa2->lisichkapokyshala();
                }
            }
        }
    }
    void step(int step)
    {
        int k = masR.size();
        int p = masF.size();
        for (int i = 0; i < k; i++)
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
        for (int i = 0; i < p; i++)
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
            int eda = masF[i].getzayacsdox();
            if (eda >= 2)
            {
                addF(x, y, s, d);
                masF[i].edacirdik();
            }
        }
    }
    void write()
    {
        cout << "COLICHESTVO Z: " << masR.size() << endl;
        cout << "COLICHESTVO F: " << masF.size() << endl;
        createmass();
        int y=masR.size();
        int s=masF.size();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; i < M; j++)
            { 
                for (int h = 0; h < y; h++)
                {
                    if (masR[h].getx() == j && masR[h].gety() == i)
                    {
                        mas[i][j]++;
                    }
                }
                for (int h = 0; h < s; h++)
                {
                    if (masF[h].getx() == j && masF[h].gety() == i)
                    {
                        mas[i][j]--;
                    }
                }
            }
        }cout << "COLICHESTVO F: " << masF.size() << endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; i < M; j++)
            {
                if (mas[i][j] == 0)
                {
                    cout << "*" << endl;
                }
                else {
                    cout << mas[i][j] << endl;
                }
            }
            cout<<endl;
        }
    }
};

int main()
{
    int N, M, couthod;
    cout << "Input height: \n";
    cin >> N;
    cout << "Input width: \n ";
    cin >> M;
    cout << "Input turns: \n ";
    cin >> couthod;
    Model razmer(N, M, couthod);
    srand(time(NULL));
    int sizerabbit = rand() % 10 + 5;
    int sizefox = rand() % 10 + 5;
    for (int i = 0; i < sizerabbit; i++)
    {
        razmer.addR(rand() % N, rand() % M, rand() % 5 + 1, rand() % 4);
    }
    for (int i = 0; i < sizefox; i++)
    {
        razmer.addF(rand() % N, rand() % M, rand() % 5 + 1, rand() % 4);
    }
    for (int i = 1; i < couthod + 1; i++)
    {
        razmer.step(i);
        razmer.write();
    }

    return 0;
}