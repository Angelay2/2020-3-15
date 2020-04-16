#include <stdio.h>
#include <assert.h>
#include <windows.h>

// ����Ƶ���Ĳ����ɾ���ǲ���˳���� ������(Ч�ʸ�)
// ˳���:(֧���������(һ�ο�����������λ��) �ʺ�β��,
// ����ʱ�临�Ӷ�
// 1. β��:ʱ�临�Ӷ�Ϊo(1), ����Ҫ�ƶ�Ԫ��
// 2. ����β��,��������(����ͷ��)λ�ò��붼��o(n), ��Ҫ���Ѿ����ڵ�Ԫ������ƶ�)
// ��Ҫ�������, ����ռ�����, ��Ҫ����, ���ݴ��۴�

// ɾ��: (�ʺ�βɾ �������ܵ�)
// ������Ҫ�ͷſռ�, ֻ��Ҫ����ԭ��λ�õ�ֵ����
// ����βɾ��ʱ�临�Ӷ�Ϊ o(1), ��������Ҫ�ƶ�Ԫ�� ����ʱ�临�Ӷ�Ϊo(n)
// ����Ҫ���� ��Ϊ��ɾ��

// 1. ���Ա�(�����洢)
// ���Ա���n��������ͬ���Ե�����Ԫ�ص���������. ���Ա���һ����ʵ���й㷺ʹ�õ����ݽṹ,
// ���������Ա�:˳���, ����, ջ, ����, �ַ���...
// ���Ա����߼��������Խṹ, Ҳ����˵��������һ��ֱ��, ����������ṹ�ϲ���һ����������, 
// ���Ա��������ϴ洢ʱ, ͨ�����������ʽ�ṹ����ʽ�洢

// 2. ˳���(���������ʽ�����, һ���Ƕ�����(��̬˳���), һ���ǲ�������(��̬˳���)
// ˳�������һ�������ַ�����Ĵ洢��Ԫ���δ洢����Ԫ�ص����Խṹ,
// һ����������������, ��������������ݵ���ɾ���
// �����ڶ���˳���ʱ, ���Ĵ�С���Ⱦ�ȷ����, ���Ƕ���˳���, һ������Ԫ���Ƿ���ջ��, (�ܴ洢��Ԫ�ز���)
// ʹ�ö�̬���ٵ�����洢���Ƕ�̬˳���.(ʹ�ö�)��̬��������Դ������ݵĴ洢 ���ϴ洢 
// ˳����ܹ��ܴ洢����Ԫ�ؾ�������, ����������Ԫ�ظ����ǲ�ͬ��, 
// ˳���֧�ַ��� �����ʺ����м����Ԫ�ص� ���ݴ��۴�
// ���Ľṹ�ýṹ�������� ����һ���ṹ����������ǰ˳���Ľṹ

typedef int datatype; //���ͱ��� ����������Ϊfloat, double ���滻int
// ��̬˳���
typedef struct seqlist{
	// ��Ҫ��̬���ٿռ�, �ڶ��Ͽ���, ֻ��ͨ��ָ�����, malloc���뷵��ָ�� �൱����int* 
	datatype* _data;
	// �����������Ǹ���, ������size_t �޷�������(0-4g) int(-2g-2g)  
	// size ��ʾ˳���ǰ��ŵ�Ԫ�ظ���
	size_t _size;
	// capacity ��ʾ˳�����Դ�ŵ����Ԫ�ظ���
	size_t _capacity;
} seqlist;// ����

// ��ӡ
void printseqlist(seqlist* sq){
	for (size_t i = 0; i < sq->_size; ++i){
		printf("%d ", sq->_data[i]);
	}
	printf("\n");
}

// ˳����ʼ��
void seqinit(seqlist* sq){
	// ��ʼ����ζ�ſյ�˳���
	sq->_data = null;
	sq->_capacity = 0;
	sq->_size = 0;
}

// ������� ����
void checkcapacity(seqlist* sq){
	if (sq->_size == sq->_capacity){
		// ˳�������, ��Ҫ����, 
		// 1. ���ٿռ�, 2. ����ԭ�пռ�����, 3. �ͷ�ԭ�пռ�
		// ȷ���µ�����, ����ǿձ�,�ȿ�10��, ��Ϊ0, ������ԭʼ������2��
		size_t newcapacity = sq->_size == 0 ? 10 : 2 * sq->_capacity;// _size=_capacity
		// malloc, memcpy, free
		// ���µĿռ�
		//// newdataΪ��ָ�� capacity(����)��ʾ���ݸ���, ���ռ�(�ֽ�)��Ҫ�����������ʹ�С datatype
		//datatype* newdata = (datatype*)malloc(newcapacity * sizeof(datatype));
		//// �µĿռ�,ԭʼ�ռ�,�ֽڸ���(��������), ��ԭʼ�ռ�����ݿ����¿ռ�
		//memcpy(newdata, sq->_data, sq->_size * sizeof(datatype));
		//// ����sq->_data���ͷ�֮ǰ�Ѿ����� ������Ҫ������ʱ����������;
		//datatype* tmp = sq->_data;
		// free(sq->_data); ���������ͷžͲ���Ҫ��������������
		//sq->_data = newdata;
		//free(tmp);
		// realloc(ԭ��ָ��,�µĴ�С)  ����malloc�����ж��������������
		sq->_data = (datatype*)realloc(sq->_data, newcapacity * sizeof(datatype));
		sq->_capacity = newcapacity; 
	}
}


// �����ӿ�: ��ɾ���
// ����ӿ�(������Ա: ָ��_data, ��ǰ����_size, ����_capacity)

// ����λ��([0,size]����Ԫ��(�Լ�ָ����λ��)
// ��position���Ԫ�ض�Ҫ����ƶ�
void seqinsert(seqlist* sq, size_t position, datatype value){
	// ��֤�����λ������ȷ�� [0,size]
	assert(position <= sq->_size);
	// �������
	checkcapacity(sq);
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
void seqpushfront(seqlist* sq, datatype value){
	checkcapacity(sq);
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

	// seqinsert(sq, 0, value);
}


// β��
// �൱������ָ��(ͷָ��)���ƫ��_size��λ��,���µ�Ԫ�طŽ�ȥ, Ȼ��Ԫ�ظ�����1(_size++)
void seqpushback(seqlist* sq, datatype value){
	// sq����˳���
	// �ȼ������ ����û�пռ�������� ,��д������� ��˳���Ϊ��, �ᵼ�·����쳣
	checkcapacity(sq);
	// �������(sq->_data��˳��������ָ��,sq->_sizeΪ��˳����е�λ��, 
	// ������ָ����±�Ϊ�ܸ���(�����ܸ���-1) => ��Ϊ���һ��Ԫ�ص���һ��Ԫ��
	// ��value�������һ��Ԫ�ص���һ��Ԫ�� Ȼ��_size��1 = (β��֮��)�����ܹ���Ԫ�ظ���
	sq->_data[sq->_size] = value;
	// ���µ�ǰ˳�����Ԫ�صĸ���
	sq->_size++;

	// �൱��
	//seqinsert(sq, sq->_size, value)
}


// ɾ���ӿ� ���ʵ�������ֻ��[0,size-1]
// ɾ��������ȥ�ͷſռ�, ���ܰѿռ仹��ϵͳ(Ҫ���ռ�Ҳ�ǰ�����ռ仹��ϵͳ,����ֻ�ѿռ��ĳһλ�û���ϵͳ), 
// ˳���ɾ�������ͷſռ�, ���ǰѺ����Ԫ��������ǰ�ƶ�һ��λ�ø���Ҫɾ����Ԫ��, �����ǲ����,--_size

// ����λ��ɾ��(�Ѹ�λ�õ����ݸ��Ǽ���)
void seqerase(seqlist* sq, size_t position){

	// ��������, ���������ǿ�����ɾ��Ԫ�صĻ�, �����ֱ�ӹҵ���,����û��Ҫ�ҵ�, assert̫���Ѻ���
	// ���Ҷ���ֻ��debug(����)�汾��, ��realease(����)�汾û����,
	// ������λ��position�Ƿ���Ч
	// assert(position < sq->_size);// ������<= size, sq->_size�Ƿ��ʲ�����
	if (position >= sq->_size)
		return;
	// �ƶ�Ԫ�� ע��Ԫ�ظ������� ->��ǰ�����ƶ�, 
	// ����βɾ�Ļ�, i = position+1ʱ �Ͳ���ѭ����,ֱ��--sq->_size,size�����һ��Ԫ�ص���һ��λ��
	for (size_t i = position + 1; i < sq->_size; ++i){
		sq->_data[i - 1] = sq->_data[i];
	}
	--sq->_size;
}

// ͷɾ
void popfront(seqlist* sq){
	seqerase(sq, 0);
}

//βɾ
void popback(seqlist* sq){
	seqerase(sq, sq->_size - 1);
}



// ���ҽӿ�(�޷��Ų��� ���صĶ��ǷǸ�����λ��)
size_t seqfind(seqlist* sq, datatype value){
	for (size_t i = 0; i < sq->_size; ++i){
		if (sq->_data[i] == value)
			return i;
	}

	return -1; // ����Ҳ������ֵ �������ֵ
}

// ���Ժ���
void test(){
	seqlist sq;
	seqinit(&sq);
	seqpushback(&sq, 0);
	seqpushback(&sq, 1);
	popfront(&sq);
	printseqlist(&sq);// ɾ��֮��ֻʣ��1��,
	seqpushback(&sq, 2);
	seqpushback(&sq, 3);
	seqpushback(&sq, 4);
	popback(&sq);// ɾ��4
	//seqinsert(&sq, 2, 100);
	printseqlist(&sq);// û��ͷ��֮ǰ��ӡһ��  ��ӡ��0,1,100,2,3,4
	seqpushfront(&sq, -1);
	printseqlist(&sq);// ͷ��֮���ٴ�ӡһ�� -1,0,1,100,2,3,4
	printf("erase: \n");
	seqerase(&sq, 3);
	printseqlist(&sq);
	seqerase(&sq, 2);
	printseqlist(&sq);
	seqerase(&sq, 3);
	printseqlist(&sq);
	seqerase(&sq, 0);
	printseqlist(&sq);
	seqerase(&sq, 0);
	printseqlist(&sq);
	seqerase(&sq, 0);
	printseqlist(&sq);
}
void test2(){
	seqlist sq;
	seqinit(&sq);
	seqpushback(&sq, 0);
	seqpushback(&sq, 1);
	seqpushback(&sq, 2);
	seqpushback(&sq, 3);
	seqpushback(&sq, 4);
	printseqlist(&sq);
	printf("%u \n", seqfind(&sq, 3));
	printf("%u \n", seqfind(&sq, 0));
	printf("%u \n", seqfind(&sq, 100));
}

int main(){
	//test();
	test2();
	system("pause");
	return 0;
}