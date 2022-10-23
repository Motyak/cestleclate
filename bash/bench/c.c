#include <stdio.h>
#include <stdint.h>

#define UNSIGNED uint32_t

void print(UNSIGNED nombre) {
    printf("\r%d", nombre);
    fflush(stdout);
}

int main()
{
    UNSIGNED i = 0;
    UNSIGNED j = 1;
    while (1)
        if (++i == 0)
            print(j++);

    return 0;
}

