/* ex: set ts=2 et: */
/*
 * Histogram
 *
 * Read input from stdin, print byte, count and
 * bar for all bytes that appear
 */

#include <stdio.h>
#include <unistd.h>

static unsigned long long Bin[256];

static int maxi(void)
{
  int max = 0;
  for (int i = 1; i < 256; i++)
    if (Bin[i] > Bin[max])
      max = i;
  return max;
}

unsigned long long totalbytes(void)
{
  unsigned long long bytes = Bin[0];
  for (int i = 1; i < 256; i++)
    bytes += Bin[i];
  return bytes;
}

static void histogram(void)
{
  static const char Bars[51] = "#####" "#####" "#####" "#####" "#####"
                               "#####" "#####" "#####" "#####" "#####" "#";
  const double normal = 50. / Bin[maxi()];
  printf("    %llu %f\n", totalbytes(), normal);
  for (int i = 0; i < 256; i++)
    if (Bin[i] > 0)
      printf("%3d %-12llu %.*s\n",
        i, Bin[i], (int)(Bin[i] * normal) + 1, Bars);
}

int main(void)
{
  static unsigned char buf[4096];
  ssize_t rd;
  while ((rd = read(STDIN_FILENO, buf, sizeof buf)) > 0)
    while (rd--)
      Bin[buf[rd]]++;
  if (rd < 0)
    perror("read");
  histogram();
  return 0;
}

