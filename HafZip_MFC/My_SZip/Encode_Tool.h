#ifndef __E_H__
#define __E_H__


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

class Encode_Tool {
public:
	bool isFileExist(const char * fileName);	// �жϱ�ѹ���ļ��Ƿ����

	ALPHA_FREQ * getAlphaFreq(const char * sourceFileName, int * alphaType);	// �õ���ĸ����Ƶ��

	void showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType);			// չʾ��ĸ����Ƶ�ʱ�

	HAFFMAN_TAB * initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid);	// ���ع�������

	void DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType);

	void showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count);

	int getMinFreq(HAFFMAN_TAB * haffmanTab, int count);				// �õ���С��ĸ����Ƶ��

	void creatHaffmanTree(HAFFMAN_TAB * haffmanTab, int alphaType);		// ������������

	void makeHaffmanCode(HAFFMAN_TAB * haffmanTab, int root, int index, char * code);	// �ݹ�ʵ�ֹ���������

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
	// ���к������õ���ĸ����Ƶ��
	// �ú�������һ������ĸƵ��ָ��
	// ����һ�����飬������256����ĸASCII���Ӧ�ĳ��ִ���

	int freq[256] = { 0 };
	int i;
	int id;

	ALPHA_FREQ * alphaFreq = NULL;
	FILE * f;
	int ch;

	f = fopen(sourceFileName, "rb");

	// ͳ�������ַ���Ƶ��
	ch = fgetc(f);
	while (!feof(f)) {
		freq[ch]++;
		ch = fgetc(f);
	}
	fclose(f);

	// ͳ�������ַ������࣬����alphaType����ַ����������
	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			(*alphaType)++;
		}
	}

	alphaFreq = (ALPHA_FREQ *)calloc(sizeof(ALPHA_FREQ), *alphaType);
	for (i = id = 0; i < 256; i++) {
		if (freq[i]) {
			alphaFreq[id].alpha = i;		// iʵ���Ͼ����ַ���Ӧ��ASCII��
			alphaFreq[id].freq = freq[i];	// freq[i]�Ǹ��ַ���Ӧ�ĳ���Ƶ��
			id++;
		}
	}

	return alphaFreq;
}

void Encode_Tool::showAlphaFreq(ALPHA_FREQ * alphaFreq, int alphaType) {
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

HAFFMAN_TAB * Encode_Tool::initHaffmanTab(ALPHA_FREQ * alphaFreq, int alphaType, int * hafid) {
	// ���к��������س�ʼ����ģ���������

	int i;
	HAFFMAN_TAB * haffmanTab = NULL;

	/*	Ϊhaffman Table �����ڴ�ռ�
	*	������ 2 * alphaVariety - 1
	*
	*	ע�⣬haffmanTab ��һ��ָ������
	*/
	int tab_length = 2 * alphaType - 1;
	haffmanTab = (HAFFMAN_TAB *)calloc(sizeof(HAFFMAN_TAB), tab_length);

	for (i = 0; i < tab_length; i++) {
		haffmanTab[i].alphaFreq.alpha = NULL;						// haffmanTab��ÿ��Ԫ�ص����ݳ�Ա��ö�Ӧ����ĸ����Ƶ��
		haffmanTab[i].alphaFreq.freq = NULL;

		haffmanTab[i].leftChild = haffmanTab[i].rightChild = -1;	// ��ʼ��Ϊ-1
		haffmanTab[i].visited = false;								// ��ʼ��Ϊfalse
		haffmanTab[i].code = NULL;
	}


	/*	alphaType��
	*
	*	��¼���ļ����ַ���ASCII�����������
	*/
	for (i = 0; i < alphaType; i++) {
		hafid[alphaFreq[i].alpha] = i;								// �ѹ��������е��ַ������Ӧ���±��γɼ�ֵ��,�浽hafid��
		haffmanTab[i].alphaFreq = alphaFreq[i];						// haffmanTab��ÿ��Ԫ�ص����ݳ�Ա��ö�Ӧ����ĸ����Ƶ��
		haffmanTab[i].leftChild = haffmanTab[i].rightChild = -1;	// ��ʼ��Ϊ-1
		haffmanTab[i].visited = false;								// ��ʼ��Ϊfalse
		haffmanTab[i].code = (char *)calloc(sizeof(char), alphaType);
	}

	return haffmanTab;
}

void Encode_Tool::DELETE_HaffmanTab(HAFFMAN_TAB * haffmanTab, int alphaType) {
	// ���к������ͷŴ���ռ�
	int i;

	for (i = 0; i < alphaType; i++) {
		free(haffmanTab[i].code);
	}

	free(haffmanTab);
}

void Encode_Tool::showHaffmanTab(HAFFMAN_TAB * haffmanTab, int count) {
	// ���к�����չʾ��������

	int i;

	cout << "�±�" << "   " << "�ַ�" << "   " << "Ƶ��" << "   " << "������" << "   " << "������" << "   " << "visited" << "   " << "����" << endl;

	for (i = 0; i < count; i++) {
		cout << i << "   " << haffmanTab[i].alphaFreq.alpha << "   " << haffmanTab[i].alphaFreq.freq << "   " << haffmanTab[i].leftChild << "   " << haffmanTab[i].rightChild << "   " << haffmanTab[i].visited << "   " << (haffmanTab[i].code ? haffmanTab[i].code : "��") << endl;
	}
}

int Encode_Tool::getMinFreq(HAFFMAN_TAB * haffmanTab, int count) {
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

void Encode_Tool::creatHaffmanTree(HAFFMAN_TAB * haffmanTab, int alphaType) {
	int i;
	int leftChild;
	int rightChild;

	// ��������ʹ��ʣ�µ� alphaType - 1���ռ�
	for (i = 0; i < alphaType - 1; i++) {
		leftChild = getMinFreq(haffmanTab, alphaType + i);			// ��С��˼�룬��ȡ����С���ִ������ַ�
		rightChild = getMinFreq(haffmanTab, alphaType + i);			// ��С��˼�룬��ȡ����С���ִ������ַ�
		haffmanTab[alphaType + i].alphaFreq.alpha = '#';
		haffmanTab[alphaType + i].alphaFreq.freq = haffmanTab[leftChild].alphaFreq.freq + haffmanTab[rightChild].alphaFreq.freq;	// �������������㷨
		haffmanTab[alphaType + i].leftChild = leftChild;
		haffmanTab[alphaType + i].rightChild = rightChild;
		haffmanTab[alphaType + i].visited = false;
	}
}

void Encode_Tool::makeHaffmanCode(HAFFMAN_TAB * haffmanTab, int root, int index, char * code) {
	// ���к������ݹ�ʵ�ֹ���������

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
	//	ptr -- ����ָ��Ҫ��д���Ԫ�������ָ�롣
	//	size -- ����Ҫ��д���ÿ��Ԫ�صĴ�С�����ֽ�Ϊ��λ��
	//	nmemb -- ����Ԫ�صĸ�����ÿ��Ԫ�صĴ�СΪ size �ֽڡ�
	//	stream -- ����ָ�� FILE �����ָ�룬�� FILE ����ָ����һ���������

	// ���ļ�ͷ��д��Ԫ����
	fwrite(&fileHead, sizeof(HAF_FILE_HEAD), 1, fpOut);

	// д��Ԫ���ݺ�д�ַ������Ƶ�ȣ���ѹ��ʱ��Ҫ����Щ����һģһ���µĹ�������
	fwrite(alphaFreq, sizeof(ALPHA_FREQ), alphaType, fpOut);

	ch = fgetc(fpIn);
	while (!feof(fpIn)) {
		hafCode = haffmanTab[hafid[ch]].code;
		if (hafCode != NULL) {
			// ��ÿ���ַ��Ĺ���������һ��һ������
			// ������ַ�'0'����ת��Ϊ�����Ƶ�0
			// ������ַ�'1'����ת��Ϊ�����Ƶ�1
			for (i = 0; hafCode[i]; i++) {
				if ('0' == hafCode[i]) {
					//valueΪһ���ֽ�
					//�ӵ�1λ���θ�ֵ�������ڰ�λ��һ���ֽڣ��ˣ���д���ļ���
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
	// ������һ�β���һ���ֽڣ���Ȼ��Ҫд���ļ��У�ע�⣺д������һ���ֽڿ��ܻ��������λ
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