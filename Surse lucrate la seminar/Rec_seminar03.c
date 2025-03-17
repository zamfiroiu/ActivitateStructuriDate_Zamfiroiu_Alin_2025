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
//void afisareMasina(Masina masina) {
//
//	printf("\nId: %d\n",masina.id);
//	printf("Numarul usilor: %d\n",masina.nrUsi);
//	printf("Pret: %.2f\n",masina.pret);
//	printf("Model: %s\n",masina.model);
//	printf("Nume sofer: %s\n",masina.numeSofer);
//	printf("Serie: %c\n",masina.serie);
//
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++)
//	{
//		afisareMasina(masini[i]);
//	}
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//	Masina* vector = malloc(sizeof(Masina) * ((*nrMasini) + 1));
//	for (int i = 0; i < (*nrMasini); i++)
//	{
//		vector[i] = (*masini)[i];
//	}
//	vector[(*nrMasini)] = masinaNoua;
//	vector[(*nrMasini)].model = malloc(sizeof(char) * (strlen(masinaNoua.model) + 1));
//	strcpy_s(vector[(*nrMasini)].model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//	vector[(*nrMasini)].numeSofer = malloc(sizeof(char) * (strlen(masinaNoua.numeSofer) + 1));
//	strcpy_s(vector[(*nrMasini)].numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//	(*nrMasini)++;
//	free(*masini);
//	(*masini) = vector;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//	//functia citeste o masina dintr-un strceam deja deschis
//	//masina citita este returnata;
//	Masina masina;
//	char separator[] = ",\n";
//	char buffer[100];
//	fgets(buffer, 100, file);
//
//
//	char* token = strtok(buffer, separator);
//	masina.id = atoi(token);
//
//	char* token1 = strtok(NULL, separator);
//	masina.nrUsi = atoi(token1);
//
//	char* token2 = strtok(NULL, separator);
//	masina.pret = atof(token2);
//
//	char* token3 = strtok(NULL, separator);
//	masina.model = malloc(sizeof(char) * (strlen(token3)+1));
//	strcpy_s(masina.model, strlen(token3) + 1, token3);
//
//	char* token4 = strtok(NULL, separator);
//	masina.numeSofer = malloc(sizeof(char) * (strlen(token4) + 1));
//	strcpy_s(masina.numeSofer, strlen(token4) + 1, token4);
//
//	char* token5 = strtok(NULL, separator);
//	masina.serie = token5[0];
//
//	return masina;
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	FILE* f = fopen(numeFisier, "r");
//	Masina* masini = NULL;
//	while (!feof(f)) {
//		Masina m = citireMasinaFisier(f);
//		adaugaMasinaInVector(&masini, nrMasiniCitite, m);
//		free(m.model);
//		free(m.numeSofer);
//	}
//	fclose(f);
//	return masini;
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//	for (int i = 0; i < *nrMasini; i++) {
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrMasini = 0;	
//}
//
//int main() {
//	Masina* masini;
//	int nrMasini = 0;
//	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//	afisareVectorMasini(masini, nrMasini);
//	dezalocareVectorMasini(&masini, &nrMasini);
//	return 0;
//}