#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int data;
    struct element* fg;
    struct element* fd;
    int hauteur;
} Noeud;


int max(int a, int b) { return (a > b) ? a : b; }

int hauteur(Noeud* n) {
    return (n == NULL) ? 0 : n->hauteur;
}

Noeud* creerNoeud(int valeur) {
    Noeud* n = (Noeud*)malloc(sizeof(Noeud));
    n->data = valeur;
    n->fg = NULL;
    n->fd = NULL;
    n->hauteur = 1;
    return n;
}

int facteur_equilibre(Noeud* n) {
    if (n == NULL) return 0;
    return hauteur(n->fg) - hauteur(n->fd);
}



Noeud* rotationDroite(Noeud* y) {
    Noeud* x = y->fg;
    Noeud* T2 = x->fd;

    x->fd = y;
    y->fg = T2;

    y->hauteur = 1 + max(hauteur(y->fg), hauteur(y->fd));
    x->hauteur = 1 + max(hauteur(x->fg), hauteur(x->fd));

    return x;
}

Noeud* rotationGauche(Noeud* x) {
    Noeud* y = x->fd;
    Noeud* T2 = y->fg;

    y->fg = x;
    x->fd = T2;

    x->hauteur = 1 + max(hauteur(x->fg), hauteur(x->fd));
    y->hauteur = 1 + max(hauteur(y->fg), hauteur(y->fd));

    return y;
}

Noeud* rotationGaucheDroite(Noeud* z) {
    z->fg = rotationGauche(z->fg);
    return rotationDroite(z);
}

Noeud* rotationDroiteGauche(Noeud* z) {
    z->fd = rotationDroite(z->fd);
    return rotationGauche(z);
}



Noeud* insererAVL(Noeud* racine, int valeur) {

    if (racine == NULL)
        return creerNoeud(valeur);

    if (valeur < racine->data)
        racine->fg = insererAVL(racine->fg, valeur);

    else if (valeur > racine->data)
        racine->fd = insererAVL(racine->fd, valeur);

    else
        return racine; 

    racine->hauteur = 1 + max(hauteur(racine->fg), hauteur(racine->fd));

    int balance = facteur_equilibre(racine);

    // LL
    if (balance > 1 && valeur < racine->fg->data)
        return rotationDroite(racine);

    // RR
    if (balance < -1 && valeur > racine->fd->data)
        return rotationGauche(racine);

    // LR
    if (balance > 1 && valeur > racine->fg->data)
        return rotationGaucheDroite(racine);

    // RL
    if (balance < -1 && valeur < racine->fd->data)
        return rotationDroiteGauche(racine);

    return racine;
}



void Prefixe(Noeud* R) {
    if (R == NULL) return;
    printf("%d ", R->data);
    Prefixe(R->fg);
    Prefixe(R->fd);
}

void Infixe(Noeud* R) {
    if (R == NULL) return;
    Infixe(R->fg);
    printf("%d ", R->data);
    Infixe(R->fd);
}

void Postfixe(Noeud* R) {
    if (R == NULL) return;
    Postfixe(R->fg);
    Postfixe(R->fd);
    printf("%d ", R->data);
}



int hauteurArbre(Noeud* R) {
    if (R == NULL) return 0;
    int hL = hauteurArbre(R->fg);
    int hR = hauteurArbre(R->fd);
    return 1 + (hL > hR ? hL : hR);
}

void afficherNiveau(Noeud* R, int niveau) {
    if (R == NULL) return;
    if (niveau == 1)
        printf("%d ", R->data);
    else {
        afficherNiveau(R->fg, niveau - 1);
        afficherNiveau(R->fd, niveau - 1);
    }
}

void ParcoursParNiveau(Noeud* R) {
    int h = hauteurArbre(R);
    for (int i = 1; i <= h; i++)
        afficherNiveau(R, i);
}
Noeud* construireABREquilibre(int* tab, int debut, int fin) {
    if (debut > fin) return NULL;

    int milieu = (debut + fin) / 2;
    Noeud* racine = creerNoeud(tab[milieu]);

    racine->fg= construireABREquilibre(tab, debut, milieu - 1);
    racine->fd= construireABREquilibre(tab, milieu + 1, fin);

    return racine;
}
Noeud* trouver_min(Noeud* racine) {
    while (racine->fg != NULL)
        racine = racine->fg;
    return racine;
}
Noeud* suppNoeud(Noeud* racine, int valeur) {
    if (racine == NULL) return NULL;
    if (valeur < racine->data) {
        racine->fg = suppNoeud(racine->fg, valeur);
    }
    else if (valeur > racine->data) {
        racine->fd = suppNoeud(racine->fd, valeur);
    }
    else { // Noeud à supprimer trouvé
        if (racine->fg == NULL) {
            Noeud* temp = racine->fd;
            free(racine);
            return temp;
        }
        else if (racine->fd == NULL) {
            Noeud* temp = racine->fg;
            free(racine);
            return temp;
        }
        // Noeud avec deux enfants
        Noeud* temp = trouver_min(racine->fd);
        racine->data = temp->data;
        racine->fd = suppNoeud(racine->fd, temp->data);
    }

    return racine;
}

Noeud* search(Noeud* R, int val)
{
    if (R == NULL) return NULL;
    if (val == R->data) return R;
    else if (val < R->data)

        return search(R->fg, val);
    else return search(R->fd, val);
}
Noeud* Min(Noeud* R)
{
    if (R == NULL) return NULL;
    Noeud* tmp = R;
    while (tmp->fg != NULL)
    {
        tmp = tmp->fg;
    }
    return tmp;
}
Noeud* Max(Noeud* R)
{
    if (R == NULL) return NULL;
    Noeud* tmp = R;
    while (tmp->fd != NULL)
    {
        tmp = tmp->fd;
    }
    return tmp;
}

int main() {

  
    Noeud* racine = NULL;
    int valeurs[] = { 30, 20, 40, 10, 25, 22, 50, 5 };
    int n = sizeof(valeurs) / sizeof(valeurs[0]);

    printf("Insertion AVL : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valeurs[i]);
        racine = insererAVL(racine, valeurs[i]);
    }
    printf("\n\n");


    
    printf("Parcours Prefixe  : ");
    Prefixe(racine);

    printf("\nParcours Infixe   : ");
    Infixe(racine);

    printf("\nParcours Postfixe : ");
    Postfixe(racine);

    printf("\nParcours Par Niveau : ");
    ParcoursParNiveau(racine);

    printf("\n\n");


 
    int valCherchee = 25;
    Noeud* trouve = search(racine, valCherchee);

    if (trouve != NULL)
        printf("Valeur %d trouvee dans l'arbre.\n", valCherchee);
    else
        printf("Valeur %d NON trouvee.\n", valCherchee);


    
    printf("Valeur MIN = %d\n", Min(racine)->data);
    printf("Valeur MAX = %d\n\n", Max(racine)->data);


    
    int aSupprimer = 20;
    printf("Suppression du noeud %d...\n", aSupprimer);
    racine = suppNoeud(racine, aSupprimer);

    printf("Infixe apres suppression : ");
    Infixe(racine);
    printf("\n\n");


    
    int tableauTrie[] = { 1, 2, 3, 4, 5, 6, 7 };
    int m = sizeof(tableauTrie) / sizeof(tableauTrie[0]);

    Noeud* arbreEquilibre = construireABREquilibre(tableauTrie, 0, m - 1);

    printf("Arbre Equilibre (Infixe) : ");
    Infixe(arbreEquilibre);
    printf("\n\n");


    return 0;
}

