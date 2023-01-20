#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Matrix.h"

int main(int argc, char *argv[]){
	FILE *in, *out;
	int op = 0, n, NZA, NZB, i, j;
	double x;
	char buf[512];
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n",argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("Unable to open file %s for reading\n",argv[1]);
		exit(1);
	}

	out = fopen(argv[2], "w");
	if(out == NULL){
		printf("Unable to open file %s for writing\n",argv[2]);
		exit(1);
	}

	Matrix A = NULL;
	Matrix B = NULL;
	while(fgets(buf,512,in) != NULL){
		switch(op){
			case 0:
				if(strcmp(buf,"\n") != 0){
					sscanf(buf,"%d %d %d",&n,&NZA,&NZB);
					A = newMatrix(n);
					B = newMatrix(n);
				}else{
					op++;
				}
				break;
			case 1:
				if(strcmp(buf,"\n") !=0){
					sscanf(buf,"%d %d %lf",&i,&j,&x);
					changeEntry(A,i,j,x);
				}else{
					op++;
				}
				break;
			case 2:
				if(strcmp(buf,"\n") != 0){
					sscanf(buf,"%d %d %lf",&i,&j,&x);
					changeEntry(B,i,j,x);
				}else{
					op++;
				}
				break;
		}
	}
	fclose(in);
	
	fprintf(out,"A has ");
	if(NNZ(A) > 1){
		fprintf(out,"%d non-zero entries:\n",NNZ(A));
	}else{
		fprintf(out,"%d non-zero entry:\n",NNZ(A));
	}
	printMatrix(out,A);
	fprintf(out,"\n");


	fprintf(out,"B has ");
        if(NNZ(B) > 1){
                fprintf(out,"%d non-zero entries:\n",NNZ(B));
        }else{
                fprintf(out,"%d non-zero entry:\n",NNZ(B));
        }
	printMatrix(out,B);
	fprintf(out,"\n");
	
	
	Matrix C,D,E,F,G,H,I,J;
	
	C = scalarMult(1.5,A);
	fprintf(out,"(1.5)*A =\n");
	printMatrix(out,C);
	fprintf(out,"\n");

	D = sum(A,B);
	fprintf(out,"A+B =\n");
	printMatrix(out,D);
	fprintf(out,"\n");
	
	E = sum(A,A);
	fprintf(out,"A+A =\n");
	printMatrix(out,E);
	fprintf(out,"\n");

	F = diff(B,A);
	fprintf(out,"B-A =\n");
	printMatrix(out,F);
	fprintf(out,"\n");
			
	G = diff(A,A);
	fprintf(out,"A-A =\n");
	printMatrix(out,G);
	fprintf(out,"\n");

	H = transpose(A);
	fprintf(out,"Transpose(A) =\n");
	printMatrix(out,H);
	fprintf(out,"\n");
	
	I = product(A,B);
	fprintf(out,"A*B =\n");
	printMatrix(out,I);
	fprintf(out,"\n");

	J = product(B,B);
	fprintf(out,"B*B =\n");
	printMatrix(out,J);
	fprintf(out,"\n");
	
	fclose(out);

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);
	freeMatrix(&J);
	
	return 0;
}
