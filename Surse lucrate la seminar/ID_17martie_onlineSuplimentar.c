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
	Masina info;
	struct Nod* prev;
	struct Nod* next;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};
typedef struct ListaDubla LD;

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

void afisareListaMasiniDeLaInceput(LD lista) {
	Nod* p = lista.prim;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}
void afisareListaMasiniDeLaSfarsit(LD lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(LD* lista,  Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;//shallow copy
	nou->prev = NULL;
	nou->next = NULL;
	if (lista->prim != NULL) {
		nou->prev = lista->ultim;
		lista->ultim->next = nou;		
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

//void adaugaLaInceputInLista(/*lista dubla de masini*/ Masina masinaNoua) {
//	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
//}

LD citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lista, m);
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(LD *lista) {
	while (lista->prim->next) {
		lista->prim = lista->prim->next;
		free(lista->prim->prev->info.numeSofer);
		free(lista->prim->prev->info.model);
		free(lista->prim->prev);

	}
	free(lista->ultim->info.numeSofer);
	free(lista->ultim->info.model);
	free(lista->ultim);
	lista->ultim = NULL;
	lista->prim = NULL;
}

float calculeazaPretMediu(LD lista) {
	float suma = 0;
	int contor = 0;
	Nod* p = lista.prim;
	while (p) {
		suma += p->info.pret;
		contor++;
		p = p->next;
	}
	if (contor > 0) {
		return suma / contor;
	}
	return 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}



int main() {

	LD lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(lista);
	printf("\n\n Invers:\n");
	afisareListaMasiniDeLaSfarsit(lista);

	printf("Pretul mediu este: %.2f", calculeazaPretMediu(lista));
	dezalocareLDMasini(&lista);
	return 0;
}