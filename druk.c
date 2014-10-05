#include <stdio.h>
#include "druk.h"
#include "dane.h"

void Drukuj(char *nazwa, int linia, wyw_t * tablica, int l_fun) {

  int i;

  printf("\n\n%d", linia);
  printf("\tFunkcja %s:\n", nazwa);

  if (l_fun != 0) {
    printf("\t   Wywoluje:\n");
    for (i = 1; i < l_fun; i++) {

      if (tablica[i].wywolanie != NULL) {
        printf("%d\t\t%s ", tablica[i].linia_nr, tablica[i].wywolanie);

        if (tablica[i].ile_razy > 1) {
          printf("(%d razy)\n", tablica[i].ile_razy);
        }
        else {
          printf("\n");
        }
      }
    }
  }
}
