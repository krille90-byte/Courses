#include <stdio.h>

int main()
{
    int listSize;

    scanf("%d", &listSize);

    int list1[listSize];
    int list2[listSize];

    int listSum[listSize];


    for (int i = 0; i < listSize; i++)
    {
        scanf("%d", &list1[i]);
    }

    for (int i = 0; i < listSize; i++)
    {
        scanf("%d", &list2[i]);
    }

    for (int i = 0; i < listSize; i++)
    {
        listSum[i] = list1[i] + list2[i];
    }

    for (int i = 0; i < listSize; i++)
    {
        printf("%d\n", listSum[i]);
    }
}