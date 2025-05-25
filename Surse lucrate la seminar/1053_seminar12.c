//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//typedef struct NodListaPrincipala NodListaPrincipala;
//typedef struct NodListaSecundara  NodListaSecundara;
//
//struct NodListaPrincipala {
//	NodListaPrincipala* next;
//	NodListaSecundara* vecini;
//	Masina info;
//
//};
//
//struct NodListaSecundara {
//	NodListaPrincipala* info;
//	NodListaSecundara* next;
//};
//
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
////1. 
//// structuri necesare
////dorim stocarea unui graf intr-o lista de liste
////astfel avem nod ListaPrincipala si NodListaSecundara
//
//
//
////2.
////functii de inserare in liste
////si in principala si in secundara
//NodListaPrincipala* inserareListaPrincipala(NodListaPrincipala* cap, Masina info)
//{
//	NodListaPrincipala* nou = (NodListaPrincipala*)malloc(sizeof(NodListaPrincipala));
//	nou->info = info;
//	nou->vecini = NULL;
//	nou->next = NULL;
//
//	if (!cap) return nou;
//
//	NodListaPrincipala* p = cap;
//	while (p->next)p = p->next;
//	p->next = nou;
//	return cap;
//}
//
//NodListaSecundara* inserareListaSecundara(NodListaSecundara* cap, NodListaPrincipala* info)
//{
//	NodListaSecundara* nou = (NodListaSecundara*)malloc(sizeof(NodListaSecundara));
//	nou->info = info;
//	nou->next = NULL;
//
//	nou->next = cap;
//	return nou;
//
//}
////3.
////functie de cautarea in lista principala dupa ID
//NodListaPrincipala* cautaNodDupaID(NodListaPrincipala* listaPrincipala, int id) {
//	while (listaPrincipala && listaPrincipala->info.id != id) {
//		listaPrincipala = listaPrincipala->next;
//	}
//	return listaPrincipala;
//	
//}
//
////4.
////inserare muchie
//void inserareMuchie(NodListaPrincipala* listaPrincipala, int idStart, int idStop) {
//	NodListaPrincipala* nodStart = cautaNodDupaID(listaPrincipala, idStart);
//	NodListaPrincipala* nodStop = cautaNodDupaID(listaPrincipala, idStop);
//	if (nodStart && nodStop) {
//		nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
//		nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
//	}
//}
//
//
//NodListaPrincipala* citireNoduriMasiniDinFisier(const char* numeFisier) {
//	NodListaPrincipala* listaPrincipala = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		inserareListaPrincipala(listaPrincipala, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return listaPrincipala;
//}
//
//void citireMuchiiDinFisier(NodListaPrincipala* listaPrincipala, const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		int idStart;
//		int idStop;
//		fscanf(f, "%d %d", &idStart, &idStop);
//		inserareMuchie(listaPrincipala, idStart, idStop);
//	}
//	fclose(f);
//}
//
//void stergereListaSecundara(NodListaSecundara** cap) {
//	NodListaSecundara* aux;
//	while ((*cap)) {
//		aux = (*cap)->next;
//		free((*cap));
//		(*cap) = aux;
//	}
//}
//
//void dezalocareNoduriGraf(NodListaPrincipala** listaPrincipala) {
//	NodListaPrincipala* aux;
//	while ((*listaPrincipala)) {
//		aux = (*listaPrincipala)->next;
//		stergereListaSecundara(&(*listaPrincipala)->vecini);
//		if ((*listaPrincipala)->info.model) {
//			free((*listaPrincipala)->info.model);
//		}
//		if ((*listaPrincipala)->info.numeSofer) {
//			free((*listaPrincipala)->info.numeSofer);
//		}
//		free(*listaPrincipala);
//		(*listaPrincipala) = aux;
//	}
//}
//
//int main() {
//	NodListaPrincipala* graf = citireNoduriMasiniDinFisier("masini.txt");
//	citireMuchiiDinFisier(graf, "muchii.txt");
//	dezalocareNoduriGraf(&graf);
//	return 0;
//}