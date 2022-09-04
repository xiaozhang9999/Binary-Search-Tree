using namespace std;
#include<iostream>
#include<string>
#include<stack>
#include<queue>
//�ڵ���
template<typename T>
struct Node
{
	T data;
	Node<T>* lchild;//����
	Node<T>* rchild;//�Һ���
	Node() { this->data = 0; this->lchild = NULL; this->rchild = NULL; };
	Node(T data) :data(data), lchild(NULL), rchild(NULL) {};
};
template<typename T>
class BSTree 
{
public:
	Node<T>* root;
	BSTree() { this->root = NULL; this->size = 0; }
	~BSTree() { Destroy(root); }
	int resize() { return size; }
	bool isEmpty() { return size == 0; }
	void add(T e);//���Ԫ��
	bool contains(T e);//�Ƿ����e
	void preOrder(); //ǰ�����	
	void inOrder(); //�������
	void postOrder();//�������
	void preOrderNR();//�ǵݹ�ʵ��ǰ�����
	void levelOrder();//�������
	T minimum();//������Сֵ
	T removeMin();//ɾ����Сֵ�ڵ㣬����ɾ��������ĸ��ڵ��ֵ
	void remove(T e);//ɾ��ֵΪe�Ľڵ�
private:
	int size;
	void Destroy(Node<T>*& r);//�ͷŽڵ�
	Node<T> *add(Node<T>* node, T e);//�ݹ����
	bool contains(Node<T>* node, T e);
	void preOrder(Node<T>* node);
	void inOrder(Node<T>* node);
	void postOrder(Node<T>* node);
	Node<T>* minimum(Node<T>* node);//�ݹ�ʵ�ַ�����nodeΪ���ڵ����Сֵ�ڵ�
	Node<T>* removeMin(Node<T>*node);//�ݹ�ɾ����nodeΪ���ڵ����Сֵ�ڵ�
	Node<T>* remove(Node<T>* node, T e);
};
template<typename T>
void BSTree<T>::Destroy(Node<T>*& r)
{
	if (r != NULL) {//���ƺ������
		Destroy(r->lchild);
		Destroy(r->rchild);
		delete r;
		r = NULL;
	}
}
template<typename T>
Node<T>* BSTree<T>::add(Node<T>* node, T e)
{
	if (node == NULL) {
		size++;
		return new Node<T>(e);
	}
	if (node->data > e)
		node->lchild=add(node->lchild, e);
	else if (node->data < e)
		node->rchild=add(node->rchild, e);
	return node;
}

template<typename T>
bool BSTree<T>::contains(Node<T>* node, T e)
{
	if (node == NULL) {
		return false;
	}
	if (node->data == e)
		return true;
	else if (node->data > e)
		return contains(node->lchild, e);
	else
		return contains(node->rchild, e);
}
template<typename T>
void BSTree<T>::preOrder(Node<T>* node)
{
	if (node == NULL)
		return;
	cout << node->data << " ";
	preOrder(node->lchild);
	preOrder(node->rchild);
}
template<typename T>
void BSTree<T>::inOrder(Node<T>* node)
{
	if (node == NULL)
		return;
	inOrder(node->lchild);
	cout << node->data << " ";
	inOrder(node->rchild);
}
template<typename T>
void BSTree<T>::postOrder(Node<T>* node)
{
	if (node == NULL)
		return;
	postOrder(node->lchild);
	postOrder(node->rchild);
	cout << node->data << " ";
}
template<typename T>
Node<T>* BSTree<T>::minimum(Node<T>* node)
{
	if (node->lchild == NULL)
		return node;
	return minimum(node->lchild);
}
template<typename T>
T BSTree<T>::minimum()
{
	Node<T>* min = minimum(root);
	return min->data;
}
template<typename T>
Node<T>* BSTree<T>::removeMin(Node<T>* node)
{
	if (node->lchild == NULL) {
		Node<T>* rightnode = node->rchild;
		delete node;
		node = NULL;
		size--;
		return rightnode;
	}
	node->lchild = removeMin(node->lchild);
	return node;
}
template<typename T>
T BSTree<T>::removeMin()
{
	T min = minimum();
	removeMin(root);
	return min;
}
template<typename T>
Node<T>* BSTree<T>::remove(Node<T>* node, T e)
{
	if (node == NULL)
		return NULL;
	if (e < node->data) {
		node->lchild= remove(node->lchild, e);
		return node;
	}
	else if (e > node->data) {
		node->rchild= remove(node->rchild, e);
		return node;
	}
	else {//e==node->data
		if (node->lchild == NULL) {
			Node<T>* rightnode = node->rchild;
			delete node;
			node = NULL;
			size--;
			return rightnode;
		}
		else if (node->rchild == NULL) {
			Node<T>* leftnode = node->lchild;
			delete node;
			node = NULL;
			size--;
			return leftnode;
		}
		else {
			//��ɾ���ڵ�d���Һ��Ӿ���Ϊ�գ��ҵ�s_>data����d->data����Сֵ��s����d
			Node<T>* s = minimum(node->rchild);
			s->rchild = removeMin(node->rchild);
			s->lchild = node->lchild;
			delete node;
			node = NULL;
			return s;
		}
	}
}
template<typename T>
void BSTree<T>::remove(T e)
{
	remove(root, e);
}
template<typename T>
void BSTree<T>::add(T e)
{
	root=add(root, e);
}

template<typename T>
bool BSTree<T>::contains(T e)
{
	return contains(root, e);
}

template<typename T>
void BSTree<T>::preOrder()
{
	preOrder(root);
	cout << endl;
}

template<typename T>
void BSTree<T>::inOrder()
{
	inOrder(root);
	cout << endl;
}

template<typename T>
void BSTree<T>::postOrder()
{
	postOrder(root);
	cout << endl;
}

template<typename T>
void BSTree<T>::preOrderNR()
{
	stack<Node<T>*> stack;
	stack.push(root);
	
	while (!stack.empty()) {
		Node<T>* cur = stack.top();
		cout << cur->data << " ";
		stack.pop();
		if (cur->rchild != NULL)
			stack.push(cur->rchild);
		if (cur->lchild != NULL)
			stack.push(cur->lchild);
	}	
	cout << endl;
}

template<typename T>
void BSTree<T>::levelOrder()
{
	queue<Node<T>*> queue;
	queue.push(root);
	while (!queue.empty()) {
		Node<T>* cur = queue.front();
		cout << cur->data << " ";
		queue.pop();
		if (cur->lchild != NULL)
			queue.push(cur->lchild);
		if (cur->rchild != NULL)
			queue.push(cur->rchild);
	}
	cout << endl;
}

int main() 
{
	BSTree<int> tree;
	int a[] = { 5,3,6,2,4,8,7 };
	for (int i = 0; i < 7; i++) {
		tree.add(a[i]);
	}
	cout << tree.root->data << endl;
	tree.preOrder();
	tree.inOrder();
	tree.postOrder();
	tree.preOrderNR();
	tree.levelOrder();
//	tree.removeMin();
//	tree.inOrder();
	tree.remove(6);
	tree.inOrder();
	return 0;
}