#include "LinkedList.h"
#include "LinkedList.h"
#include "Node.cpp"

template<typename T>
Node<T>* LinkedList<T>::getNode(int iterator) {
    if (iterator < 0 || iterator >= size)
        throw Exception("iterator out of range!(func:getNode)");
    if (iterator == 0) {
        return this->start;
    }
    else if (iterator == this->size - 1) {
        return this->end;
    }
    else {
        Node<T>* tmp = start;
        for (int i = 0; i < iterator; i++) {
            tmp = tmp->next;
        }
        return tmp;
    }
}

template<typename T>
LinkedList<T>::LinkedList() {
    this->size = 0;
    this->start = nullptr;
    this->end = nullptr;
}

template<typename T>
T& LinkedList<T>::at(int iterator) {
    if (iterator < 0 || iterator >= size)
        throw Exception("iterator out of range!(func:at)");
    return this->getNode(iterator)->content;
}

template<typename T>
LinkedList<unsigned int> LinkedList<T>::findAll(T context) {
    static LinkedList<unsigned int> tmp;
    for (int i = 0; i < this->size; i++) {
        if (this->at(i) == context) {
            tmp.push(i);
        }
    }
    return tmp;
}

template<typename T>
int LinkedList<T>::findFirst(T content, int startFrom) {
    for (int i = startFrom; i < this->size; i++) {
        if (this->at(i) == content) {
            return i;
        }
    }
    return -1;
}

template<typename T>
int LinkedList<T>::findLast(T content, int min) {
    for (int i = size - 1; i >= min; i--) {
        if (this->at(i) == content) {
            return i;
        }
    }
    return -1;
}

template<typename T>
void LinkedList<T>::insert(int position, T content) {
    if (position < 0 || position > size)
        throw Exception("Given invalid position(func:insert)");
    if (position == size) {
        this->push(content);
        return;
    }
    if (position == 0) {
        Node<T>* tmp = start;
        start = new Node<T>(content);
        start->next = tmp;
    }
    else {
        Node<T>* tmp = getNode(position);
        getNode(position - 1)->next = new Node<T>(content);
        getNode(position)->next = tmp;
    }
}

template<typename T>
T LinkedList<T>::pop() {
    if (size == 0)
        throw Exception("list is empty already!(func:pop)");
    if (size == 1) {
        T tmp = start->content;
        delete start;
        size = 0;
        return tmp;
    }
    Node<T>* tmp = getNode(this->size - 1);
    T tmp2 = tmp->next->content;
    delete this->end;
    this->end = tmp;
    size--;
    return tmp2;
}

template<typename T>
void LinkedList<T>::remove(int startPos, int endPos) {
    if (startPos < 0 || startPos >= size)
        throw Exception("start position out of range!(func:remove(range))");
    if (endPos < 0 || endPos >= size)
        throw Exception("start position out of range!(func:remove(range))");
    if (startPos >= endPos)
        throw Exception("end position must be greater than start position!(func:remove(range))");
    Node<T>* tmp = this->getNode(startPos), * tmp2;
    this->getNode(startPos - 1)->next = getNode(endPos + 1);
    for (int i = 0; i < endPos - startPos + 1; i++) {
        tmp2 = tmp->next;
        delete tmp;
        tmp = tmp2;
    }
    size -= endPos - startPos + 1;
}

template<typename T>
void LinkedList<T>::remove(int position) {
    if (position < 0 || position >= size)
        throw Exception("position out of range!func:remove)");
    if (position == 0) {
        Node<T>* tmp = start;
        start = start->next;
        delete tmp;
        size--;
    }
    else if (position == this->size - 1) {
        Node<T>* tmp = this->getNode(size - 2);
        delete this->end;
        this->end = tmp;
        size--;
    }
    else {
        Node<T>* tmp = this->getNode(position);
        this->getNode(position - 1)->next = getNode(position + 1);
        delete tmp;
        size--;
    }
}

template<typename T>
void LinkedList<T>::push(T context) {
    if (this->size != 0) {
        this->end->next = new Node<T>(context);
        this->end = this->end->next;
        this->size++;
    }
    else {
        this->start = new Node<T>(context);
        this->end = start;
        size++;
    }
}