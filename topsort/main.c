#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define INT_MAX 2147483647

typedef struct
{
    short int *edges;
    short int edges_count;
    short int color;
} vert;

typedef struct
{
    int v1;
    int v2;
} edge;

void popelem(short int* edges, int N, int e)
{
    int i = 0, k = 0;
    while(edges[i]!=e)
    {
        i++;
        k = i;
    }
    for(i = k; i < N-1; i++)
        edges[i] = edges[i+1];
    edges[N-1] = -1;
}

void topsort(vert* Vertex, int N)
{
    int *blue = calloc(N, sizeof(int)), i = 0, j, l, k = 0, r = 0;
    if(!blue)
    {
        printf("Allocation error.");
        return 0;
    }
    while(i<N)
    {

        if(!Vertex[i].edges_count && !Vertex[i].color)
        {
            for(l = 0; l < N; l++)
            {
                for (j = 0; j < Vertex[l].edges_count; j++)
                {
                    if (Vertex[l].edges[j] == i+1)
                    {
                        popelem(Vertex[l].edges, Vertex[l].edges_count, i+1);
                        Vertex[l].edges_count = Vertex[l].edges_count-1;
                    }
                }
            }
            Vertex[i].color +=1;
            blue[r] = i + 1;
            r +=1;
            k +=1;
        }
        i++;
        if(i==N && k)
        {
            i = 0;
            k = 0;
        }
    }
    for(i = 0; i < N; i++)
        if(!blue[i])
        {
            free(blue);
            return printf("impossible to sort");
        }
    for(i = 0; i<N; i++)
        printf("%d ", blue[i]);
    free(blue);
}

int main()
{
    int N=0, M=0, s, f, i, j = 0,l = 0;
    edge* Edges = NULL;
    vert* Vertex = NULL;
    if(scanf("%d", &N)==EOF)
        {printf("bad number of lines");
        return 0;}
    if(scanf("%d", &M)==EOF)
        {printf("bad number of lines");
        return 0;}
    Edges = (edge *)malloc(M*sizeof(edge));
    Vertex = (vert *)malloc(N*sizeof(edge));
    if(!Edges)
    {
        printf("Allocation error.");
        return 0;
    }
    if(!Vertex)
    {
        printf("Allocation error.");
        return 0;
    }
    for(i = 0; scanf("%d %d", &s, &f)!=EOF; i++)
    {
        if((s < 1||s > N) || (f < 1|| f> N))
        {
            printf("bad vertex");
            return 0;
        }
        Edges[i].v1 = s;
        Edges[i].v2 = f;
    }
    if(M < 0 || M > N*(N+1)/2)
    {
        printf("bad number of edges");
        return 0;
    }
    if(i + 1 < M + 1)
    {
        printf("bad number of lines");
        return 0;
    }
    if(N < 0 || N > 1000)
    {
        printf("bad number of vertices");
        return 0;
    }
    for(i = 0; i < N; i++)
    {
        Vertex[i].color=0;
        Vertex[i].edges_count = 0;
    }
    for(i = 0; i < M; i++)
    {
        Vertex[Edges[i].v2-1].edges_count = Vertex[Edges[i].v2-1].edges_count+1;
    }
    for(i = 0; i < N; i++)
    {
        Vertex[i].edges = (short int *)calloc(Vertex[i].edges_count, sizeof(edge));
        if(!Vertex[i].edges)
        {
            printf("Allocation error.");
            return 0;
        }
    }
    for(i = 0; i<M; i++)
    {
        j = 0;
        l = 0;
        while(j < Vertex[Edges[i].v2-1].edges_count && l==0 )
            {
                if(!Vertex[Edges[i].v2-1].edges[j])
                {
                     Vertex[Edges[i].v2-1].edges[j] = Edges[i].v1;
                     l++;
                }
                j++;
            }
    }
    topsort(Vertex, N);
    free(Vertex);
    free(Edges);
    return 0;
}
