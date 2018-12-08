#ifndef __HAF_H__
#define __HAF_H__

/*	���ߣ�
*	��Ϊ��
*	
*	���ڣ�
*	24/12/18
*/

/*	ȡ��idλ��ֵ
*	ԭ��
*	ȡ��var�ĵ�һλ��
*	((var) & (1 << ((1) ^ 7)))
*	
*	Ч����
*	
*	xxxx xxxx
*	1000 0000
*	_________
*	x000 0000
*
*	ȡ��var�ĵڶ�λ��
*	((var) & (1 << ((2) ^ 7)))
*
*	Ч����
*
*	xxxx xxxx
*	01000 0000
*	_________
*	0x00 0000
*
*	�Դ�����
*/
// ͬ����ԭ�������ǣ�ȡ��varλ�����ж��Ƿ�Ϊ1
#define GET_BYTE(var, id) (((var) & (1 << ((id) ^ 7))) != 0)

// ͬ����ԭ����������ǣ�����varλΪ1
#define SET_BYTE(var, id) ((var) |= (1 << ((id) ^ 7)))
// ͬ����ԭ����������ǣ�����varλΪ0
#define CLR_BYTE(var, id) ((var) &= (~(1 << ((id) ^ 7))))

typedef unsigned char boolean;

#define NOT_INIT -1

typedef struct HAF_FILE_HEAD {
	unsigned char flag[3];				// ѹ���������ļ�ͷ����־ bwj����Ϊ�ѵ���д��
	unsigned char alphaType;			// �ַ�����
	unsigned char lastValidBit;			// ���һ���ֽڵ���Чλ��
	unsigned char leftspace[11];		// ʣ��ռ�
} HAF_FILE_HEAD;

typedef struct ALPHA_FREQ {
	unsigned char alpha;					// �ַ�, ���ǵ��ļ����к���, ���Զ����unsigned char
	int freq;								// �ַ����ֵ�Ƶ��
} ALPHA_FREQ;

typedef struct HAFFMAN_TAB {				// ��������
	ALPHA_FREQ alphaFreq;
	int leftChild;
	int rightChild;
	bool visited;							// �Ƿ��Ѿ�������
	char * code;							// ����������
} HAFFMAN_TAB;

#endif // !__HAF_H__
