
// 3. ����
// ����:�߼������� �����ϲ����� ����һ���� ����һ����һ�� 
// ÿһ�����ݵ�Ԫ�в��������� ����ָ�� ָ����һ��Ԫ�ص���ʼλ��\
// ���ݵ�Ԫ�ǽṹ��(����) 
// 8������ṹ
// 1. ��������ͷ��ѭ������ ���ײ�ṹ��ʵ��(ջ�ĵײ�ʵ��)
// һ�����ݵ�Ԫ����һ�����ݺ�ָ��, ���ݵ�Ԫ���ǰ��ŵ�, ͨ��ָ��������һ������
// �������߼�����, ����һ�����������Ա�
typedef struct Node{
	int _data;
	struct Node* _next;
}Node;// ���ݵ�Ԫ�ýṹ���ʾ
// ��������Ҫ��¼ÿ���ڵ� ��¼һ��ͷ(��һ���ڵ����ʼλ��)

// ʵ��'/'''''''''��ͷ��ѭ��������
typedef struct sList{
	Node* _head;
}sList;

void sListInit(sList* sl){
	// ������
	// �µ�ͷָ���µĽڵ� ָ��newNode ��ָ��ԭ���Ľڵ� ָ���µ�
	// �ȴ����½ڵ�
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
	// ÿ����һ�� next��ָ��NULL
	Node* node = createNode(data);

	// �ж������Ƿ�Ϊ�� (ֻ��һ���ڵ������)ֻ�е�һ�ν�if
	if (sl->_head == NULL){
		sl->_head = node;
	}
	else{
		// ͷ��
		node->_next = sl->_head;// 
		sl->_head = node;
	}
}

void sListPopFront(sList* sl){

}
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
// Ҫ��ǰ���, Ҫ���������� Ҫ���ҵ�����ǰ��, ����next���ڵ�ǰ���, O(N)
// ������һ���ڽ��������, ʱ�临�Ӷ�ΪO(1)
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


// cur��ǰ�ƶ�һ��λ�� preҲ������ǰ�� cur
// ��Preָ���,
void sListPopBack(sList* sl){
	Node* cur, *pre;
	// ������
	if (sl->_head == NULL){
		return;
	}
	// ֻ��һ��ͷ���		
	if (sl->_head->_next == NULL){
		// ɾ��֮���̿�����
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
		//	// �൱��ֻ��һ��ͷ�ڵ�
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

	printsList(&sl);// ��ӡ��6,5,4,3,2,1
}
// 2. ˫���ͷ��ѭ�� 