
// 3. 链表
// 链表:逻辑上连续 物理上不连续 不是一条线 而是一环扣一环 
// 每一个数据单元中不光有数据 还有指针 指向下一个元素的起始位置\
// 数据单元是结构体(单向) 
// 8中链表结构
// 1. 单链表不带头非循环链表 做底层结构的实现(栈的底层实现)
// 一个数据单元包括一个数据和指针, 数据单元不是挨着的, 通过指针连接下一个数据
// 所以是逻辑连续, 物理不一定连续的线性表
typedef struct Node{
	int _data;
	struct Node* _next;
}Node;// 数据单元用结构体表示
// 单链表不需要记录每个节点 记录一个头(第一个节点的起始位置)

// 实现'/'''''''''无头非循环单链表
typedef struct sList{
	Node* _head;
}sList;

void sListInit(sList* sl){
	// 空链表
	// 新的头指向新的节点 指向newNode 不指向原来的节点 指向新的
	// 先创建新节点
	sl->_head = NULL;
}

void printsList(sList* sl){
	Node* cur = sl->_head;
	while (cur){
		printf("%d ", cur->_data);
		cur = cur->_next;
	}
}
Node* createNode(int* data){
	Node* node = (Node*)malloc(sizeof(Node));
	node->_data = data;
	node->_next = NULL;
	return node;
}
void sListPushFront(sList* sl, int data){
	// 每创建一个 next都指向NULL
	Node* node = createNode(data);

	// 判断链表是否为空 (只有一个节点的链表)只有第一次进if
	if (sl->_head == NULL){
		sl->_head = node;
	}
	else{
		// 头插
		node->_next = sl->_head;// 
		sl->_head = node;
	}
}

void sListPopFront(sList* sl){

}
// 应返回在当前链表的位置 所以返回值为Node*
Node* sListFind(sList* sl, int data){
	Node* cur = sl->_head;
	while (cur){
		if (cur->_data == data)
			return cur;
		cur = cur->_next;
	}
	return NULL;
}
// 要在前面插, 要遍历单链表 要先找到结点的前驱, 他的next等于当前结点, O(N)
// 单链表一般在结点后面插入, 时间复杂度为O(1)
void sListInsertAfter(Node* node, int data){
	if (node != NULL){
		Node* next = node->_next;
		Node* newNode = createNode(data);
		node->_next = newNode;
		newNode->_next = next;
	}
}

void sListEraseAfter(Node* node){
	if (node != NULL){
		Node* next = node->next;

	}

}


// cur向前移动一个位置 pre也跟着往前走 cur
// 让Pre指向空,
void sListPopBack(sList* sl){
	Node* cur, *pre;
	// 空链表
	if (sl->_head == NULL){
		return;
	}
	// 只有一个头结点		
	if (sl->_head->_next == NULL){
		// 删除之后编程空链表
		free(sl->_head);
		sl->_head = NULL;
	}
	else{
		pre = NULL;
		cur = sl->_head;
		while (cur-> - next){
			pre = cur;
			cur = cur->_next;
		}

		//if (pre == NULL){
		//	// 相当于只有一个头节点
		//	sl->_head = NULL;
		//}
		//else{
		//	pre->_next = NULL;
		//}
		pre->_next = NULL;
		free(cur);
	}


}

void sListDestory(sList* sl){

}

void testsList(){
	sList sl;
	sListInit(&sl);
	sListPushFront(&sl, 1);
	sListPushFront(&sl, 2);
	sListPushFront(&sl, 3);
	sListPushFront(&sl, 4);
	sListPushFront(&sl, 5);
	sListPushFront(&sl, 6);

	printsList(&sl);// 打印出6,5,4,3,2,1
}
// 2. 双向带头非循环 