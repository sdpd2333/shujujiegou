#ifndef RQUEUE_H
#define RQUEUE_H

constexpr int QUEUE_SIZE = 100;

class CircularQueue {
	public:
	CircularQueue();
	~CircularQueue();
	
	bool isFull();
	bool isEmpty();
	void enqueue(int element);
	int dequeue();
	int front();
	
	private:
	int* queue;
	int frontIndex;
	int rearIndex;
};

#endif // RQUEUE_H