#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "igrac.h"

int ucitajIgraceIzDatoteke(Igrac igraci[]) {
FILE* datoteka = fopen("igraci.txt", "r");
if (datoteka == NULL) {
return 0;
}

int brojIgraca = 0;
while (fscanf(datoteka, "%49s %49s %d %d %d %d", igraci[brojIgraca].ime, igraci[brojIgraca].prezime, &igraci[brojIgraca].broj, &igraci[brojIgraca].kosevi, &igraci[brojIgraca].skokovi, &igraci[brojIgraca].asistencije) != EOF) {
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
printf("Igraci su uspjesno spremljeni u datoteku.\n");
}

void dodajIgraca(Igrac igraci[], int* brojIgraca) {
if (*brojIgraca >= MAX_IGRACA) {
printf("Dosegnut maksimalni broj igraca.\n");
return;
}

printf("Unesite ime: ");
scanf("%49s", igraci[*brojIgraca].ime);
printf("Unesite prezime: ");
scanf("%49s", igraci[*brojIgraca].prezime);

while (1) {
printf("Unesite broj: ");
if (scanf("%d", &igraci[*brojIgraca].broj) != 1) {
printf("Pogresan unos. Molimo unesite broj.\n");
while (getchar() != '\n');
}
else {
break;
}
}

igraci[*brojIgraca].kosevi = 0;
igraci[*brojIgraca].skokovi = 0;
igraci[*brojIgraca].asistencije = 0;

(*brojIgraca)++;
printf("Igrac uspjesno dodan.\n");
}

void dodajStatistiku(Igrac igraci[], int brojIgraca) {
if (brojIgraca == 0) {
printf("Nema unesenih igraca.\n");
return;
}

int broj;
while (1) {
printf("Unesite broj igraca kojem zelite dodati statistiku: ");
if (scanf("%d", &broj) != 1) {
printf("Pogresan unos. Molimo unesite broj.\n");
while (getchar() != '\n');
}
else {
break;
}
}

int found = 0;
for (int i = 0; i < brojIgraca; i++) {
if (igraci[i].broj == broj) {
printf("Unesite broj koseva: ");
scanf("%d", &igraci[i].kosevi);
printf("Unesite broj skokova: ");
scanf("%d", &igraci[i].skokovi);
printf("Unesite broj asistencija: ");
scanf("%d", &igraci[i].asistencije);
found = 1;
break;
}
}

if (!found) {
printf("Igrac s brojem %d nije pronaden.\n", broj);
}
else {
printf("Statistika uspjesno dodana.\n");
}
}

void prikaziIgrace(Igrac igraci[], int brojIgraca) {
if (brojIgraca == 0) {
printf("Nema unesenih igraca.\n");
return;
}

for (int i = 0; i < brojIgraca; i++) {
printf("Igrac %d: Ime: %s, Prezime: %s, Broj: %d, Kosevi: %d, Skokovi: %d, Asistencije: %d\n",
i + 1, igraci[i].ime, igraci[i].prezime, igraci[i].broj, igraci[i].kosevi, igraci[i].skokovi, igraci[i].asistencije);
}
}

void izbrisiIgraca(Igrac igraci[], int* brojIgraca) {
int broj;
while (1) {
printf("Unesite broj igraca kojeg zelite izbrisati: ");
if (scanf("%d", &broj) != 1) {
printf("Pogresan unos. Molimo unesite broj.\n");
while (getchar() != '\n');
}
else {
break;
}
}

int found = 0;
for (int i = 0; i < *brojIgraca; i++) {
if (igraci[i].broj == broj) {
for (int j = i; j < *brojIgraca - 1; j++) {
igraci[j] = igraci[j + 1];
}
(*brojIgraca)--;
found = 1;
break;
}
}

if (!found) {
printf("Igrac s brojem %d nije pronaden.\n", broj);
}
else {
printf("Igrac uspjesno izbrisan.\n");
}
}

void azurirajInformacije(Igrac igraci[], int brojIgraca) {
if (brojIgraca == 0) {
printf("Nema unesenih igraca.\n");
return;
}

prikaziIgrace(igraci, brojIgraca);

int redniBroj;
while (1) {
printf("Unesite redni broj igraca kojeg zelite azurirati: ");
if (scanf("%d", &redniBroj) != 1 || redniBroj < 1 || redniBroj > brojIgraca) {
printf("Pogresan unos. Molimo unesite ispravan redni broj.\n");
while (getchar() != '\n');
}
else {
break;
}
}

redniBroj--; // Pretvaramo u indeks

printf("Unesite novo ime: ");
scanf("%49s", igraci[redniBroj].ime);
printf("Unesite novo prezime: ");
scanf("%49s", igraci[redniBroj].prezime);

while (1) {
printf("Unesite novi broj: ");
if (scanf("%d", &igraci[redniBroj].broj) != 1) {
printf("Pogresan unos. Molimo unesite broj.\n");
while (getchar() != '\n');
}
else {
break;
}
}

printf("Informacije o igracu uspjesno azurirane.\n");
}

void sortirajIgracePoBroju(Igrac igraci[], int brojIgraca) {
for (int i = 0; i < brojIgraca - 1; i++) {
for (int j = i + 1; j < brojIgraca; j++) {
if (igraci[i].broj > igraci[j].broj) {
Igrac temp = igraci[i];
igraci[i] = igraci[j];
igraci[j] = temp;
}
}
}
printf("Igraci su uspjesno sortirani po broju.\n");
}

Igrac* pretraziIgraca(Igrac igraci[], int brojIgraca, const char* ime, const char* prezime) {
for (int i = 0; i < brojIgraca; i++) {
if (strcmp(igraci[i].ime, ime) == 0 && strcmp(igraci[i].prezime, prezime) == 0) {
return &igraci[i];
}
}
return NULL;
}
