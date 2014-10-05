#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plik.h"

char *WczytajLinie(FILE * fplik, int *status) {

  char *linia;
  linia = (char *) malloc(1024 * sizeof(char *));

  if (fplik == NULL) {
    *status = 1;
    return linia = "BLAD ODCZYTU PLIKU";
  }
  if (fgets(linia, 1024, fplik) != NULL) {
    return linia;
  }
  else if (feof(fplik)) {
    *status = 2;
    return linia = "KONIEC PLIKU";
  }
  else {
    *status = 3;
    return linia = "BLAD ODCZYTU PLIKU";

  }
}

int PominFunckje(char *tab, char **pomin) {

  FILE *fplik;
  int stan = 0;
  int i;
  int ile_pomin = 0;
  if ((fplik = fopen("funkcje_omijane.txt", "r")) == NULL) {
    printf("\nNie moge otworzyc pliku: funkcje_omijane.txt\n");
    return EXIT_FAILURE;

  }
  else {

    int i = 0;
    int size;
    while (stan == 0) {
      tab = WczytajLinie(fplik, &stan);
      if (stan == 0) {

        size = strlen(tab) * sizeof(char);
        pomin[i] = malloc(size);
        strcpy(pomin[i], tab);

        i++;
      }
    }

    printf("\nPominięto %d funcje.", i);
    return ile_pomin = i;

  }
}
