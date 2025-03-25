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

typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
};

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

void afisareListaMasini(Nod* lista) {
	while (lista) {
		afisareMasina(lista->info);
		lista = lista->next;
	}
}

void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	if ((*lista) == NULL) {
		(*lista) = nou;
	}
	else {
		Nod* temp = *lista;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void adaugaLaInceputInLista(Nod** lista, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *lista;
	*lista = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(file)) {
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareListaMasini(Nod** lista) {
	while (*lista)
	{
		Nod* p = (*lista);
		(*lista) = (*lista)->next;

		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
	}
}

float calculeazaPretMediu(Nod* lista) {
	float s = 0;
	int k = 0;

	while (lista)
	{
		s += lista->info.pret;
		k++;
		lista = lista->next;
	}

	return (k>0) ? s/k : 0;
}

void stergeMasiniDinSeria(Nod** lista, char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	while ((*lista) != NULL && (*lista)->info.serie == serieCautata) {
		Nod* temp = (*lista);
		(*lista) = temp->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);

	}
	Nod* p = (*lista);
	while (p != NULL) {
		while (p->next && p->next->info.serie != serieCautata) {
			p = p->next;

		}
		if (p->next != NULL) {
			Nod* temp = p->next;
			p->next = temp->next;
			free(temp->info.model);
			free(temp->info.numeSofer);
			free(temp);
		}
		else {
			p = p->next;
		}
	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	float suma = 0;

	while (lista)
	{
		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
		{
			suma += lista->info.pret;
		}
		lista = lista->next;
	}
	return suma;
}

int main() {

	Nod* masini = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(masini);
	printf("----------PRET MEDIU---------\n");
	printf("%.2f", calculeazaPretMediu(masini));
	printf("\n----------SUMA MASINI SOFER--------- \n");
	printf("Suma masinilor lui Ionescu: %.2f", calculeazaPretulMasinilorUnuiSofer(masini, "Ionescu"));
	printf("Sterge seria A:\n");
	char serieCautata = 'A';
	stergeMasiniDinSeria(&masini, serieCautata);
	stergeMasiniDinSeria(&masini, 'B');
	afisareListaMasini(masini);
	dezalocareListaMasini(&masini);

	

	return 0;
}