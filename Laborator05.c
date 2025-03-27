#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina masina;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

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

void afisareListaMasiniDeLaInceput(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareMasina(p->masina);
		p = p->next;
	}
}

void afisareListaMasiniDeLaSfarsit(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareMasina(p->masina);
		p = p->prev;
	}
}
void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua; //shallow copy
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last != NULL) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;
}

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua; //shallow copy
	nou->next = lista->first;
	nou->prev = NULL;
	if (lista->first != NULL) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	while (!feof(f)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->masina.model) {
			free(aux->masina.model);
		}
		if (aux->masina.numeSofer) {
			free(aux->masina.numeSofer);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

float calculeazaPretMediu(ListaDubla lista) {
	if (lista.nrNoduri>0) {
		float suma = 0;
		Nod* p = lista.first;
		while (p) {
			suma += p->masina.pret;
			p = p->next;
		}
		return suma/lista.nrNoduri;
	}
	return 0;
}

void stergeMasinaDupaID(ListaDubla* lista, int id) {
	if (lista->first == NULL) {
		return;
	}
	Nod* p = lista->first;
	while (p!=NULL && p->masina.id != id) {
		p = p->next;
	}
	if (p==NULL) {
		return;
	}
	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first) {
			lista->first->prev = NULL;
		}
	}
	else {
		p->prev->next = p->next;
	}
	if (p->next != NULL) {
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;
	}
	if (p->masina.model) {
		free(p->masina.model);
	}
	if (p->masina.numeSofer) {
		free(p->masina.numeSofer);
	}
	free(p);
	lista->nrNoduri--;
}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {
	if (lista.first) {
		Nod* max = lista.first;
		Nod* p = lista.first->next;
		while (p) {
			if (p->masina.pret > max->masina.pret) {
				max = p;
			}
			p = p->next;
		}
		char* nume = (char*)malloc(strlen(max->masina.numeSofer) + 1);
		strcpy_s(nume, strlen(max->masina.numeSofer) + 1, max->masina.numeSofer);
		return nume;
	}
	else {
		return NULL;
	}
}

int main() {
	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(lista);
	printf("----------------------------\n");
	stergeMasinaDupaID(&lista, 10);
	stergeMasinaDupaID(&lista, 9);
	stergeMasinaDupaID(&lista, 8);
	stergeMasinaDupaID(&lista, 7);
	stergeMasinaDupaID(&lista, 6);
	stergeMasinaDupaID(&lista, 5);
	stergeMasinaDupaID(&lista, 4);
	stergeMasinaDupaID(&lista, 3);
	stergeMasinaDupaID(&lista, 2);
	stergeMasinaDupaID(&lista, 1);
	afisareListaMasiniDeLaSfarsit(lista);

	printf("\nPretul mediu al masinilor este %.2f.\n", calculeazaPretMediu(lista));

	char* numeSofer = getNumeSoferMasinaScumpa(lista);
	printf("Soferul cu cea mai scumpa masina este: %s\n", numeSofer);
	if (numeSofer) {
		free(numeSofer);
	}
	dezalocareLDMasini(&lista);
	return 0;
}