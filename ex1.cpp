#include <iostream>
#include "btree.h"
#include "rqueue.h"

using namespace std;
// Function to test overflow condition of circular queue
void testCircularQueueOverflow() {
CircularQueue cq;
cout << "\nTest case 6: Testing circular queue overflow\n";
try {
for (int i = 0; i <= QUEUE_SIZE; i++) {
cq.enqueue(i);
}
} catch (const std::runtime_error& e) {
cout << "Caught an exception: " << e.what() << endl;
}
}

// Function to test underflow condition of circular queue
void testCircularQueueUnderflow() {
CircularQueue cq;
cout << "\nTest case 7: Testing circular queue underflow\n";
try {
cq.dequeue();
} catch (const std::runtime_error& e) {
cout << "Caught an exception: " << e.what() << endl;
}
}

// Function to test insertion of duplicate elements in binary tree
void testDuplicateInsertionBinaryTree() {
BinaryTree bt;
cout << "\nTest case 8: Testing insertion of duplicate elements in binary tree\n";
int elements[] = {5, 3, 7, 2, 4, 6, 8, 3};
for(int i = 0; i < 8; ++i) {
bt.insert(elements[i]);
}
cout << "Level order traversal of the binary tree is: ";
bt.levelOrderTraversal();
}


int main() {
CircularQueue cq;

// Test case 1: 测试循环队列的基本操作
cout << "Test case 1: \n";
cout << "Enter the number of elements to enqueue in the circular queue: ";
int n;
cin >> n;
for(int i = 0; i < n; ++i) {
int x;
cout << "Enter the element to enqueue: ";
cin >> x;
cq.enqueue(x);
}
cout << "The dequeued order of elements is: ";
while(!cq.isEmpty()) {
cout << cq.dequeue() << " ";
}
cout << endl;

// Test case 2: 测试二叉树的插入与层序遍历
BinaryTree bt;
cout << "\nTest case 2: \n";
cout << "Enter the number of elements to insert into binary tree: ";
cin >> n;
for(int i = 0; i < n; ++i) {
int x;
cout << "Enter the element to insert: ";
cin >> x;
bt.insert(x);
}
cout << "Level order traversal of the binary tree is: ";
bt.levelOrderTraversal();

// Test case 3: 测试顺序存储结构转链式结构
BinaryTree* bt2 = new BinaryTree();
cout << "\nTest case 3: \n";
cout << "Enter the number of elements to convert from array to binary tree: ";
cin >> n;
int* arr = new int[n];
for(int i = 0; i < n; ++i) {
cout << "Enter the element in array: ";
cin >> arr[i];
}
bt2 = bt.arrayToBinaryTree(arr, n);
delete[] arr;
cout << "Level order traversal of the converted binary tree is: ";
bt2->levelOrderTraversal();

// Test case 4: 测试二叉树的宽度计算
cout << "\nTest case 4: The width of the binary tree is - " << bt.getWidth() << endl;

// Test case 5: 测试空二叉树的宽度计算
BinaryTree bt3;
cout << "\nTest case 5: The width of an empty binary tree is - " << bt3.getWidth() << endl;

// Test case 6: 测试循环队列溢出
testCircularQueueOverflow();
// Test case 7: 测试循环队列下溢
testCircularQueueUnderflow();
// Test case 8: 测试二叉树重复元素插入
testDuplicateInsertionBinaryTree();

return 0;
}