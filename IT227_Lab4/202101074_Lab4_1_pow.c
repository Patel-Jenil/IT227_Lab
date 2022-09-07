long mypow (long a, long b) {
    if (b == 0)
        return 1;
    else if (b%2 == 0)
        return mypow(a*a, b/2);
    else
        return a*mypow(a*a, b/2);
}