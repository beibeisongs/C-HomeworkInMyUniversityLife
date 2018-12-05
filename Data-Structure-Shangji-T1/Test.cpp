// Test.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"Encode_Tool.h"
#include"Decode_Tool.h"

#include "Haf.h"


int main() {
	/*
	ALPHA_FREQ * alphaFreq = NULL;				// ͳ���ַ���Ƶ�ȵ�����
	int alphaType = 0;							// �ַ�����

	HAFFMAN_TAB * haffmanTab = NULL;			// ��������
	char * code = NULL;							// �洢�ַ��Ĺ���������

	int hafIndex[256] = { 0 };					// �±�Ϊ�ַ���ASCII�룬��ֵΪ���ַ��ڹ��������е��±꣬�γɼ�ֵ��

	Encode_Tool encode;

	// string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\lz.bmp";
	// string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1.doc";
	string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.txt";

	const char * sourceFileName = source_file_path.data();

	// string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\lz.Haf";
	string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.Haf";

	const char * targetFileName = target_file_path.data();

	alphaFreq = encode.getAlphaFreq(sourceFileName, &alphaType);
	encode.showAlphaFreq(alphaFreq, alphaType);

	haffmanTab = encode.initHaffmanTab(alphaFreq, alphaType, hafIndex);
	encode.creatHaffmanTree(haffmanTab, alphaType);

	code = (char *)calloc(sizeof(char), alphaType);

	encode.makeHaffmanCode(haffmanTab, 2 * alphaType - 2, 0, code);
	encode.showHaffmanTab(haffmanTab, 2 * alphaType - 1);

	encode.haffmanEncoding(haffmanTab, sourceFileName, targetFileName, hafIndex, alphaType, alphaFreq);

	encode.DELETE_HaffmanTab(haffmanTab, alphaType);

	free(alphaFreq);
	free(code);
	*/
	
	HAF_FILE_HEAD fileHead;

	ALPHA_FREQ * alphaFreq = NULL;				// ͳ���ַ���Ƶ�ȵ�����
	int alphaType = 0;							// �ַ�����

	HAFFMAN_TAB * haffmanTab = NULL;			// ��������
	char * code = NULL;							// �洢�ַ��Ĺ���������

	int hafid[256] = { 0 };						// �±�Ϊ�ַ���ASCII�룬��ֵΪ���ַ��ڹ��������е��±꣬�γɼ�ֵ��

	Decode_Tool decode;

	// string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\lz.Haf";
	string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.Haf";

	const char * sourceFileName = source_file_path.data();

	// string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_ded.doc";
	// string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\lz_ded.bmp";
	string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2_ded.txt";

	const char * targetFileName = target_file_path.data();

	fileHead = decode.readFileHead(sourceFileName);

	alphaFreq = decode.getAlphaFreq(sourceFileName, &alphaType, fileHead);
	decode.showAlphaFreq(alphaFreq, alphaType);

	haffmanTab = decode.initHaffmanTab(alphaFreq, alphaType, hafid);
	decode.creatHuffmanTree(haffmanTab, alphaType);

	code = (char *)calloc(sizeof(char), alphaType);

	decode.makeHaffmanCode(haffmanTab, 2 * alphaType - 2, 0, code);
	decode.showHaffmanTab(haffmanTab, 2 * alphaType - 1);

	decode.haffmanDecoding(haffmanTab, sourceFileName, targetFileName, alphaType, fileHead);

	decode.DELETE_HaffmanTab(haffmanTab, alphaType);
	free(alphaFreq);
	free(code);
	

	return 0;
}