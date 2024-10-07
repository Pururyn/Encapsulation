#include <iostream>
#include <string>
using namespace std;

/*class CompteBancaire
{
private:
	string utilisateur;
	double solde;

public:
	CompteBancaire(string nom,double argent) {
		utilisateur = nom;
		solde = argent;
	 }
	void debiter(double montant) {

		solde -= montant;

		if (solde >= 0){
		cout << "Vous avez retire " << montant << " euro a votre compte. Vous avez actuellement " << solde << " euro sur votre compte.\n";
		}
		else{
			cout << "Vous ne pouvez pas retirer " << montant << "euro. \n";
		}
	}
	void crediter(double montant) {

		solde += montant;

		cout << "Vous avez ajoute " << montant << " euro a votre compte. Vous avez actuellement " << solde << " euro sur votre compte.\n";
				
	}
	void afficher() {
		cout << utilisateur << ", vous avez actuellement " << solde << " euro sur votre compte.\n";
	}
};

int main() {

	CompteBancaire user("Toto",100);
	user.afficher();
	user.debiter(100);
	user.crediter(20);
	user.afficher();

	return 0;
}*/