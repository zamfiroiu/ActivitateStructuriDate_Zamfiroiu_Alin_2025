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
//struct Nod
//{
//	Masina info;
//	struct Nod* dr;
//	struct Nod* st;
//};
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
//	m1.pret= atof(strtok(NULL, sep));
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
//
//void adaugaMasinaInArbore(Nod** nod, Masina masinaNoua) {
//	if ((*nod) != NULL)
//	{
//		if (masinaNoua.id > (*nod)->info.id)
//		{
//			adaugaMasinaInArbore(&(*nod)->dr, masinaNoua);
//		}
//		else if (masinaNoua.id < (*nod)->info.id)
//		{
//			adaugaMasinaInArbore(&(*nod)->st, masinaNoua);
//		}
//	}
//	else
//	{
//		(*nod) = (Nod*)malloc(sizeof(Nod));
//		(*nod)->info = masinaNoua;
//		(*nod)->st = NULL;
//		(*nod)->dr = NULL;
//	}
//}
//
//void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* f = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	while (!feof(f))
//	{
//		adaugaMasinaInArbore(&nod, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return nod;
//}
//
//void afisareMasiniDinArbore(/*arbore de masini*/) {
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//}
//
//void afisarePreOrdineRSD(Nod* radacina) {
//	if (radacina != NULL)
//	{
//		afisareMasina(radacina->info);
//		afisarePreOrdineRSD(radacina->st);
//		afisarePreOrdineRSD(radacina->dr);
//	}
//}
//
//
//void afisareInOrdineSRD(Nod* radacina) {
//	if (radacina != NULL)
//	{
//		afisareInOrdineSRD(radacina->st);
//		afisareMasina(radacina->info);
//		afisareInOrdineSRD(radacina->dr);
//	}
//}
//
////void afisareInOrdineSRD(Nod* radacina) {
////	if (radacina != NULL)
////	{
////		afisareInOrdineSRD(radacina->st);
////		afisareMasina(radacina->info);
////		afisareInOrdineSRD(radacina->dr);
////	}
////}
//
//void dezalocareArboreDeMasini(/*arbore de masini*/) {
//	//sunt dezalocate toate masinile si arborele de elemente
//}
//
//Masina getMasinaByID(Nod *radacina, int id) {
//	Masina m;
//	m.id = -1;
//	if (radacina != NULL) {
//		if (id < radacina->info.id) {
//			return getMasinaByID(radacina->st, id);
//		}
//		else {
//			if (id > radacina->info.id) {
//				return getMasinaByID(radacina->dr, id);
//			}
//			else {
//				return radacina->info;
//			}
//		}
//
//	}
//	return m;
//}
//
//int determinaNumarNoduri(Nod * radacina) {
//	//calculeaza numarul total de noduri din arborele binar de cautare
//	int nrNoduri = 0;
//	if (radacina != NULL) {
//		nrNoduri += determinaNumarNoduri(radacina->st);
//		nrNoduri += determinaNumarNoduri(radacina->dr);
//		nrNoduri += 1;
//	}
//	return nrNoduri;
//}
//
//int calculeazaInaltimeArbore(/*arbore de masini*/) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	return 0;
//}
//
//float calculeazaPretTotal(/*arbore de masini*/) {
//	//calculeaza pretul tuturor masinilor din arbore.
//	return 0;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	return 0;
//}
//
//int main() {
//
//	Nod* rad = citireArboreDeMasiniDinFisier("masini_arbore.txt");
//	afisarePreOrdineRSD(rad);
//	printf("Masinile\n");
//	afisareInOrdineSRD(rad);
//	printf("\nMasina gasita: ");
//	afisareMasina(getMasinaByID(rad, 6));
//	printf("\nnrnoduri:%d", determinaNumarNoduri(rad));
//
//	//dezalocare
//	return 0;
//}