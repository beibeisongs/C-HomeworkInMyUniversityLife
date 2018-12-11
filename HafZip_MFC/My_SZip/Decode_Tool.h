#ifndef __D_H__
#define __D_H__


/*	���ߣ�
*	��Ϊ��
*
*	���ڣ�
*	24/12/18
*/

/*	���ͣ�
*
*	������뽫����ĸƵ�ʽṹ����ڴ����ģʽ����Ϊ��1�ֽڣ�������ʾ��
*	00 00 00 ..
*	00 00 00 ..
*
*	���ã���ʡ�ռ�
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
	bool isFileExist(char * fileName);	// �жϱ�ѹ���ļ��Ƿ����

	HAF_FILE_HEAD readFileHead(const char * sourceFileName);					//	��ȡѹ�����ļ���ͷ��Ԫ���ݣ�һ��16���ֽ�

	ALPHA_FREQ * getAlphaFreq(const char * sourceFileName, int * alphaType, HAF_FILE_HEAD fileHead);	// �õ���ĸ����Ƶ��

	void showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType);			// չʾ��ĸ����Ƶ�ʱ�

	HAFFMAN_TAB * initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid);	// ���ع�������

	void DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType);

	void showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count);

	int getMinFreq(HAFFMAN_TAB * haffmanTab, int count);				// �õ���С��ĸ����Ƶ��

	void creatHuffmanTree(HAFFMAN_TAB * haffmanTab, int alphaType);		// ������������

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

	// ��ȡѹ�����ļ���ͷ��Ԫ���ݣ�16���ֽ�
	fread(&fileHead, sizeof(HAF_FILE_HEAD), 1, f);
	fclose(f);

	return fileHead;
}

ALPHA_FREQ * Decode_Tool::getAlphaFreq(const char * sourceFileName, int * alphaType, HAF_FILE_HEAD fileHead) {
	// ���к������õ���ĸ����Ƶ��
	// �ú�������һ������ĸƵ��ָ��
	// ����һ�����飬������256����ĸASCII���Ӧ�ĳ��ִ���

	int freq[256] = { 0 };
	
	ALPHA_FREQ * alphaFreq = NULL;
	FILE * f;
	// int ch;

	* alphaType = fileHead.alphaType;
	alphaFreq = (ALPHA_FREQ *)calloc(sizeof(ALPHA_FREQ), * alphaType);
	f = fopen(sourceFileName, "rb");

	// �Թ�ǰ16���ֽڵ�Ԫ����
	fseek(f, 16, SEEK_SET);
	fread(alphaFreq, sizeof(ALPHA_FREQ), * alphaType, f);
	fclose(f);

	return alphaFreq;
}

void Decode_Tool::showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType) {
	int i;

	for (i = 0; i < alphaType; i++) {
		int ch = alphaFreq[i].alpha;
		// �ַ�������ASCII���ʾ��Χ
		if (ch > 127) {
			cout << ch << " " << alphaFreq[i].freq << endl;
		}
		else {
			cout << ch << " " << alphaFreq[i].freq << endl;
		}
	}
}

HAFFMAN_TAB * Decode_Tool::initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid) {
	// ���к��������س�ʼ����ģ���������

	int i;
	HAFFMAN_TAB * haffmanTab = NULL;

	/*	Ϊhaffman Table �����ڴ�ռ�
	*	������ 2 * alphaVariety - 1
	*/
	haffmanTab = (HAFFMAN_TAB *)calloc(sizeof(HAFFMAN_TAB), 2 * alphaType - 1);

	for (i = 0; i < alphaType; i++) {
		hafid[alphaFreq[i].alpha] = i;	// �ѹ��������е��ַ������Ӧ���±��γɼ�ֵ��, �浽hafid��

		haffmanTab[i].alphaFreq = alphaFreq[i];
		haffmanTab[i].leftChild = haffmanTab[i].rightChild = -1;
		haffmanTab[i].visited = false;
		haffmanTab[i].code = (char *)calloc(sizeof(char), alphaType);
	}

	return haffmanTab;
}

void Decode_Tool::DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType) {
	// ���к������ͷŴ���ռ�
	int i;

	for (i = 0; i < alphaType; i++) {
		free(haffmanTab[i].code);
	}

	free(haffmanTab);
}

void Decode_Tool::showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count) {
	// ���к�����չʾ��������

	int i;

	printf("%-4s %-4s %-4s %-6s %-6s %-6s %s\n", "�±�", "�ַ�", "Ƶ��", "������", "������", "visited", "����");
	for (i = 0; i < count; i++) {
		printf("%-5d %-4c %-5d %-6d %-7d %-4d %s\n",
			i,
			haffmanTab[i].alphaFreq.alpha,
			haffmanTab[i].alphaFreq.freq,
			haffmanTab[i].leftChild,
			haffmanTab[i].rightChild,
			haffmanTab[i].visited,
			(haffmanTab[i].code ? haffmanTab[i].code : "��"));
	}
}

int Decode_Tool::getMinFreq(HAFFMAN_TAB * haffmanTab, int count) {
	// ���к������ڹ�����������û�з��ʹ�����СƵ���±�

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

	// ��������ʹ��ʣ�µ� alphaType - 1���ռ�
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
	int root = 2 * alphaType - 2;						// ��ʼ�����λ��
	
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
	fileSize = ftell(fIn);								// ��ȡ�ļ��ܳ���fileSize
	fseek(fIn, 16 + 5 * fileHead.alphaType, SEEK_SET);	// �Թ�ǰ��16���ֽڵ�Ԫ���ݣ�5�ֽڵ��ַ������Ƶ��
	
	current_Location = ftell(fIn);

	// �Ӹ�������'1'���������ߣ�'0'���������ߣ�������Ҷ�ӽ�㣬���Ҷ�ӽ���±��Ӧ���ַ�,�ٻص���������
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

		// ȡ����һ���ֽڴӵ�һλ��ʼ����'1'���������ߣ�'0'����������
		// ������һ���ֽڣ�8λ������Ҫ��ȡ��һ���ֽ�
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

		// �����ִ����һ���������ݳ��ȳ���int�ı�ʾ��Χ���ͻ����
		sum &= 0xFF; // 0xFF��Ϊ������λ1111 1111��������sumʼ�������һ���ֽ�, 8λ��
	}

	/*	���������������7λ�����ƣ�����Ϊһ���ֽڣ���ô����һ���ֽ�ֻ��7λΪ��Чλ�����඼������λ��
	*	����ֻ��Ҫȡ������ֽڵ���7����Чλ������sum��8ȡ�༴��
	*	sum = sum % 8 <=> sum = sum & 0x7
	*	�������һ���ֽڵ���Чλ��
	*/
	sum &= 0x7;

	return sum == 0 ? 8 : sum;
}

#pragma pack(pop)

#endif // !__E_H__