#include <stdio.h>
#include <windows.h>

 //链表OJ题
 //单链表他是一个物理上不连续逻辑上连续的一个线性表,
 //所以在给单链表进行数据的操作时,跟我们的数组(顺序表)是不一样的,
 //顺序表的插入(除过尾插)一般是O(N)的复杂度,
 //但是对于单链表来说 要给某一个位置(一般是给某一个元素的后面插入)插入元素是O(1)复杂度 
 //要是给某一结点的前面插入 就是O(N)的复杂度, 单向非带头不循环的结点插入,应为后面插入
 //删除的话(删除某一节点后面的结点)是O(1)复杂度, 删除前面是O(N)复杂度
 //要在单向链表中进行查找是否结点存在是O(N)复杂度,从开始类似遍历找结点知道找到 所以是O(N)

// 1. 删除链表中等于给定val的所有结点
// 输入1->2->6->3->4->5->6, val=6
// 输出1->2->3->4->5 (->NULL)
// 把该结点(6)找到删除(释放空间)后, 再把前后结点连接
// 顺序表的删除是覆盖 链表的删除是释放空间
// 从头开始遍历找val,删除后 再连接前后结点, 
// 先拿到链表的头(head) 定义cur指向头结点
// 涉及三个结点, 一个是前驱(NULL), 一个是当前遍历(1), 一个是next(2)
// 当前结点不等于6时, 结点同时向后移动, 直到cur等于6 把6释放掉,
// 释放+连接结点
// 先保存当前结点cur->_next,                  next = cur->next
// 再让前驱的prev->next指向cur的原始next,     prev->_next = next
// 再释放掉cur(删掉)                          free(cur)
// 再让cur指向下一个元素                      cur = next
struct ListNode {
	int val;
	struct ListNode* next;
};
struct ListNode* removeElement(struct ListNode* head, int val){
	if (head == NULL)
		return NULL;// 返回空
	struct ListNode* cur = head;
	struct ListNode* prev = NULL;
	while (cur){// 遍历所有
		struct ListNode* next = cur->next;
		if (cur->val == val){// 要删除啦
			// 此时已经找到要删除的点了, 则释放要被删除的结点
			// 如果要释放的为头结点 即第一个就是要删除的结点 则更新头结点
			// prev = NULL的前提是已经找到等于val的结点,则就是头结点,
			if (prev == NULL){// cur == head){
				head = next;// 更新头结点
			}
			else{// 如果删的不是头
				prev->next = next;
			}
			free(cur);
			cur = next;
		}
		else{// 当不是要删除的结点, 同时更新这两个结点 都向后以移动一个结点
			prev = cur;
			cur = next;
		}
	}
	return head;// 最终返回头
}

// 反转(逆转)一个单链表
// 输入: 1->2->3->4->5->NULL
// 输出: 5->4->3->2->1->NULL
// 1. 头插法 pushFront (
// 创建一个空链表, 进行头插,
// 第一次访问1, 让1的next等于NULL, 第二次访问2, 让2的next = 1.... 
// 三个指针: prev=NULL, cur=head, next=next; 
// 让整个链表向左指, 1的next指向NULL,prev式中指向头,cur指向新的链表的头(prev)
// next = cur->next;
// 让cur->next = prev(NULL);
// prev = cur(原始的头);
// cur = next(下一个元素);
// 最终返回新的链表的头(prev)
struct ListNode* reverse(struct ListNode* head){
if (head == NULL || head->next == NULL)
return head;
// prev: 表示新的链表头结点的位置
struct ListNode* prev = NULL;
struct ListNode* cur = head;
while (cur){
	struct ListNode* next = cur->next;
	cur->next = prev;
	prev = cur;
	cur = next;
}
return prev;
}
// 法2:  三指针法, n0=NULL,n1,n2=next
// n1->next = n0; n0 = n1; n1= n2; if(n2) n2 = n2->next
if (head == NULL || head->next == NULL)
return head;
struct ListNode* n0 = NULL;
struct ListNode* n1 = head;
struct ListNode* n2 = head->next;
while (n1){
	n1->next = n0;
	no = n1;
	n1 = n2;
}
if (n2)
n2 = n2->next;
return n0;

// 3. 如果是奇数 返回中间; 如果是偶数 返回第二个中间结点
// 先统计结点个数

struct ListNode* Move(struct ListNode* head){
	//if (head == NULL)
	//	return head;
	//// 统计结点个数
	//int count = 0;
	//struct ListNode* cur = head;
	//while (cur){
	//	++count;
	//	cur = cur->next;
	//}// O(N) 遍历1.5倍
	//// 从头开始遍历
	//cur = head;
	//int mid = count / 2 + 1;
	//int idx = 1;
	//while (cur){
	//	if (idx = mid)
	//		return cur;
	//	cur = cur->next;
	//	++idx;
	//}
	//return NULL;

// 法2: 快慢指针(满指针一次走一步, 快指针一次走两步) 
// slow = slow->next;
// fast = fast->next->next
struct ListNode* slow = head;
struct ListNode* fast = head;
while (fast && fast->next){// 若只判断fast(每次要走两步)是否为空,fast下一步为空 后一步就走不了了 
	slow = slow->next;
	fast = fast->next->next;
}
return slow;
}


// 返回倒数第k 个结点
// 法1: 返回n-k
// 法2: 快慢 先让fast往前走k步, 当第一个指针走道NULL,slow就指向倒数第K个
struct ListNode* ReturnBack(struct ListNode* head){
	if (head == NULL)
		return head;
	int count = 0;
	struct ListNode* cur = head;
	while (cur && cur->next != NULL){
		++count;
		cur = cur->next;
	}
	for (int i = k; i > 0; i--){

	}
	
	
}
struct ListNode* (){
	struct ListNode* slow = head;
	struct ListNode* fast = slow;
	if (head == NULL)
		return head;
	while (k--){
		// 	fast = fast->next写在上面这里会多走一步
		if (fast == NULL)
			return NULL;
		fast = fast->next;
	}
	// 让fast, slow同时走, fast走完之后, slow就是倒数第k个结点
	while (fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

// 5. 将两个有序链表合并为一个有序链表
// 输入1->2->4   1->3->4
// 输出1->1->2->3->4->4
// 构件一个新的链表, 谁的头小 就去存放谁的第一个结点
// 一个指针cur1指向第一个链表的头, cur2指向第二个链表的头
// 两个链表的头进行比较, 选出比较小的头进行重新链接 再去比较下一个结点
// 选出及诶单的对应链表的指针向后移动一次, 指向新的头,重复上述操作, 直到一个链表遍历完毕
// 判断是否有剩余结点, 若有, 把剩余结点拼接到新的链表的尾部
// 两个头先比较 小的先走,(若相同, 指定一个先走,然后再比较两个头,重复)
// 法1: 比较两个头
typedef struct ListNode Node;
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
	if (l1 == NULL)
		return l2;
	else if (l2 == NULL)
		return l1;

	Node* head = NULL, *tail = NULL;
	//创建空链表
	head = tail = (Node*)malloc(sizeof(Node));
	tail->next = NULL;
	while (l1 && l2)
	{
		// 取小的进行尾插
		if (l1->val < l2->val)
		{
			tail->next = l1;
			tail = tail->next;

			l1 = l1->next;
		}
		else
		{
			tail->next = l2;
			tail = tail->next;

			l2 = l2->next;
		}
	}
	//剩余元素直接拼接
	if (l1)
		tail->next = l1;
	else
		tail->next = l2;

	Node* list = head->next;
	free(head);
	return list;
}

// 法2: 创建带一个头的链表 将所有元素放在后面, 最终返回表头的next
// 首先创建一个表头
struct ListNode* {
	if (l1 == NULL)
	return l2;
	if (l2 == NULL)
	return l1;
	struct 
};


// 6. 所有小于x的结点排在大于或等于x的结点之前 返回重新排列的链表的头
// 10,3,5,6,9,20,4,7,8  所有小于9的排在链表的前半部分, 大于等于9的放在后半部分
// 保证元素的相对位置不发生变化  val=9
// 3,5,6,4,7,8,10,9,20
// 创建两个表头, 小于9的, 大于9的
// 小于9的放在第一个链表表尾, 大于等于9的放在第二个链表的尾部
// 遍历结束后, 第一个链表的表尾接在第二个链表的表头next, 
// 最终返回第一个链表的表头的next
struct ListNode* part(struct ListNode* pHead, int x){
	struct ListNode* HL, *GL;
	struct ListNode* cur
	if (pHead == NULL)
		return pHead;
	struct listNode* LH, *LT, *GH, *GT;
	// 创建头
	LH = LT - (struct ListNode*)malloc(sizeof(struct ListNode));
	GH = GT - (struct ListNode*)malloc(sizeof(struct ListNode));
	cur = pHead;
	while (cur){
		if (cur->val < x){
			LT->next = cur;
			LT = LT->next;
		}
		else{
			GT->next = cur;
			GT = GT->next;
		}
		cur = cur->next;
	}
	LT->next = GH->next;
	// 如果不赋值, 可能会出现循环链表
	GT->next = NULL;// 怕成为野指针
	struct ListNode* newH = LH->next;
	free(GH);
	free(LH);
	return newH;
	}
}


// 7. 链表的回文结构
// 1->2->2->1
// (1). 一个头指针 一个尾指针 第一个结点和最后一个结点比较 每次都需要遍历很麻烦(O(N2))
// (2). 不能整体逆转 原来的链表就丢了, 但是可以逆转半个链表
// (3). 可以先做一个拷贝 再对拷贝的链表逆转 分别比对两个链表的前半部分数据(两个头指针)
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {};
};
int chkPalindrome(ListNode* A){

	if (A == NULL || A->next == NULL)
		return 1;
	// 拷贝链表 让新的头和新的尾都指向新开辟的空间
	struct ListNode* newH, *newT;
	newH = newT = (struct ListNode*)malloc(sizeof(struct ListNode));
	newT->val = A->val;
	newT->next = NULL;
	// 遍历第一个链表, 
	struct ListNode* cur = A->next;
	// 统计链表长度
	int len = 1;
	while (cur){
		struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->val = cur->val;
		newNode->next = NULL;
		// 拷贝
		newT = newT->next;
		++len;
		cur = cur->next;
	}
	len /= 2;
	//比对两个链表的前半部分结点, 如果相等,则为回文结构, 如果不相等, 就是一个非回文结构
	newT = newH;
	cur = A;
	while (len--){
		if (cur->val != newT->val)
			return 0;
		cur = cur->next;
		newT = newT->next;
	}
	return 1;
}

// 找打两个单链表橡胶的起始结点 

// 环形链表
int main(){
	removeElement();
	system("pause");
	return 0;
}