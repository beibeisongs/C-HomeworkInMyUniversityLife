#ifndef __HAF_H__
#define __HAF_H__

/*	作者：
*	贝为佳
*	
*	日期：
*	24/12/18
*/

/*	取出id位的值
*	原理：
*	取出var的第一位：
*	((var) & (1 << ((1) ^ 7)))
*	
*	效果：
*	
*	xxxx xxxx
*	1000 0000
*	_________
*	x000 0000
*
*	取出var的第二位：
*	((var) & (1 << ((2) ^ 7)))
*
*	效果：
*
*	xxxx xxxx
*	01000 0000
*	_________
*	0x00 0000
*
*	以此类推
*/
// 同上面原理，动作是，取出var位，并判断是否为1
#define GET_BYTE(var, id) (((var) & (1 << ((id) ^ 7))) != 0)

// 同上面原理，动作变成是，设置var位为1
#define SET_BYTE(var, id) ((var) |= (1 << ((id) ^ 7)))
// 同上面原理，动作变成是，设置var位为0
#define CLR_BYTE(var, id) ((var) &= (~(1 << ((id) ^ 7))))

typedef unsigned char boolean;

#define NOT_INIT -1

typedef struct HAF_FILE_HEAD {
	unsigned char flag[3];				// 压缩二进制文件头部标志 bwj（贝为佳的缩写）
	unsigned char alphaType;			// 字符种类
	unsigned char lastValidBit;			// 最后一个字节的有效位数
	unsigned char leftspace[11];		// 剩余空间
} HAF_FILE_HEAD;

typedef struct ALPHA_FREQ {
	unsigned char alpha;					// 字符, 考虑到文件中有汉字, 所以定义成unsigned char
	int freq;								// 字符出现的频率
} ALPHA_FREQ;

typedef struct HAFFMAN_TAB {				// 哈夫曼表
	ALPHA_FREQ alphaFreq;
	int leftChild;
	int rightChild;
	bool visited;							// 是否已经被访问
	char * code;
} HAFFMAN_TAB;

#endif // !__HAF_H__
