#include <stdio.h>
#include <setjmp.h>

/*
   <Important>
   Header file is <setjmp.h>
   Buffer is jmp_buf
   setjmp(buf) returns 0 first then non zero positive values
   longjmp(buf,value)
*/

jmp_buf buf;

void fun1()
{
    printf("In fun1()\n");
    longjmp(buf, 1);
}

void fun2()
{
    printf("In fun2()\n");
    longjmp(buf, 2);
}

int main()
{
    int pivot = setjmp(buf);
    switch (pivot)
    {
    case 0:
    {
        fun1();
        break;
    }
    case 1:
    {
        printf("Returned from fun1()\n");
        fun2();
        break;
    }
    case 2:
    {
        printf("Retured from fun2()\n");
        break;
    }
    default:
        break;
    }

    return 0;
}
