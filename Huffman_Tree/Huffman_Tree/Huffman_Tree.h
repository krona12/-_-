#pragma once
#include"Tree.h"
int num = 27;
int weight_arr[27] = { 186,64,13,22,32,103,21,15,47,
									 57,   1,   5,32, 20,57, 63,  15,  1 ,
								   48	,51	,80	,23	,8	,18,	1	,16	,1 };
char name_arr[27] = { ' ','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

// ≤‚ ‘ ˝æ›
//int num = 4;
//int weight_arr[4] = { 2,1,5,4 };
//char name_arr[4] = { 'A','B','C','D' };
vector<Tree> Huffman_Tree;
void Initial_Huffman();
void Create_Huffman( int n);
vector<int> En_Code(string str);
string De_Code(vector<int> vec);
