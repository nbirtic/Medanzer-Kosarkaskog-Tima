#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "igrac.h"

int ucitajIgraceIzDatoteke(Igrac igraci[]) {
	FILE* datoteka = fopen("igraci.txt", "r");
	if (datoteka == NULL) {
		return 0;
	}

	int brojIgraca = 0;
	while (fscanf(datoteka, "%s %s %d %d %d %d", igraci[brojIgraca].ime, igraci[brojIgraca].prezime, &igraci[brojIgraca].broj, &igraci[brojIgraca].kosevi, &igraci[brojIgraca].skokovi, &igraci[brojIgraca].asistencije) != EOF) {
		brojIgraca++;
	}

	fclose(datoteka);
	return brojIgraca;
}

void spremiIgraceUDatoteku(Igrac igraci[], int brojIgraca) {
	FILE* datoteka = fopen("igraci.txt", "w");
	if (datoteka == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return;
	}

	for (int i = 0; i < brojIgraca; i++) {
		fprintf(datoteka, "%s %s %d %d %d %d\n",
			igraci[i].ime, igraci[i].prezime, igraci[i].broj,
			igraci[i].kosevi, igraci[i].skokovi, igraci[i].asistencije);
	}

	fclose(datoteka);
	printf("Spremanje uspjesno.\n");
}

void izbrisiDatoteku() {
	if (remove("igraci.txt") == 0) {
		printf("Brisanje uspjesno.\n");
	}
	else {
		printf("Greska pri brisanju datoteke.\n");
	}
}


void dodajIgraca(Igrac igraci[], int* brojIgraca) {
	if (*brojIgraca >= MAX_IGRACA) {
		printf("Nemoguce dodati novog igraca. Popunjen maksimalan broj igraca.\n");
		return;
	}

	printf("Unesite ime igraca: ");
	scanf("%s", igraci[*brojIgraca].ime);
	printf("Unesite prezime igraca: ");
	scanf("%s", igraci[*brojIgraca].prezime);
	printf("Unesite broj igraca: ");
	scanf("%d", &igraci[*brojIgraca].broj);
	printf("Unesite broj koseva: ");
	scanf("%d", &igraci[*brojIgraca].kosevi);
	printf("Unesite broj skokova: ");
	scanf("%d", &igraci[*brojIgraca].skokovi);
	printf("Unesite broj asistencija: ");
	scanf("%d", &igraci[*brojIgraca].asistencije);

	(*brojIgraca)++;
	printf("Igrac uspjesno dodan!\n");
}

void dodajStatistiku(Igrac igraci[], int brojIgraca) {
	char ime[50], prezime[50];
	printf("Unesite ime igraca: ");
	scanf("%s", ime);
	printf("Unesite prezime igraca: ");
	scanf("%s", prezime);

	int i;
	for (i = 0; i < brojIgraca; i++) {
		if (strcmp(igraci[i].ime, ime) == 0 && strcmp(igraci[i].prezime, prezime) == 0) {
			printf("Unesite dodatni broj koseva: ");
			int kosevi;
			scanf("%d", &kosevi);
			igraci[i].kosevi += kosevi;

			printf("Unesite dodatni broj skokova: ");
			int skokovi;
			scanf("%d", &skokovi);
			igraci[i].skokovi += skokovi;

			printf("Unesite dodatni broj asistencija: ");
			int asistencije;
			scanf("%d", &asistencije);
			igraci[i].asistencije += asistencije;

			printf("Statistika igraca uspjesno azurirana.\n");
			return;
		}
	}

	printf("Igrac nije pronaden.\n");
}

void prikaziIgrace(Igrac igraci[], int brojIgraca) {
	printf("===== Popis igraca =====\n");


	int vecPrikazan[MAX_IGRACA] = { 0 };

	for (int i = 0; i < brojIgraca; i++) {

		if (vecPrikazan[i] == 1) {
			continue;
		}

		printf("Ime: %s, Prezime: %s, Broj: %d, Kosevi: %d, Skokovi: %d, Asistencije: %d\n",
			igraci[i].ime, igraci[i].prezime, igraci[i].broj, igraci[i].kosevi, igraci[i].skokovi, igraci[i].asistencije);


		vecPrikazan[i] = 1;


		for (int j = i + 1; j < brojIgraca; j++) {
			if (strcmp(igraci[i].ime, igraci[j].ime) == 0 &&
				strcmp(igraci[i].prezime, igraci[j].prezime) == 0 &&
				igraci[i].broj == igraci[j].broj &&
				igraci[i].kosevi == igraci[j].kosevi &&
				igraci[i].skokovi == igraci[j].skokovi &&
				igraci[i].asistencije == igraci[j].asistencije) {

				vecPrikazan[j] = 1;
			}
		}
	}
}


void izbrisiIgraca(Igrac igraci[], int* brojIgraca) {
	char ime[50], prezime[50];
	printf("Unesite ime igraca za brisanje: ");
	scanf("%s", ime);
	printf("Unesite prezime igraca za brisanje: ");
	scanf("%s", prezime);

	int i;
	for (i = 0; i < *brojIgraca; i++) {
		if (strcmp(igraci[i].ime, ime) == 0 && strcmp(igraci[i].prezime, prezime) == 0) {
			break;
		}
	}

	if (i < *brojIgraca) {
		for (int j = i; j < *brojIgraca - 1; j++) {
			igraci[j] = igraci[j + 1];
		}
		(*brojIgraca)--;
		printf("Igrac uspjesno izbrisan.\n");
	}
	else {
		printf("Igrac nije pronaden.\n");
	}
}

void azurirajInformacije(Igrac igraci[], int brojIgraca) {
	prikaziIgrace(igraci, brojIgraca);
	if (brojIgraca == 0) {
		return;
	}

	int odabir;
	printf("Odaberite redni broj igraca za azuriranje: ");
	scanf("%d", &odabir);

	if (odabir < 1 || odabir > brojIgraca) {
		printf("Pogresan odabir.\n");
		return;
	}

	int index = odabir - 1;
	printf("Unesite novo ime igraca: ");
	scanf("%s", igraci[index].ime);
	printf("Unesite novo prezime igraca: ");
	scanf("%s", igraci[index].prezime);
	printf("Unesite novi broj igraca: ");
	scanf("%d", &igraci[index].broj);

	printf("Informacije igraca uspjesno azurirane.\n");
}
