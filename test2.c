#include <stdio.h>
#include <windows.h>

 //����OJ��
 //����������һ�������ϲ������߼���������һ�����Ա�,
 //�����ڸ�������������ݵĲ���ʱ,�����ǵ�����(˳���)�ǲ�һ����,
 //˳���Ĳ���(����β��)һ����O(N)�ĸ��Ӷ�,
 //���Ƕ��ڵ�������˵ Ҫ��ĳһ��λ��(һ���Ǹ�ĳһ��Ԫ�صĺ������)����Ԫ����O(1)���Ӷ� 
 //Ҫ�Ǹ�ĳһ����ǰ����� ����O(N)�ĸ��Ӷ�, ����Ǵ�ͷ��ѭ���Ľ�����,ӦΪ�������
 //ɾ���Ļ�(ɾ��ĳһ�ڵ����Ľ��)��O(1)���Ӷ�, ɾ��ǰ����O(N)���Ӷ�
 //Ҫ�ڵ��������н��в����Ƿ��������O(N)���Ӷ�,�ӿ�ʼ���Ʊ����ҽ��֪���ҵ� ������O(N)

// 1. ɾ�������е��ڸ���val�����н��
// ����1->2->6->3->4->5->6, val=6
// ���1->2->3->4->5 (->NULL)
// �Ѹý��(6)�ҵ�ɾ��(�ͷſռ�)��, �ٰ�ǰ��������
// ˳����ɾ���Ǹ��� �����ɾ�����ͷſռ�
// ��ͷ��ʼ������val,ɾ���� ������ǰ����, 
// ���õ������ͷ(head) ����curָ��ͷ���
// �漰�������, һ����ǰ��(NULL), һ���ǵ�ǰ����(1), һ����next(2)
// ��ǰ��㲻����6ʱ, ���ͬʱ����ƶ�, ֱ��cur����6 ��6�ͷŵ�,
// �ͷ�+���ӽ��
// �ȱ��浱ǰ���cur->_next,                  next = cur->next
// ����ǰ����prev->nextָ��cur��ԭʼnext,     prev->_next = next
// ���ͷŵ�cur(ɾ��)                          free(cur)
// ����curָ����һ��Ԫ��                      cur = next
struct ListNode {
	int val;
	struct ListNode* next;
};
struct ListNode* removeElement(struct ListNode* head, int val){
	if (head == NULL)
		return NULL;// ���ؿ�
	struct ListNode* cur = head;
	struct ListNode* prev = NULL;
	while (cur){// ��������
		struct ListNode* next = cur->next;
		if (cur->val == val){// Ҫɾ����
			// ��ʱ�Ѿ��ҵ�Ҫɾ���ĵ���, ���ͷ�Ҫ��ɾ���Ľ��
			// ���Ҫ�ͷŵ�Ϊͷ��� ����һ������Ҫɾ���Ľ�� �����ͷ���
			// prev = NULL��ǰ�����Ѿ��ҵ�����val�Ľ��,�����ͷ���,
			if (prev == NULL){// cur == head){
				head = next;// ����ͷ���
			}
			else{// ���ɾ�Ĳ���ͷ
				prev->next = next;
			}
			free(cur);
			cur = next;
		}
		else{// ������Ҫɾ���Ľ��, ͬʱ������������� ��������ƶ�һ�����
			prev = cur;
			cur = next;
		}
	}
	return head;// ���շ���ͷ
}

// ��ת(��ת)һ��������
// ����: 1->2->3->4->5->NULL
// ���: 5->4->3->2->1->NULL
// 1. ͷ�巨 pushFront (
// ����һ��������, ����ͷ��,
// ��һ�η���1, ��1��next����NULL, �ڶ��η���2, ��2��next = 1.... 
// ����ָ��: prev=NULL, cur=head, next=next; 
// ��������������ָ, 1��nextָ��NULL,prevʽ��ָ��ͷ,curָ���µ������ͷ(prev)
// next = cur->next;
// ��cur->next = prev(NULL);
// prev = cur(ԭʼ��ͷ);
// cur = next(��һ��Ԫ��);
// ���շ����µ������ͷ(prev)
struct ListNode* reverse(struct ListNode* head){
if (head == NULL || head->next == NULL)
return head;
// prev: ��ʾ�µ�����ͷ����λ��
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
// ��2:  ��ָ�뷨, n0=NULL,n1,n2=next
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

// 3. ��������� �����м�; �����ż�� ���صڶ����м���
// ��ͳ�ƽ�����

struct ListNode* Move(struct ListNode* head){
	//if (head == NULL)
	//	return head;
	//// ͳ�ƽ�����
	//int count = 0;
	//struct ListNode* cur = head;
	//while (cur){
	//	++count;
	//	cur = cur->next;
	//}// O(N) ����1.5��
	//// ��ͷ��ʼ����
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

// ��2: ����ָ��(��ָ��һ����һ��, ��ָ��һ��������) 
// slow = slow->next;
// fast = fast->next->next
struct ListNode* slow = head;
struct ListNode* fast = head;
while (fast && fast->next){// ��ֻ�ж�fast(ÿ��Ҫ������)�Ƿ�Ϊ��,fast��һ��Ϊ�� ��һ�����߲����� 
	slow = slow->next;
	fast = fast->next->next;
}
return slow;
}


// ���ص�����k �����
// ��1: ����n-k
// ��2: ���� ����fast��ǰ��k��, ����һ��ָ���ߵ�NULL,slow��ָ������K��
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
		// 	fast = fast->nextд��������������һ��
		if (fast == NULL)
			return NULL;
		fast = fast->next;
	}
	// ��fast, slowͬʱ��, fast����֮��, slow���ǵ�����k�����
	while (fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

// 5. ��������������ϲ�Ϊһ����������
// ����1->2->4   1->3->4
// ���1->1->2->3->4->4
// ����һ���µ�����, ˭��ͷС ��ȥ���˭�ĵ�һ�����
// һ��ָ��cur1ָ���һ�������ͷ, cur2ָ��ڶ��������ͷ
// ���������ͷ���бȽ�, ѡ���Ƚ�С��ͷ������������ ��ȥ�Ƚ���һ�����
// ѡ���������Ķ�Ӧ�����ָ������ƶ�һ��, ָ���µ�ͷ,�ظ���������, ֱ��һ������������
// �ж��Ƿ���ʣ����, ����, ��ʣ����ƴ�ӵ��µ������β��
// ����ͷ�ȱȽ� С������,(����ͬ, ָ��һ������,Ȼ���ٱȽ�����ͷ,�ظ�)
// ��1: �Ƚ�����ͷ
typedef struct ListNode Node;
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
	if (l1 == NULL)
		return l2;
	else if (l2 == NULL)
		return l1;

	Node* head = NULL, *tail = NULL;
	//����������
	head = tail = (Node*)malloc(sizeof(Node));
	tail->next = NULL;
	while (l1 && l2)
	{
		// ȡС�Ľ���β��
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
	//ʣ��Ԫ��ֱ��ƴ��
	if (l1)
		tail->next = l1;
	else
		tail->next = l2;

	Node* list = head->next;
	free(head);
	return list;
}

// ��2: ������һ��ͷ������ ������Ԫ�ط��ں���, ���շ��ر�ͷ��next
// ���ȴ���һ����ͷ
struct ListNode* {
	if (l1 == NULL)
	return l2;
	if (l2 == NULL)
	return l1;
	struct 
};


// 6. ����С��x�Ľ�����ڴ��ڻ����x�Ľ��֮ǰ �����������е������ͷ
// 10,3,5,6,9,20,4,7,8  ����С��9�����������ǰ�벿��, ���ڵ���9�ķ��ں�벿��
// ��֤Ԫ�ص����λ�ò������仯  val=9
// 3,5,6,4,7,8,10,9,20
// ����������ͷ, С��9��, ����9��
// С��9�ķ��ڵ�һ�������β, ���ڵ���9�ķ��ڵڶ��������β��
// ����������, ��һ������ı�β���ڵڶ�������ı�ͷnext, 
// ���շ��ص�һ������ı�ͷ��next
struct ListNode* part(struct ListNode* pHead, int x){
	struct ListNode* HL, *GL;
	struct ListNode* cur
	if (pHead == NULL)
		return pHead;
	struct listNode* LH, *LT, *GH, *GT;
	// ����ͷ
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
	// �������ֵ, ���ܻ����ѭ������
	GT->next = NULL;// �³�ΪҰָ��
	struct ListNode* newH = LH->next;
	free(GH);
	free(LH);
	return newH;
	}
}


// 7. ����Ļ��Ľṹ
// 1->2->2->1
// ��1:
// (1). һ��ͷָ�� һ��βָ�� ��һ���������һ�����Ƚ� ÿ�ζ���Ҫ�������鷳(O(N2))
// (2). ����������ת ԭ��������Ͷ���, ���ǿ�����ת�������
// (3). ��������һ������ �ٶԿ�����������ת �ֱ�ȶ����������ǰ�벿������(����ͷָ��)

// ����:
// ֻ��ת����ĺ�벿��
// δ��ת�Ĳ��ֺ���ת�Ĳ���ͬʱ����, ���бȶ�, ֱ��ĳһ������ֵΪ��, �ȶԽ��� 
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {};
};
int chkPalindrome(ListNode* A){

	if (A == NULL || A->next == NULL)
		return 1;
	// �������� ���µ�ͷ���µ�β��ָ���¿��ٵĿռ�
	struct ListNode* newH, *newT;
	newH = newT = (struct ListNode*)malloc(sizeof(struct ListNode));
	newT->val = A->val;
	newT->next = NULL;
	// ������һ������, 
	struct ListNode* cur = A->next;
	// ͳ��������
	int len = 1;
	while (cur){
		struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->val = cur->val;
		newNode->next = NULL;
		// ����
		newT = newT->next;
		++len;
		cur = cur->next;
	}

	// ��ת
	struct ListNode* prev = NULL;
	cur = newH;
	while (cur){
		// ͷ��
		struct ListNode* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	newH = prev;

	len /= 2;
	//�ȶ����������ǰ�벿�ֽ��, ������,��Ϊ���Ľṹ, ��������, ����һ���ǻ��Ľṹ
	newT = newH;
	cur = A;
	while (len--){
		if (cur->val != newT->val)
			return 0;
		cur = cur->next;
		newT = newT->next;
		return 1;
	}
}

int chkPalindrome2(ListNode* A){
	if (A == NULL || A->next == NULL)
		return 1;
	// �ֲ���ת, �����ȶ�
	// 1. �ҵ��м���
	struct ListNode* fast, *slow; // ����ָ��
	fast = slow = A; // ������ͷ
	while (fast && fast->next){
		slow = slow->next;
		fast = fast->next->next;
	}
	// slow: �м�ڵ�, �����ż��, ���ǵڶ����м�ڵ�
	struct ListNode* prev = NULL;
	struct ListNode* cur = slow;
	while (cur){
		struct ListNode* next = cur->next; // ����cur->next
		cur->next = prev; // ��cur->next ָ��prev
		prev = cur; // cur��Ϊprev
		cur = next; // �����cur->next��Ϊcur
	}
	// ��ͷ��ʼ����
	// prev: ��ת֮���ͷ���
	// ��ǰһ����ͺ�һ���㿪ʼ��ͷ�ȶ� 
	// �����ż�� �պñȶԵ�����ͬ�Ľ�� 
	// ���������, ��ת��ǰ�벿�ֶ�һ����� ���ǱȶԵĽ������һ����
	cur = prev;
	while (A && cur){
		if (A->val != cur->val)
			return 0;
		A = A->next;  // ��Ϊǰ�벿�ֵ�A->next����ָ���м�ڵ��
		cur = cur->next;
	}
}
// ����������д 
int chkPalindrome3(ListNode* A){
	if (A == NULL || A->next == NULL)
		return 1;
	// ��һ��������
	int* array = (int*)malloc(sizeof(int)* 900);
	// ��������
	struct ListNode* cur = A;
	int count = 0;// ����
	while (cur){
		array[count++] = cur->val;
		cur = cur->next;
	}
	// �жϻ���
	int begin = 0;
	int end = count - 1;
	while (begin < end){
		if (array[begin] != array[end])
			return 0;
		++begin;
		--end;
	}
	return 1;
}

// 8. �������������ཻ����ʼ��� 
// �Ӻ���ǰ�� ��������
// 1. ���ȱ������������
// 2. �ó��������������ڵ��Ĳ���, 
// 3. Ȼ������������ͬʱ��, 
// 4. ��һ����ȵĵ�һ������������
// 
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB){
	if (headA == NULL || headB == NULL)
		return NULL;
	// ͳ��������
	struct ListNode* curA = headA;
	struct ListNode* curB = headB;
	int lenA, lenB;
	lenA = lenB = 0;
	while (curA){
		++lenA;
		curA = curA->next;
	}
	while (curB){
		++lenB;
		curB = curB->next;
	}

	// ���
	int diff = abs(lenA - lenB);
	// ��������A������B��,
	curA = headA;
	curB = headB;
	if (lenB > lenA){
		curA = headB;
		curB = headA;
	}
	while (diff--){
		curA = curA->next;
	}
	// ͬʱ��
	while (curA && curB){
		// ��ñȽ�ָ��, ����ȥ�Ƚ�ֵ(�������ظ���ֵ)
		if (curA == curB)
			return curA;
		curA = curA->next;
		curB = curB->next;
	}
	return NULL;
}

// 9. �������� 
// 9.1 (�ж��������Ƿ��л�, �л��Ļ�,������Զ���ᵽNULL)
// slowָ��: ÿ����һ��   , �����ĺ��������100��, ��ô�������100��, һ���ܸ�����ָ��, 
// fastָ��: ÿ��������     ÿ�α���ָ�����һ��,һ��һ���ֲ� ��ֹÿ���ߵĲ���̫�� ����������
// ���fast = slow; ����ָ��������,���л�, 
// ���fastÿ��������, �൱��fastÿ�ζ����Ժ�slow֮��ļ���1. 
int hasCycle(struct ListNode* head){
	if (head == NULL)
		return 0;
	struct ListNode* fast, *slow;
	fast = slow = head;
	while (fast && fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return 1;
	}
	return 0;
}
// ����󻷵ĳ���?
// ��ָ��������������, ����һ���ߵ�������ʱ, �������ĵ�ĸ������ǻ��ĳ���

// 9.2 ����һ������, ��������ʼ�뻷�ĵ�һ���ڵ�, ��������޻�, �򷵻�NULL
// (1). ���ж��Ƿ��л�, 
// fast��slow������
// L:��ͷ��㵽�뻷�ڵľ���
// C:���ĳ���
// X:����ڵ㵽������ľ���
// (2). ������ָ���߹��ľ���Ϊ: L + X + kC (k>=1)   ����ָ�����ľ���һ����С��һ�����ĳ���
// (3). ��ָ���߹��ľ���: L + X. ��ָ��һ������һ�����ĳ�����׷����ָ�� 
// ����������ָ��ս���, ����ָ�������ڵ���һ���ڵ�, 
// ����������ָ��ս����ͺͿ�ָ����������ڵ�, ���1��, Ҫ������-1��ȥ�ֲ�(����������������ڽڵ��ǰһ��λ��)
// 2 * (L + X) = L + X + k*C
// L + X = k*C
// L = k*C -X (k>=1)
// L = C - X + (k-1) * C   �������㵽��ڴ�ΪC - X 
// slow�������㿪ʼ��, cur��ͷ��ʼ��, cur��slow�����ĵ������ڵ� --> ��õ����


struct ListNode* hasCycle(struct ListNode* head){
	if (head == NULL)
		return NULL;// ���û�������� ����NULL
	struct ListNode* fast, *slow;
	fast = slow = head;
	while (fast && fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return slow;// �����������, ����slowָ��
	}
	return NULL;
}
struct ListNode* deteCycle(struct ListNode* head){
	struct ListNode* slow = hasCycle(head);
	if (slow){
		while (1){
			if (slow == head)
				return slow;
			slow = slow->next;
			head = head->next;
		}
	}
	// ���û�л�
	return NULL;
	
}

// 10. ���ƴ����ָ�������(ÿ���ڵ������ָ�� next��random
// ����һ������, ÿ���ڵ����һ���������ӵ����ָ��, ��ָ�����ָ�������е��κν���սڵ�, Ҫ�󷵻������������
// 1. ���� ��ÿ����㸴��һ���µĽ��, ���ڸý��ĺ���, ָ�򲻱�, ���ƵĽ��ָ���Ƶ���һ�����, ԭ���ָ��ԭ�ڵ����һ�����  
// 2. ����randomָ��     copy->random = cur->random->next
// 3. ����(�ѿ�������������) cur->next = copy->next, copy->next = cur->next->next
// Ȼ������cur�ߵ�cur->next, copy�ߵ�copy->next ,copy������cur����
Node* copyRandomList(Node* head){
	if (head == NULL)
		return NULL;
	// �����ڵ� ����ָ��(next, newNode, cur)
	Node* cur = head;
	while (cur){
		Node* next = cur->next;
		// �����ڵ�
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->val = cur->val;
		// ����cur, newNode, next
		newNode->next = next;
		cur->next = newNode;
		cur = next;
	}
	// ����random
	cur = head;
	while (cur){
		Node* copy = cur->next;
		if (cur->random)
			cur->random = cur->random->next;
		else
			copy->random = NULL;
		cur = copy->next;
	}
	// ����
	cur = head;
	Node* newH = cur->next;
	while (cur){
		Node* copy = cur->next;
		Node* next = copy->next;

		cur->next = next;
		if (next)
			copy->next = next->next;
		else
			copy->next = NULL;
		cur = next;
	}
	return newH;
}



int main(){
	removeElement();
	system("pause");
	return 0;
}