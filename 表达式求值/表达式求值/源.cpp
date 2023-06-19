#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;
#define M 1000
char a[M];
typedef struct Stack
{
    char elem[M];
    double  num[M];
    int  top, topi;
}sqstack;
void initial(sqstack* s)
{
    s->top = -1;
    s->topi = -1;
}
void push(sqstack* s, char x)
{
    s->elem[++s->top] = x;
}
void push_i(sqstack* s, double x)
{
    s->num[++s->topi] = x;
}
char pop(sqstack* s)
{
    return s->elem[s->top--];
}
double pop_i(sqstack* s)
{
    return s->num[s->topi--];
}
bool Is_operator(char x)
{
    switch (x)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '#':
        return 1;
    default:
        return 0;
    }
}
char Operator(char a, char b)
{
    int i = 0, j = 0;
    char pre[7][7] = {
                     {'>','>','<','<','<','>','>'},
                     {'>','>','<','<','<','>','>'},
                     {'>','>','>','>','<','>','>'},
                     {'>','>','>','>','<','>','>'},
                     {'<','<','<','<','<','=','0'},
                     {'>','>','>','>','0','>','>'},
                     {'<','<','<','<','<','0','='}
    };
    switch (a)
    {
    case '+':i = 0; break;
    case '-':i = 1; break;
    case '*':i = 2; break;
    case '/':i = 3; break;
    case '(':i = 4; break;
    case ')':i = 5; break;
    case '#':i = 6; break;
    }
    switch (b)
    {
    case '+':j = 0; break;
    case '-':j = 1; break;
    case '*':j = 2; break;
    case '/':j = 3; break;
    case '(':j = 4; break;
    case ')':j = 5; break;
    case '#':j = 6; break;
    }
    return pre[i][j];
}
double calculate(double a, double b, char c)
{
    switch (c)
    {
    case '+':return a + b;
    case '-':return a - b;
    case '*':return a * b;
    case '/':return a / b;
    }
    return 0;
}
void fun(sqstack* s)
{
    int i = 0;
    double x1, x2;
    push(s, '#');
    do
    {
        if (isdigit(a[i]))
        {
            x1 = a[i] - '0';
            push_i(s, x1);
            if (isdigit(a[i + 1]))
            {
                i++;
                x2 = a[i] - '0';
                x1 = x1 * 10 + x2;
                pop_i(s);
                push_i(s, x1);
                i++;
            }
            else if (a[++i] == '.')
            {
                int cnt = 1;
                i++;
                while (isdigit(a[i]))
                {
                    x2 = a[i] - '0';
                    x1 = x1 + pow(0.1, cnt) * x2;
                    cnt++;
                    pop_i(s);
                    push_i(s, x1);
                    i++;
                }
            }
        }
        if (Is_operator(a[i]))
        {
            switch (Operator(s->elem[s->top], a[i]))
            {
            case '<':push(s, a[i]); i++; break;
            case '>':x1 = pop_i(s); x2 = pop_i(s);
                x1 = calculate(x2, x1, pop(s));
                push_i(s, x1);
                break;
            case '=':pop(s); i++; break;
            }
        }
    } while (s->top != -1);
}

int main()
{
    sqstack* s = new sqstack;
    initial(s);
    cin >> a;
    fun(s);

    printf("%.2f", s->num[s->topi]);
    //cout<<fixed<<setprecision(2)<<s->num[s->topi]<<endl;
    return 0;
}