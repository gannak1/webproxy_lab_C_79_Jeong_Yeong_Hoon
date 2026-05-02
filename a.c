#include <stdio.h>

  

int f(int x, int *py, int **ppz)

{
   printf("1");
  int y, z;

  **ppz += 1;

   z  = **ppz;

    printf("%d\n",*py);
  *py += 2;
   y = *py;
    printf("%d, %d, %d\n", x,y,z);

   x += 3;
   return x + y + z;

}

     

int main()

{

   int c, *b, **a;

   c = 4;

   b = &c;

   a = &b;

   printf("%d\n", f(c, b, a));

   return 0;

}