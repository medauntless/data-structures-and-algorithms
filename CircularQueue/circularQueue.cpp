/*
 * Circular Queue
 *
 * A fixed-size FIFO (First-In-First-Out) queue implemented
 * using a circular array.
 *
 * Time Complexity:
 * Push  : O(1)
 * Pop   : O(1)
 * Front : O(1)
 *
 * Space Complexity:
 * O(n)
 */

#include <iostream>

class CircularQueue {
private:
    int* data;
    int capacity;
    int size;
    int frontIndex;
    int rearIndex;

public:
    explicit CircularQueue(int capacity)
        : data(new int[capacity]),
          capacity(capacity),
          size(0),
          frontIndex(0),
          rearIndex(-1) {}

    ~CircularQueue() {
        delete[] data;
    }

    // Disable copying to prevent shallow copies.
    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;

    bool push(int value) {
        if (full()) {
            std::cout << "Queue is full.\n";
            return false;
        }

        rearIndex = (rearIndex + 1) % capacity;
        data[rearIndex] = value;
        ++size;

        return true;
    }

    bool pop() {
        if (empty()) {
            std::cout << "Queue is empty.\n";
            return false;
        }

        frontIndex = (frontIndex + 1) % capacity;
        --size;

        return true;
    }

    int front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty.");
        }

        return data[frontIndex];
    }

    bool empty() const {
        return size == 0;
    }

    bool full() const {
        return size == capacity;
    }

    int currentSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void print() const {
        if (empty()) {
            std::cout << "Queue is empty.\n";
            return;
        }

        int index = frontIndex;

        for (int i = 0; i < size; ++i) {
            std::cout << data[index] << ' ';
            index = (index + 1) % capacity;
        }

        std::cout << '\n';
    }
};

int main() {
    CircularQueue queue(4);

    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);

    std::cout << "Initial Queue: ";
    queue.print();

    queue.pop();

    std::cout << "After Pop: ";
    queue.print();

    queue.push(5);

    std::cout << "After Push(5): ";
    queue.print();

    std::cout << "Front Element: " << queue.front() << '\n';

    return 0;
}
