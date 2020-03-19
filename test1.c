#include <stdio.h>
#include <windows.h>

// 3. ����
// ����:�߼������� �����ϲ����� ����һ���� ����һ����һ�� 
// ÿһ�����ݵ�Ԫ�в��������� ����ָ�� ָ����һ��Ԫ�ص���ʼλ��\
// һ�����ݵ�Ԫ����һ�����ݺ�ָ��, ���ݵ�Ԫ���ǰ��ŵ�, ͨ��ָ��������һ������, ���൱����һ���ṹ��
// �������߼�����, ����һ�����������Ա�
// ���ݵ�Ԫ�ǽṹ��(����) 
// 8������ṹ
// ���õ���2��: 
// 1. ��������ͷ��ѭ������( ���ײ�ṹ��ʵ��(ջ�ĵײ�ʵ��) ) 
// 2. ˫�����ͷѭ���ṹ
// NodeΪ���(һ�����ݵ�Ԫ) sList��ʾ����������(����ʵ�ֵ�Ϊ��ͷ��ѭ��������)

typedef struct Node{// ����һ�����
	int _data;// ����
	struct Node* _next;// ָ����һ��ָ��
}Node;// ���ݵ�Ԫ�ýṹ���ʾ
// ��������Ҫ��¼ÿ���ڵ� ��¼һ��ͷ(��һ���ڵ����ʼλ��)

// ʵ����ͷ��ѭ��������(����һ��ʼ��һ��������)
// (��ԱΪͷ���)
typedef struct sList{
	Node* _head;// ������ֻ��Ҫ��¼��һ��������ʼλ��
}sList;

// �������ʼ��, �ŵ��ǽṹ��(sList����Ҳ��Ҫ��һ���ṹ��)
void sListInit(sList* sl){
	// ������
	// �µ�ͷָ���µĽڵ� ָ��newNode ��ָ��ԭ���Ľڵ� ָ���µ�
	// �ȴ����½ڵ�
	sl->_head = NULL;// ��ͷָ��NULL(��Ч��ַ)
}

// ��ӡ
void printsList(sList* sl){
	Node* cur = sl->_head;
	while (cur){
		printf("%d ", cur->_data);
		cur = cur->_next;
	}
}

//�����µĽ��(���з�װ)
//û��Ҫ��ָ��, �½��ָ��վ�����
Node* createNode(int data){
	// ������ռ�
	Node* node = (Node*)malloc(sizeof(Node));
	node->_data = data;
	node->_next = NULL;
	return node;
}

// ͷ��
// �õ������ͷ(sL->head)����ָ��ԭ���ĵ�һ�����, ��ָ��newNode ,��newNoded->nextָ��֮ǰ�ĵ�һ�����
void sListPushFront(sList* sl, int data){
	// ÿ����һ��node(�½��) next��ָ��NULL
	Node* node = createNode(data);

	// �ж�ԭʼ�����Ƿ�Ϊ�� ������������˳�ʼ��, ���Ե�һ�λ��if(Ҳֻ�е�һ�ν�if)
	// ���ԭʼ����Ϊ��, �����½��node��Ϊ���ǵ�ͷ(���ֻ��һ���ڵ������)
	if (sl->_head == NULL){
		sl->_head = node;
	}
	else{
		// ͷ��
		// sl->headԭ��ָ��ľ�������ĵ�һ����� �����½���next����ָ���µĽ��
		node->_next = sl->_head;
		sl->_head = node;
	}
}

// ͷɾ(ɾ��ͷ���)�޸�ͷָ���ָ��
// �� sl->head ����ָ��ԭʼ�ĵ�һ����� ָ���һ��������һ�����, Ȼ���ͷ�ԭʼͷ���
// ���Ȱ�ԭ����ͷ��������,         node = sl->_head
// ����sl->_head ָ����һ�����    sl->head = sl->_head->_next,
// ���ͷ�ԭʼͷ���(������node��)  free(node)
void sListPopFront(sList* sl){
	Node* node = (Node*)malloc(sizeof(Node));// head������ΪNode* ������Node*����node
	// �ձ���Ҫɾ��
	if (sl->_head == NULL)
		return;
	node = sl->_head;
	sl->_head = sl->_head->_next;
	free(node);

}

/*β��
����һ���½��(newNode),�����һ������nextָ��newNode, ��newNode��nextָ��NULL
����Ӧ���ҵ����һ���ǿյĽ��,
����һ��ָ��cur ���������һ��, ֻҪcur->_next��ΪNULL, �ͼ��������
��cur->nextΪNULLʱ, ��cur��������½��,*/
void sListPushBack(sList* sl, int data){

	// �ҵ����һ�����
	Node* cur = sl->_head;
	// 
	while (cur->_next){
		cur = cur->_next;// �����һ��
	}
	// ������curָ�������һ���ǿս��
	cur->_next = createNode(data);
}

// βɾ
// ɾ�����һ���ڵ��, Ҫ�����һ������ǰһ�����(ǰ��)->next = NULL,
// ����3��ָ��: sl->head, cur(��ǰ), prev(ǰ��, һ��ʼ����ʹһ��NULL��λ��, )
// ��curָ��ڶ���ʱ, prevָ���һ��,cur��ǰ�ƶ�һλ,prev������ǰһλ
// ���cur��next��ΪNULL��һֱ��,��cur->next = NULLʱ,Ҫɾ��cur
// ��prev->next����ָ��cur,ָ��NULL
// ���������ֻ��һ�����Ļ� ֻ��Ҫ��sl->head = NULL �Ϳ�����,
void sListPopBack(sList* sl){
	Node* cur, *prev;
	// ������
	if (sl->_head == NULL)
		return;
	// ���ǿ����� ����ֻ��һ��ͷ���
	if (sl->_head->_next == NULL){
		// ֱ�Ӱ�ͷfree����൱��ɾ��ͷ���, ֮���ɿ�����
		sl->_head = NULL;
		free(sl->_head);
	}
	// �ж�����
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
		// curָ�����һ�����, ��ǰ��ָ��NULL
		prev->_next = NULL;
		free(cur);
	}
}

// �ڵ���������һ��ֵ
// Ӧ�����ڵ�ǰ�����λ�� ���Է���ֵΪNode*
Node* sListFind(sList* sl, int data){
	Node* cur = sl->_head;
	while (cur){
		if (cur->_data == data)
			return cur;
		cur = cur->_next;
	}
	return NULL;
}

// ����λ�ú����
// Ҫ�ڵ�����ǰ���, Ҫ����������,O(N)
// �ȱ���ǰ��ԭʼ��next, ��ǰ����nextָ���µĽ��, �µĽ���nextָ��ǰ����ԭʼnext, 

// ������һ���ڽ��������,ʱ�临�Ӷ�ΪO(1), 
// ������node�����һ��newNode, 
// ��node->nextָ��newNode,��newNode->nextָ��ԭ��node����һ�����
// (���õ�nodeԭʼ����ǰ��next ��������)    next = node->_next
// ����node��nextָ��newNode                node->_next = newNode
// ����newNode��nextָ��nodeԭʼ��next      newNode->_next = next
// ��Ϊβ��, ��node->_nextΪNULL
// ����һ������(��Ч)���(Node* node), ������������(int data)
void sListInsertAfter(Node* node, int data){
	if (node != NULL){
		Node* next = node->_next;
		// �����½��
		Node* newNode = createNode(data);
		node->_next = newNode;
		newNode->_next = next;
	}
}

//// ����λ��ɾ��
//void sListEraseAfter(Node* node){
//	if (node != NULL){
//		Node* next = node->next;
//
//	}
//
//}


// ����������
void sListDestory(sList* sl){

}

void testsList(){
	sList sl;// ��������
	sListInit(&sl);// ��ʼ��(�����ÿ�)
	sListPushFront(&sl, 1);
	sListPushFront(&sl, 2);
	sListPushFront(&sl, 3);
	sListPushFront(&sl, 4);
	sListPushFront(&sl, 5);
	sListPushFront(&sl, 6);// β��
	sListPopFront(&sl);// ͷɾ
	sListPopBack(&sl);// βɾ
	printsList(&sl);// ��ӡ
}
int main(){
	testsList();
	system("pause");
	return 0;
}