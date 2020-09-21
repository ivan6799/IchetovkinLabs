#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647

void prim(int** G, int N, int s)
{
    int *blue = calloc(N, sizeof(int)), *in = calloc(N, sizeof(int)), *out = calloc(N, sizeof(int)), i, j, k = 0, l = 0, m = INT_MAX, a=1,b=0;
    if (!blue) return;
    blue[s] = 1;
    while(b<N && a)
    {
        a=0;
        for( j = 0; j < N; j++)
        {
            if(blue[j]==1)
            {
                for (i = 0; i < N; i++)
                {
                    if (m >= G[j][i] && G[j][i] > 0 && !blue[i])
                    {

                        m = G[j][i];
                        k = i;
                        l = j;
                        a++;
                    }
                }
            }
        }
        blue[k] = 1;
        m = INT_MAX;
        if (a)
        {
            in[b] = l;
            out[b] = k;
        }
        b++;
    }
    if (N==0)
    {
        printf("no spanning tree");
        return;
    }

    for (i=0; i<N; i++)
    {
        if(!blue[i])
            {
                printf("no spanning tree");
                return;
            }
    }
    for(i = 0; i<b-1; i++) printf("%d %d\n", in[i]+1, out[i]+1);
    return;
}

int main()
{
    int N, M, s, f, lng, i, **A;
    scanf("%d", &N);
    scanf("%d", &M);
    A = (int **)malloc(N*sizeof(int *));
    if(!A)
        {
            printf("Allocation error.");
            return 0;
        }
    if(N<0||N>5000)
        {
            printf("bad number of vertices");
            return 0;
        }
    if(M<0||M>N*(N+1)/2)
        {
            printf("bad number of edges");
            return 0;
        }
    for(int i = 0; i < N; i++)
        {
            A[i] = (int *)malloc(N*sizeof(int));
            if(!A[i])
            {
                printf("Allocation error.");
                return 0;
            }
        }
    for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++) A[i][j] = -1;
            A[i][i] = 0;
        }
    for(i = 0;scanf("%d %d %d", &s, &f, &lng)!=EOF ; i++)
        {
            //scanf("%d %d %d", &s, &f, &lng);
            //scanf("%d %d %d", &s, &f, &lng)!=EOF
            if((s<1||s>N) || (f<1||f>N))
                {
                    printf("bad vertex");
                    return 0;
                }
            if (lng<0 || INT_MAX-lng<0)
                {
                    printf("bad length");
                    return 0;
                }
            A[s-1][f-1] = lng;
            A[f-1][s-1] = lng;
        }
    if(i<M)
        {
            printf("bad number of lines");
            return 0;
        }

    prim(A, N, 0);
    free(A);
    return 0;
}
