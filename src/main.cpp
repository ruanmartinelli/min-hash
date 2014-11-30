#include <iostream>
#include <functional>
#include <set>
#include <vector>  
#include <string>  
#include <iterator>
#include <cmath>
#include <algorithm>

#define A 	23 		
#define B 	89			
#define C 	211		

#define MAX 5

using namespace std;

int minHash(const char* s)
{
	unsigned h = 31 /* also prime */;
	while 	(*s)
	{
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h; 			// or return h % C;
}

int min(	int* set,
			int menor)
{
	int min = menor;
	for (unsigned i = 0; i < MAX; i++)
	{
		if (set[i] < min)
		{
			min = set[i];
		}
	}
	return min;
}

void fillHash(	const char** set,
				int* hashSet)
{
	for (unsigned i = 0; i < MAX; ++i)
	{
		hashSet[i] = minHash(set[i]);
	}

}

int findRealSize(	vector<int> set,
					int size)
{
	int rSize;
	for(int i = 0; i < size; i++)
	{
		if(set[i] != 0)
			rSize++;
	}
	return rSize;
}

float calculateJaccardCoefficient(	float uni,
									float intersec)
{
	return intersec/uni;
}

int main() {

	
	const char* set1[MAX] 		= { "1", "2", "3", "5", "8"	};		/* set1, set2: conjuntos de elementos de tamanho MAX */
	const char* set2[MAX] 		= { "1", "3", "5", "7", "9"	};
	
	int 		hashSet1[MAX];										/* hashSet1, hashSet2: vetor com os valores de Hash de cada elemento do conjutno*/
	int 		hashSet2[MAX];
	
	float		uni;												/* Cardinalidade da união */
	float		intersec;											/* Cardinalidade da interseção*/
	float 		j;													

	vector<int> v1(MAX*2);											/* v1, v2: vetores para armazenar o resultado do sort */
	vector<int> v2(MAX*2); 
	

	fillHash	(set1, hashSet1);									/* Popula o vetor de hashs*/
	fillHash	(set2, hashSet2);
	
	sort				(hashSet1, hashSet1 + MAX);					/* Ordena de forma crescente */
	sort				(hashSet2, hashSet2 + MAX);
	
	set_union 			(hashSet1, 
							hashSet1+MAX,
							hashSet2,
							hashSet2+MAX,
							v1.begin()
						);											/* Armazena a união no vetor v1*/
	
	set_intersection	(	hashSet1,
							hashSet1+MAX,
							hashSet2,
							hashSet2+MAX,
							v2.begin()
						);											/* Armazena a interseção no vetor v2*/
	
	uni 		= findRealSize(v1,MAX*2);							/* uni, intersec: Calcula o tamanho dos vetores sem zeros (cardinalidade do conj.) */
	intersec 	= findRealSize(v2, MAX*2);									
	j 			= calculateJaccardCoefficient(uni, intersec);		/* Calcula o índice de Jaccard */
	
	cout << "Coeficiente de Jaccard: " << j << 										endl;	
	cout << "Esse valor representa  similaridade de dois conjuntos finitos." << 	endl;
	cout << "Na estrutura de dados MinHash, o coeficiente de Jaccard representa" << endl;
	cout << "também a probabilidade do menor valor de hash do conjunto ser igual"<<	endl;
	cout << "ao menor valor do outro conjunto." << endl;
	
	system("pause");
	return 	0;
}

