#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main(){
	FILE *DATA;
	DATA = fopen("Data.txt", "w");
	FILE *DATAC;
	DATAC = fopen("DataC.txt", "w");
	int i, j, N, b, it, n;
	n = 1000000;
	N = 102;
	double v[N][N], vBound1, vBound2, vBound3, vBound4, R[n], RSUM, vij, itN;
	
	/*Empty the Array*/
	for(i=0; i<=(N-1); i++){
		for(j=0; j<=(N-1); j++){
			v[i][j] = 0;
		}
	}
	
	/*Define the Boundary Condition Values*/
	vBound1 = 0;
	vBound2 = 0;
	vBound3 = 0;
	vBound4 = 0;
	
	/*Place Boundary Condition Values into the Array*/
	for(b=1; b<=(N-2); b++){
		v[0][b] = vBound2;
		v[N-1][b] = vBound3;
		v[b][0] = (6*sin((M_PI*b)/(N-2)));
		v[b][N-1] = vBound4;	
	}
	
	/*Begin Construction of Array over n Iterations*/
	for(it=1; it<=n; it++){
		for(i=1; i<=(N-2); i++){
			for(j=1; j<=(N-2); j++){
				vij = v[i][j];
				v[i][j] = 0.25*(v[i+1][j]+v[i-1][j]+v[i][j+1]+v[i][j-1]);
				RSUM = (fabs(v[i][j]-vij)/fabs(v[i][j]));
			}
		}
		R[it-1] = (1/pow(N,2))*RSUM;
		fprintf(DATAC, "%d %e\n", it, R[it-1]);
		if(R[it-1] == 0){
			itN = it/pow(N,2);
			printf("%d\n", it );
			it = n+1;
		}
	}
	
	for(i=0; i<=(N-1); i++){
		for(j=0; j<=(N-1); j++){
			fprintf(DATA, "%d %d %e\n",  i, j, v[i][j]);
		}
	}
	
	
}
