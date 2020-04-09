#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {

    int n, fmeret;
    
    printf("x-ig megkeresi a primszamokat es y hosszu fajlokba menti\n");
	printf("Adja meg x erteket\n");
    scanf("%d", &n);
    printf("Adja meg y erteket\n");
    scanf("%d", &fmeret);

    clock_t start = clock();

    int *prim = (int*)malloc((n+1) * sizeof(int));
    for (int i = 2; i <= n; i++) {
        prim[i] = i;
    }

    for (int i = 2; i*i <= n; i++) {
        printf("%d ", i);
        if (prim[i] != 0) {
            for (int j = 2; prim[i]*j <= n; j++) {
                prim[prim[i]*j] = 0;
            }
        }
    }

    int f = 0, a = 2, b, c = 0;

    for (int s = 0;;) {
        if (s == 0) {
            f++;
        }
        char fajl[] = "prim_", sorsz[100];
        itoa(f, sorsz, 10);
        strcat(fajl, sorsz);
        strcat(fajl, ".txt");
        FILE *out = fopen(fajl, "w");
	    if (out == 0) {
        	printf("Nem lehet megnyitni a fajlt.\n");
	    	exit(-1);
	    }
        for (int i = a;; i++) {
            if (i > n) {
                c = 1;
                break;
            }
            else if (prim[i] != 0) {
                s++;
                b = i;
                printf("%d %d %d\n", f, s, prim[i]);
                fprintf(out, "%d\n", prim[i]);
                if (s == fmeret) {
                    break;
                }
            }
        }
        fclose(out);
        s = 0;
        a = b+1;
        if (c == 1) {
            break;
        }
    }

    clock_t stop = clock();
    double time_spent = (double)(stop - start) / CLOCKS_PER_SEC;
	double time_spenth = floor(time_spent/3600), time_spentm = floor(time_spent/60)-time_spenth*60, time_spents = time_spent-time_spenth*3600-time_spentm*60;
    printf("Befejezve %.0fh %.0fm %.0fs alatt.\n", time_spenth, time_spentm, time_spents);
    
    //fclose(out);
    free(prim);
    printf("A kilepeshez nyomjon entert.\n");
    getchar();
    getchar();
    return 0;
}