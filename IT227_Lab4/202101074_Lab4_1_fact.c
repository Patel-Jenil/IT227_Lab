long myfact (int n) {
    if (n<=1)
        return 1;
    return n*myfact(n-1);
}