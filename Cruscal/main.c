#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647

typedef struct
{
    short int v1;
    short int v2;
    int wet;
}edge;

void min(int start, int end, edge* lst)
{

  int s = start, f = end;
  edge a;
  int m = lst[(s + f) / 2].wet;
  while(s<=f)
  {
      while(lst[s].wet<m) s++;
      while(lst[f].wet>m) f--;
      if(s<=f)
      {
          a = lst[s];
          lst[s] = lst[f];
          lst[f] = a;
          s++;
          f--;
      }
  }

  if(start<f) min(start, f, lst);
  if(end>s) min(s, end, lst);
}
void color(int* nodes, int N, int a, int b)
{
    for(int i = 0; i<N; i++) if (nodes[i] == b) nodes[i] = a;

}

void Kruskal(edge* edges, int N, int M, int* nodes)
{
    int i, j,k = 0, a, b;
    edge* res;
    res = (edge *)malloc((N)*sizeof(edge));
    if(!res) {
            printf("Allocation error.");
            return;
            }

    for(i = 0; i < M; i++)
    {
        a = edges[i].v1;
        b = edges[i].v2;
      if(nodes[a]!=nodes[b])
      {

            if(nodes[a]<0 && nodes[b]<0)
            {
              nodes[a] = nodes[a] * -1;
              nodes[b] = nodes[a];
            }
            else if(nodes[a]>0 && nodes[b]>0 )
            {
            color(nodes, N, nodes[a], nodes[b]);
            }
            else if(nodes[a]>0 && nodes[b]<0)
            {
              nodes[b] = nodes[a];
            }
            else if(nodes[a]<0 && nodes[b]>0)
            {
              nodes[a] = nodes[b];
            }
            res[k] = edges[i];
            k++;
      }
   }
   if (N==0)
   {
       printf("no spanning tree");
       return;
   }
   j = nodes[0];
   for(i = 0; i < N; i++) if (nodes[i]!=j)
   {
       free(res);
       printf("no spanning tree");
       return;
   }
   for(i = 0; i<k; i++)  printf("%d %d\n", res[i].v1+1, res[i].v2+1);
   free(res);
}

int main(){

    int N, M, s, f, lng, i, *nodes;
    edge* Edges = NULL;
    scanf("%d", &N);
    scanf("%d", &M);
    Edges = (edge *)malloc(M*sizeof(edge));
    nodes = (int*)calloc(N, sizeof(int));
    if(!Edges)
        {
            printf("Allocation error.");
            return 0;
        }
    if(!nodes)
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

    for(i = 0;scanf("%d %d %d", &s, &f, &lng)!= EOF ; i++)
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
            Edges[i].v1 = s-1;
            Edges[i].v2 = f-1;
            Edges[i].wet = lng;
        }
    if(i<M)
        {
            printf("bad number of lines");
            return 0;
        }
    for(i = 0; i < N; i++) nodes[i] = -1-i;
    min(0, M-1, Edges);
    Kruskal(Edges, N, M, nodes);
    free(nodes);
   return 0;
}

