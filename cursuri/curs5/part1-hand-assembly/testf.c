int f1(int a, int b)
{
    return a * (b - 1);
}

int f2(int a1, int a2, int a3, int a4, int a5)
{
    return (a1 + a2 + a3 + a4 + a5) * 752 ;
}

int f3(int a1, int a2, int a3, int a4, int a5, int a6)
{
    return (a1 + a2 + a3 + a4 + a5 + a6) * 752 ;
}

int f4(int a1, int a2, int a3, int a4, int a5, int a6)
{
    return f1(a1 + a2 + a3 + a4 + a5 + a6, 752) ;
}

int f5(int a, int b) {
    return f3(a, b, a+5, b+5, a+7, b+7)+ f1(a,b);
}
