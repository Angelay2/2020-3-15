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
		return head;// ���ؿ�
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
struct listNode* mergeTwolists(struct ListNode* l1, struct ListNode* l2){
	// �������
	if (l1 == NULL)
		return l2;
	if (l2 == NULL)
		return l1;
	struct ListNode* newH, *newT;
	//ȷ���µı�ͷ
	if (l1->val < l2->val){

	


	if (l1->val < l2->val){
		newT->next = l1;
		l1 = l1->next;
	}
	else{
		newT->next = l2;
		l2 = l2->next;
	}
	newT = newT->newt;
}
	// �ж��Ƿ���ʣ����û�кϲ�
	if (l1)
		newT->next = l1;
	if (l2)
		newT->next = l2;
	return newT
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


// ����Ļ��Ľṹ
// 1->2->2->1
// 1. һ��ͷָ�� һ��βָ�� ��һ���������һ�����Ƚ� ÿ�ζ���Ҫ�������鷳(O(N2))
// 2. ����������ת ԭ��������Ͷ���, ���ǿ�����ת�������
// 3. ��������һ������ �ٶԿ�����������ת �ֱ�ȶ����������ǰ�벿������(����ͷָ��)

if (A == NULL || A->next )

// �Ҵ������������𽺵���ʼ��� 

// ��������
int main(){
	removeElement();
	system("pause");
	return 0;
}