#ifndef GRAPHE_H
#define GRAPHE_H


class Graphe
{
    public:
        Graphe();
        Graphe(int n);
        void afficher();
        int* fourmis(int f, int debut);
        virtual ~Graphe();
    protected:
    private:
        int n;
        int** matrice;
};

#endif // GRAPHE_H
