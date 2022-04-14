// SERIJSKO IZVRSAVANJE

/*#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SEED_VREDNOST 123456
#define N 500000000

    int main()
{

    int count = 0;
    double pi;

    srand(SEED_VREDNOST);

    // Pokretanje simulacije za N puta
    for (int i = 0; i < N; i++)
    {

        // Racun kordinata x i y
        double x, y;
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Provera da li je u okviru vrednosti
        if (x * x + y * y <= 1)
            count++;
    }

    // Racuna se odnos(ratio) i vrednost broja Pi
    pi = (double)count / N * 4;

    printf("Jedna nit : # pokusaja = %14ld , aproksimacija Pi: %1.16f", N, pi);

    return 0;
}*/

// PARALELIZACIJA KODA

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <omp.h>

#define SEED_VREDNOST 123456
#define N 500000000

unsigned int seed = 777777777;

// random generator pomocu LKG algoritma
double randUint(long i)
{
    seed = seed * 1103515245 + 123456;

    return seed / (double)UINT_MAX;
}

int main()
{

    long count = 0;
    double pi;

// Pokrenuta paralelizacija sa redukcionom tehnikom
#pragma omp parallel for reduction(+ \
                                   : count)
    for (long i = 0; i < N; i++)
    {

        // Racunanje kordinati kao i u sekvencijalnom slucaju
        double x, y;
        x = randUint(i);
        y = randUint(i);

        // Da li je u okviru “kruga”
        if (x * x + y * y <= 1)
            count = count + 1;
    }

    // Racuna se odnos(ratio) i vrednost broja Pi
    pi = ((double)count / (double)N) * 4.0;

    printf("Paralelno : # pokusaja = %14ld , aproksimacija Pi: %1.16f ", N, pi);

    return 0;
}
