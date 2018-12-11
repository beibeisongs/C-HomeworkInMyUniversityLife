#ifndef __D_H__
#define __D_H__


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



class Decode_Tool {
public:
	bool isFileExist(char * fileName);	// 判断被压缩文件是否存在

	HAF_FILE_HEAD readFileHead(const char * sourceFileName);					//	读取压缩的文件的头部元数据，一共16个字节

	ALPHA_FREQ * getAlphaFreq(const char * sourceFileName, int * alphaType, HAF_FILE_HEAD fileHead);	// 得到字母出现频率

	void showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType);			// 展示字母出现频率表

	HAFFMAN_TAB * initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid);	// 返回哈夫曼表

	void DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType);

	void showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count);

	int getMinFreq(HAFFMAN_TAB * haffmanTab, int count);				// 得到最小字母出现频率

	void creatHuffmanTree(HAFFMAN_TAB * haffmanTab, int alphaType);		// 创建哈夫曼树

	void makeHaffmanCode(HAFFMAN_TAB * haffmanTab, int root, int index, char * code);
	
	void haffmanDecoding(HAFFMAN_TAB * haffmanTab, const char * sourceFileName, const char * targetFileName, int alphaType, HAF_FILE_HEAD fileHead);

	int getlastValidBit(HAFFMAN_TAB * haffmanTab, int alphaType);
};

bool Decode_Tool::isFileExist(char * fileName) {
	FILE * f;

	f = fopen(fileName, "rb");
	if (f == NULL) {
		return false;
	}

	fclose(f);
	return true;
}

HAF_FILE_HEAD Decode_Tool::readFileHead(const char * sourceFileName) {
	HAF_FILE_HEAD fileHead;
	FILE * f;

	f= fopen(sourceFileName, "rb");

	// 读取压缩的文件的头部元数据，16个字节
	fread(&fileHead, sizeof(HAF_FILE_HEAD), 1, f);
	fclose(f);

	return fileHead;
}

ALPHA_FREQ * Decode_Tool::getAlphaFreq(const char * sourceFileName, int * alphaType, HAF_FILE_HEAD fileHead) {
	// 公有函数：得到字母出现频率
	// 该函数返回一个，字母频率指针
	// 它是一个数组，储存了256个字母ASCII码对应的出现次数

	int freq[256] = { 0 };
	
	ALPHA_FREQ * alphaFreq = NULL;
	FILE * f;
	// int ch;

	* alphaType = fileHead.alphaType;
	alphaFreq = (ALPHA_FREQ *)calloc(sizeof(ALPHA_FREQ), * alphaType);
	f = fopen(sourceFileName, "rb");

	// 略过前16个字节的元数据
	fseek(f, 16, SEEK_SET);
	fread(alphaFreq, sizeof(ALPHA_FREQ), * alphaType, f);
	fclose(f);

	return alphaFreq;
}

void Decode_Tool::showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType) {
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

HAFFMAN_TAB * Decode_Tool::initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid) {
	// 公有函数：返回初始化后的，哈夫曼表

	int i;
	HAFFMAN_TAB * haffmanTab = NULL;

	/*	为haffman Table 申请内存空间
	*	申请了 2 * alphaVariety - 1
	*/
	haffmanTab = (HAFFMAN_TAB *)calloc(sizeof(HAFFMAN_TAB), 2 * alphaType - 1);

	for (i = 0; i < alphaType; i++) {
		hafid[alphaFreq[i].alpha] = i;	// 把哈夫曼表中的字符和其对应的下标形成键值对, 存到hafid中

		haffmanTab[i].alphaFreq = alphaFreq[i];
		haffmanTab[i].leftChild = haffmanTab[i].rightChild = -1;
		haffmanTab[i].visited = false;
		haffmanTab[i].code = (char *)calloc(sizeof(char), alphaType);
	}

	return haffmanTab;
}

void Decode_Tool::DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType) {
	// 公有函数：释放储存空间
	int i;

	for (i = 0; i < alphaType; i++) {
		free(haffmanTab[i].code);
	}

	free(haffmanTab);
}

void Decode_Tool::showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count) {
	// 公有函数：展示哈夫曼表

	int i;

	printf("%-4s %-4s %-4s %-6s %-6s %-6s %s\n", "下标", "字符", "频度", "左子树", "右子树", "visited", "编码");
	for (i = 0; i < count; i++) {
		printf("%-5d %-4c %-5d %-6d %-7d %-4d %s\n",
			i,
			haffmanTab[i].alphaFreq.alpha,
			haffmanTab[i].alphaFreq.freq,
			haffmanTab[i].leftChild,
			haffmanTab[i].rightChild,
			haffmanTab[i].visited,
			(haffmanTab[i].code ? haffmanTab[i].code : "无"));
	}
}

int Decode_Tool::getMinFreq(HAFFMAN_TAB * haffmanTab, int count) {
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

void Decode_Tool::creatHuffmanTree(HAFFMAN_TAB * haffmanTab, int alphaType) {
	int i;
	int leftChild;
	int rightChild;

	// 哈夫曼表使用剩下的 alphaType - 1个空间
	for (i = 0; i < alphaType - 1; i++) {
		leftChild = getMinFreq(haffmanTab, alphaType + i);
		rightChild = getMinFreq(haffmanTab, alphaType + i);
		haffmanTab[alphaType + i].alphaFreq.alpha = '#';
		haffmanTab[alphaType + i].alphaFreq.freq = haffmanTab[leftChild].alphaFreq.freq + haffmanTab[rightChild].alphaFreq.freq;
		haffmanTab[alphaType + i].leftChild = leftChild;
		haffmanTab[alphaType + i].rightChild = rightChild;
		haffmanTab[alphaType + i].visited = false;
	}
}

void Decode_Tool::makeHaffmanCode(HAFFMAN_TAB * haffmanTab, int root, int index, char * code) {

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

void Decode_Tool::haffmanDecoding(HAFFMAN_TAB * haffmanTab, const char * sourceFileName, const char * targetFileName, int alphaType, HAF_FILE_HEAD fileHead) {
	int root = 2 * alphaType - 2;						// 初始化结点位置
	
	FILE * fIn;
	FILE * fOut;

	bool finished = false;
	unsigned char value;
	unsigned char outValue;
	
	int index = 0;
	
	long fileSize;
	long current_Location;

	fIn = fopen(sourceFileName, "rb");
	fOut = fopen(targetFileName, "wb");

	fseek(fIn, 0L, SEEK_END);
	fileSize = ftell(fIn);								// 获取文件总长度fileSize
	fseek(fIn, 16 + 5 * fileHead.alphaType, SEEK_SET);	// 略过前面16个字节的元数据，5字节的字符种类和频率
	
	current_Location = ftell(fIn);

	// 从根出发，'1'向左子树走，'0'向右子树走，若到达叶子结点，输出叶子结点下标对应的字符,再回到根结点继续
	fread(&value, sizeof(unsigned char), 1, fIn);

	while (!finished) {
		if (haffmanTab[root].leftChild == -1 && haffmanTab[root].rightChild == -1) {
			outValue = haffmanTab[root].alphaFreq.alpha;

			fwrite(&outValue, sizeof(unsigned char), 1, fOut);
			if (current_Location >= fileSize && index >= fileHead.lastValidBit) {
				break;
			}

			root = 2 * alphaType - 2;
		}

		// 取出的一个字节从第一位开始看，'1'向左子树走，'0'向右子树走
		// 若超过一个字节，8位，则需要读取下一个字节
		if (GET_BYTE(value, index)) {
			root = haffmanTab[root].leftChild;
		}
		else {
			root = haffmanTab[root].rightChild;
		}
		if (++index >= 8) {
			index = 0;
			fread(&value, sizeof(unsigned char), 1, fIn);
			current_Location = ftell(fIn);
		}
	}

	fclose(fIn);
	fclose(fOut);
}

int Decode_Tool::getlastValidBit(HAFFMAN_TAB * haffmanTab, int alphaType) {
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