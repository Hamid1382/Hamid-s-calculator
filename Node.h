#pragma once
/**
 * Node class for linked list.
 * @related 1.LikedList.
 */
template<typename T>
class Node {
public:
    Node* next;
    T content;
    /**
     * base constructor.
     * @param context
     */
    Node(T content);
};

