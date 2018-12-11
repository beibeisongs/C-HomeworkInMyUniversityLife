#ifndef __E_H__
#define __E_H__


/*	作者：
*	贝为佳
*
*	日期：
*	24/12/18
*/

/*	解释：
*
*	下面代码将，字母频率结构体的内存对齐模式，改为了1字节，如下所示：
*	00 00 00 ..
*	00 00 00 ..
*
*	作用：节省空间
*/

#pragma pack(push)
#pragma pack(1)	

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#include "Haf.h"

using namespace std;

class Encode_Tool {
public:
	bool isFileExist(const char * fileName);	// 判断被压缩文件是否存在

	ALPHA_FREQ * getAlphaFreq(const char * sourceFileName, int * alphaType);	// 得到字母出现频率

	void showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType);			// 展示字母出现频率表

	HAFFMAN_TAB * initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid);	// 返回哈夫曼表

	void DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType);

	void showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count);

	int getMinFreq(HAFFMAN_TAB * haffmanTab, int count);				// 得到最小字母出现频率

	void creatHaffmanTree(HAFFMAN_TAB * haffmanTab, int alphaType);		// 创建哈夫曼树

	void makeHaffmanCode(HAFFMAN_TAB * haffmanTab, int root, int index, char * code);	// 递归实现哈夫曼编码

	void haffmanEncoding(HAFFMAN_TAB * haffmanTab, const char * sourceFileName, const char * targetFileName,
		int * hafid, int alphaType, ALPHA_FREQ * alphaFreq);

	int getlastValidBit(HAFFMAN_TAB * haffmanTab, int alphaType);
};

bool Encode_Tool::isFileExist(const char * fileName) {
	FILE * f;

	f = fopen(fileName, "rb");
	if (f == NULL) {
		return false;
	}

	fclose(f);
	return true;
}

ALPHA_FREQ * Encode_Tool::getAlphaFreq(const char * sourceFileName, int * alphaType) {
	// 公有函数：得到字母出现频率
	// 该函数返回一个，字母频率指针
	// 它是一个数组，储存了256个字母ASCII码对应的出现次数

	int freq[256] = { 0 };
	int i;
	int id;

	ALPHA_FREQ * alphaFreq = NULL;
	FILE * f;
	int ch;

	f = fopen(sourceFileName, "rb");

	// 统计所有字符的频度
	ch = fgetc(f);
	while (!feof(f)) {
		freq[ch]++;
		ch = fgetc(f);
	}
	fclose(f);

	// 统计所有字符的种类，变量alphaType获得字符种类的数量
	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			(*alphaType)++;
		}
	}

	alphaFreq = (ALPHA_FREQ *)calloc(sizeof(ALPHA_FREQ), *alphaType);
	for (i = id = 0; i < 256; i++) {
		if (freq[i]) {
			alphaFreq[id].alpha = i;		// i实际上就是字符对应的ASCII码
			alphaFreq[id].freq = freq[i];	// freq[i]是该字符对应的出现频率
			id++;
		}
	}

	return alphaFreq;
}

void Encode_Tool::showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType) {
	int i;

	for (i = 0; i < alphaType; i++) {
		int ch = alphaFreq[i].alpha;
		// 字符超出了ASCII码表示范围
		if (ch > 127) {
			cout << ch << " " << alphaFreq[i].freq << endl;
		}
		else {
			cout << ch << " " << alphaFreq[i].freq << endl;
		}
	}
}

HAFFMAN_TAB * Encode_Tool::initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid) {
	// 公有函数：返回初始化后的，哈夫曼表

	int i;
	HAFFMAN_TAB * haffmanTab = NULL;

	/*	为haffman Table 申请内存空间
	*	申请了 2 * alphaVariety - 1
	*
	*	注意，haffmanTab 是一个指针数组
	*/
	int tab_length = 2 * alphaType - 1;
	haffmanTab = (HAFFMAN_TAB *)calloc(sizeof(HAFFMAN_TAB), tab_length);

	for (i = 0; i < tab_length; i++) {
		haffmanTab[i].alphaFreq.alpha = NULL;						// haffmanTab的每个元素的数据成员获得对应的字母出现频率
		haffmanTab[i].alphaFreq.freq = NULL;

		haffmanTab[i].leftChild = haffmanTab[i].rightChild = -1;	// 初始化为-1
		haffmanTab[i].visited = false;								// 初始化为false
		haffmanTab[i].code = NULL;
	}


	/*	alphaType：
	*
	*	记录了文件中字符的ASCII码种类的数量
	*/
	for (i = 0; i < alphaType; i++) {
		hafid[alphaFreq[i].alpha] = i;								// 把哈夫曼表中的字符和其对应的下标形成键值对,存到hafid中
		haffmanTab[i].alphaFreq = alphaFreq[i];						// haffmanTab的每个元素的数据成员获得对应的字母出现频率
		haffmanTab[i].leftChild = haffmanTab[i].rightChild = -1;	// 初始化为-1
		haffmanTab[i].visited = false;								// 初始化为false
		haffmanTab[i].code = (char *)calloc(sizeof(char), alphaType);
	}

	return haffmanTab;
}

void Encode_Tool::DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType) {
	// 公有函数：释放储存空间
	int i;

	for (i = 0; i < alphaType; i++) {
		free(haffmanTab[i].code);
	}

	free(haffmanTab);
}

void Encode_Tool::showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count) {
	// 公有函数：展示哈夫曼表

	int i;

	cout << "下标" << "   " << "字符" << "   " << "频率" << "   " << "左子树" << "   " << "右子树" << "   " << "visited" << "   " << "编码" << endl;

	for (i = 0; i < count; i++) {
		cout << i << "   " << haffmanTab[i].alphaFreq.alpha << "   " << haffmanTab[i].alphaFreq.freq << "   " << haffmanTab[i].leftChild << "   " << haffmanTab[i].rightChild << "   " << haffmanTab[i].visited << "   " << (haffmanTab[i].code ? haffmanTab[i].code : "无") << endl;
	}
}

int Encode_Tool::getMinFreq(HAFFMAN_TAB * haffmanTab, int count) {
	// 公有函数：在哈夫曼表中找没有访问过的最小频率下标

	int index;
	int minIndex = NOT_INIT;	// NOT_INIT = -1

	for (index = 0; index < count; index++) {
		if (false == haffmanTab[index].visited) {
			if (NOT_INIT == minIndex || haffmanTab[index].alphaFreq.freq < haffmanTab[minIndex].alphaFreq.freq) {
				minIndex = index;
			}
		}
	}
	haffmanTab[minIndex].visited = true;

	return minIndex;
}

void Encode_Tool::creatHaffmanTree(HAFFMAN_TAB * haffmanTab, int alphaType) {
	int i;
	int leftChild;
	int rightChild;

	// 哈夫曼表使用剩下的 alphaType - 1个空间
	for (i = 0; i < alphaType - 1; i++) {
		leftChild = getMinFreq(haffmanTab, alphaType + i);			// 最小堆思想，提取出最小出现次数的字符
		rightChild = getMinFreq(haffmanTab, alphaType + i);			// 最小堆思想，提取出次小出现次数的字符
		haffmanTab[alphaType + i].alphaFreq.alpha = '#';
		haffmanTab[alphaType + i].alphaFreq.freq = haffmanTab[leftChild].alphaFreq.freq + haffmanTab[rightChild].alphaFreq.freq;	// 哈夫曼树生成算法
		haffmanTab[alphaType + i].leftChild = leftChild;
		haffmanTab[alphaType + i].rightChild = rightChild;
		haffmanTab[alphaType + i].visited = false;
	}
}

void Encode_Tool::makeHaffmanCode(HAFFMAN_TAB * haffmanTab, int root, int index, char * code) {
	// 公有函数：递归实现哈夫曼编码

	if (haffmanTab[root].leftChild != -1 && haffmanTab[root].rightChild != -1) {
		code[index] = '1';
		makeHaffmanCode(haffmanTab, haffmanTab[root].leftChild, index + 1, code);
		code[index] = '0';
		makeHaffmanCode(haffmanTab, haffmanTab[root].rightChild, index + 1, code);
	}
	else {
		code[index] = 0;
		strcpy(haffmanTab[root].code, code);
	}
}

void Encode_Tool::haffmanEncoding(HAFFMAN_TAB * haffmanTab, const char * sourceFileName, const char * targetFileName,
	int * hafid, int alphaType, ALPHA_FREQ * alphaFreq) {

	FILE * fpIn;
	FILE * fpOut;

	int ch;

	unsigned char value;

	int bitIndex = 0;

	int i;

	char * hafCode = NULL;

	HAF_FILE_HEAD fileHead = { 'h', 'a', 'f' };

	fpIn = fopen(sourceFileName, "rb");
	fpOut = fopen(targetFileName, "wb");

	fileHead.alphaType = (unsigned char)alphaType;
	fileHead.lastValidBit = getlastValidBit(haffmanTab, alphaType);

	//	size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
	//	ptr -- 这是指向要被写入的元素数组的指针。
	//	size -- 这是要被写入的每个元素的大小，以字节为单位。
	//	nmemb -- 这是元素的个数，每个元素的大小为 size 字节。
	//	stream -- 这是指向 FILE 对象的指针，该 FILE 对象指定了一个输出流。

	// 给文件头部写入元数据
	fwrite(&fileHead, sizeof(HAF_FILE_HEAD), 1, fpOut);

	// 写入元数据后写字符种类和频度，解压缩时需要用这些生成一模一样新的哈夫曼树
	fwrite(alphaFreq, sizeof(ALPHA_FREQ), alphaType, fpOut);

	ch = fgetc(fpIn);
	while (!feof(fpIn)) {
		hafCode = haffmanTab[hafid[ch]].code;
		if (hafCode != NULL) {
			// 把每个字符的哈夫曼编码一个一个过。
			// 如果是字符'0'，就转换为二进制的0
			// 如果是字符'1'，就转换为二进制的1
			for (i = 0; hafCode[i]; i++) {
				if ('0' == hafCode[i]) {
					//value为一个字节
					//从第1位依次赋值，若大于八位（一个字节）了，就写入文件中
					CLR_BYTE(value, bitIndex);
				}
				else {
					SET_BYTE(value, bitIndex);
				}
				bitIndex++;
				if (bitIndex >= 8) {
					bitIndex = 0;
					fwrite(&value, sizeof(unsigned char), 1, fpOut);

					// cout << value << endl;
				}
			}
		}
		ch = fgetc(fpIn);
	}
	// 如果最后一次不满一个字节，依然需要写到文件中，注意：写入的最后一个字节可能会存在垃圾位
	if (bitIndex) {
		fwrite(&value, sizeof(unsigned char), 1, fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);

}

int Encode_Tool::getlastValidBit(HAFFMAN_TAB * haffmanTab, int alphaType) {
	int sum = 0;
	int i;

	for (i = 0; i < alphaType; i++) {
		sum += strlen(haffmanTab[i].code) * haffmanTab[i].alphaFreq.freq;

		// 如果不执行这一步，当数据长度超过int的表示范围，就会出错
		sum &= 0xFF; // 0xFF化为二进制位1111 1111，这样做sum始终是最后一个字节, 8位的
	}

	/*	举例：若最后生成7位二进制，划分为一个字节，那么，这一个字节只有7位为有效位，其余都是垃圾位。
	*	我们只需要取出这个字节的那7个有效位，所以sum和8取余即可
	*	sum = sum % 8 <=> sum = sum & 0x7
	*	返回最后一个字节的有效位数
	*/
	sum &= 0x7;

	return sum == 0 ? 8 : sum;
}

#pragma pack(pop)

#endif // !__E_H__