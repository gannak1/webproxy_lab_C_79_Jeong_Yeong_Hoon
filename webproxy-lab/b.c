#include <stdio.h>

int main() {
  int a;
  int f = 1;
  f <<= 14;
  a = -1;

  a *= f;
  for (int i = 31; i >= 0; i--) {
      printf("%d", (a >> i) & 1);
  }
  a /= 2;
  printf("\n");
  for (int i = 31; i >= 0; i--) {
      printf("%d", (a >> i) & 1);
  }
}