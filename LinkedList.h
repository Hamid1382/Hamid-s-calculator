#pragma once
#include "Node.h"
#include "Exception.h"

/**
 * Simple class for linked list
 */
template<typename T>
class LinkedList {
private:
    int size;
    Node<T>* start;
    Node<T>* end;
    /**
     * Provides pointer to node for internal functions.
     * @param iterator node number(stating from 0)
     * @return pointer pointing to needed node.
     */
    Node<T>* getNode(int iterator);
public:
    /**
     * base constructor
     */
    LinkedList();
    /**
     * @param iterator node number(starting from 0)
     * @return content
     */
    T& at(int iterator);
    void push(T context);
    /**
     * @return list size (node(s) count)
     */
    int Size() {
        return size;
    }
    /**
     * Removes a node
     * @param position  node number to be deleted
     */
    void remove(int position);
    /**
     * Removes a range of nodes
     * @param startPos beginning node (includes)
     * @param endPos ending node (includes)
     */
    void remove(int startPos, int endPos);
    /**
     * Removes last node and returns its content.
     * @return Last node's content
     */
    T pop();
    /**
     * insert a node at provided position
     * @param position node will be there
     * @param content for node
     */
    void insert(int position, T content);
    /**
     * finds specific node in the list .
     * @param content what look for.
     * @param start starting position(default = 0).
     * @return first accepted node number.
     */
    int findFirst(T content, int startFrom = 0);
    /**
     * finds specific node in the list .
     * @param content what look for.
     * @param start searches from last to .
     * @return last accepted node number.
     */
    int findLast(T content, int min = 0);
    /**
     * Finds all nodes with specific content
     * @param context what look for.
     * @return list of all accepted nodes' numbers.
     */
    LinkedList<unsigned int> findAll(T context);
};

