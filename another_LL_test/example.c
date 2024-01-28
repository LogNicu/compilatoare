
//testing single line: non turing-complete C

int pi200() {
    return 314;
}

int f1(int a, int b, int c) {
    return b * b - 4 * a * c;
}

int pi100(int a, int b) {
    int x, y;
    x = b * b;
    y = 4 * a - 2;
    x = x - y;
    return x+ f1(1,2,y);
}