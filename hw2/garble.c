#include <stdio.h>
#include <ctype.h>

int main(){
    int c;
    int prev = -1;

    while ((c = getchar()) != EOF){
        // Don't swap but prev is empty so don't output
        if (prev == -1){
            prev = c;
        }
        // Don't swap
        else if (!islower(c) || !islower(prev) || c % 7 != prev % 7) {
            putchar(prev);
            prev = c;
        }
        // Swap them
        else {
            putchar(c);
            putchar(prev);
            prev = -1;
        }
    }
    // Output the last character
    if (prev != -1){
        putchar(prev);
    }
    return 0;
}