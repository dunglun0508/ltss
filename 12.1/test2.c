//Input: N
//Nhap A[i]=i & B[i]=2*i
//Tinh C
//Output: In ra A, B, C
#include<stdio.h>
#define N 10
int main(){
    int i,A[N], B[N], C[N];
    for( i=0;i<N;i++){
        A[i]=i;
        B[i]=2*i;
    }
    for(i=0;i<N;i++)
        C[i]= A[i]+B[i];
   
    printf("Mang A:\n");
    for (i=0;i<N;i++){
        printf("%d\t",A[i]);
        printf("\n");
    }
    printf("Mang B:\n");
    for(i=0;i<N;i++){
        printf("%d\t",B[i]);
        printf("\n");
    }
    printf("Mang C:\n");
    for(i=0;i<N;i++){
        printf("%d\t",C[i]);
        printf("\n");


    }
    
    
return 0;


}
