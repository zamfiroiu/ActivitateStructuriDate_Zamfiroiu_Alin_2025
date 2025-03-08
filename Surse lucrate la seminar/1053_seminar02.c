//#include<stdio.h>
//#include<malloc.h>
//
//struct Masina {
//	int id;
//	int nrLocuri;
//	char* marca;
//	float capacitateC;
//	char normaPoluare;
//};
//
//struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char normaPoluare) {
//	struct Masina m;
//	m.id = id;
//	m.nrLocuri = nrLocuri;
//	m.capacitateC = capacitateC;
//	m.normaPoluare = normaPoluare;
//	if (marca == NULL)
//	{
//		m.marca = NULL;
//	}
//	else
//	{
//		m.marca = (char*)malloc(strlen(marca) + 1);
//		strcpy_s(m.marca, strlen(marca) + 1, marca);
//	}
//	return m;
//}
//
//void afisare(struct Masina m) {
//	printf("\n Id masina: %d\n Nr locuri: %d\n Capacitate: %.2f\n Marca: %s\n Euro%c\n", m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare); 
//}
//void afisareVector(struct Masina* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++)
//		afisare(vector[i]);
//}
//
//struct Masina* copiazaPrimeleMasini(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
//	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
//	if (nrElementeCopiate > nrElemente)
//		nrElementeCopiate = nrElemente;
//
//	struct Masina *vectorNou=NULL;
//	vectorNou = (struct Masina*)malloc(nrElementeCopiate * sizeof(struct Masina));
//
//	for (int i = 0; i < nrElementeCopiate; i++)
//		vectorNou[i] = initializare(vector[i].id, vector[i].nrLocuri, vector[i].marca, vector[i].capacitateC, vector[i].normaPoluare);
//
//	return vectorNou;
//}
//
//void dezalocare(struct Masina** vector, int* nrElemente) {
//	
//	for (int i = 0; i < *nrElemente; i++)
//	{
//		free((*vector)[i].marca);
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrElemente = 0;
//
//}
//
//void copiazaMasiniCuCCMare(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
//	
//	 *dimensiune = 0;
//	 for (char i = 0; i < nrElemente; i++)
//	 {
//		 if (prag < vector[i].capacitateC)
//		 {
//			 (*dimensiune)++;
//
//		 }
//	 }
//	 if (*dimensiune > 0)
//	 {
//		 int j = 0;
//		 *vectorNou = (struct Masina*)malloc((*dimensiune) * sizeof(struct Masina));
//		 for (int i = 0; i < nrElemente; i++)
//		 {
//			 if (prag < vector[i].capacitateC)
//			 {
//				 (*vectorNou)[j] = vector[i];
//				 (*vectorNou)[j].marca = malloc(sizeof(char)*(strlen(vector[i].marca)+1));
//				 strcpy_s((*vectorNou)[j].marca, strlen(vector[i].marca) + 1, vector[i].marca);
//				 j++;
//			 }
//		 }
//	 }
//
//
//}
//
//struct Masina getPrimaMasinaDupaMarca(struct Masina* vector, int nrElemente, const char* conditie) {
//	
//	for (int i = 0; i < nrElemente; i++)
//	{
//		if (strcmp(vector[i].marca, conditie) == 0)
//			return vector[i];
//	}
//	return initializare(1, 0, NULL, 0, '0');
//}
//	
//
//
//int main() {
//	struct Masina* vector;
//	int nrElem = 3;
//	vector = (struct Masina*)malloc(nrElem * sizeof(struct Masina));
//
//	vector[0] = initializare(1, 3, "Dacia", 40, '5');
//	vector[1] = initializare(2, 5, "Honda", 30, '6');
//	vector[2] = initializare(3, 4, "Dacia", 50, '3');
//
//	afisareVector(vector, nrElem);
//
//	struct Masina* vectorMasiniCopiate;
//	int nrElemCop = 2;
//
//	printf("\nAfisare elemente copiate:\n");
//	vectorMasiniCopiate = copiazaPrimeleMasini(vector, nrElem, nrElemCop);
//	afisareVector(vectorMasiniCopiate, nrElemCop);
//	dezalocare(&vectorMasiniCopiate, &nrElemCop);
//
//	printf("afisare masini cu capacitate mai mare");
//	copiazaMasiniCuCCMare(vector, nrElem, 10, &vectorMasiniCopiate, &nrElemCop);
//
//	afisareVector(vectorMasiniCopiate, nrElemCop);
//	dezalocare(&vectorMasiniCopiate, &nrElemCop);
//	struct Masina m1 = getPrimaMasinaDupaMarca(vector, nrElem, "Opel");
//
//	printf("masina dupa marca\n");
//	afisare(m1);
//	dezalocare(&vector, &nrElem);
//	return 0;
//}