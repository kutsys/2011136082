#include "libfooboobar.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int num[2];

    if (argc != 3) {
        printf("Usage: %s num1 num2\n", argv[0]);
        return 1;
    }

    num[0] = atoi(argv[1]);
    num[1] = atoi(argv[2]);

    printf("%d + %d = %d\n", num[0], num[1], InFoo(num[0], num[1])); 
    printf("%d - %d = %d\n", num[0], num[1], InBoo(num[0], num[1]));
    printf("%d * %d = %d\n", num[0], num[1], InBar(num[0], num[1]));

    return 0;
}
