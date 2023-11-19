#include "rqueue.h"
#include <stdexcept>

CircularQueue::CircularQueue() {
	queue = new int[QUEUE_SIZE];
	frontIndex = 0;
	rearIndex = 0;
}

CircularQueue::~CircularQueue() {
	delete[] queue;
}

bool CircularQueue::isFull() {
	return ((rearIndex + 1) % QUEUE_SIZE == frontIndex);
}

bool CircularQueue::isEmpty() {
	return (rearIndex == frontIndex);
}

void CircularQueue::enqueue(int element) {
	if (isFull()) {
	throw std::runtime_error("Error: Queue is full!");
} else {
	queue[rearIndex] = element;
	rearIndex = (rearIndex + 1) % QUEUE_SIZE;
	}
}

int CircularQueue::dequeue() {
if (isEmpty()) {
throw std::runtime_error("Error: Queue is empty!");
} else {
int result = queue[frontIndex];
frontIndex = (frontIndex + 1) % QUEUE_SIZE;
return result;
}
}
int CircularQueue::front() {
if (isEmpty()) {
throw std::runtime_error("Error: Queue is empty!");
} else {
return queue[frontIndex];
}
}