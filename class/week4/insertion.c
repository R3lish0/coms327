#include <stdio.h>
#include <malloc.h>
#include <string.h>

//function that takes two const void * params and returns pointer to int
//int *compare(const void *v1, const void *v2);

//pointer to function that takes to const void *params and returns int
//int (*compare)(const void *v1, const void *v2);


/* Pointer arithmetic -- compiler multiplies index by size to get offset
int *i;

i = malloc();

i* // first int in array

*(i+1) //second int in array; same as a[i]

&a[i] == (a + i) <--> a[i] == *(a+i)
*/

int compare_int_reverse(const void *v1, const void *v2)
{
    return *


void insertion_sort(void *v, int s, int n,
        int (*compare)(const void *v1, const void *v2))
{
    int i, j;
    void *t;
    char *a = v;
    t = malloc(s);

    for (i = 2; i< n; i++)
    {
        for (memcpy(t,a+(i*s),s ), j= i- 1;
                j >-1 && compare(a + (j*s),t) > 0;
                j--) {
            memcpy(a + ((j+1) * s), a + (j * s),s);
        }
        memcpy(a + ((j + 1) * s), t, s);
    }
}


void inserstion_sort_int(int *a, int n)
{
    int i,j,t;

    for (i = 1; i < n; i++) {
        for (t = a[i],j=i-1;j>-1 && a[j] > t;j--)
        {
            a[j+1] = a[j];
        }
        a[j+1] = t;
    }
}





int main(int argc, char *argv[])
{
    int a[] = {9,8,7,6,5,4,3,2,1,0};
    int i;
    insertion_sort(a,10);

    for (i = 0; i < 10; i++) {
        printf("%d\t",a[i]);
    }
    printf("\n");

    
    return 0;
}

