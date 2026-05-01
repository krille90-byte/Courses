#include <stdio.h>
#include <string.h>

int main()
{
    int textInputSize = 100;
    char textInput[textInputSize];

    int stringLength;

    int i = 0;

    scanf("%s", textInput);

    stringLength = strlen(textInput);

    for (i; i < stringLength; i++)
    {
        textInput[i] = textInput[i] - 3;

        //ABC ÄR CURSED
    }

    for (int i = 0; i < stringLength; i++)
    {
        printf("%c", textInput[i]);
    }

    return 0;
}