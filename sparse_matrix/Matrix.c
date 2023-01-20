#include <stdio.h>
#include "Matrix.h"

// STRUCT //

typedef struct EntryObj *Entry;

typedef struct EntryObj{
	int col;
	double entry;
}EntryObj;

typedef struct MatrixObj{
	List *row;
	int size;
	int NNZ;

}MatrixObj;

// CONSTRUCTOR - DESTRUCTOR//
Matrix newMatrix(int n){
	// param: Int
	// return: Matrix
	// func: initailize a new matrix

	Matrix out = malloc(sizeof(MatrixObj));
	out->row = calloc(n+1,sizeof(List));
	for(int i = 1; i <= n;i++){
		out->row[i] = newList();
	}
	out->size = n;
	out->NNZ = 0;
	return out;

}

void freeEntry(Entry *pE){
	// param: Entry
	// return: None
	// func: free the memory that the individual entry is using

	free(*pE);
	*pE = NULL;
}

void freeMatrix(Matrix *pM){
	// param: Matrix
	// return: None
	// func: free the memory that the matrix is using

	for(int i = 1; i <= size(*pM);i++){
		moveFront((*pM)->row[i]);
		while(index((*pM)->row[i])>=0){
			Entry delete = get((*pM)->row[i]);
			freeEntry(&delete);
			moveNext((*pM)->row[i]);
			deleteFront((*pM)->row[i]);
		}
		freeList(&((*pM)->row[i]));
		(*pM)->row[i] = NULL;
	}
	free((*pM)->row);
	free(*pM);
	*pM = NULL;
}

// ACCESS FUNCTION //

int size(Matrix M){
	// param: Matrix
	// return: Int
	// func: return the size of the matrix, n in (nxn)

	return M->size;
}
int NNZ(Matrix M){
	// param: Matrix
	// return: Int
	// func: return the number of non-zero entry in the matrix

	return M->NNZ;
}

int equals(Matrix A, Matrix B){
	// param: Matrix
	// return: Int
	// func: return 1 if matrix A and B are the same, else return 0

	if(size(A) != size(B)){
		return 0;
	}
	for(int i = 1; i <= size(A);i++){
		if(length(A->row[i]) > 0 && length(B->row[i]) > 0){
			if(length(A->row[i]) == length(B->row[i])){
				moveFront(A->row[i]);
				moveFront(B->row[i]);
				while(index(A->row[i])>=0 && index(B->row[i])>=0){
					Entry eA = get(A->row[i]), eB = get(B->row[i]);
					if((eA->col != eB->col) || (eA->entry != eB->entry)){
						return 0;
					}
					moveNext(A->row[i]);
					moveNext(B->row[i]);
				}
			}else{
				return 0;
			}
		}
	}
	return 1;
}

double vectorDot(List P, List Q){
	// param: List
	// return: double
	// func: return the dot product of two list

	moveFront(P);
	moveFront(Q);
	double res = 0;
	while(index(P)>=0 && index(Q)>=0){
		Entry eP = get(P), eQ = get(Q);
		if(eP->col == eQ->col){
			res += eP->entry * eQ->entry;
			if(P != Q){
				moveNext(P);
				moveNext(Q);
			}else{
				moveNext(P);
			}
		}else if(eP->col > eQ->col){
			moveNext(Q);
		}else if(eQ->col > eP->col){
			moveNext(P);
		}
	}
	return res;
}

// MANIPULATION PROCEDURES //

void makeZero(Matrix M){
	// param: Matrix
	// return: None
	// func: set all the entry in the matrix to zero

	for(int i = 1; i <= size(M); i++){
		if(length(M->row[i]) > 0){
			moveFront(M->row[i]);
			while(index(M->row[i])>=0){
				Entry del = get(M->row[i]);
				freeEntry(&del);
				moveNext(M->row[i]);
				deleteFront(M->row[i]);
			}
		}
	}
	M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
	// param: Matrix, int, double
	// return: None
	// func: set a value at i-th row and j-th column in the matrix 

	if( i < 1 || i > size(M) || j < 1 || j > size(M)){
		printf("Matrix error -called changeEntry(): out of range... Exiting Program\n");
		freeMatrix(&M);
		exit(EXIT_FAILURE);
	}
	if(x!= 0){
		if(length(M->row[i]) == 0){
			Entry info = malloc(sizeof(EntryObj));
			info->col = j;
			info->entry = x;
			append(M->row[i],info);
			M->NNZ++;
			return;
		}else{
			Entry Back = back(M->row[i]);
			if(j > Back->col){
				Entry info = malloc(sizeof(EntryObj));
				info->col = j;
				info->entry = x;
				append(M->row[i],info);
				M->NNZ++;
				return;
			}
		}
	}
	moveFront(M->row[i]);
	while(index(M->row[i])>=0){
		Entry ptr = get(M->row[i]);
		if(ptr->col == j){
			if(x != 0){
				ptr->entry = x;
			}else{
				freeEntry(&ptr);
				delete(M->row[i]);
				M->NNZ--;
			}
			return;
		}else if(j < ptr->col){ 
			if(x != 0){
				Entry info = malloc(sizeof(EntryObj));
				info->col = j;
				info->entry = x;
				insertBefore(M->row[i],info);
				M->NNZ++;
				return;
			}
		}
		moveNext(M->row[i]);
	}
}

Matrix copy(Matrix A){
	// param: Matrix
	// return: Matrix
	// func: return a copy of a matrix

	Matrix out = newMatrix(size(A));
	for(int i = 1; i<= size(A); i++){
		if(length(A->row[i]) > 0 ){
			moveFront(A->row[i]);
			while(index(A->row[i])>=0){
				Entry info = get(A->row[i]);
				changeEntry(out,i,info->col,info->entry);
				moveNext(A->row[i]);
			}	
		}
	}
	return out;
}

Matrix transpose(Matrix A){
	// param: Matrix
	// return: Matrix
	// func: return a transpose version of a matrix

	Matrix out = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) > 0){
			moveFront(A->row[i]);
			while(index(A->row[i])>=0){
				Entry info = get(A->row[i]);
				if(info->entry != 0){
					changeEntry(out,info->col,i,info->entry);
				}
				moveNext(A->row[i]);
			}
		}
	}
	return out;
}

Matrix scalarMult(double x, Matrix A){
	// param: double, Matrix
	// return: Matrix
	// func: return a new Matrix that had been multiplied

	Matrix out = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) > 0){
			moveFront(A->row[i]);
			while(index(A->row[i])>=0){
				Entry info = get(A->row[i]);
				double res = info->entry * x;
				if(res != 0){
					changeEntry(out,i,info->col,res);
				}
				moveNext(A->row[i]);
			}
		}
	}
	return out;
}

// HELPER //

double add(double x, double y){
	return x + y;
}

double sub(double x, double y){
	return x - y;
}
void operation(Matrix M, int i,List P, List Q, double (*op)(double,double)){
	// param: Matrix, int, List, function (that return a double)
	// return: None
	// func: do the selected operation on there two matrcies.

	moveFront(P);
	moveFront(Q);
	while(index(P)>=0 || index(Q)>=0){
		Entry eP = NULL, eQ = NULL;
		int cP = size(M) + 1, cQ = size(M) + 1, c;
		double res = 0;

		if(index(P)>=0){
			eP = get(P);
			cP = eP->col;
		}

		if(index(Q)>=0){
			eQ = get(Q);
			cQ = eQ->col;
		}
		if(cQ == cP){
			res = op(eP->entry,eQ->entry);
			c = cP;
			if(P != Q){               // for situation when A+A
				moveNext(P);
				moveNext(Q);
			}else{
				moveNext(P);
			}	
		}else if(cP < cQ){
			res = op(eP->entry,0);
			c = cP;
			moveNext(P);
		}else if(cQ < cP){
			c = cQ;
			res = op(0,eQ->entry);
			moveNext(Q);
		}
		if(res != 0){
			changeEntry(M,i,c,res);
		}
	}
}
/***********************************************/
Matrix sum(Matrix A, Matrix B){
	// param:
	// return:
	// func:

	if(size(A) != size(B)){
		printf("Matrix Error -caled sum(): different size... Exiting Program\n");
		freeMatrix(&A);
		freeMatrix(&B);
		exit(EXIT_FAILURE);
	}
	Matrix out = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) > 0 || length(B->row[i]) > 0){
			operation(out,i,A->row[i],B->row[i],add);
		}
	}
	return out;
}

Matrix diff(Matrix A, Matrix B){
	// param:
	// return:
	// func:

	if(size(A) != size(B)){
		printf("Matrix Error -called diff(): different size... Exiting Program\n");
		freeMatrix(&A);
		freeMatrix(&B);
		exit(EXIT_FAILURE);
	}
        Matrix out = newMatrix(size(A));
        for(int i = 1; i <= size(A); i++){
                if(length(A->row[i]) > 0 || length(B->row[i]) > 0){
			operation(out,i,A->row[i],B->row[i],sub);
                }
        }
        return out;	

}

Matrix product(Matrix A, Matrix B){
	// param:
	// return:
	// func:

	if(size(A) != size(B)){
		printf("Matrix Error -called product(): different size... Exiting Program\n");
		freeMatrix(&A);
		freeMatrix(&B);
		exit(EXIT_FAILURE);
	}
	Matrix BT = transpose(B);
	Matrix out = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) > 0){
			for(int j = 1; j <= size(BT);j++){
				if(length(BT->row[j])>0){
					double res = vectorDot(A->row[i],BT->row[j]);
					if(res != 0){
						changeEntry(out,i,j,res);
					}
				}
		
			}
		}
	}
	freeMatrix(&BT);
	return out;
}
// OTHER //

void printMatrix(FILE *out, Matrix M){ 
	// param:
	// return:
	// func:

	for(int i = 1; i <= size(M);i++){
		if(length(M->row[i]) > 0){
			fprintf(out,"%d:",i);
			moveFront(M->row[i]);
			while(index(M->row[i])>=0){
				Entry info = get(M->row[i]);
				fprintf(out," (%d, %.1f)",info->col,info->entry);
				moveNext(M->row[i]);
			}
			fprintf(out,"\n");
		}
	}
}




