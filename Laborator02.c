//#include<stdio.h>
//#include<malloc.h>
//
//struct Telefon {
//	int id;
//	int RAM;
//	char* producator;
//	float pret;
//	char serie;
//};
//
//struct Telefon initializare(int id, int ram,const char* producator, float pret, char serie) {
//	struct Telefon t;
//	t.id = id;
//	t.RAM = ram;
//	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
//	strcpy_s(t.producator, strlen(producator) + 1, producator);
//	t.pret = pret;
//	t.serie = serie;
//	return t;
//}
//
//void afisare(struct Telefon t) {
//	if (t.producator != NULL) {
//		printf("%d. Telefonul %s seria %c are %d GB RAM si costa %5.2f RON.\n",
//			t.id, t.producator, t.serie, t.RAM, t.pret);
//	}
//	else {
//		printf("%d. Telefonul din seria %c are %d GB RAM si costa %5.2f RON.\n",
//			t.id, t.serie, t.RAM, t.pret);
//	}
//}
//
//void afisareVector(struct Telefon* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++) {
//		afisare(vector[i]);
//	}
//}
//
//struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
//	struct Telefon*vectorNou=NULL;
//	vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
//	for (int i = 0; i < nrElementeCopiate; i++) {
//		vectorNou[i] = vector[i];
//		vectorNou[i].producator = (char*)malloc(strlen(vector[i].producator) + 1);
//		strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1, vector[i].producator);
//	}
//	return vectorNou;
//}
//
//void dezalocare(struct Telefon** vector, int* nrElemente) {
//	for (int i = 0; i < (*nrElemente); i++) {
//		if ((*vector)[i].producator != NULL) {
//			free((*vector)[i].producator);
//		}
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrElemente = 0;
//}
//
//void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
//	*dimensiune = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].pret >= pretMinim) {
//			(*dimensiune)++;
//		}
//	}
//	if ((*vectorNou) != NULL) {
//		free(*vectorNou);
//	}
//	*vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * (*dimensiune));
//	int k = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].pret >= pretMinim) {
//			(*vectorNou)[k] = vector[i];
//			(*vectorNou)[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
//			strcpy_s((*vectorNou)[k].producator, strlen(vector[i].producator) + 1, vector[i].producator);
//			k++;
//		}
//	}
//}
//
//struct Telefon getPrimulTelefonByProducator(struct Telefon* vector, int nrElemente, const char* producator) {
//	struct Telefon t;
//	t.producator = NULL;
//	for (int i = 0; i < nrElemente; i++) {
//		if (strcmp(vector[i].producator, producator) == 0) {
//			t = vector[i];
//			t.producator = (char*)malloc(strlen(vector[i].producator) + 1);
//			strcpy_s(t.producator, strlen(vector[i].producator) + 1, vector[i].producator);
//			return t;
//		}
//	}
//	return t;
//}
//	
//
//
//int main() {
//
//	struct Telefon* telefoane = NULL;
//	int nrTelefoane = 3;
//	telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
//	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
//	telefoane[1] = initializare(2, 512, "Motorola", 1500, 'M');
//	telefoane[2] = initializare(3, 256, "Apple", 2200, 'A');
//
//	afisareVector(telefoane, nrTelefoane);
//
//	struct Telefon* primeleTelefoane = NULL;
//	int nrPrimeleTelefoane = 2;
//
//	primeleTelefoane = copiazaPrimeleNElemente(telefoane, nrTelefoane, nrPrimeleTelefoane);
//	printf("\n\nPrimele telefoane:\n");
//	afisareVector(primeleTelefoane, nrPrimeleTelefoane);
//	dezalocare(&primeleTelefoane, &nrPrimeleTelefoane);
//	afisareVector(primeleTelefoane, nrPrimeleTelefoane);
//
//	//copiaza telefoane scumpe
//	struct Telefon* telefoaneScumpe = NULL;
//	int nrTelefoaneScumpe = 0;
//	copiazaTelefoaneScumpe(telefoane, nrTelefoane, 1000, &telefoaneScumpe, &nrTelefoaneScumpe);
//	printf("\n\nTelefoane Scumpe:\n");
//	afisareVector(telefoaneScumpe, nrTelefoaneScumpe);
//	dezalocare(&telefoaneScumpe, &nrTelefoaneScumpe);
//
//	struct Telefon telefon = getPrimulTelefonByProducator(telefoane, nrTelefoane, "Apple");
//	printf("\n\nTelefonul gasit:\n");
//	afisare(telefon);
//	if (telefon.producator != NULL) {
//		free(telefon.producator);
//		telefon.producator = NULL;
//	}
//	dezalocare(&telefoane, &nrTelefoane);
//	return 0;
//}