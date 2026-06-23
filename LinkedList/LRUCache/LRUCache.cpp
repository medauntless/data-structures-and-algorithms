#include <unordered_map>

class Node {
public:
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int key, int value)
        : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    std::unordered_map<int, Node*> cache;

    // Dummy nodes to eliminate edge cases
    Node* head;
    Node* tail;

    // Removes a node from its current position.
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Inserts a node right after the dummy head.
    // The front of the list always represents the Most Recently Used (MRU) item.
    void addToFront(Node* node) {
        node->prev = head;
        node->next = head->next;

        head->next->prev = node;
        head->next = node;
    }

public:
    explicit LRUCache(int capacity)
        : capacity(capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        auto it = cache.find(key);

        if (it == cache.end())
            return -1;

        Node* node = it->second;

        removeNode(node);
        addToFront(node);

        return node->value;
    }

    void put(int key, int value) {

        auto it = cache.find(key);

        // Key already exists.
        if (it != cache.end()) {
            Node* node = it->second;

            node->value = value;

            removeNode(node);
            addToFront(node);

            return;
        }

        // Cache is full. Evict the Least Recently Used (LRU) node.
        if (cache.size() == capacity) {
            Node* lru = tail->prev;

            removeNode(lru);
            cache.erase(lru->key);

            delete lru;
        }

        Node* newNode = new Node(key, value);

        addToFront(newNode);
        cache[key] = newNode;
    }

    ~LRUCache() {
        Node* current = head;

        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Prevent accidental copying.
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
};
