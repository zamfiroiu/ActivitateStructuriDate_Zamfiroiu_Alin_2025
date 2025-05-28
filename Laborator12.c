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

typedef struct NodSecundar NodSecundar;
typedef struct NodPrincipal NodPrincipal;

struct NodPrincipal {
	Masina info;
	NodSecundar* vecini;
	struct NodPrincipal* next;
};

struct NodSecundar {
	NodPrincipal* nodInfo;
	NodSecundar* next;
};

void inserareListaPrincipala(NodPrincipal** cap, Masina m) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = NULL;
	nou->vecini = NULL;
	if (*cap) {
		NodPrincipal* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareListaSecundara(NodSecundar** cap, NodPrincipal* nodInfo) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nodInfo = nodInfo;
	nou->next = *cap;
	*cap = nou;
}

NodPrincipal* cautaNodDupaID(NodPrincipal* cap, int idCautat) {
	while (cap && cap->info.id != idCautat) {
		cap = cap->next;
	}
	return cap;
}

void inserareMuchie(NodPrincipal* graf, int idStart, int idStop) {
	NodPrincipal* nodStart = cautaNodDupaID(graf, idStart);
	NodPrincipal* nodStop = cautaNodDupaID(graf, idStop);
	if (nodStart && nodStop) {
		inserareListaSecundara(&(nodStart->vecini), nodStop);
		inserareListaSecundara(&(nodStop->vecini), nodStart);
	}
}

NodPrincipal* citireNoduriMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	NodPrincipal* graf = NULL;
	if (f) {
		while (!feof(f)) {
			inserareListaPrincipala(&graf, citireMasinaDinFisier(f));
		}
		fclose(f);
	}
	return graf;
}

void citireMuchiiDinFisier(NodPrincipal*graf, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	while (f && !feof(f)) {
		int idStart=0;
		int idStop=0;
		fscanf(f, "%d %d", &idStart, &idStop);
		inserareMuchie(graf, idStart, idStop);
	}
	fclose(f);
}

void dezalocareListaSecundara(NodSecundar** cap) {
	while (*cap) {
		NodSecundar* temp = (*cap);
		(*cap) = (*cap)->next;
		free(temp);
	}
}

void dezalocareNoduriGraf(NodPrincipal** graf) {
	while (*graf) {
		NodPrincipal* temp = (*graf);
		(*graf) = (*graf)->next;
		dezalocareListaSecundara(&(temp->vecini));
		if (temp->info.model) {
			free(temp->info.model);
		}
		if (temp->info.numeSofer) {
			free(temp->info.numeSofer);
		}
		free(temp);
	}
}

//Parcurgere in adancime

typedef struct NodStiva NodStiva;
struct NodStiva {
	int id;
	NodStiva* next;
};

void push(NodStiva** cap, int id) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->id = id;
	nou->next = *cap;
	*cap = nou;
}

int pop(NodStiva** cap) {
	if (*cap) {
		NodStiva* temp = *cap;
		*cap = (*cap)->next;
		int id = temp->id;
		free(temp);
		return id;
	}
	else {
		return -1;
	}
}

int calculeazaNrNoduriGraf(NodPrincipal* listaPrincipala) {
	int count = 0;
	while (listaPrincipala) {
		count++;
		listaPrincipala = listaPrincipala->next;
	}
	return count;
}

void afisareGrafInAdancime(NodPrincipal* graf, int idPlecare) {
	int nrNoduri = calculeazaNrNoduriGraf(graf);
	unsigned char* vizitate = (unsigned char*)malloc(sizeof(unsigned char) * nrNoduri);
	for (int i = 0;i<nrNoduri;i++){
		vizitate[i] = 0;
	}
	NodStiva* stiva = NULL;
	vizitate[idPlecare - 1] = 1;
	push(&stiva, idPlecare);
	while (stiva) {
		int idNod = pop(&stiva);
		NodPrincipal* nodCurent = cautaNodDupaID(graf, idNod);
		afisareMasina(nodCurent->info);
		NodSecundar* p = nodCurent->vecini;
		while (p) {
			if (vizitate[p->nodInfo->info.id - 1] == 0) {
				push(&stiva, p->nodInfo->info.id);
				vizitate[p->nodInfo->info.id - 1] = 1;
			}
			p = p->next;
		}
	}
}


//Parcurgere in latime
typedef struct NodCoada NodCoada;
struct NodCoada {
	int id;
	NodCoada* next;
};

void enqueue(NodCoada** cap, int id) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->id = id;
	nou->next = NULL;
	if (*cap) {
		NodCoada* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

int dequeue(NodCoada** cap) {
	if (*cap) {
		NodCoada* temp = *cap;
		*cap = (*cap)->next;
		int id = temp->id;
		free(temp);
		return id;
	}
	else {
		return -1;
	}
}

void afisareGrafInLatime(NodPrincipal* graf, int idPlecare) {
	int nrNoduri = calculeazaNrNoduriGraf(graf);
	unsigned char* vizitate = (unsigned char*)malloc(sizeof(unsigned char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	NodCoada* coada = NULL;
	vizitate[idPlecare - 1] = 1;
	enqueue(&coada, idPlecare);
	while (coada) {
		int idNod = dequeue(&coada);
		NodPrincipal* nodCurent = cautaNodDupaID(graf, idNod);
		afisareMasina(nodCurent->info);
		NodSecundar* p = nodCurent->vecini;
		while (p) {
			if (vizitate[p->nodInfo->info.id - 1] == 0) {
				enqueue(&coada, p->nodInfo->info.id);
				vizitate[p->nodInfo->info.id - 1] = 1;
			}
			p = p->next;
		}
	}
}


int main() {
	NodPrincipal* graf = NULL;
	graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");

	afisareGrafInLatime(graf, 1);

	dezalocareNoduriGraf(&graf);

	return 0;
}