#include "Graphe.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

Graphe::Graphe()
{
    n = 0;
    matrice = nullptr;
}

Graphe::Graphe(int n)
{
    this->n = n;
    std::srand(std::time(0));
    matrice = new int*[n];
    for(int i = 0; i < n; i++)
    {
        matrice[i] = new int[n];
        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                matrice[i][j] = std::rand()%(n -1) +1;
            }
            else
            {
                matrice[i][j] = 0;
            }

        }
    }
}

void Graphe::afficher()
{
    std::cout<<"\t";
    int i;
    for(i = 0; i < n; i++)
    {
        std::cout<<i<<"\t";
    }
    std::cout<<std::endl;
    for(i = 0; i < n; i++)
    {
        std::cout<<i<<"\t";
        for(int j = 0; j < n; j++)
        {
            std::cout<<matrice[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }

}

int* Graphe::fourmis(int f, int debut)
{
    int* solution = new int[n];
    int * sol = new int[n];
    int* choisi = new int[n];
    int sol_min;
    int min_final = 0;
    int** pheromones = new int*[n];
    double* proba = new double[n];
    int min_prec;
    for(int i = 0; i < n; i++)
    {
        pheromones[i] = new int[n];
        proba[i] = 0;
        choisi[i] = 0;
        for(int j = 0; j < n; j++)
        {
            pheromones[i][j] = 1;
        }
    }
    int courant;
    int id_min;
    double somme;
    double selection;
    std::srand(std::time(0));
    int h;
    for(int i = 0; i < f; i++)
    {
        courant = debut;
        sol_min = 0;
        for(int j = 0; j < n; j++)
        {
            solution[j] = -1;
            proba[j] = 0;
            choisi[j] = 0;
        }
        for(int k = 0; k < n-1; k++)
        {
            somme = 0;
            id_min = -1;
            for(int j = 0; j < n; j++)
            {
                if(j != courant && j != debut && choisi[j] != 1)
                {
                    proba[j] = pheromones[courant][j] * ((double)1/(double)matrice[courant][j]);
                    somme += proba[j];
                }
            }
            for(int j = 0; j < n; j++)
            {
                proba[j] = proba[j] / somme;
            }
            h = 0;
            while(id_min == -1)
            {
                if(courant != h && choisi[h] != 1 && h != debut)
                {
                    selection = (double)std::rand()/(double)RAND_MAX;
                    if(selection < proba[h])
                    {
                        id_min = h;
                    }
                }
                h = (h+1)%n;
            }
            pheromones[courant][id_min] += n*n*((double)1/(double)matrice[courant][id_min]);
            solution[courant] = id_min;
            choisi[id_min] = 1;
            courant = id_min;

        }
        solution[courant] = debut;
        for(int k = 0; k < n; k++)
        {

            for(int j = 0; j <n; j++)
            {
                pheromones[j][k] = pheromones[j][k] * (1-(1/(n*n)));
                if(pheromones[j][k] < 1)
                {
                    pheromones[j][k] = 1;
                }
            }
            sol_min += matrice[k][solution[k]];
        }
        for(int k = 0; k < n; k++)
        {

        }
        if(i > 0)
        {
            if(sol_min < min_final)
            {
                min_final = sol_min;
                for(int m = 0; m <n; m++)
                {
                    sol[m] = solution[m];
                }
            }
            if(sol_min < min_prec)
            {
                for(int m = 0; m < n; m++)
                {
                    pheromones[m][solution[m]] += n*n*((double)1/(double)matrice[m][solution[m]]);
                }
                min_prec = sol_min;
            }

        }
        else
        {
            min_final = sol_min;
            for(int m = 0; m <n; m++)
            {
                sol[m] = solution[m];
            }
        }
    }
    std::cout<<"Solution: "<<min_final<<std::endl;
    delete[] solution;
    delete[] pheromones;
    delete[] choisi;
    delete[] proba;
    return sol;
}



Graphe::~Graphe()
{
    //dtor
    for(int i = 0; i < n; i++)
    {
        delete[] matrice[i];
    }
    delete matrice;
}
