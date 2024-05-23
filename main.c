#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "igrac.h"

typedef enum {
	DODAJ_IGRACA = 1,
	PRIKAZI_IGRACE,
	IZBRISI_IGRACA,
	AZURIRAJ_IGRACE,
	SPREMI_IGRACE,
	UCITAJ_IGRACE,
	IZBRISI_DATOTEKU,
	DODAJ_STATISTIKU,
	IZLAZ
} Opcija;

void inicijalizirajProgram(Igrac igraci[], int* brojIgraca) {
	FILE* file = fopen("igraci.txt", "r");
	if (file != NULL) {
		fclose(file);

		char odgovor[3];
		while (1) {
			printf("Zelite li ucitati kosarkaski tim (da/ne): ");
			scanf("%s", odgovor);
			if (strcmp(odgovor, "da") == 0) {
				*brojIgraca = ucitajIgraceIzDatoteke(igraci);
				printf("Igraci uspjesno ucitani.\n");
				break;
			}
			else if (strcmp(odgovor, "ne") == 0) {
				remove("igraci.txt");
				*brojIgraca = 0;
				printf("Datoteka igraci.txt izbrisana.\n");
				break;
			}
			else {
				printf("Pogresan odabir, pokusajte ponovo.\n");
			}
		}
	}
}

int main() {
	Igrac igraci[MAX_IGRACA];
	int brojIgraca = 0;
	Opcija opcija;

	inicijalizirajProgram(igraci, &brojIgraca);

	do {
		printf("\nIzbornik:\n");
		printf("1. Dodaj igraca\n");
		printf("2. Prikazi igrace\n");
		printf("3. Izbrisi igraca\n");
		printf("4. Azuriraj igraca\n");
		printf("5. Spremi igrace u datoteku\n");
		printf("6. Ucitaj igrace iz datoteke\n");
		printf("7. Izbrisi datoteku\n");
		printf("8. Dodaj statistiku\n");
		printf("9. Izlaz\n");
		printf("Odaberite opciju: ");
		while (scanf("%d", (int*)&opcija) != 1 || opcija < DODAJ_IGRACA || opcija > IZLAZ) {
			printf("Pogresan unos. Molimo unesite broj od 1 do 9: ");
			while (getchar() != '\n'); 
		}

		switch (opcija) {
		case DODAJ_IGRACA:
			dodajIgraca(igraci, &brojIgraca);
			break;
		case PRIKAZI_IGRACE:
			prikaziIgrace(igraci, brojIgraca);
			break;
		case IZBRISI_IGRACA:
			if (brojIgraca == 0) {
				printf("Nema unesenih igraca.\n");
			}
			else {
				izbrisiIgraca(igraci, &brojIgraca);
			}
			break;
		case AZURIRAJ_IGRACE:
			azurirajInformacije(igraci, brojIgraca);
			break;
		case SPREMI_IGRACE:
			spremiIgraceUDatoteku(igraci, brojIgraca);
			break;
		case UCITAJ_IGRACE:
			brojIgraca = ucitajIgraceIzDatoteke(igraci);
			printf("Ucitavanje uspjesno.\n");
			break;
		case IZBRISI_DATOTEKU:
			printf("Zelite li obrisati ovaj kosarkaski tim? (da/ne): ");
			char odgovor[3];
			scanf("%s", odgovor);
			if (strcmp(odgovor, "da") == 0) {
				remove("igraci.txt");
				brojIgraca = 0;
				printf("Kosarkaski tim uspjesno izbrisan.\n");
			}
			break;
		case DODAJ_STATISTIKU:
			dodajStatistiku(igraci, brojIgraca);
			break;
		case IZLAZ:
			printf("Izlaz iz programa.\n");
			break;
		default:
			printf("Nepostojeca opcija. Molimo odaberite ponovno.\n");
		}
	} while (opcija != IZLAZ);

	return 0;
}
