#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Tree
{
public:
	int weight;
	char name;
	Tree* Parents;
	Tree* LChild;
	Tree* RChild;
	vector<int> Code;
	Tree();
	Tree(int w,char n,Tree*P,Tree*L,Tree*R);
	void Show_Code();
};
