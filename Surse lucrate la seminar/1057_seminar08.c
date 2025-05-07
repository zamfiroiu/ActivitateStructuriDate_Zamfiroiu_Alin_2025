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
////creare structura pentru Heap
////un vector de elemente, lungimea vectorului si numarul de elemente din vector
//struct Heap {
//	int lungime;
//	int nrElemente;
//	Masina* masini;
//};
//typedef struct Heap Heap;
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
//Heap initializareHeap(int lungime) {
//	//initializeaza heap-ul cu 0 elemente 
//	//dar cu o lungime primita ca parametru
//	Heap heap;
//	heap.lungime = lungime;
//	heap.masini = (Masina*)malloc(sizeof(Masina) * lungime);
//	heap.nrElemente = 0;
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	int fiuStanga = pozitieNod * 2 + 1;
//	int fiuDreapta = pozitieNod * 2 + 2;
//	int pozMax = pozitieNod;
//
//	if (fiuStanga < heap.nrElemente && heap.masini[pozMax].id < heap.masini[fiuStanga].id)
//	{
//		pozMax = fiuStanga;
//	}
//	if (fiuDreapta < heap.nrElemente && heap.masini[pozMax].id < heap.masini[fiuDreapta].id)
//	{
//		pozMax = fiuDreapta;
//	}
//	if (pozMax != pozitieNod)
//	{
//		Masina aux;
//		aux = heap.masini[pozMax];
//		heap.masini[pozMax] = heap.masini[pozitieNod];
//		heap.masini[pozitieNod] = aux;
//		if (pozMax <= (heap.nrElemente - 2) / 2)
//		{
//			filtreazaHeap(heap, pozMax);
//		}
//	}
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) { 
//	FILE* f = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(10);
//	while(!feof(f))
//	{
//		Masina m = citireMasinaDinFisier(f);
//		heap.masini[heap.nrElemente] = m;
//		heap.nrElemente++;
//	}
//	for (int i = ((heap.nrElemente - 2) / 2); i >= 0; i--)
//	{
//		filtreazaHeap(heap, i);
//	}
//
//	fclose(f);
//
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrElemente; i++)
//	{
//		afisareMasina(heap.masini[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	for (int i = heap.nrElemente; i < heap.lungime; i++)
//	{
//		afisareMasina(heap.masini[i]);
//	}
//}
//
//Masina extrageMasina(Heap* heap) {
//	//extrage si returneaza masina de pe prima pozitie
//	//elementul extras nu il stergem...doar il ascundem
//	Masina gol = heap->masini[0];
//	heap->masini[0] = heap->masini[heap->nrElemente - 1];
//	heap->masini[heap->nrElemente - 1] = gol;
//	heap->nrElemente--;
//	for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--)
//	{
//		filtreazaHeap(*heap, i);
//	}
//	return gol;
//}
//
//
//void dezalocareHeap(Heap* heap) 
//{
//	for (int i = 0; i < heap->lungime; i++)
//	{
//		free(heap->masini[i].model);
//		free(heap->masini[i].numeSofer);
//	}
//	free(heap->masini);
//	heap->masini = NULL;
//	heap->lungime = 0;
//	heap->nrElemente = 0;
//
//}
//
//int main() {
//	Heap h;
//	h = citireHeapDeMasiniDinFisier("masini.txt");
//	
//	Masina masina;
//	masina = extrageMasina(&h);
//
//	afisareMasina(masina);
//
//
//	dezalocareHeap(&h);
//
//	return 0;
//}