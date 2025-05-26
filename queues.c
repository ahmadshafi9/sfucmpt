#define MAX 5
int queue[MAX], front = 0, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) printf("Queue Overflow\n");
    else queue[++rear] = value;
}

int dequeue() {
    if (front > rear) printf("Queue Underflow\n");
    return queue[front++];
}
