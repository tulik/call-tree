#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decyzja.h"
#include "plik.h"
#include "analizator.h"
#include "druk.h"
#include "dane.h"

#define N 100

int Analiza(FILE * in, int *flaga_ign) {

  int i = 0;
  int pom = 0;
  int licznik = 0;
  int nr_funckji = 0;           /* liczba funkcji (bez pominietych) */
  int liczba_funkcji = 0;       /* liczba wszystkich funkcji */
  int ile_pomin = 0;            /* liczba pominietych funkcji z pliku */
  int znaki = 0;
  int flaga = 0;                /* informacja o stanie analizy */
  int stan = 0;                 /* informacja o stanie odczytu */
  int klamra_otw = 0;           /* flaga - otwarta klamra */
  int klamra_zam = 0;           /* flaga - zamknieta klamra */
  int klamra_z = 0;             /* nawiasy klamrowe - otwarte */
  int klamra_o = 0;             /* nawiasy klamrowe - zamkniete */
  int w_funkcji = 0;            /* czy w funkcji */
  int w_procedurze = 0;         /* czy w procedurze */
  int linia_nr = 0;             /* aktualna linia */
  int ile_wywolan = 0;          /* ile elementow w tablicy wywolan */
  int klam_o = 0;               /* liczba otwartych klamr */
  int klam_z = 0;               /* liczba zamknietych klamr */
  int ile_pominac = 29;         /* liczba pominietych slow kluczowych */


  char *wczytana_linia;
  char *nazwa;
  char *point;
  char *tabl;
  char *tymcz;
  char *pomin_funcje;
  char *pomin_makrodef;
  char **pomin_z_pliku;
  char **pomin_z_makrodef;
  char **tab;

  char *pomijane[] = { "if", "for", "auto", "enum", "restrict", "unsigned", "break", "extern",
    "return",
    "voidcase", "float", "short", "volatilechar", "signed", "whileconst",
    "goto",
    "sizeof", "_Boolcontinue", "static", "inline struct", "_Imaginarydo",
    "int",
    "switch", "double", "long", "typedef", "else", "register union", "while"
  };

  wczytana_linia = (char *) malloc(N * sizeof(char *));
  nazwa = (char *) malloc(N * sizeof(char *));
  point = (char *) malloc(N * sizeof(char *));
  tabl = (char *) malloc(N * sizeof(char *));
  tymcz = (char *) malloc(N * sizeof(char *));
  pomin_funcje = (char *) malloc(N * sizeof(char *));
  pomin_makrodef = (char *) malloc(N * sizeof(char *));
  pomin_z_pliku = (char **) malloc(N);
  pomin_z_makrodef = (char **) malloc(N);

  if (*flaga_ign == 1)
    ile_pomin = PominFunckje(tabl, pomin_z_pliku, pomin_funcje);

  wyw_t *tablica = (wyw_t *) malloc(N * sizeof(wyw_t));

  while (stan == 0) {

    licznik++;
    wczytana_linia = WczytajLinie(in, &stan);

    /* Zliczanie otwartych klamr */
    if (strpbrk(wczytana_linia, "{") != NULL)
      klam_o++;

    /* Zliczanie zamknietych klamr */
    if (strpbrk(wczytana_linia, "}") != NULL)
      klam_z++;

    /* Obsluga makrodefinicji */
    if ((strstr(wczytana_linia, "//")) == NULL && (strstr(wczytana_linia, "define")) != NULL && (strstr(wczytana_linia, "#")) != NULL) {
      if ((znaki = strcspn(wczytana_linia, "(")) != 0) {

        strncpy(tymcz, wczytana_linia, znaki);
        sscanf(tymcz, "%*s %[a-zA-Z]", pomin_makrodef);

        *pomin_z_makrodef = pomin_makrodef;

      }
    }

    flaga = AnalizaLex(wczytana_linia, &nazwa, &klamra_otw, &klamra_zam, w_funkcji, &tab, &ile_wywolan);

    /* Poczatek procedury */
    if (klamra_otw == 1 && (klamra_z != klamra_o) && w_procedurze == 0) {
      klamra_z++;
      w_procedurze = 1;
      klamra_otw = 0;
    }

    /* Koniec procedury */
    if (flaga == 2 && klamra_zam == 1 && w_procedurze == 1) {
      klamra_o++;
      w_procedurze = 0;
      klamra_zam = 0;
    }

    /* Poczatek deklaracji funkcji */
    if (flaga == 1 && w_procedurze == 0) {
      klamra_z++;
      linia_nr = licznik;
      if ((point = strstr(*pomijane, nazwa)) == NULL) {
        w_funkcji = 1;
        klamra_otw = 0;
      }
    }

    /* Bilans nawiasow klamrowych */
    if (klam_o != klam_z && stan == 1) {
      fprintf(stderr, "\nBLAD: NIE ZBILANSOWANE NAWIASY KLAMROWE!\n");
      break;
    }

    /* Dopisanie do struktury */
    if (flaga == 3) {

      for (i = 0; i < ile_wywolan; i++) {
        tablica[nr_funckji].wywolanie = tab[i];
        tablica[nr_funckji].ile_razy = 1;
        tablica[nr_funckji].linia_nr = licznik + 1;
        nr_funckji++;
      }

    }

    /* Koniec funkcji */
    if (flaga == 2 && w_procedurze == 0 && klamra_zam == 1) {
      klamra_o++;

      if (klamra_z == klamra_o) {

        if (nr_funckji != 0) {

          liczba_funkcji = 0;
          pom = 0;

          /* Pomijanie slow kluczowych */
          do {

            for (i = 0; i < nr_funckji; i++) {
              if (tablica[i].wywolanie == NULL) {
                i++;
              }
              else if ((pomijane[pom] != NULL)
                       && (strcmp(pomijane[pom], tablica[i].wywolanie) == 0)) {
                tablica[i].wywolanie = NULL;

              }
            }
            pom++;

          }
          while (pom < ile_pominac);

          /* Zliczanie wystapien funkcji w wywolaniu */
          while (liczba_funkcji < nr_funckji) {
            for (i = 1; i < nr_funckji; i++) {

              if ((tablica[i].wywolanie != NULL)
                  && (tablica[liczba_funkcji].wywolanie != NULL)
                  && (strcmp(tablica[liczba_funkcji].wywolanie, tablica[i].wywolanie) == 0)
                  && (liczba_funkcji != i)) {
                tablica[liczba_funkcji].ile_razy++;
                tablica[i].wywolanie = NULL;
              }
            }
            if (liczba_funkcji < nr_funckji) {
              liczba_funkcji++;
            }

          }

          pom = 0;

          /* Pomijanie funkcji z pliku */
          while (pom < ile_pomin) {

            for (i = 0; i < nr_funckji; i++) {
              if (tablica[i].wywolanie == NULL) {
                i++;
              }
              else if ((pomin_z_pliku[pom] != NULL)
                       && (strcmp(pomin_z_pliku[pom], tablica[i].wywolanie) == 1)) {
                tablica[i].wywolanie = NULL;

              }
              else if ((pomin_z_makrodef[pom] != NULL)
                       && (strcmp(pomin_z_makrodef[pom], tablica[i].wywolanie) == 1)) {
                tablica[i].wywolanie = NULL;
              }

            }
            pom++;
          }
        }

        Drukuj(nazwa, linia_nr, tablica, nr_funckji);

        w_funkcji = nr_funckji = liczba_funkcji = linia_nr = klamra_otw = klamra_zam = klamra_z = klamra_o = 0;
      }
    }

  }

  fprintf(stderr, "\n**** Koniec pliku ****\n\n");
  free(tablica);

  return 0;
}
