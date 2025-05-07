//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
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
//	Masina* vector;
//	int nrMasini;
//	int lungime;
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
//	
//	Heap h;
//	h.lungime = lungime;
//	h.nrMasini = 0;
//	h.vector = (Masina*)malloc(sizeof(Masina) * lungime);
//	return h;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
//	int pozS = 2 * pozitieNod + 1;
//	int pozD = 2 * pozitieNod + 2;
//	int pozMax = pozitieNod;
//	if (pozS<heap.nrMasini && heap.vector[pozS].id > heap.vector[pozMax].id)
//		pozMax = pozS;
//	if (pozD< heap.nrMasini && heap.vector[pozD].id > heap.vector[pozMax].id)
//		pozMax = pozD;
//	if (pozMax != pozitieNod)
//	{
//		Masina aux = heap.vector[pozMax];
//		heap.vector[pozMax] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//		if (pozMax < (heap.nrMasini - 2) / 2)    // 2*pozMax+1 <= heap.nrMasini-1
//		{
//			filtreazaHeap(heap, pozMax);
//		}
//
//	}
//
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
//	
//	Heap h = initializareHeap(10);
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f))
//	{
//		
//		h.vector[h.nrMasini] = citireMasinaDinFisier(f);
//		h.nrMasini++;
//	}
//	fclose(f);
//	for (int i = (h.nrMasini - 2) / 2; i >= 0; i--)
//	{
//		filtreazaHeap(h, i);
//	}
//	return h;
//}
//
//void afisareHeap(Heap heap) {
//	
//	if (heap.vector)
//	{
//		for (int i = 0; i < heap.nrMasini; i++)
//		{
//			afisareMasina(heap.vector[i]);
//		}
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	//afiseaza elementele ascunse din heap
//	for (int i = heap.nrMasini; i < heap.lungime; i++)
//	{
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//Masina extrageMasina(Heap* heap) {
//	if (heap->lungime > 0)
//	{
//		Masina aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrMasini - 1];
//		heap->vector[heap->nrMasini - 1] = aux;
//
//		heap->nrMasini--;
//
//		for (int i = (heap->lungime - 2) / 2; i >= 0; i--)
//		{
//			filtreazaHeap((*heap), i);
//		}
//		return aux;
//	}
//	Masina m;
//	m.numeSofer = NULL;
//	m.model = NULL;
//	return m;
//}
//
////o lista cu masinile din heap care au id-ul > ca un id parametru
////masinile vor fi extrase din heap
//
//struct Nod
//{
//	Masina info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//void inserareInLista(Nod** lista, Masina m)
//{
//	Nod* nou = malloc(sizeof(Nod));
//	nou->info = m;
//	nou->next = (*lista);
//
//	(*lista) = nou;
//}
//
//void afisareLista(Nod* lista)
//{
//	if (lista)
//	{
//		Nod* aux = lista;
//		while (aux)
//		{
//			afisareMasina(aux->info);
//			aux = aux->next;
//		}
//	}
//}
//
//Nod* masiniCuIDMare(Heap* heap, int idMinim)
//{
//	Nod* lista = NULL;
//
//	while (heap->vector[0].id >= idMinim)
//	{
//		Masina m = extrageMasina(heap);
//		inserareInLista(&lista, m);
//	}
//
//	return lista;
//}
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++)
//	{
//		free(heap->vector[i].numeSofer);
//		free(heap->vector[i].model);
//	}
//	free(heap->vector);
//	heap->lungime = 0;
//	heap->nrMasini = 0;
//	heap->vector = NULL;
//}
//
//int main() {
//
//	Heap h = citireHeapDeMasiniDinFisier("masini.txt");
//	printf("Elementele sunt : \n");
//	afisareHeap(h);
//
//	//Masina m = extrageMasina(&h);
//	//printf("\nPrima masina extrasa: \n");
//	//afisareMasina(m);
//	//extrageMasina(&h);
//	//extrageMasina(&h);
//	//extrageMasina(&h);
//	//extrageMasina(&h);
//
//	Nod* lista = masiniCuIDMare(&h, 4);
//	printf("\nLISTA:\n");
//	afisareLista(lista);
//
//	printf("\nElementele ascunse sunt: \n");
//	afiseazaHeapAscuns(h);
//
//	dezalocareHeap(&h);
//	while (lista)
//	{
//		Nod* aux = lista;
//		lista = aux->next;
//		free(aux);
//	}
//
//	return 0;
//}