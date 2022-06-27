#include <stdio.h>
#include <cs50.h>

int main (void)
{
   bool k = false;
   printf("%i\n", k);

   int ki = k + false;
   printf("k + false = %i\n", ki);

    int kl = k + true;
   printf("k + true = %i\n", kl);
}
