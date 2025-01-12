#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#define MAX_COMPTES 100
#define NOM_FICHIER "comptes.csv"

typedef struct {
    int numeroCompte;
    char nom[50];
    char email[50];
    char telephone[50];
    float solde;
    int estActif;
} Compte;

Compte comptes[MAX_COMPTES];
int nombreComptes = 0;
int choix;
int lireEntier();
float lireFlottant();
int rechercherCompte(int numeroCompte);
void afficherComptes();
void ajouterCompte();
void supprimerCompte();
void deposerArgent();
void retirerArgent();
void transfertArgent();
void sauvegarderComptes();
void trierComptes();




#endif // FONCTION_H_INCLUDED
