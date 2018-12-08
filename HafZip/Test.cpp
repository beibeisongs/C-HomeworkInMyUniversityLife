// Test.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"Encode_Tool.h"
#include"Decode_Tool.h"

#include "Haf.h"

void encode(string source_file_path, string target_file_path) {
	ALPHA_FREQ * alphaFreq = NULL;				// 统计字符及频度的数组
	int alphaType = 0;							// 字符种类

	HAFFMAN_TAB * haffmanTab = NULL;			// 哈夫曼表
	char * code = NULL;							// 存储字符的哈夫曼编码

	int hafIndex[256] = { 0 };					// 下标为字符的ASCII码，其值为该字符在哈夫曼表中的下标，形成键值对

	Encode_Tool encode;

	// string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.txt";

	const char * sourceFileName = source_file_path.data();

	// string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.Haf";

	const char * targetFileName = target_file_path.data();

	alphaFreq = encode.getAlphaFreq(sourceFileName, &alphaType);
	encode.showAlphaFreq(alphaFreq, alphaType);

	haffmanTab = encode.initHaffmanTab(alphaFreq, alphaType, hafIndex);
	encode.creatHaffmanTree(haffmanTab, alphaType);

	code = (char *)calloc(sizeof(char), alphaType);
	if (alphaType <= 0 || code == NULL) {
		cout << "Error : Empty freq ! 或内存分配失败 ！" << endl;
		exit(1);
	}
	for (int i = 0; i < alphaType; i++) {
		code[i] = NULL;
	}

	encode.makeHaffmanCode(haffmanTab, 2 * alphaType - 2, 0, code);
	encode.showHaffmanTab(haffmanTab, 2 * alphaType - 1);

	encode.haffmanEncoding(haffmanTab, sourceFileName, targetFileName, hafIndex, alphaType, alphaFreq);

	encode.DELETE_HaffmanTab(haffmanTab, alphaType);

	free(alphaFreq);
	free(code);

}

void decode(string source_file_path, string target_file_path) {
	HAF_FILE_HEAD fileHead;

	ALPHA_FREQ * alphaFreq = NULL;				// 统计字符及频度的数组
	int alphaType = 0;							// 字符种类

	HAFFMAN_TAB * haffmanTab = NULL;			// 哈夫曼表
	char * code = NULL;							// 存储字符的哈夫曼编码

	int hafid[256] = { 0 };						// 下标为字符的ASCII码，其值为该字符在哈夫曼表中的下标，形成键值对

	Decode_Tool decode;

	// string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1.Haf";

	const char * sourceFileName = source_file_path.data();

	// string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2_ded.txt";

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
}


int main() {

	string command_rd = "python D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\hello.py D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.txt";
	system(command_rd.c_str());

	string source_file_path;
	string target_file_path;

	char mark;
	cout << "If you want to Szip file ?" << endl;
	cin >> mark;
	if (mark == 'y') {
		cout << "If you want to Szip or unZip doc file ?" << endl;
		cin >> mark;
		if (mark == 'y') {
			cout << "Please input the absolute directory : " << endl;
			cout << "Sample : D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1.doc" << endl;
			cin >> source_file_path;

			string command_rd = "python D:\\USBei\\C++Projects_Py35_Scripts\\encode_trf.py D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1.doc";
			system(command_rd.c_str());

			encode("D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_doc.txt", "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_doc.Haf");

			cout << "If you want to unZip file ?" << endl;
			cin >> mark;
			if (mark == 'y') {
				cout << "Please input the absolute directory to unZip : " << endl;
				cout << "Sample : D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.Haf" << endl;
				cin >> source_file_path;

				source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_doc.Haf";

				cout << "Please input the absolute directory for the target file : " << endl;
				cout << "Sample : D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2_ded.txt" << endl;
				cin >> target_file_path;

				target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_doc.txt";

				decode(source_file_path, target_file_path);

				string command_rd = "python D:\\USBei\\C++Projects_Py35_Scripts\\decode_trf.py D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_ded.doc";
				system(command_rd.c_str());
			}
		}
		else {
			cout << "Please input the absolute directory to unZip : " << endl;
			cout << "Sample : D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.Haf" << endl;
			cin >> source_file_path;

			cout << "Please input the absolute directory for the target file : " << endl;
			cout << "Sample : D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2_ded.txt" << endl;
			cin >> target_file_path;

			encode(source_file_path, target_file_path);
		}
		
	}
	else {
		cout << "If you want to unZip file ?" << endl;
		cin >> mark;
		if (mark == 'y') {
			cout << "Please input the absolute directory to unZip : " << endl;
			cout << "Sample : D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.Haf" << endl;
			cin >> source_file_path;

			cout << "Please input the absolute directory for the target file : " << endl;
			cout << "Sample : D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2_ded.txt" << endl;
			cin >> target_file_path;

			decode(source_file_path, target_file_path);
		}
	}

	return 0;
}