
//testing single line: non turing-complete C

int idk() {
    return 314;
}

int pi100(int a, int b, int c) {
    return b * b - 4 * a * c;
}

int f1(int a, int b, int c, int d) {
    int x, y;
    x = b ;
    y = a;
    x = a;
    return x+ f1(1,2,y);
}