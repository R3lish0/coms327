#include <stdio.h>

#define MAX_INDEX 300

void times_table(int a[MAX_INDEX][MAX_INDEX])
{
  int i, j;
  
  for (j = 0; j < MAX_INDEX; j++) {
    for (i = 0; i < MAX_INDEX; i++) {
      a[j][i] = (i + 1) * (j + 1);
    }
  }
}

int main(int argc, char *argv[])
{
  int a[MAX_INDEX][MAX_INDEX];
  int i, j;

  times_table(a);

  for (j = 0; j < MAX_INDEX; j++) {
    for (i = 0; i < MAX_INDEX; i++) {
      printf("%5d ", a[j][i]);
    }
    printf("\n");
  }

  return 0;
}
