int pi100() {
    return 314;
}

int f1(int a, int b, int c) {
    return b * b - 4 * a * c;
}

int f2(int a, int b, int c, int d) {
    int x, y;
    x = b * b;
    y = 4 * a * c;
    x = x - y;
    return x;
}