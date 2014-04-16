// Matrice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "Matrix.h"
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
using namespace std;

int ** multiple_combinations;
//int index =0;

void InsertCombinations(const vector<int>& v, int *index) {
  static int count = 0;
  cout << "combination no " << (++count) << ": [ ";
  for (int i = 0; i < v.size(); ++i) 
  { 
	  //cout << v[i]-1 << " "; 
	  multiple_combinations[*index-1][i] = v[i]-1;
	  cout << *index-1;
  }
  cout << "] " << endl;
}

void MultipleCombinations(int offset, int k, vector<int> elements, vector<int> combination, int * index) {
	//cout <<*x << endl;
  if (k == 0) {
	  *index = *index+1;
    InsertCombinations(combination, index);
    return;
  }
  for (int i = offset; i <= elements.size() - k; ++i) {
    combination.push_back(elements[i]);
	MultipleCombinations(i+1, k-1, elements, combination, index);
    combination.pop_back();
  }
}



long long Factorial(long long x) 
{
   return (x == 1 ? x : x * Factorial(x - 1));
}

unsigned long long factorial(long long n) 
{
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}


int _tmain(int argc, wchar_t *argv[])
{
	
	int k = 2;
	int n;
	int t;
	int m;
	int p;
	int logic; // 1 - binarna logika, 2 - troznacna ...
	// t == m
	//racunam broj kombinacija t, p 
	
	int matrixes;
	long long num_of_comb;

	cout << "Insert number of matrices: ";
	cin >> matrixes;
	cout << endl;

	cout << "Set matrix size" << endl;
	cout << "Number of rows = ";
	cin >> n;
	cout << "Number of columns = ";
	cin >> m;
	cout << endl;
	t = m;
	int value = log(float(n)) / log(2.0) + 0.9;
	p = 0;
	cout << "Number of bits for coding: ";
	cin >> p;
	if (p < value)
	{
		while (p<value)
		{
			cout << "Number of bits for coding must be more than " << value << endl;
			cout << "Number of bits for coding: ";
			cin >> p;
		}

	}
	if (p > m)
	{
		while (p > m || p<value)
		{
			if (p < value)
			{
				cout << "Number of bits for coding must be more than " << value << endl;
				cout << "Number of bits for coding: ";
			}
			else
			{
				cout << "Number of bits for coding must be less than number of columns" <<endl;
				cout << "Number of bits for coding: ";
			}
			cin >> p;
		}
	}
	cout << endl;

	cout << "Logic (1 for binary): ";
	cin >> logic;
	cout << endl;
	if(t==p)
		num_of_comb = 1;
	else
		num_of_comb = Factorial(t)/(Factorial(p)*(Factorial(t-p)));

   
	
   cout<<endl;
   cout<<endl;
   const clock_t begin_time = clock(); // pocetak racunanja vremena
	vector<int> elements;
	vector<int> col_elements;
    vector<int> combination;
	//kombinacije za vrste, prilikom ispitivanja
	for (int i = 0; i < n; ++i) 
	{ 
		elements.push_back(i+1); 
	}
	//sve moguce kombinacije kolona, za koje se formiraju vrste
	for (int i = 0; i < t; ++i) 
	{ 
		col_elements.push_back(i+1); 
	}

	////////////////// NOVO ////////////////
	int comb = Factorial(n)/(Factorial(2)*(Factorial(n-2)));
	cout << comb;
	multiple_combinations = new int*[comb]; // vrste
	int index = 0;
	for (int i = 0; i < comb; ++i) {
	 multiple_combinations[i] = new int[2]; //za svaku vrstu pravimo kolonu
	}
	MultipleCombinations(0,2,col_elements, combination, &index);

	int tmp = 0;
	while(tmp == 0 && p <=m)
	{
		if(t==p)
		num_of_comb = 1;
	else
		num_of_comb = Factorial(t)/(Factorial(p)*(Factorial(t-p)));

	//Combinations(0, 4, col_elements, combination);
	Matrix * mat = new Matrix(n,m, num_of_comb, p);
	mat->CreateRandomMatrix(n,m, matrixes, logic+1); //generisemo n matrica reda n x m 
	mat->index = 0;
	mat->num_of_combinations = num_of_comb; // n = 6, r = 3
	mat->Combinations(0,p,col_elements, combination, 0);


	ofstream myfile;
    myfile.open ("result.txt");
 
	int pera;
	
/*	for(int i=0;i<;i++)  // loop 3 times for three lines
	{
		for(int j=0;j<p;j++)  // loop for the three elements on the line
		{
			cout<<multiple_combinations[i][j];  // display the current element out of the array
			cout << " ";
		}
		cout<<endl;  // when the inner loop is done, go to a new line
		 
	}*/

  for(int counter =0; counter < matrixes; counter ++)
  {
	  //ucitavanje niza iz fajla i smestanje u matricu
	  mat->FillMatrix(counter);
	  myfile << "Matrix: " << counter << " "<< endl <<endl;
		for(int i=0;i<n;i++)  //
		{
			for(int j=0;j<m;j++)  // 
			{
				myfile<<mat->matrix[i][j];  // display the current element out of the array
				myfile << " ";
			}
		 myfile<<endl;  // when the inner loop is done, go to a new line
		}
		int tmp2 =0;

	  //uzimamo svaku kombinaciju kolona
	  for(int i=0; i<mat->num_of_combinations; i++)
	  {
		int ** rows = mat->getRows(mat->all_combinations[i],p);
		
		//kombinacije svih vrsta za izabrane kolone
		mat->Combinations(0,k,elements,combination, rows, n, p);
	
		int * index = mat->all_combinations[i];
		if(mat->are_eq == false)
		{   
			tmp2++;
			myfile << "Index: [";
			int brojac=0;
			for(brojac;brojac<p-1;brojac++)  // loop 3 times for three lines
			{
				myfile <<index [brojac]<< ", ";
			}
			myfile << index [brojac] << "]"<< endl;
			myfile << "Rows: " <<endl <<endl;
			
			for(int i=0;i<n;i++)  // loop 3 times for three lines
			{
				for(int j=0;j<p;j++)  // loop for the three elements on the line
				{
					myfile<<rows[i][j];  // display the current element out of the array
					myfile << " ";
				}
			 myfile<<endl;  // when the inner loop is done, go to a new line
		 
			}
			myfile<<"-----------------------------------------------" << endl;
		}
		mat->are_eq = false;
		
	  }
	  if(tmp2>0)
		  tmp ++;
	  myfile<<"___________ END ______________" << endl;
    }
    myfile.close();
	cout << "Number of solutions: " << tmp << endl;
	cout << "Number of bits for coding: " << p << endl;
	cout << "_____________________________" << endl;
	p++;
	}
  cout << "Required time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<"s" <<endl;

   
  system("pause");

 
  return 0;
}



