// LinkNode.h

# ifndef __LN_H__
# define __LN_H__

template<class T>
class LinkNode {
public:
	LinkNode(T x, LinkNode<T> * link);

	// 数据域，存放该节点的数据
	T data;
	// 指针域，指向下一个节点
	LinkNode<T> * link;
};

template<class T>
LinkNode<T>::LinkNode(T x, LinkNode<T> * link) {
	this->data = x;
	this->link = link;
}

# endif
