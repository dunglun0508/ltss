#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>

#define m 5
#define n 5
#define eps 0.001

int main(){

float *C,*C1,d,*west,*east,*south,*north;
C = (float *) malloc ((m*n)*sizeof(float));	
C1 = (float *) malloc ((m*n)*sizeof(float));
west = (float *) malloc ((m*n)*sizeof(float));	
east = (float *) malloc ((m*n)*sizeof(float));	
south = (float *) malloc ((m*n)*sizeof(float));	
north = (float *) malloc ((m*n)*sizeof(float));	
int i,j;

// Khoi tao
for ( i = 0 ; i < m ; i++ )
for ( j = 0 ; j < n ; j++ ){

*(C+i*n+j) = 0;

}
// vong lap
//do{
	
	for ( i = 0 ; i < m ; i++ )
		for ( j = 0 ; j < n ; j++ ){
			if(i==0) *(C1+i*n+j) =1.0;
            else if(i==(n-1)) *(C1+i*n+j) =0.0;
            else{
            	
				if(j==0)
                	*(west+i*n+j)= *(C);
            	else{
            		*(west+i*n+j) = *(C+i*n +(j-1));
            		
				}
				if(j==(m-1))
                	*(east+i*n+j)= *(C+i*n);
            	else{
            		*(east+i*n+j) = *(C+i*n +(j+1));	
				}
				if(i==0)
                	*(north+i*n+j)= 1;
            	else{
            		*(north+i*n+j) = *(C+(i-1)*n +j);	
				}
				if(i==(n-1))
                	*(south+i*n+j)= 0;
            	else{
            		*(south+i*n+j) = *(C+(i+1)*n +j);	
				}
				 *(C1+i*n+j) = (*(west+i*n+j) + *(east+i*n+j) + *(north+i*n+j) + *(south+i*n+j))/4;
            	
           
			}
			 *(C+i*n+j) = *(C1+i*n+j);
			
		}
	float max = 0;
	for ( i = 0 ; i < m ; i++ ){
		for ( j = 0 ; j < n ; j++ ){
			if(abs(*(C1+i*n+j)-*(C+i*n+j)) > max) max = abs(*(C1+i*n+j)-*(C+i*n+j));
			d=max;	
		}
	}
	printf("d = %f",d);
	
//	for (i=0;i<m;i++){
//		for(j=0;j<n;j++){
//			
//		}
//	}

//}while(d>eps);


for ( i = 0 ; i < m ; i++ )
for ( j = 0 ; j < n ; j++ ){
	printf("%f \t",*(C+i*n+j));
	
}
}
