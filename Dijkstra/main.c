#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647
int min(int *minimum, int n, int* blue)
{
    int m = INT_MAX;
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        if (m >= minimum[i] && minimum[i] > 0 && !blue[i])
        {
            m = minimum[i];
            k = i;
        }
    }
    return k;
}
int path(int *j, int n)
{

    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (j[i] > 0 )
        {
            k++;
        }
    }
    return k;
}
void DIJKSTRA(int** G, int N, int s, int f)
{
    int *blue = calloc(N, sizeof(*blue)), *dmin = malloc(N * sizeof(int)), *d = calloc(N, sizeof(int)),  i, j, jmin =1, k = 0, end;
    if(!blue || !dmin || !d )
    {
        printf("Allocation error.");
        return;
    }
    for (i = 0; i < N; i++)
        {
            dmin[i] = INT_MAX;
        }
    dmin[s] = 0; blue[s] = 1; d[s]=1;
    j = s;
    do
    {
        jmin = 0;
        for (i = 0; i < N; i++)
        {
            if(i!=j && G[j][i]>=0 && dmin[i]-dmin[j]>=G[j][i])
                {
                dmin[i] = G[j][i]+dmin[j];
                d[i] = 1;
                blue[i] = 0;
                }
        }
        blue[j] = 1;
        for (i = 0; i < N; i++)
        {
            if(G[j][i]!=-1 && blue[i]==0) jmin = 1;
        }
        j = min(G[j],N,blue);

    }while(jmin);
    for (i = 0; i < N; i++)
    {
        if(blue[i] && d[i]) printf("%d ", dmin[i]);
        else if(blue[i]==0) printf("oo ");
        else if(!d[i]) printf("INT_MAX+ ");

    }
    printf("\n");
    j = f;
    if(!blue[f]) printf("no path");
    else if(!d[f])
    {
        if(k=path(G[j],N)>1) printf("overflow");
        else

            {
            printf("%d ", j+1);
            while(j!=s)
            {

                end = j;
                for (int i = 0; i < N; i++) if (G[j][i] > 0 && end!=i)j = i;
                printf("%d ", j+1);
            }
            }
    }
    else if(blue[f])
    { j = f;
    while (j != s)
    {
        for (int i = 0; i < N; i++)
            if (G[j][i] > 0 && (dmin[j] - G[j][i] == dmin[i] ))
            {
                printf("%d ", j+1);
                j = i;
            }
        if(j==s) printf("%d ", j+1);
    }
    free(dmin);
    free(blue);
    free(d);
    if(s == f) printf("%d ", j+1);
    }
}

int main()
{
    int N, S, F, M, s, f, lng, i, **A;
    scanf("%d", &N);
    scanf("%d %d", &S, &F);
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
    if((S<1||S>N) || (F<1||F>N))
        {
            printf("bad vertex");
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
    for(i = 0; scanf("%d %d %d", &s, &f, &lng)!=EOF; i++)
        {
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
    DIJKSTRA(A, N, S-1, F-1);
    free(A);
    return 0;
}
