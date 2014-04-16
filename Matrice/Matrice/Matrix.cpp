#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include "mtrand.h"
using namespace std;

Matrix::Matrix(void)
{

}

Matrix::~Matrix(void)
{
	delete [] matrix;
}

Matrix::Matrix(int n, int m, int num_of_com)
{
	this->n = n;
	this->m = m;
	this->matrix = new int*[n]; // vrste
	
	for (int i = 0; i < n; ++i) {
	  this->matrix[i] = new int[m]; //za svaku vrstu pravimo kolonu
	}
	this->are_eq = false;
	this->all_combinations = new int* [num_of_com]; // broj vrsta za matricu kombinacija
}

Matrix::Matrix(int n, int m, int num_of_com, int size)
{
	this->n = n;
	this->m = m;
	this->matrix = new int*[n]; // vrste
	
	for (int i = 0; i < n; ++i) {
	  this->matrix[i] = new int[m]; //za svaku vrstu pravimo kolonu
	}
	this->are_eq = false;
	this->all_combinations = new int* [num_of_com]; // broj vrsta za matricu kombinacija
	for (int i = 0; i < num_of_com; ++i) {
	  this->all_combinations[i] = new int[size]; //za svaku vrstu pravimo kolonu
	}
}

void Matrix::NewCombinations(int num_of_com, int size)
{
	this->are_eq = false;
	this->all_combinations = new int* [num_of_com]; // broj vrsta za matricu kombinacija
	for (int i = 0; i < num_of_com; ++i) {
	  this->all_combinations[i] = new int[size]; //za svaku vrstu pravimo kolonu
	}

}

void Matrix::FillMatrix()
{
   ifstream myfile;
   myfile.open("example.txt");
   string line;
   
	int size = this->n * this->m;
	getline(myfile,line);
	int * buffer = new int[size];

	for(int i = 0; i < size; i++)
	{
		buffer[i] = line[i]-48;
	}
	for (int i = 0; i < this->n; ++i) 
	{   // for each row
	  for (int j = 0; j < this->m; ++j) 
	  { // for each column
		this->matrix[i][j] = buffer[this->n*j + i];//rand() % 2;
	  }
	}
}

void Matrix::FillMatrix(int row)
{
   ifstream myfile;
   myfile.open("matrix.txt");
   string line;
   
	int size = this->n * this->m;

	for(int i=0; i<=row; i++)
		getline(myfile,line);

	int * buffer = new int[size];

	for(int i = 0; i < size; i++)
	{
		buffer[i] = line[i]-48;
	}

	for (int i = 0; i < this->n; ++i) 
	{   // for each row
	  for (int j = 0; j < this->m; ++j) 
	  { // for each column
		matrix[i][j] = buffer[this->n*j + i];//rand() % 2;
	  }
	}
}

void Matrix::PrintMatrix()
{
	
	for(int i=0;i<this->n;i++)  // loop 3 times for three lines
    {
        for(int j=0;j<this->m;j++)  // loop for the three elements on the line
        {
            cout<<this->matrix[i][j];  // display the current element out of the array
			cout << " ";
        }
	 cout<<endl;  // when the inner loop is done, go to a new line
    }
}




int * Matrix::getColumn(int i)
{
	int * column = new int[this->n];
	for(int j=0; j<this->n; j++)
		column[j] = this->matrix[j][i];

	return column;
}

int** Matrix::getColumns(int * column_index, int size)
{
	int **columns;

	columns = new int* [size];

	for (int j = 0; j < size; ++j) {
		columns[j] = getColumn(column_index[j]);
	  // each i-th pointer is now pointing to dynamic array (size 10) of actual int values
	}

	return columns;
}

int** Matrix::getRows(int * column_index, int size)
{
	int **rows;

	rows = new int* [this->n];

	for (int i = 0; i < this->n; ++i) {
		rows[i] = getRow(column_index, i, size);
	  // each i-th pointer is now pointing to dynamic array (size 10) of actual int values
	}

	return rows;
}

int * Matrix::getRow(int *i, int index, int size)
{
	int * row = new int[size];
	for(int j=0; j<size; j++)
	{
		row[j] = this->matrix[index][i[j]];
	}
	return row;
}

void Matrix::AllColumnCombinations(int k)
{
	//int k = 3;
	vector<int> elements;
    vector<int> combination;

	for (int i = 0; i < this->m; ++i) 
	{ 
		elements.push_back(i+1);
	}
    Combinations(0, k, elements, combination, k);
}

bool Matrix::CompareTwoArrays(int * a, int *b, int p)
{
	bool tmp = false;

	for(int i =0; i<p; i++)
	{
		if(a[i] == b[i])
			tmp = true;
		else 
		{
			tmp = false;
			break;
		}
	}

	return tmp;
}

//ovu f-ju treba da sredim, srediti ispitivanje kolona
void Matrix::Combinations(int offset, int k, vector<int> elements, vector<int> combination, int ** columns, int size, int p) {
  if (k == 0 ) 
  {
	if(CompareTwoArrays(columns[combination[0]-1], columns[combination[1]-1], p))
	{
		 this->are_eq = true;
	}
	return;
  }
  for (int i = offset; i <= elements.size() - k; ++i) {
    combination.push_back(elements[i]);
	Combinations(i+1, k-1, elements, combination, columns, size, p);
    combination.pop_back();
  }
}

void Matrix::pretty_print(const vector<int>& v, int index) {

  for(int i=0;i<v.size(); i++)
  {
	this->all_combinations[this->index-1][i] = v[i]-1; 
  }
}

void Matrix::Combinations(int offset, int k, vector<int> elements, vector<int> combination, int index) {
  if (k == 0 ) 
  {
	 pretty_print(combination, this->index++);
	 return;
  }
  for (int i = offset; i <= elements.size() - k; ++i) {
    combination.push_back(elements[i]);
	Combinations(i+1, k-1, elements, combination, index);
    combination.pop_back();
  }
}

void Matrix::CreateRandomMatrix(int n, int m, int num_of_mat, int logic)
{
	//rand() % 2;
	ofstream myfile;
    myfile.open ("matrix.txt");
	int * mat = new int[n*m];
	srand((unsigned)time(0));
	int random_integer;
	for(int i=0; i<num_of_mat; i++)
	{
		for(int j=0; j<n*m; j++)
		{
			random_integer = rand(); 
			myfile << random_integer %logic;
		}
		myfile << endl;
	}
  
  myfile.close();
}

