#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "analizator.h"
#define N 100

int AnalizaLex(char *wczytana_linia, char **nazwa, int *klamra_otw, int *klamra_zam, int w_funkcji, char ***tab, int *ile_tab) {

  /*
   * deklaracje tablic
   */

  char *poszukiwany_fragment;
  char *wskaznik_2;
  char *temp2;
  char *temp1;
  char *koniec;
  char *name;

  /*
   * zmienne i flagi
   */

  int ile_znakow = 0;
  int i = 0;
  int j = 0;

  /*
   * alokacja pamieci
   */

  *tab = (char **) malloc(N);
  poszukiwany_fragment = (char *) malloc(N * sizeof(char *));
  wskaznik_2 = (char *) malloc(N * sizeof(char *));
  temp2 = (char *) malloc(N * sizeof(char *));
  temp1 = (char *) malloc(N * sizeof(char *));
  koniec = (char *) malloc(N * sizeof(char *));
  name = (char *) malloc(N * sizeof(char *));

  // ////////////////// procedury leksykalne ////////////////////

  /*
   * Obsluga komentarzy
   */
  if ((poszukiwany_fragment = strstr(wczytana_linia, "//")) != NULL || (poszukiwany_fragment = strstr(wczytana_linia, "/*")) != NULL) {

    if ((ile_znakow = strcspn(wczytana_linia, "//") != 0)
        || (ile_znakow = strcspn(wczytana_linia, "/*") != 0)) {
      strncpy(wczytana_linia, wczytana_linia, ile_znakow);
    }


  }

  if ((poszukiwany_fragment = strchr(wczytana_linia, '\"')) != NULL && (ile_znakow = strcspn(wczytana_linia, "\"")) != 0) {

    if (strncpy(temp1, wczytana_linia, ile_znakow) != 0) {
      poszukiwany_fragment = strrchr(poszukiwany_fragment, '"') + 1;
    }
    if (strcat(temp1, poszukiwany_fragment) != 0)
      wczytana_linia = temp1;
  }

  if ((strstr(wczytana_linia, "{")) != NULL && w_funkcji == 0) {
    *klamra_otw = 1;
    if ((ile_znakow = strcspn(wczytana_linia, "(")) != 0 && (strpbrk(wczytana_linia, "(") != NULL)) {

      if (strncpy(temp2, wczytana_linia, ile_znakow) != 0)
        sscanf(temp2, "%*s %s", &name[0]);
      if (strpbrk(name, "!^&*@#%$;") != NULL)
        *name = ' ';

      *nazwa = name;
      ile_znakow = 0;
      temp2 = 0;
      return 1;

    }
  }


  if ((strstr(wczytana_linia, "{")) != NULL && w_funkcji == 1) {
    *klamra_otw = 1;
  }

  if ((strstr(wczytana_linia, "}")) != NULL && w_funkcji == 1) {
    *klamra_zam = 1;
    return 2;
  }

  if ((strstr(wczytana_linia, "}")) != NULL && w_funkcji == 0) {
    *klamra_zam = 1;
  }

  if ((ile_znakow = strcspn(wczytana_linia, "(")) != 0 && w_funkcji == 1 && (strpbrk(wczytana_linia, "(") != NULL)) {

    ile_znakow = 0;

    do {
      i = 0;
      i = strcspn(wczytana_linia, "(");
      strncpy(temp2, wczytana_linia, i);
      wczytana_linia[i] = ' ';
      koniec = strrchr(temp2, ' ');

      if (((j = strcspn(koniec, "!@#$%^&*")) != 0)
          && (strpbrk(koniec, "!@#$%^^&*") != NULL)) {

        koniec[j] = ' ';
        koniec = strrchr(koniec, ' ');

      }


      (*tab)[ile_znakow] = malloc(strlen(koniec) * sizeof(char));

      sscanf(koniec, "%s", (*tab)[ile_znakow]);
      ile_znakow++;


    }
    while (strpbrk(wczytana_linia, "(") != NULL);


    *ile_tab = ile_znakow;

    return 3;
  }

  wczytana_linia = NULL;

  return 0;
}
