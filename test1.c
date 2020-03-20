#include <stdio.h>
#include <windows.h>

// 3. 链表
// 链表:逻辑上连续 物理上不连续 不是一条线 而是一环扣一环 
// 每一个数据单元中不光有数据 还有指针 指向下一个元素的起始位置\
// 一个数据单元包括一个数据和指针, 数据单元不是挨着的, 通过指针连接下一个数据, 都相当于是一个结构体
// 所以是逻辑连续, 物理不一定连续的线性表
// 数据单元是结构体(单向) 
// 8种链表结构
// 常用的有2种: 
// 1. 单链表不带头非循环链表( 做底层结构的实现(栈的底层实现) ) 
// 2. 双链表带头循环结构
// Node为结点(一个数据单元) sList表示整个单链表(本次实现的为无头非循环单链表)

typedef struct Node{// 定义一个结点
	int _data;// 数据
	struct Node* _next;// 指向下一个指针
}Node;// 数据单元用结构体表示
// 单链表不需要记录每个节点 记录一个头(第一个节点的起始位置)

// 实现无头非循环单链表(所以一开始是一个空链表)
// (成员为头结点)
typedef struct sList{
	Node* _head;// 单链表只需要记录第一个结点的起始位置
}sList;

// 单链表初始化, 放的是结构体(sList本身也需要给一个结构体)
void sListInit(sList* sl){
	// 空链表
	// 新的头指向新的节点 指向newNode 不指向原来的节点 指向新的
	// 先创建新节点
	sl->_head = NULL;// 让头指向NULL(无效地址)
}

// 打印
void printsList(sList* sl){
	Node* cur = sl->_head;
	while (cur){
		printf("%d ", cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}

//创建新的结点(进行封装)
//没必要传指针, 新结点指向空就行了
Node* createNode(int data){
	// 先申请空间
	Node* node = (Node*)malloc(sizeof(Node));
	node->_data = data;
	node->_next = NULL;
	return node;
}

// 头插
// 让单链表的头(sL->head)不在指向原来的第一个结点, 而指向newNode ,让newNoded->next指向之前的第一个结点
void sListPushFront(sList* sl, int data){
	// 每创建一个node(新结点) next都指向NULL
	Node* node = createNode(data);

	// 判断原始链表是否为空 由于链表进行了初始化, 所以第一次会进if(也只有第一次进if)
	// 如果原始链表为空, 就让新结点node作为我们的头(变成只有一个节点的链表)
	if (sl->_head == NULL){
		sl->_head = node;
	}
	else{
		// 头插
		// sl->head原来指向的就是链表的第一个结点 赋给新结点的next后再指向新的结点
		node->_next = sl->_head;
		sl->_head = node;
	}
}

// 头删(删除头结点)修改头指针的指向
// 让 sl->head 不再指向原始的第一个结点 指向第一个结点的下一个结点, 然后释放原始头结点
// 首先把原来的头保存下来,         node = sl->_head
// 再让sl->_head 指向下一个结点    sl->head = sl->_head->_next,
// 再释放原始头结点(保存在node里)  free(node)
void sListPopFront(sList* sl){
	Node* node = (Node*)malloc(sizeof(Node));// head的类型为Node* 所以用Node*定义node
	// 空表不需要删除
	if (sl->_head == NULL)
		return;
	node = sl->_head;
	sl->_head = sl->_head->_next;
	free(node);

}

/*尾插
给定一个新结点(newNode),让最后一个结点的next指向newNode, 而newNode的next指向NULL
首先应该找到最后一个非空的结点,
定义一个指针cur 将链表遍历一遍, 只要cur->_next不为NULL, 就继续向后走
当cur->next为NULL时, 在cur后面插入新结点,*/
void sListPushBack(sList* sl, int data){

	// 找到最后一个结点
	Node* cur = sl->_head;
	// 判断是否为空链表
	if (cur == NULL){
		sl->_head = createNode(data);
		return;
	}
	// 若不为空链表 就让cur往后走, 直到指向NULL.
	while (cur->_next){
		cur = cur->_next;// 向后走一步
	}
	// 到这里cur指向了最后一个非空结点
	cur->_next = createNode(data);

}

// 尾删
// 删除最后一个节点后, 要让最后一个结点的前一个结点(前驱)->next = NULL,
// 设置3个指针: sl->head, cur(当前), prev(前驱, 一开始可以使一个NULL的位置, )
// 当cur指向第二个时, prev指向第一个,cur往前移动一位,prev跟着往前一位
// 如果cur的next不为NULL就一直走,当cur->next = NULL时,要删掉cur
// 让prev->next不再指向cur,指向NULL
// 如果链表中只有一个结点的话 只需要让sl->head = NULL 就可以了,
void sListPopBack(sList* sl){
	Node* cur, *prev;
	// 空链表
	if (sl->_head == NULL)
		return;
	// 不是空链表 但是只有一个头结点
	if (sl->_head->_next == NULL){
		// 直接把头free后就相当于删除头结点, 之后变成空链表
		sl->_head = NULL;
		free(sl->_head);
	}
	// 有多个结点
	else{
		prev = NULL;
		cur = sl->_head;
		while (cur->_next){
			prev = cur;
			cur = cur->_next;
		}
		if (prev == NULL){
			sl->_head = NULL;
		}
		// cur指向最后一个结点, 让前驱指向NULL
		prev->_next = NULL;
		free(cur);
	}
}

// 在单链表中找一个值
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

// 任意位置后插入
// 要在单链表前面插, 要遍历单链表,O(N)
// 先保存前驱原始的next, 让前驱的next指向新的结点, 新的结点的next指向前驱的原始next, 

// 单链表一般在结点后面插入,时间复杂度为O(1), 
// 假设在node结点后插一个newNode, 
// 则node->next指向newNode,让newNode->next指向原来node的下一个结点
// (先拿到node原始插入前的next 保存起来)    next = node->_next
// 再让node的next指向newNode                node->_next = newNode
// 再让newNode的next指向node原始的next      newNode->_next = next
// 若为尾插, 则node->_next为NULL
// 给定一个任意(有效)结点(Node* node), 后面插入的数据(int data)
void sListInsertAfter(Node* node, int data){
	// 先判断结点是否有效
	if (node != NULL){
		Node* next = node->_next;
		// 创建新结点
		Node* newNode = createNode(data);
		node->_next = newNode;
		newNode->_next = next;
	}
}

// 任意位置删除
// 先把指定结点->_next保存起来, 将该结点的next指向
// 时间复杂度为O(1),
void slisteraseafter(Node* node){
	if (node != NULL){
		if (node->_next){
			// Node* next = node->_next;
			// node->_next = next->_next;
			 node->_next = node->_next->_next;
			// free(next);
		}
	}
}

// 单链表销毁(这些结点都是malloc的, 要还给系统,每个都free掉
// 如果直接删除头结点, 相当于后面的结点都没有释放掉
// 先拿到cur的next, 再把cur free掉, 再让cur指向next,逐个free掉,
void sListDestory(sList* sl){
	if (sl->_head){
		Node* cur = sl->_head;
		while (cur){
			Node* next = cur->_next;
			free(cur);
			cur = next;
		}
		sl->_head = NULL;// 链表置空
	}
	//sl->_head = NULL;
}

void testsList(){
	sList sl;// 定义链表
	sListInit(&sl);// 初始化(链表置空)
	sListPushFront(&sl, 1);
	sListPushFront(&sl, 2);
	sListPushFront(&sl, 3);
	sListPushFront(&sl, 4);
	sListPushFront(&sl, 5);
	sListPushFront(&sl, 6);// 尾插
	sListPopFront(&sl);// 头删
	sListPopBack(&sl);// 尾删
	printsList(&sl);// 打印
}
void test(){
	Node* cur;
	sList sl;
	sListInit(&sl);
	sListPushBack(&sl, 1);
	sListPushBack(&sl, 2);
	sListPushBack(&sl, 3);
	sListPushBack(&sl, 4);
	sListPushBack(&sl, 5);
	sListPushBack(&sl, 6);
	printsList(&sl);
	// 在中间某个结点后面插入数据
	cur = sListFind(&sl, 4);
	printf("4 after: 100\n");
	sListInsertAfter(cur, 100);
	printsList(&sl);
	// 在头结点后面插入数据
	cur = sListFind(&sl, 1);
	printf("1 after: 200\n");
	sListInsertAfter(cur, 200);
	printsList(&sl);
	// 在最后一个结点后面插入数据
	cur = sListFind(&sl, 6);
	printf("6 after: 300\n");
	sListInsertAfter(cur, 300);
	printsList(&sl);
}
void test1(){
	Node* cur;
	sList sl;
	sListInit(&sl);
	sListPushBack(&sl, 1);
	sListPushBack(&sl, 2);
	sListPushBack(&sl, 3);
	sListPushBack(&sl, 4);
	sListPushBack(&sl, 5);
	sListPushBack(&sl, 6);
	printsList(&sl);
	cur = sListFind(&sl, 4);
	printf("Erase 4 after: \n");
	slisteraseafter(cur);
	printsList(&sl);

	cur = sListFind(&sl, 1);
	printf("Erase 1 after: \n");
	slisteraseafter(cur);
	printsList(&sl);
}
void test2(){
	Node* cur;
	sList sl;
	sListInit(&sl);
	sListPushBack(&sl, 1);
	sListPushBack(&sl, 2);
	sListPushBack(&sl, 3);
	sListPushBack(&sl, 4);
	sListPushBack(&sl, 5);
	sListPushBack(&sl, 6);
	printsList(&sl);
	sListDestory(&sl);
	printsList(&sl);
	cur = sListFind(&sl, 4);
	printsList(&sl);
}
int main(){
	//testsList();
	//test();
	//test1();
	test2();
	system("pause");
	return 0;
}