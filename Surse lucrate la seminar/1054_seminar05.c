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
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* inceput;
	Nod* final;
};
typedef struct ListaDubla Lista;

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

void afisareListaMasiniDeLaInceput(Lista lis) {
	Nod* p = lis.inceput;
	while (p)
	{
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaMasiniDeLaFinal(Lista lis) {
	Nod* p = lis.final;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(Lista* lis, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = lis->final;
	if (lis->final != NULL)
	{
		lis->final->next = nou;
	}
	else
	{
		lis->inceput = nou;
	}
	lis->final = nou;
}

void adaugaLaInceputInLista(Lista* lis, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = lis->inceput;
	nou->prev = NULL;
	if (lis->inceput) {
		lis->inceput->prev = nou;
	}
	else {
		lis->final = nou;
	}
	lis->inceput = nou;
}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista lis;
	lis.final = NULL;
	lis.inceput = NULL;
	while (!feof(f)) {
		Masina m;
		m = citireMasinaDinFisier(f);
		adaugaLaInceputInLista(&lis, m);
	}
	fclose(f);
	return lis;
}

void dezalocareLDMasini(Lista* lis) {
	while (lis->inceput)
	{
		if (lis->inceput->info.numeSofer)
			free(lis->inceput->info.numeSofer);
		if (lis->inceput->info.model)
			free(lis->inceput->info.model);
		Nod* p = lis->inceput;
		lis->inceput = p->next;
		free(p);
	}
	lis->final = NULL;
}

float calculeazaPretMediu(Lista lis) {
	float suma = 0;
	int contor = 0;
	Nod* temp = lis.inceput;
	while (temp) {
		suma += temp->info.pret;
		contor++;
		temp = temp->next;
	}
	return (contor > 0) ? suma/contor : 0;
}

void stergeMasinaDupaID(Lista* lis, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	Nod* p = lis->inceput;
	while (p && p->info.id != id) {
		p = p->next;
	}
	if (p) {
		if (p->prev) {
			p->prev->next = p->next;
			if (p->next) {
				p->next->prev = p->prev;
			}
			else {
				lis->final = p->prev;
			}
		}
		else {
			lis->inceput = p->next;
			if (p->next) {
				p->next->prev = NULL;
			}
			else {
				lis->final = NULL;
			}
		}
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
	}
	
}

char* getNumeSoferMasinaScumpa(Lista lis) {
	Nod* p = lis.inceput;
	Nod* maxPretMasina = p;
	if (lis.inceput) {
		while (p) {
			if (p->info.pret > maxPretMasina->info.pret) {
				maxPretMasina = p;
			}
			p = p->next;
		}
		char* nume = malloc(strlen(maxPretMasina->info.numeSofer) + 1);
		strcpy_s(nume, strlen(maxPretMasina->info.numeSofer) + 1, maxPretMasina->info.numeSofer);
		return nume;
	}
	return NULL;
}

int main() {
	Lista lis;
	lis=citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(lis);
	printf("\n");
	stergeMasinaDupaID(&lis,10);
	afisareListaMasiniDeLaFinal(lis);
	printf("\n");
	float medie = calculeazaPretMediu(lis);
	printf("%.2f", medie);
	char* nume = getNumeSoferMasinaScumpa(lis);
	printf("%s \n", nume);
	free(nume);
	

	dezalocareLDMasini(&lis);
	return 0;
}