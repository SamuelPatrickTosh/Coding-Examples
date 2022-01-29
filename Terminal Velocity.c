double AirDensityFunc(double h){
	double p0, T0, g, L, R, M, p;
	p0 = 101325;
	T0 = 288.15;
	g = 9.80665;
	L = 0.0065;
	R = 8.31446;
	M = 0.0289652;
	
	p = ((p0*M)/(R*T0))*(1-pow(((L*h)/T0), (((g*M)/(R*L))-1)));
	
	return(p);
}

double DragForceFunc(double p, double v){
	double A, CD, FD;
	A = 0.1750;
	CD = 1;
	
	FD = (0.5*(p*pow(v, 2))*CD*A);
	
	return(FD);
}

double AnalyticalVelocityFunc(double p, double t){ 
	double m, g, A, CD, av;
	m = 100;
	g = 9.80665;
	A =  0.1750;
	CD = 1; 
	
	av = sqrt((2*m*g)/(p*A*CD))*tanh(t*sqrt((g*p*CD*A)/(2*m)));
	
	return(av);
}

void main(){
	FILE *DATA;
	DATA = fopen("Data.txt", "w");
	
	double SimulationLength, DeltaT;
	int LoopIterations;
	
	SimulationLength = 420;
	DeltaT = 0.05;
	LoopIterations = (SimulationLength/DeltaT)+1;
	
	int i;
	double h[LoopIterations], v[LoopIterations], t[LoopIterations], ax1[LoopIterations], ax2[LoopIterations], av1[LoopIterations], av2[LoopIterations], vi, hi;
	
	double h0, v0, m, FD, p, pSeaLvl, g;
	
	h0 = 39000;
	v0 = 0;
	m = 100;
	g = 9.80665;
	pSeaLvl = 1.225;
	
	h[0] = h0;
	v[0] = v0;
	t[0] = 0;
	
	h[1] = h[0] + (v[0]*DeltaT);
	v[1] = v[0] + ((g+((1/m)*(DragForceFunc(AirDensityFunc(h[0]), v[0]))))*DeltaT);
	t[1] = DeltaT;
	
	ax1[0] = h0;
	ax2[0] = h0;
	av1[0] = v0;
	av2[0] = v0;
	
	ax1[1] = h[1];
	ax2[1] = h[1];
	
	hi = 0;
	vi = 0;
	FD = 0;
	
	for(i = 1; i <= (LoopIterations-1); i++){
		
		hi = h[i-1] - (v[i-1]*DeltaT);
		vi = v[i-1] + (g*DeltaT)-(((1/m)*(DragForceFunc(AirDensityFunc(h[i-1]), v[i-1])))*DeltaT);
		
		av1[i] = AnalyticalVelocityFunc(pSeaLvl, (i*DeltaT));
		av2[i] = AnalyticalVelocityFunc(AirDensityFunc(ax2[i]), (i*DeltaT));
		
		ax1[i+1] = ax1[i-1] - (2*av1[i]*DeltaT);
		ax2[i+1] = ax2[i-1] - (2*av2[i]*DeltaT);
		
		t[i+1] = (i+1)*DeltaT;
		h[i+1] = h[i-1] - (2*vi*DeltaT);
		v[i+1] = v[i-1] + (2*g*DeltaT)-(2*((1/m)*(DragForceFunc(AirDensityFunc(hi), vi)))*DeltaT);
		
		fprintf(DATA, "%0.4e %0.4e %0.4e %0.4e %0.4e %0.4e %0.4e\n", t[i], h[i], v[i], av1[i], av2[i], ax1[i], ax2[i]);
	}
}
