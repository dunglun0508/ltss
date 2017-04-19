#include <stdio.h>
#include <omp.h>
int main(){
	#pragma omp parallel
	printf("Number thread in laptop  %d\n", omp_get_num_threads() );
	return 0;
}