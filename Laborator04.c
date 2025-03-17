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
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//
//typedef struct Nod Nod;
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
//void afisareListaMasini(Nod* cap) {
//	while (cap != NULL) {
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod* *cap, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua; 
//	nou->next = NULL;
//	if (*cap) {
//		Nod* p = *cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//	else {
//		*cap = nou;
//	}
//}
//
//void adaugaLaInceputInLista(Nod* *cap, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	Nod* cap = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	if (f) {
//		while (!feof(f)) {
//			//creem lista cu inserare la sfarsit
//			adaugaMasinaInLista(&cap, citireMasinaDinFisier(f));			
//		}
//	}
//	fclose(f);
//	return cap;
//}
//
//void dezalocareListaMasini(Nod* *cap) {
//	while(*cap){
//		Nod* p = *cap;
//		(*cap) = p->next;
//		if (p->info.model) {
//			free(p->info.model);
//		}
//		if (p->info.numeSofer) {
//			free(p->info.numeSofer);
//		}
//		free(p);
//	}
//}
//
//float calculeazaPretMediu(/*lista de masini*/) {
//	//calculeaza pretul mediu al masinilor din lista.
//	return 0;
//}
//
//void stergeMasiniDinSeria(/*lista masini*/ const char* serieCautata) {
//	//sterge toate masinile din lista care au seria primita ca parametru.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//}
//
//float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	return 0;
//}
//
//int main() {
//	Nod* cap = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(cap);
//	dezalocareListaMasini(&cap);
//	return 0;
//}