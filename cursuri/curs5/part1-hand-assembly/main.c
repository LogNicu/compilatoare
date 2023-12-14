#include <stdio.h>

extern int f1(int a, int b);
extern int f2(int a1, int a2, int a3, int a4, int a5);
extern int f3(int a1, int a2, int a3, int a4, int a5, int a6);
extern int f4(int a1, int a2, int a3, int a4, int a5, int a6);
extern int f5(int a, int b);
int main()
{
    printf("%d\n", f1(4,5));
    printf("%d\n", f2(1,2,3,5,8));
    printf("%d\n", f3(1,2,3,5,8,13));
    printf("%d\n", f4(1,2,3,5,8,13));
    printf("%d\n", f5(4,5));
    return 0;
}
