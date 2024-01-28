
//testing single line: non turing-complete C

int idk(int y) {
    return y+314;
}

int pi200(int a, int b, int c) {
    return b * b - 4 * a * c;
}

int pi100(int a, int b) {
    int x,y;
    x = b -1 ;
    y = a /2 ;
    x = a*3 << 2;
    return 1+ x+ idk(x) + idk(a) + 3 ;
}