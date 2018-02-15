#include <stdio.h>
#include <limits.h>

int main(void)
{
    /*
     * ------------------------------------
     *     4-bit integer representation
     * ------------------------------------
     *
     * N    binary   ~N (complment)   -N (2's complement)
     * 0     0000         1111            0000
     * 1     0001         1110            1111
     * 2     0010         1101            1110
     * 3     0011         1100            1101
     * 4     0100         1011            1100
     * 5     0101         1010            1011
     * 6     0110         1001            1010
     * 7     0111         1000            1001
     * 8     ----         ----            1000
     *
     * ------------------------------------
     *    4-bit integer range on a line
     * ------------------------------------
     *
     * -|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|------>
     * 0000  0001  0010  0011  0100  0101  0110  0111  1000  1001  1010  1011  1100  1101  1110  1111
     *  0     1     2     3     4     5     6     7     -8    -7    -6    -5    -4    -3    -2    -1
     *
     */
    printf("INT_MAX: %d, INT_MIN: %d\n", INT_MAX, INT_MIN);
    printf("INT_MAX > INT_MIN: %s\n", INT_MAX > INT_MIN ? "TRUE" : "FALSE");
    printf("(INT_MAX + 1 == INT_MIN): %s -> dist(INT_MAX, INT_MIN): %d\n\n",
            INT_MAX + 1 == INT_MIN ? "TRUE" : "FALSE",
            INT_MIN - INT_MAX);

    /*
     * ------------------------------------
     * AND (&), OR (|) and XOR(^) operations
     * ------------------------------------
     *
     * N & 0s = 0s
     * N & 1s = N
     * N & N  = N
     *
     * N | 0s = N
     * N | 1s = 1s
     * N | N  = N
     *
     * N ^ 0s = N
     * N ^ 1s = ~N (not the same as -N which is 2's complement)
     * N ^ N  = 0s
     *
     * where 0s = 0000...0 = 0 and
     *       1s = 1111...1 = -1.
     *
     */
    int N = 6;

    printf("N: %d\n", N);
    printf("-- N & 0s: 0s (%d)\n", N & 0);
    printf("-- N & 1s: N  (%d)\n", N & -1);
    printf("-- N & N : N  (%d)\n\n", N & N);

    printf("-- N | 0s: N  (%d)\n", N | 0);
    printf("-- N | 1s: 1s  (%d)\n", N | -1);
    printf("-- N | N : N  (%d)\n\n", N | N);

    printf("-- N ^ 0s: N  (%d)\n", N ^ 0);
    printf("-- N ^ 1s: ~N (%d)\n", N ^ -1);
    printf("-- N ^ N : 0s (%d)\n\n", N ^ N);
}
