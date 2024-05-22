

#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main()
{
	BinarySearchTree<int> mina;
	mina.insert(6);
	mina.insert(2);
	mina.insert(8);
	mina.insert(1);
	mina.insert(5);
	mina.insert(3);
	mina.insert(4);
	mina.remove(6);
	mina.printTree();
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "does tree contains: " << i << " ? " << mina.contains(i) << endl;
	}
	cout << mina.findMax()<<endl;
	cout << mina.findMin()<<endl;

}