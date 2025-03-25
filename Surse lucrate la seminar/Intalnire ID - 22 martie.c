#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;


// 
//creare structura pentru un nod dintr-o lista simplu inlantuita

struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;


struct HashTable {
	int dim;
	Nod** vector;
};
typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod**cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;//shallow copy
	nou->next = *cap;
	*cap = nou;
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.vector=(Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	ht.dim = dimensiune;
	return ht;
}

//cheie: numeSofer + Id
int calculeazaHash(const char* numeSofer, int id, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(numeSofer); i++) {
		suma += numeSofer[i];
	}
	suma *= 17;
	return (dimensiune > 0 ? (suma % dimensiune) : -1);

}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	int pozitie = calculeazaHash(masina.numeSofer, masina.id, hash.dim);
	if (pozitie >= 0 && pozitie<hash.dim) {
		if (hash.vector[pozitie] != NULL) {
			//avem coliziune
			adaugaMasinaInLista(&(hash.vector[pozitie]), masina);
		}
		else {
			adaugaMasinaInLista(&(hash.vector[pozitie]), masina);
		}
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) {
	HashTable ht = initializareHashTable(dimensiune);
	FILE* file = fopen(numeFisier,"r");
	while (!feof(file)) {
		Masina m = citireMasinaDinFisier(file);
		inserareMasinaInTabela(ht, m);
	}
	fclose(file);
	return ht;
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		printf("\nCluster %d:\n", (i + 1));
		afisareListaMasini(ht.vector[i]);
	}
}

void stergeLista(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.model != NULL) {
			free(p->info.model);
		}
		if (p->info.numeSofer) {
			free(p->info.numeSofer);
		}
		free(p);
	}
}

void dezalocareTabelaDeMasini(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		stergeLista(&(ht->vector[i]));
	}
	free(ht->vector);
	ht->vector = NULL;
	ht->dim = 0;
}

float calculeazaPretMediuLista(Nod* cap) {
	if (cap) {
		float suma = 0;
		int contor = 0;
		while (cap) {
			suma += cap->info.pret;
			contor++;
			cap = cap->next;
		}
		return suma / contor;
	}
	return 0;
}

float** calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	*nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i] != NULL) {
			(*nrClustere)++;
		}
	}
	float** medii = (float**)malloc(sizeof(float*) * 2);
	medii[0] = (float*)malloc(sizeof(float) * (*nrClustere));
	medii[1] = (float*)malloc(sizeof(float) * (*nrClustere));

	int index = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i] != NULL) {
			medii[0][index] = i;
			medii[1][index] = calculeazaPretMediuLista(ht.vector[i]);
			index++;
		}
	}
	return medii;
}

Masina getMasinaByIdDinLista(Nod* cap, int idCautat) {
	while (cap) {
		if (cap->info.id == idCautat) {
			return cap->info; //shallow copy
		}
		else {
			cap = cap->next;
		}
	}
	Masina m;
	m.id = -1;
	return m;
}
Masina getMasinaDupaID(HashTable ht, int idCautat) {
	Masina m;
	for (int i = 0; i < ht.dim; i++) {
		m = getMasinaByIdDinLista(ht.vector[i], idCautat);
		if (m.id == idCautat) {
			return m;
		}
	}
	return m;
}

Masina getMasinaDupaSoferSiID(HashTable ht, const char* numeSofer, int idCautat) {
	int pozitie = calculeazaHash(numeSofer, idCautat, ht.dim);
	if (pozitie >= 0 && pozitie < ht.dim) {
		return getMasinaByIdDinLista(ht.vector[pozitie], idCautat);
	}
	else {
		return getMasinaByIdDinLista(NULL, idCautat);
	}
}

//poate fi imbunatatita
void afisarePreturiMedii(float** matrice, int nrColoane, int nrLinii) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			printf("%.2f ", matrice[i][j]);
		}
		printf("\n");
	}
}
void afisarePreturiMediiImbunatatita(float** matrice, int nrColoane, int nrLinii) {
		for (int j = 0; j < nrColoane; j++) {
			printf("     %d ", (int)matrice[0][j]);
		}
		printf("\n");
		for (int j = 0; j < nrColoane; j++) {
			printf("%.2f ", matrice[1][j]);
		}
}

void dezalocareMatrice(float*** matrice, int* nrLinii, int* nrColoane) {
	for (int i = 0; i < *nrLinii; i++) {
		free((*matrice)[i]);
	}
	free(*matrice);
	*matrice = NULL;
	*nrLinii = 0;
	*nrColoane = 0;
}


int main() {
	HashTable ht = citireMasiniDinFisier("masini.txt", 6);
	afisareTabelaDeMasini(ht);

	Masina m = getMasinaDupaID(ht, 6);
	if (m.id != -1) {
		printf("Masina cautat dupa id:\n");
		afisareMasina(m);
	}
	Masina mSofer = getMasinaDupaSoferSiID(ht, "Ionescu", 9);
	if (m.id != -1) {
		printf("\nMasina cautat dupa sofer si ID:\n");
		afisareMasina(mSofer);
	}
	printf("Preturi medii pe clustere:\n");
	int nrClustere = 0;
	float** matrice = calculeazaPreturiMediiPerClustere(ht, &nrClustere);
	int nrLinii = 2;
	afisarePreturiMediiImbunatatita(matrice, nrClustere, 2);

	dezalocareTabelaDeMasini(&ht);
	dezalocareMatrice(&matrice, &nrLinii, &nrClustere);

	return 0;
}