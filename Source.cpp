#include <iostream>

using namespace std;
#include<vector>
#include<map>
struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;

	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->i = q->i;
	q = p;
	p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->i < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->i > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->i < pRoot->i)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}
/*Function takes a Root, a path vecotor, and a map to store paths and distances*/
void Summation(Node*& pRoot,int sum, vector<int> path, map<vector<int>, int > & x) { 
	sum += pRoot->i;     // we are summing distances up to that node.                                                             
	path.push_back(pRoot->i);  // we are adding that node to path vector.
	if (!pRoot->pRight && !pRoot->pLeft) {
		x.emplace(path, sum);       // if there is no way from that node , we are emplacing path,distance pair to the map.
	}
	if (pRoot->pRight) {
		Summation(pRoot->pRight, sum,path,x); //if proot has right side child, we continue with this root.
	}
	
	if (pRoot->pLeft) {
		Summation(pRoot->pLeft, sum,path,x);  //if proot has left side child, we continue with this root.
	}
	
}
void Sorting(map<vector<int>, int > Distance) {
	auto itbiggest = Distance.begin();         // itbiggest equals first object of map in the firstç
	for (auto it = Distance.begin(); it != Distance.end(); it++) {
		if (it->second > itbiggest->second) {     //if "it"'s second is bigger than itbiggest second then we assign it to itbiggest.
			itbiggest = it;
		}
	}

	vector<int>path1 = itbiggest->first;
	int distance = itbiggest->second;           //now, itbiggest's first is our path and it biggest's second is largest Sum.
	cout << "Branch with the largest sum is: ";
	for (int i = 0; i < path1.size(); i++) {              
		cout << path1[i] << " ";
	}
	cout << " -> Sum : " << distance << endl;

}
void main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}
	int sum = 0;
	vector<int> path;
	map<vector<int>, int > Distance;
	PrintTree(pRoot, 1);
	Summation(pRoot, sum,path,Distance);
	Sorting(Distance);
}
