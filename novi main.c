#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "igrac.h"

typedef enum {
ISPISI_IZBORNIK = 1,
DODAJ_IGRACA,
PRIKAZI_IGRACE,
IZBRISI_IGRACA,
AZURIRAJ_IGRACA,
SPREMI_IGRACE,
UCITAJ_IGRACE,
IZBRISI_DATOTEKU,
DODAJ_STATISTIKU,
SORTIRAJ_IGRACE,
PRETRAZI_IGRACE,
IZLAZ
} Opcija;

void ispisiIzbornik() {
printf("\nIzbornik:\n");
printf("1. Ispisi izbornik\n");
printf("2. Dodaj igraca\n");
printf("3. Prikazi igrace\n");
printf("4. Izbrisi igraca\n");
printf("5. Azuriraj igraca\n");
printf("6. Spremi igrace u datoteku\n");
printf("7. Ucitaj igrace iz datoteke\n");
printf("8. Izbrisi datoteku\n");
printf("9. Dodaj statistiku\n");
printf("10. Sortiraj igrace po broju\n");
printf("11. Pretrazi igrace\n");
printf("12. Izlaz\n");
}

void inicijalizirajProgram(Igrac igraci[], int* brojIgraca) {
FILE* file = fopen("igraci.txt", "r");
if (file != NULL) {
fclose(file);

char odgovor[3];
while (1) {
printf("Zelite li ucitati kosarkaski tim (da/ne): ");
scanf("%2s", odgovor);
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

ispisiIzbornik();

do {
printf("Odaberite opciju: ");
while (scanf("%d", (int*)&opcija) != 1 || opcija < ISPISI_IZBORNIK || opcija > IZLAZ) {
printf("Pogresan unos. Molimo unesite broj od 1 do 12: ");
while (getchar() != '\n');
}

switch (opcija) {
case ISPISI_IZBORNIK:
ispisiIzbornik();
break;
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
case AZURIRAJ_IGRACA:
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
{
printf("Zelite li obrisati ovaj kosarkaski tim? (da/ne): ");
char odgovor[3];
scanf("%2s", odgovor);
if (strcmp(odgovor, "da") == 0) {
remove("igraci.txt");
brojIgraca = 0;
printf("Kosarkaski tim uspjesno izbrisan.\n");
}
}
break;
case DODAJ_STATISTIKU:
dodajStatistiku(igraci, brojIgraca);
break;
case SORTIRAJ_IGRACE:
sortirajIgracePoBroju(igraci, brojIgraca);
break;
case PRETRAZI_IGRACE:
{
printf("Unesite ime igraca za pretrazivanje: ");
char ime[50], prezime[50];
scanf("%49s", ime);
printf("Unesite prezime igraca za pretrazivanje: ");
scanf("%49s", prezime);
Igrac* igrac = pretraziIgraca(igraci, brojIgraca, ime, prezime);
if (igrac) {
printf("Igrac pronaden: Ime: %s, Prezime: %s, Broj: %d, Kosevi: %d, Skokovi: %d, Asistencije: %d\n",
igrac->ime, igrac->prezime, igrac->broj, igrac->kosevi, igrac->skokovi, igrac->asistencije);
}
else {
printf("Igrac nije pronaden.\n");
}
}
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
