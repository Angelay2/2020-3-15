#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <Windows.h>

// 1. ���Ա�(�����洢)
// ���Ա���n��������ͬ���Ե�����Ԫ�ص���������. ���Ա���һ����ʵ���й㷺ʹ�õ����ݽṹ,
// ���������Ա�:˳���, ����, ջ, ����, �ַ���...
// ���Ա����߼��������Խṹ, Ҳ����˵��������һ��ֱ��, ����������ṹ�ϲ���һ����������, 
// ���Ա��������ϴ洢ʱ, ͨ�����������ʽ�ṹ����ʽ�洢

// 2. ˳���(���������ʽ�����, һ���Ƕ�����(��̬˳���), һ���ǲ�������(��̬˳���,)
// ˳�������һ�������ַ�����Ĵ洢��Ԫ���δ洢����Ԫ�ص����Խṹ,
// һ����������������, ��������������ݵ���ɾ���
// �����ڶ���˳���ʱ, ���Ĵ�С���Ⱦ�ȷ����, ���Ƕ���˳���, һ������Ԫ���Ƿ���ջ��, (�ܴ洢��Ԫ�ز���)
// ʹ�ö�̬���ٵ�����洢���Ƕ�̬˳���.(ʹ�ö�)��̬��������Դ������ݵĴ洢 ���ϴ洢 
// ˳����ܹ��ܴ洢����Ԫ�ؾ�������, ����������Ԫ�ظ����ǲ�ͬ��, 
// ˳���֧�ַ��� �����ʺ����м����Ԫ�ص� ���ݴ��۴�
// ���Ľṹ�ýṹ�������� ����һ���ṹ����������ǰ˳���Ľṹ

typedef int DataType; //���ͱ��� ����������Ϊfloat, double ���滻int
// ��̬˳���
typedef struct seqList{
	// ��Ҫ��̬���ٿռ�, �ڶ��Ͽ���, ֻ��ͨ��ָ�����, malloc���뷵��ָ�� �൱����int* 
	DataType* _data;
	// �����������Ǹ���, ������size_t �޷�������(0-4G) int(-2G-2G)  
	// size ��ʾ˳���ǰ��ŵ�Ԫ�ظ���
	size_t _size;
	// capacity ��ʾ˳�����Դ�ŵ����Ԫ�ظ���
	size_t _capacity;
} seqList;// ����

// ��ӡ
void printSeqList(seqList* sq){
	for (size_t i = 0; i < sq->_size; ++i){
		printf("%d ", sq->_data[i]);
	}
	printf("\n");
}

// ˳����ʼ��
void seqInit(seqList* sq){
	// ��ʼ����ζ�ſյ�˳���
	sq->_data = NULL;
	sq->_capacity = 0;
	sq->_size = 0;
}

// �������                                           
void checkCapacity(seqList* sq){
	if (sq->_size == sq->_capacity){
		// ˳�������, ��Ҫ����, 
		// 1. ���ٿռ�, 2. ����ԭ�пռ�����, 3. �ͷ�ԭ�пռ�
		// ȷ���µ�����, ����ǿձ�,�ȿ�10��, ��Ϊ0, ������ԭʼ������2��
		size_t newCapacity = sq->_size == 0 ? 10 : 2 * sq->_capacity;// _size=_capacity
		// malloc, memcpy, free
		// ���µĿռ�
		//// newDataΪ��ָ�� capacity(����)��ʾ���ݸ���, ���ռ�(�ֽ�)��Ҫ�����������ʹ�С DataType
		//DataType* newData = (DataType*)malloc(newCapacity * sizeof(DataType));
		//// �µĿռ�,ԭʼ�ռ�,�ֽڸ���(��������), ��ԭʼ�ռ�����ݿ����¿ռ�
		//memcpy(newData, sq->_data, sq->_size * sizeof(DataType));
		//// ����sq->_data���ͷ�֮ǰ�Ѿ����� ������Ҫ������ʱ����������;
		//DataType* tmp = sq->_data;
		// free(sq->_data); ���������ͷžͲ���Ҫ��������������
		//sq->_data = newData;
		//free(tmp);
		// realloc(ԭ��ָ��,�µĴ�С)  ����malloc�����ж��������������
		sq->_data = (DataType*)realloc(sq->_data, newCapacity * sizeof(DataType));
		sq->_capacity = newCapacity; 
	}
}
// ����

// �����ӿ�: ��ɾ���
// ����ӿ�(������Ա: ָ��_data, ��ǰ����_size, ����_capacity)

// ����λ��([0,size]����Ԫ��(�Լ�ָ����λ��)
// ��position���Ԫ�ض�Ҫ����ƶ�
void seqInsert(seqList* sq, size_t position, DataType value){
	// ��֤�����λ������ȷ�� [0,size]
	assert(position <= sq->_size);
	// �������
	checkCapacity(sq);
	// Ԫ���ƶ�
	for (size_t i = sq->_size; i > position; --i){
		sq->_data[i] = sq->_data[i - 1];// [size-1,position]

	}
	// ����
	sq->_data[position] = value;
	++sq->_size;

}
// ͷ��(����ǰ�����ݱ�, �Լ�Ҫ�����ֵ)
// �����е�Ԫ������ƶ�, �ٲ���
void seqPushFront(seqList* sq, DataType value){
	checkCapacity(sq);
	// �ƶ�Ԫ��, ����Ԫ������ƶ�һ��λ��
	// ��ǰ�����ƶ�, ���� ���ݻᱻ����
	//for (int i = 0; i < sq->_size; ++i){
	//	sq->_data[i + 1] = sq->_data[i];// ��������ɸ���, ����Ԫ�ض���һ����,
	//}
	// �Ӻ���ǰ�ƶ� ������i>=0 :1. ��ѭ��, 2. ����Խ�� �Ǹ����ǲ�����С��0��,
	for (size_t i = sq->_size; i > 0; --i){
		// sq->_data[i + 1] = sq->_data[i]; 
		sq->_data[i] = sq->_data[i - 1];//

	}
	// ����
	sq->_data[0] = value;
	++sq->_size;

	// seqInsert(sq, 0, value);
}


// β��
// �൱������ָ��(ͷָ��)���ƫ��_size��λ��,���µ�Ԫ�طŽ�ȥ, Ȼ��Ԫ�ظ�����1(_size++)
void seqPushBack(seqList* sq, DataType value){
	// sq����˳���
	// �ȼ������ ����û�пռ�������� ,��д������� ��˳���Ϊ��, �ᵼ�·����쳣
	checkCapacity(sq);
	// �������(sq->_data��˳��������ָ��,sq->_sizeΪ��˳����е�λ��, 
	// ������ָ����±�Ϊ�ܸ���(�����ܸ���-1) => ��Ϊ���һ��Ԫ�ص���һ��Ԫ��
	// ��value�������һ��Ԫ�ص���һ��Ԫ�� Ȼ��_size��1 = (β��֮��)�����ܹ���Ԫ�ظ���
	sq->_data[sq->_size] = value;
	// ���µ�ǰ˳�����Ԫ�صĸ���
	sq->_size++;

	// �൱��
	//seqInsert(sq, sq->_size, value)
}


// ɾ���ӿ�


// ���ҽӿ�

// ���Ժ���
void test(){
	seqList sq;
	seqInit(&sq);
	seqPushBack(&sq, 0);
	seqPushBack(&sq, 1);
	seqPushBack(&sq, 2);
	seqPushBack(&sq, 3);
	seqPushBack(&sq, 4);
	seqInsert(&sq, 2, 100);
	printSeqList(&sq);// û��ͷ��֮ǰ��ӡһ��  ��ӡ��0,1,100,2,3,4
	seqPushFront(&sq, -1);
	printSeqList(&sq);// ͷ��֮���ٴ�ӡһ�� -1,0,1,100,2,3,4
}

int main(){
	test();
	system("pause");
	return 0;
}