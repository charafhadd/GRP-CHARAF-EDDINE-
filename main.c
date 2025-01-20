#include <stdio.h>
#include <string.h>

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

int lireEntier() {
    int valeur;
    while (scanf("%d", &valeur) != 1) {
        printf("Entree invalide. Reessayez : ");
        while (getchar() != '\n');
    }
    return valeur;
}

int rechercherCompte(int numeroCompte) {
    for (int i = 0; i < nombreComptes; i++) {
        if (comptes[i].numeroCompte == numeroCompte) return i;
    }
    return -1;
}

void afficherComptes() {
    if (nombreComptes == 0) {
        printf("Aucun compte.\n");
        return;
    }
    printf("Numero \t| Nom \t| Email \t| Solde \t| Statut\n");
    for (int i = 0; i < nombreComptes; i++) {
        printf("%d |\t %s  |\t %s |\t %.2f |\t %s\n", comptes[i].numeroCompte, comptes[i].nom, comptes[i].email, comptes[i].solde, comptes[i].estActif ? "Actif" : "Inactif");
    }
}

void ajouterCompte() {
    if (nombreComptes >= MAX_COMPTES) {
        printf("Limite de comptes atteinte.\n");
        return;
    }

    Compte nouveauCompte;
    printf("Numero de compte : ");
    nouveauCompte.numeroCompte = lireEntier();
    if (rechercherCompte(nouveauCompte.numeroCompte) != -1) {
        printf("Ce compte existe deja.\n");
        return;
    }
    printf("Nom : ");
    scanf("%s", nouveauCompte.nom);
    printf("Email : ");
    scanf("%s", nouveauCompte.email);
    printf("Telephone : ");
    scanf("%s", nouveauCompte.telephone);
    printf("Solde initial : ");
    nouveauCompte.solde = lireFlottant();
    nouveauCompte.estActif = 1;

    comptes[nombreComptes++] = nouveauCompte;
    printf("Compte ajoute.\n");
}

void supprimerCompte() {
    printf("Numero de compte a supprimer : ");
    int numero = lireEntier();
    int index = rechercherCompte(numero);
    if (index == -1) {
        printf("Compte introuvable.\n");
        return;
    }

    for (int i = index; i < nombreComptes - 1; i++) {
        comptes[i] = comptes[i + 1];
    }
    nombreComptes--;
    printf("Compte supprime.\n");
}

void deposerArgent() {
    printf("Numero de compte pour le depot : ");
    int numero = lireEntier();
    int index = rechercherCompte(numero);
    if (index == -1) {
        printf("Compte introuvable.\n");
        return;
    }
    printf("Montant a deposer : ");
    float montant = lireFlottant();
    if (montant <= 0) {
        printf("Le montant doit etre positif.\n");
        return;
    }
    comptes[index].solde += montant;
    printf("Depot effectue. Nouveau solde : %.2f\n", comptes[index].solde);
}

void retirerArgent() {
    printf("Numero de compte pour le retrait : ");
    int numero = lireEntier();
    int index = rechercherCompte(numero);
    if (index == -1) {
        printf("Compte introuvable.\n");
        return;
    }
    printf("Montant à retirer : ");
    float montant = lireFlottant();
    if (montant <= 0 || comptes[index].solde < montant) {
        printf("Montant invalide ou fonds insuffisants.\n");
        return;
    }
    comptes[index].solde -= montant;
    printf("Retrait effectue. Nouveau solde : %.2f\n", comptes[index].solde);
}

void transfertArgent() {
    printf("Numero de compte source : ");
    int source = lireEntier();
    int indexSource = rechercherCompte(source);
    if (indexSource == -1) {
        printf("Compte source introuvable.\n");
        return;
    }

    printf("Numero de compte destination : ");
    int destination = lireEntier();
    int indexDestination = rechercherCompte(destination);
    if (indexDestination == -1) {
        printf("Compte destination introuvable.\n");
        return;
    }

    printf("Montant à transferer : ");
    float montant = lireFlottant();
    if (montant <= 0 || comptes[indexSource].solde < montant) {
        printf("Montant invalide ou fonds insuffisants.\n");
        return;
    }

    comptes[indexSource].solde -= montant;
    comptes[indexDestination].solde += montant;
    printf("Transfert effectue. Nouveau solde compte source : %.2f, destination : %.2f\n", comptes[indexSource].solde, comptes[indexDestination].solde);
}

void sauvegarderComptes() {
    FILE *fichier = fopen(NOM_FICHIER, "w");
    if (!fichier) {
        printf("Erreur fichier.\n");
        return;
    }
    fprintf(fichier, "numeroCompte,nom,email,telephone,solde,estActif\n");
    for (int i = 0; i < nombreComptes; i++) {
        fprintf(fichier, "%d,%s,%s,%s,%.2f,%d\n", comptes[i].numeroCompte, comptes[i].nom, comptes[i].email, comptes[i].telephone, comptes[i].solde, comptes[i].estActif);
    }
    fclose(fichier);
    printf("Comptes sauvegardes.\n");
}

void trierComptes() {
    int choixTri;
    printf("Trier par :\n1. Numero de compte\n2. Nom\n3. Solde\n");
    choixTri = lireEntier();

    for (int i = 0; i < nombreComptes - 1; i++) {
        for (int j = i + 1; j < nombreComptes; j++) {
            int condition = 0;
            if (choixTri == 1 && comptes[i].numeroCompte > comptes[j].numeroCompte) {
                condition = 1;
            } else if (choixTri == 2 && strcmp(comptes[i].nom, comptes[j].nom) > 0) {
                condition = 1;
            } else if (choixTri == 3 && comptes[i].solde > comptes[j].solde) {
                condition = 1;
            }

            if (condition) {
                Compte temp = comptes[i];
                comptes[i] = comptes[j];
                comptes[j] = temp;
            }
        }
    }
    printf("Comptes tries.\n");
}

int main() {
    int choix;
    while (1) {
        printf("\n1. Afficher les comptes\n2. Ajouter un compte\n3. Supprimer un compte\n4. Deposer de l'argent\n5. Retirer de l'argent\n6. Transferer de l'argent\n7. Sauvegarder\n8. Trier les comptes\n9. Quitter\n");
        printf("Entrer votre Choix : ");
        choix = lireEntier();
        switch (choix) {
            case 1: afficherComptes(); break;
            case 2: ajouterCompte(); break;
            case 3: supprimerCompte(); break;
            case 4: deposerArgent(); break;
            case 5: retirerArgent(); break;
            case 6: transfertArgent(); break;
            case 7: sauvegarderComptes(); break;
            case 8: trierComptes(); break;
            case 9: sauvegarderComptes(); printf("Au revoir.\n"); return 0;
            default: printf("Choix invalide.\n");
        }
    }
}

