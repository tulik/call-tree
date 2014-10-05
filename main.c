#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "decyzja.h"
#define N 1024

int main(int argc, char **argv) {
  char nazwa_pliku[N][N];
  int k, i, j;
  int stat[N];
  if (argc == 1) {
    fprintf(stderr, "\n Wywolaj z opcja -h w celu uzyskania pomocy.\n\n");
  }
  /* Jesli wywolano program z parametrami (opcjami) */
  while ((k = getopt(argc, argv, "f:ih")) != -1)
    switch (k) {
    case 'f':
      i = 0;
      strcpy(nazwa_pliku[i++], optarg);
      while (argv[optind] != NULL && argv[optind][0] != '-')
        strcpy(nazwa_pliku[i++], argv[optind++]);
      for (j = 0; j < i; j++) {
        FILE *fplik;
        fplik = fopen(nazwa_pliku[j], "r");
        printf("\n======================");
        printf("\n%s:\n", nazwa_pliku[j]);
        printf("======================");
        Analiza(fplik, stat);

      }
      break;
    case 'h':
      fprintf(stderr, "\n\tANALIZATOR WYWOLAN FUNKCJI:" "\n\n\t -f [plik_1]...[plik_n] \t Wywolanie programu z plikami do analizy." "\n\t -i \t\t\t\t Pominięcie funkcji z pliku pomin.txt." "\n\t -h \t\t\t\t Wyswietla plik pomocy\n\n");
      break;
    case 'i':
      *stat = 1;
      for (j = 0; j < i; j++) {
        FILE *fplik;
        fplik = fopen(nazwa_pliku[j], "r");
        printf("\n======================");
        printf("\n%s:\n", nazwa_pliku[j]);
        printf("======================");
        Analiza(fplik, stat);

      }
      break;

    case '?':
      if (optopt == 'f')
        fprintf(stderr, "Opcja -%c wymaga argumentu.\n", optopt);
    }

  return 0;
}
