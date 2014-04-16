#include <vector>
using namespace std;
#pragma once
class Matrix
{
private:
	int n;
	int m;
	
	
public:
	int **matrix;
	int **all_combinations;
	int  index;
	int num_of_combinations;
	bool are_eq;
	Matrix();
	Matrix(int n, int m, int k);
	Matrix(int n, int m, int k, int p);
	~Matrix(void);

	void FillMatrix();
	void FillMatrix(int row);
	void PrintMatrix();
	void NewCombinations(int num_of_com, int p);
	int* getColumn(int i);
	int* getRow(int *i, int index, int size);
	int** getColumns(int * i,int size);
	int** getRows(int * cols,int size);
	bool CompareTwoArrays(int * a, int *b, int p);
	void AllColumnCombinations(int k);
	void Combinations(int offset, int k, vector<int> elements, vector<int> combination);
	void Combinations(int offset, int k, vector<int> elements, vector<int> combination, int size); 
	void Combinations(int offset, int k, vector<int> elements, vector<int> combination, int ** columns, int size, int p);
	void CreateRandomMatrix(int n, int m, int num_of_mat,int logic);

	void pretty_print(const vector<int>& v,int index); 
	int numRows() {return this->n;}
	int munColumns() {return this->m;}
};
