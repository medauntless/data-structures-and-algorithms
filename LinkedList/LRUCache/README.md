LRU Cache
Approach

The cache is implemented using two data structures:

Hash Map (unordered_map) for O(1) key lookup.
Doubly Linked List to maintain the order of usage.
Front → Most Recently Used (MRU)
Back → Least Recently Used (LRU)

Dummy head and tail nodes are used to simplify insertion and deletion by eliminating edge cases.

Algorithm

get(key) O(1)
  Return -1 if the key doesn't exist.
  Otherwise, move the node to the front (MRU) and return its value.

put(key, value)O(1)
  If the key exists, update its value and move it to the front.
  Otherwise:
  If the cache is full, remove the LRU node.
  Insert the new node at the front.

Complexity
Time Complexity: O(1)
Space Complexity: O(capacity)
