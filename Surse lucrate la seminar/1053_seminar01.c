//#include<stdio.h>
//#include<stdlib.h>
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
//	m.marca = (char*)malloc(strlen(marca) + 1);
//	strcpy_s(m.marca, strlen(marca) + 1, marca);
//	return m;
//}
//
//void afisare(struct Masina m) {
//	printf("\n Id masina: %d\n Nr locuri: %d\n Capacitate: %.2f\n Marca: %s\n Euro%c", m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare); 
//}
//
//void modifica_NrLocuri(struct Masina* m, int nrNou) {
//	if (nrNou > 0) {
//		m->nrLocuri = nrNou;
//	} 
//}
//
//void dezalocare(struct Masina* m) {
//	free(m->marca);
// 	(*m).marca = NULL;
//	
//}
//
//int main() {
//	struct Masina masina = initializare(1, 5, "Dacia", 1.5, '4'); // "4" '4'
//	afisare(masina);
//	modifica_NrLocuri(&masina, 6);
//	afisare(masina);
//	dezalocare(&masina);
//	afisare(masina);
//	printf("\n%d", sizeof(struct Masina*));
//	printf("\n%d", sizeof(masina));
//
//
//
//	return 0;
//}