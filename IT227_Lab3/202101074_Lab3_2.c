#include <stdio.h>
#include <string.h>
// Jenil_Patel_202101074
// recursive_strlen to find length of the string

int recursive_strlen(char *str) {
    if (str[0] == '\0')
        return 0;
    return 1 + recursive_strlen(str + 1);
}

int main() {
    char input[100];
    printf("\nInput your string: ");
    fgets(input, 100, stdin);
    input[strcspn(input,"\n")] = '\0';
    int length = recursive_strlen(input);
    printf("\nLength of the string: %d\n", length);
    return 0;
}