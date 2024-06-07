#ifndef IGRAC_H
#define IGRAC_H

#define MAX_IGRACA 100

typedef struct {
char ime[50];
char prezime[50];
int broj;
int kosevi;
int skokovi;
int asistencije;
} Igrac;

int ucitajIgraceIzDatoteke(Igrac igraci[]);
void spremiIgraceUDatoteku(Igrac igraci[], int brojIgraca);
void dodajIgraca(Igrac igraci[], int* brojIgraca);
void dodajStatistiku(Igrac igraci[], int brojIgraca);
void prikaziIgrace(Igrac igraci[], int brojIgraca);
void izbrisiIgraca(Igrac igraci[], int* brojIgraca);
void azurirajInformacije(Igrac igraci[], int brojIgraca);
void sortirajIgracePoBroju(Igrac igraci[], int brojIgraca);
Igrac* pretraziIgraca(Igrac igraci[], int brojIgraca, const char* ime, const char* prezime);

#endif
