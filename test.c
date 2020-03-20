//#include <stdio.h>
//#include <assert.h>
//#include <Windows.h>
//
//// 进行频繁的插入或删除是不用顺序表的 用链表(效率高)
//// 顺序表:(支持随机访问(一次可以跳到任意位置) 适合尾插,
//// 插入时间复杂度
//// 1. 尾插:时间复杂度为O(1), 不需要移动元素
//// 2. 除过尾插,其他任意(包括头插)位置插入都是O(N), 需要把已经存在的元素向后移动)
//// 需要检查容量, 如果空间已满, 需要增容, 增容代价大
//
//// 删除: (适合尾删 其他性能低)
//// 并不需要释放空间, 只需要覆盖原有位置的值即可
//// 除过尾删的时间复杂度为 O(1), 其他都需要移动元素 所以时间复杂度为O(N)
//// 不需要增容 因为是删除
//
//// 1. 线性表(连续存储)
//// 线性表是n个具有相同特性的数据元素的有限序列. 线性表是一种在实际中广泛使用的数据结构,
//// 常见的线性表:顺序表, 链表, 栈, 队列, 字符串...
//// 线性表在逻辑上是线性结构, 也就是说是连续的一条直线, 但是在物理结构上并不一定是连续的, 
//// 线性表在物理上存储时, 通常以数组和链式结构的形式存储
//
//// 2. 顺序表(以数组的形式来存放, 一种是定长的(静态顺序表), 一种是不定长的(动态顺序表)
//// 顺序表是用一段物理地址连续的存储单元依次存储数据元素的线性结构,
//// 一般情况采用数组存休, 在数组上完成数据的增删查改
//// 当你在定义顺序表时, 他的大小长度就确定了, 就是定长顺序表, 一般他的元素是放在栈上, (能存储的元素不多)
//// 使用动态开辟的数组存储就是动态顺序表.(使用多)动态调整满足对大量数据的存储 堆上存储 
//// 顺序表总共能存储多少元素就是容量, 但是容量跟元素个数是不同的, 
//// 顺序表支持访问 但不适合在中间插入元素等 增容代价大
//// 他的结构用结构体来定义 定义一个结构体来描述当前顺序表的结构
//
//typedef int DataType; //类型别名 若数据类型为float, double 就替换int
//// 动态顺序表
//typedef struct seqList{
//	// 是要动态开辟空间, 在堆上开辟, 只能通过指针访问, malloc申请返回指针 相当于是int* 
//	DataType* _data;
//	// 个数不可能是负数, 所以用size_t 无符号整数(0-4G) int(-2G-2G)  
//	// size 表示顺序表当前存放的元素个数
//	size_t _size;
//	// capacity 表示顺序表可以存放的最大元素个数
//	size_t _capacity;
//} seqList;// 别名
//
//// 打印
//void printSeqList(seqList* sq){
//	for (size_t i = 0; i < sq->_size; ++i){
//		printf("%d ", sq->_data[i]);
//	}
//	printf("\n");
//}
//
//// 顺序表初始化
//void seqInit(seqList* sq){
//	// 初始化意味着空的顺序表
//	sq->_data = NULL;
//	sq->_capacity = 0;
//	sq->_size = 0;
//}
//
//// 检查容量 增容
//void checkCapacity(seqList* sq){
//	if (sq->_size == sq->_capacity){
//		// 顺序表已满, 需要增容, 
//		// 1. 开辟空间, 2. 拷贝原有空间内容, 3. 释放原有空间
//		// 确定新的容量, 如果是空表,先开10个, 不为0, 则扩大到原始容量的2倍
//		size_t newCapacity = sq->_size == 0 ? 10 : 2 * sq->_capacity;// _size=_capacity
//		// malloc, memcpy, free
//		// 开新的空间
//		//// newData为新指针 capacity(容量)表示数据个数, 开空间(字节)需要个数乘以类型大小 DataType
//		//DataType* newData = (DataType*)malloc(newCapacity * sizeof(DataType));
//		//// 新的空间,原始空间,字节个数(拷贝多少), 将原始空间的内容拷到新空间
//		//memcpy(newData, sq->_data, sq->_size * sizeof(DataType));
//		//// 由于sq->_data在释放之前已经变了 所以需要借助临时变量来保存;
//		//DataType* tmp = sq->_data;
//		// free(sq->_data); 若在这里释放就不需要借助变量保存了
//		//sq->_data = newData;
//		//free(tmp);
//		// realloc(原有指针,新的大小)  上面malloc后所有都可以用下面代替
//		sq->_data = (DataType*)realloc(sq->_data, newCapacity * sizeof(DataType));
//		sq->_capacity = newCapacity; 
//	}
//}
//
//
//// 操作接口: 增删查改
//// 插入接口(三个成员: 指针_data, 当前个数_size, 容量_capacity)
//
//// 任意位置([0,size]插入元素(以及指定的位置)
//// 从position后的元素都要向后移动
//void seqInsert(seqList* sq, size_t position, DataType value){
//	// 保证插入的位置是正确的 [0,size]
//	assert(position <= sq->_size);
//	// 检查容量
//	checkCapacity(sq);
//	// 元素移动
//	for (size_t i = sq->_size; i > position; --i){
//		sq->_data[i] = sq->_data[i - 1];// [size-1,position]
//
//	}
//	// 插入
//	sq->_data[position] = value;
//	++sq->_size;
//
//}
//// 头插(传当前的数据表, 以及要插入的值)
//// 把所有的元素向后移动, 再插入
//void seqPushFront(seqList* sq, DataType value){
//	checkCapacity(sq);
//	// 移动元素, 所有元素向后移动一个位置
//	// 从前往后移动, 错误 数据会被覆盖
//	//for (int i = 0; i < sq->_size; ++i){
//	//	sq->_data[i + 1] = sq->_data[i];// 这样会造成覆盖, 所有元素都是一样的,
//	//}
//	// 从后往前移动 不能是i>=0 :1. 死循环, 2. 访问越界 非负数是不可能小于0的,
//	for (size_t i = sq->_size; i > 0; --i){
//		// sq->_data[i + 1] = sq->_data[i]; 
//		sq->_data[i] = sq->_data[i - 1];//
//
//	}
//	// 插入
//	sq->_data[0] = value;
//	++sq->_size;
//
//	// seqInsert(sq, 0, value);
//}
//
//
//// 尾插
//// 相当于数组指针(头指针)向后偏移_size个位置,把新的元素放进去, 然后元素个数加1(_size++)
//void seqPushBack(seqList* sq, DataType value){
//	// sq代表顺序表
//	// 先检查容量 看有没有空间继续插入 ,不写检查容量 若顺序表为空, 会导致访问异常
//	checkCapacity(sq);
//	// 插入操作(sq->_data是顺序表的数组指针,sq->_size为在顺序表中的位置, 
//	// 让数组指针的下标为总个数(不是总个数-1) => 即为最后一个元素的下一个元素
//	// 将value赋给最后一个元素的下一个元素 然后_size加1 = (尾插之后)现在总共的元素个数
//	sq->_data[sq->_size] = value;
//	// 更新当前顺序表中元素的个数
//	sq->_size++;
//
//	// 相当于
//	//seqInsert(sq, sq->_size, value)
//}
//
//
//// 删除接口 访问到的区间只有[0,size-1]
//// 删除并不是去释放空间, 不能把空间还给系统(要还空间也是把整块空间还给系统,不能只把空间的某一位置还给系统), 
//// 顺序表删除不是释放空间, 而是把后面的元素整体向前移动一个位置覆盖要删除的元素, 容量是不变的,--_size
//
//// 任意位置删除(把该位置的数据覆盖即可)
//void seqErase(seqList* sq, size_t position){
//
//	// 断言慎用, 假设现在是空链表删除元素的话, 程序就直接挂掉了,本来没必要挂掉, assert太不友好了
//	// 而且断言只在debug(开发)版本用, 在realease(发行)版本没作用,
//	// 检测给定位置position是否有效
//	// assert(position < sq->_size);// 不能是<= size, sq->_size是访问不到的
//	if (position >= sq->_size)
//		return;
//	// 移动元素 注意元素覆盖问题 ->从前往后移动, 
//	// 当是尾删的话, i = position+1时 就不进循环了,直接--sq->_size,size是最后一个元素的下一个位置
//	for (size_t i = position + 1; i < sq->_size; ++i){
//		sq->_data[i - 1] = sq->_data[i];
//	}
//	--sq->_size;
//}
//
//// 头删
//void popFront(seqList* sq){
//	seqErase(sq, 0);
//}
//
////尾删
//void popBack(seqList* sq){
//	seqErase(sq, sq->_size - 1);
//}
//
//
//
//// 查找接口(无符号查找 返回的都是非负数的位置)
//size_t seqFind(seqList* sq, DataType value){
//	for (size_t i = 0; i < sq->_size; ++i){
//		if (sq->_data[i] == value)
//			return i;
//	}
//
//	return -1; // 如果找不到这个值 返回最大值
//}
//
//// 测试函数
//void test(){
//	seqList sq;
//	seqInit(&sq);
//	seqPushBack(&sq, 0);
//	seqPushBack(&sq, 1);
//	popFront(&sq);
//	printSeqList(&sq);// 删除之后只剩下1了,
//	seqPushBack(&sq, 2);
//	seqPushBack(&sq, 3);
//	seqPushBack(&sq, 4);
//	popBack(&sq);// 删掉4
//	//seqInsert(&sq, 2, 100);
//	printSeqList(&sq);// 没有头插之前打印一下  打印了0,1,100,2,3,4
//	seqPushFront(&sq, -1);
//	printSeqList(&sq);// 头插之后再打印一下 -1,0,1,100,2,3,4
//	printf("Erase: \n");
//	seqErase(&sq, 3);
//	printSeqList(&sq);
//	seqErase(&sq, 2);
//	printSeqList(&sq);
//	seqErase(&sq, 3);
//	printSeqList(&sq);
//	seqErase(&sq, 0);
//	printSeqList(&sq);
//	seqErase(&sq, 0);
//	printSeqList(&sq);
//	seqErase(&sq, 0);
//	printSeqList(&sq);
//}
//void test2(){
//	seqList sq;
//	seqInit(&sq);
//	seqPushBack(&sq, 0);
//	seqPushBack(&sq, 1);
//	seqPushBack(&sq, 2);
//	seqPushBack(&sq, 3);
//	seqPushBack(&sq, 4);
//	printSeqList(&sq);
//	printf("%u \n", seqFind(&sq, 3));
//	printf("%u \n", seqFind(&sq, 0));
//	printf("%u \n", seqFind(&sq, 100));
//}
//
//int main(){
//	//test();
//	test2();
//	system("pause");
//	return 0;
//}