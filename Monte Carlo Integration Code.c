#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double Function(double x, double y, double z){
	double fx;
	fx = (10+pow(x,(3.0/2.0)));
	return(fx);
}

void main(){
	int i, N, xWidth, yWidth, zWidth;
	double xUpper, yUpper, zUpper, xLower, yLower, zLower, Result, Volume, Test1, Test2;
	N = 100000000;
	xUpper = 4;
	yUpper = sqrt(15);
	zUpper = 1;
	xLower = 1;
	yLower = -3;
	zLower = -1;
	
	xWidth = 3.5;
	yWidth = 7.5;
	zWidth = 2.5;
	
	double px[N], py[N], pz[N], Weight[N], WeightSum;
	
	WeightSum = 0;
	for(i=0; i<=(N-1); i++){
		px[i] = (((rand()%(xWidth*1000000))/1000000.0)+xLower-((xWidth-(xUpper-xLower))/2));
		py[i] = (((rand()%(yWidth*1000000))/1000000.0)+yLower-((yWidth-(yUpper-yLower))/2));
		pz[i] = (((rand()%(zWidth*1000000))/1000000.0)+zLower-((zWidth-(zUpper-zLower))/2));
		
		if((pow(pz[i],2)+pow((sqrt(pow(px[i],2)+pow(py[i],2))-3),2))<=1){
			Weight[i] = Function(px[i], py[i], pz[i]);
		} else {
			Weight[i] = 0;
		}
		
		WeightSum=WeightSum+Weight[i];
	}
	printf("%e\n", WeightSum);
	Volume = xWidth*yWidth*zWidth;
	printf("%e\n", Volume);
	Result = ((WeightSum*Volume)/(N));
	printf("%e\n", Result);
}
