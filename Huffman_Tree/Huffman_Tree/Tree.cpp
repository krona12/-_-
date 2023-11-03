#include"Tree.h"

Tree::Tree()
{
	this->weight = 0; this->name = '0'; this->Parents = NULL; this->LChild = NULL; this->RChild = NULL;
}

Tree::Tree(int w,char n, Tree* P, Tree* L, Tree* R)
{
	this->weight = w; this->name = n; this->Parents = P; this->LChild = L; this->RChild = R;
}

void Tree::Show_Code()
{
	cout << this->name << ":";
	for (int i = this->Code.size()-1; i>=0; i--)
	{
		cout << this->Code[i];
	}
	cout << endl;
}
