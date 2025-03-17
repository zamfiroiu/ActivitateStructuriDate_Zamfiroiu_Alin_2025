//#include<stdio.h>
//#include<stdlib.h>
//
//struct Masina {
//	int id;
//	int nrKm;
//	char* model;
//	float pret;
//	char tipMotor;
//};
//
//struct Masina initializare(int id, int nrKm, const char* model, float pret, char tipMotor) {
//	struct Masina m;
//	m.id = id;
//	m.nrKm = nrKm;
//	m.model = (char*)malloc(strlen(model) + 1);
//	strcpy(m.model, model);
//	m.pret = pret;
//	m.tipMotor = tipMotor;
//	return m;
//}
//
//void afisare(struct Masina m) {
//	printf("Id: %d, nr km: %d, model: %s, pret: %f, tip motor: %c", m.id, m.nrKm, m.model, m.pret, m.tipMotor);
//
//}
//
//void modifica_Pret(struct Masina* m, float pretNou) {
//	if (pretNou > 0)
//		m->pret = pretNou;
//
//}
//
//void dezalocare(struct Masina* m) {
//	free(m->model);
//	m->model = NULL;
//}
//
//int main() {
//	struct Masina masina;
//	masina = initializare(1, 50000, "Logan", 3000.50, 'B'); // 'B'
//	afisare(masina);
//	modifica_Pret(&masina, 1000.50);
//	afisare(masina);
//	dezalocare(&masina);
//	afisare(masina);
//	return 0;
//}