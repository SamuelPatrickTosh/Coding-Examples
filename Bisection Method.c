#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fx(double x){
	double y;
	y = (pow(x, 3))-(7*pow(x, 2))+(14*x)-8;
	return(y);
}

void main(){
	FILE *DATA;
	DATA = fopen("Data.txt", "w");
	
	int Iterations;
	double a, b, xu, xl, xGuess, y, fxu, fxl, ySign, fxuSign, fxlSign, WhileTest;
	
	a = 4.5;
	b = 3;
	WhileTest = 0;
	Iterations = 0;
	
	xu = a;
	xl = b;
	
	while(WhileTest==0){
		xGuess = (xu+xl)/2;
		y = fx(xGuess);
		fxu = fx(xu);
		fxl = fx(xl);
		
		if(y == 0){
			WhileTest = 1;
		}
		
		ySign = y/fabs(y);
		fxuSign = fxu/fabs(fxu);
		fxlSign = fxl/fabs(fxl);
		
		if(ySign == fxuSign){
			xu = xGuess;
		} else if(ySign == fxlSign){
			xl = xGuess;
		}
		Iterations = Iterations + 1;
	}
	printf("%e\n", xGuess);
	printf("%d\n", Iterations);
}
