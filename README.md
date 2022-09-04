# Binary-Search-Tree
# 树结构
将数据使用树结构存储后，出奇高效。
二分搜索树：有序
平衡二叉树：AVL；红黑树；
堆；并查集；（对数据某类特殊操作进行高效处理）
线段树；Trie（字典树，前缀树）；（处理特殊数据）
## 二分搜索树
Binary Search Tree，是二叉树。
二叉树：
 - 动态数据结构
 - 唯一的根节点，有左右孩子Node lchild;Node rchild
 - 每个节点最多两个孩子，一个父亲
 - 具有天然递归结构（每个节点左子树/右子树也是二叉树）
 - 二叉树不一定都是“满”的，除叶子节点无左右孩子外其他节点也不一定是全都有左右孩子。
 - 一个节点/NULL也是二叉树。

二分搜索树：

 - 每个节点值大于其左子树所有节点值，小于其右子树所有节点值
 - 存储元素必须有可比较性

### 二分搜索树结构
定义一个节点结构体Node包括左、右孩子指针，和数据data，和一个BSTree类包括节点Node指针为树的根节点root。
```c++
//节点域
template<typename T>
struct Node
{
	T data;
	Node<T>* lchild;//左孩子
	Node<T>* rchild;//右孩子
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
	void add(T e);//添加元素
	bool contains(T e);//是否包含e
	void preOrder(); //前序遍历	
	void inOrder(); //中序遍历
	void postOrder();//后序遍历
	void preOrderNR();//非递归实现前序遍历
	void levelOrder();//层序遍历
	T minimum();//查找最小值
	T removeMin();//删除最小值节点，返回删除后的树的根节点的值
	void remove(T e);//删除值为e的节点
private:
	int size;
	void Destroy(Node<T>*& r);//释放节点
	Node<T> *add(Node<T>* node, T e);//递归添加
	bool contains(Node<T>* node, T e);
	void preOrder(Node<T>* node);
	void inOrder(Node<T>* node);
	void postOrder(Node<T>* node);
	Node<T>* minimum(Node<T>* node);//递归实现返回以node为根节点的最小值节点
	Node<T>* removeMin(Node<T>*node);//递归删除以node为根节点的最小值节点
	Node<T>* remove(Node<T>* node, T e);
};
template<typename T>
void BSTree<T>::Destroy(Node<T>*& r)
{
	if (r != NULL) {//类似后序遍历
		Destroy(r->lchild);
		Destroy(r->rchild);
		delete r;
		r = NULL;
	}
}
```

### 添加新元素
从根节点root开始，新元素与根节点的data值比较，比根节点小，添加到左子树（递归调用添加函数，以根节点左孩子为根节点）；比根节点大，添加到右子树（递归调用添加函数，以根节点右孩子为根节点）；相等则不添加该元素。此时二分搜索树不包含重复元素，若要包含可直接在添加时的条件改为小于等于根节点时递归左子树（或者大于等于根节点时递归右子树）。
```c++
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
	retu
rn node;
}
void BSTree<T>::add(T e)
{
	root=add(root, e);
}
```
### 查询，是否包含元素e
递归实现，将e与根节点的data比较，小于则递归访问左子树，大于则递归访问右子树，等于则说明包含返回true；若访问到NULL则不包含元素e返回false。
```c++
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
bool BSTree<T>::contains(T e)
{
	return contains(root, e);
}
```
### 前序遍历
也可以理解为深度优先遍历。

> 输出节点data
> 递归左子树
> 递归右子树

```c++
template<typename T>
void BSTree<T>::preOrder(Node<T>* node)
{
	if (node == NULL)
		return;
	cout << node->data << " ";
	preOrder(node->lchild);
	preOrder(node->rchild);
}
```
### 中序遍历
遍历结果是按顺序的

> 递归左子树
> 输出节点data
> 递归右子树

```c++
template<typename T>
void BSTree<T>::inOrder(Node<T>* node)
{
	if (node == NULL)
		return;
	inOrder(node->lchild);
	cout << node->data << " ";
	inOrder(node->rchi
ld);
}
```
### 后序遍历
一个应用：为二分搜索树释放内存（前面BSTree类的析构函数实现就是与后序遍历方法相同）

> 递归左子树
> 递归右子树
> 输出节点data

```c++
template<typename T>
void BSTree<T>::postOrder(Node<T>* node)
{
	if (node == NULL)
		return;
	postOrder(node->lchild);
	postOrder(node->rchild);
	cout << node->data << " ";
}
```
前中后序遍历都是先左子树后右子树遍历，但是三种遍历对节点操作的时机不同。

### 前序遍历的非递归实现

通过栈结构存放节点，先将根节点压入栈中。根据栈**后入先出**的特性需要先压入后访问的节点，所以若要先访问左子树则要按先右子树后左子树的顺序将节点压入栈中。
访问根节点后，分别将右、左孩子节点压入栈中，再从栈顶访问一个节点并取出，接着将该节点的右、左孩子分别压入栈中，循环执行，若左右孩子为空则继续从栈顶访问节点，直到栈为空。
```c++
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
```
非递归比递归实现复杂很多，中序、后序遍历的非递归实现更加复杂，实际应用也不广泛。
### 层序遍历
也可以理解为广度优先遍历，是通过非递归借助队列实现。
根据队列“先进先出”的特性，要先访问左孩子所以左孩子先入队先出队。起始根节点root先入队，然后循环执行，访问队首元素并出队，接着该元素左右孩子入队，访问下个队首元素，如此...直到队列为空。
```c++
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
```

**广度优先遍历意义** ：更快找到查询的元素，多用在搜索策略上。对于遍历操作，深度优先和广度优先并无区别；但在一棵树中寻找问题的解时，广度优先则更有意义，常用于算法设计中无权图的最短路径。
### 删除最大值和最小值
最小值：树中最左边的节点，无左孩子；
不断递归左子树，直到节点没有左孩子则说明该节点为最小值，然后用rightnode保存该节点的右孩子是否为空都没有关系，最后删除最小值节点，返回rightnode。
最大值：树中最右边的节点，无右孩子；方法与最小值同理只是将左孩子改为右孩子。
```c++
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
	retur min;
}
```
通过删除最大值最小值的方法类推就可以实现删除任意元素的节点。
### 删除任意元素

    只有左孩子/右孩子
    左右都有孩子
**Hibbard Deletion**方法
删除左右孩子都有的节点d，先找到大于d的最小值s=min(d->rchild)来代替d;令s->rchild=removeMin(d->rchild);s->lchild=d->lchild;然后删除d，s为新的子树的根。
```c++
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
			//待删除节点d左右孩子均不为空，找到s_>data大于d->data的最小值，s代替d
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
void BSTree
<T>::remove(T e)
{
	remove(root, e);
}
```
## 二分搜索树的应用 集合和映射
### 集合set
每个元素只能存在一次，可用于“去重”。
set<E>//java

 - void add(E)
 - void remove(E)
 - boolean contains(E)
 - int gatSize()
 - boolean isEmpty()

基于二分搜索树的实现
在set类中声明一个私有的BSTree对象，在实现set中的方法时只需调用BSTree中对应功能的方法。
基于链表的实现，同理，运行的明显慢很多。
### 集合类的复杂度分析

|  |linkedlist|BST(平均)|BST(最差)
|--|--|--|--|--|
|增|O(n)|O(h)/O(logn)|O(n)|
|删 |O(n)|O(h)/O(logn)|O(n)|
|查|O(n)|O(h)/O(logn)|O(n)|

n为节点个数，h为二分搜索树的深度。当二分搜索树为满二叉树时，$n=2^h-1$，则$h=log(n+1)=O(logn)$
logn比n快很多。BST最差情况时退化为O(n),可以通过平衡二叉树解决。
同样的数据可以有不同的二分搜索树。
### leetcode集合相关问题
804.唯一摩尔斯密码
使用提供的集合类，c++:#include < set >
set< string > s;保存摩尔斯码
先逐个计算words[]的摩斯码序列insert到set集合中，这个insert不会加入重复的元素，最后返回s的大小。

> 有序集合：元素有顺序性，基于搜索树实现
> 无需集合：没有顺序性，基于哈希表实现
> 多重集合：允许重复元素

### 映射map
整体和集合一致。

 - 存储（键，值）数据对的数据结构(Key,Value)
 - 根据键(Key)寻找值(Value)

Node:
Key;
Value;
next;/rchild;lchild;
基于链表实现；基于二分搜索树实现。不能复用链表类或BST类的代码。
时间复杂度分析与集合类似。

 

