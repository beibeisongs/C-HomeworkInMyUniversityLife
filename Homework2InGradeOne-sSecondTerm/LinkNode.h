// LinkNode.h

# ifndef __LN_H__
# define __LN_H__

template<class T>
class LinkNode {
public:
	LinkNode(T x, LinkNode<T> * link);

	// �����򣬴�Ÿýڵ������
	T data;
	// ָ����ָ����һ���ڵ�
	LinkNode<T> * link;
};

template<class T>
LinkNode<T>::LinkNode(T x, LinkNode<T> * link) {
	this->data = x;
	this->link = link;
}

# endif