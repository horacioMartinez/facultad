int a(int x);
int b(int x);
int c(int x);

int f(int x)
{
    a(x);
    return b(x);
}

int g(int x)
{
    if ( a(x) ) {
        return b(x);
    }
    return  c(x);
}

int h1(int x)
{
    return a(x) + 1;
}

int h2(int x)
{
    int ret = a(x);
    return ret;
}

int h3(int x)
{
    var ret = a(x);
    return (ret == 0) ? 1 : ret;
}
