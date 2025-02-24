#include <stdio.h>
#include <stdlib.h>

int main()
{
 int n;
 scanf("%d",&n);
 if (n <= 12 && n > 0)
 {
     printf("Chisloto e validno\n");
     switch (n){
    case 1:
        printf("%d -> January (winter)",n);
        break;
    case 2:
        printf("%d -> February (winter)",n);
        break;
    case 3:
        printf("%d -> March (spring)",n);
          break;
    case 4:
        printf("%d -> April (spring)",n);
          break;
    case 5:
        printf("%d -> May (spring)",n);
          break;
    case 6:
        printf("%d -> June (summer)",n);
          break;
    case 7:
        printf("%d -> July (summer)",n);
          break;
    case 8:
        printf("%d -> August (summer)",n);
         break;
    case 9:
        printf("%d -> September (fall)",n);
          break;
    case 10:
        printf("%d -> October (fall)",n);
          break;
    case 11:
        printf("%d -> November (fall)",n);
          break;
    case 12:
        printf("%d -> December (winter)",n);
          break;
        }
 }
 else{
       printf("Chisloto e nevalidno");
 }
    return 0;
}
