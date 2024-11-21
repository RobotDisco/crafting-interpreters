#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char* value;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct DoubleLinkedList {
  Node *head;
  Node *tail;
  size_t size;
} DoublyLinkedList;

// Creation and Destruction
DoublyLinkedList* list_create() {

  DoublyLinkedList* list = malloc(sizeof(DoublyLinkedList));

  // If we fail to malloc for some reason, return NULL
  if (!list) return NULL;

  // set the head and tail to null, because we have no nodes.
  list->head = NULL;
  list->tail = NULL;
  // our list has 0 entries since it has no nodes.
  list->size = 0;

  return list;
}

// Should I be returning a result here?
// We can't fail on a free() call but we can know
// if we didn't properly iterate through the list...
// I could do consistency checks here.
void list_delete(DoublyLinkedList* list) {
  if (!list) return;

  Node* curr = list->head;
  while(curr) {
    curr = curr->next;
    free(curr->prev);
  }
  free(list);
}

// Extend list
// The list ought to own the data value now.
int list_push_front(DoublyLinkedList* list, char* value) {
  // Make sure we're given a valid list
  if (!list) return -1;

  // Allocate space for a new node.
  Node* new_node = malloc(sizeof(Node));
  // error out if we fail to allocate
  if (!new_node) return -1;

  // Assign value to node, attach to list.
  new_node->value = value;

  // Node is at the front, so prev is NULL
  new_node->prev = NULL;
  // Attach node to list
  new_node->next = list->head;

  // If the list already has a head, link it to this node.
  if(list->head) {
    list->head->prev = new_node;
  } else {
    // If there was no previous node in the list, assign this node as the tail
    // as well.
    list->tail = new_node;
  }

  // Link this as the new head of the list
  list->head = new_node;

  // Increment the size counter
  list->size++;
  // Our push succeeded.
  return 0;
}

// Extend list
// The list ought to own the data value now.
int list_push_back(DoublyLinkedList* list, char* value) {
  // Make sure we're given a valid list
  if (!list) return -1;

  // Allocate space for a new node.
  Node* new_node = malloc(sizeof(Node));
  // error out if we fail to allocate
  if (!new_node) return -1;

  // Assign value to node, attach to list.
  new_node->value = value;

  // Node is at the end, so next is NULL
  new_node->next = NULL;
  // Attach node to end of list
  new_node->prev = list->tail;

  // If the list already has a tail, link it to this node.
  if(list->tail) {
    list->tail->next = new_node;
  } else {
    // If there was no node in the list, assign this node as the head
    // as well.
    list->head = new_node;
  }

  // Link this as the new head of the list
  list->tail = new_node;

  // Increment the size counter
  list->size++;
  // Our push succeeded.
  return 0;
}

// Remove nodes from list.
// The caller owns the data now.
int list_pop_front(DoublyLinkedList* list, char** value) {
  // Make sure we're given a valid list
  if (!list) return -1;

  // Error if our list is empty.
  if (!list->head) return -1;

  // We're removing this node from the list.
  Node* popped = list->head;

  // If this was the last node in the list, nullify the other end of the list.
  if (popped == list->tail) list->tail = NULL;
  // Adjust pointers in the list and newly promoted node to remove popped node
  list->head = popped->next;
  list->head->prev = NULL;

  // Set the output variable
  *value = popped->value;
  // Deallocate our popped node, we don't need it anymore.
  free(popped);
  // Decrement our tracking size variable
  --list->size;

  return 0;
}

// Remove nodes from list.
// The caller owns the data now.
int list_pop_back(DoublyLinkedList* list, char** value) {
    // Make sure we're given a valid list
  if (!list) return -1;

  // Error if our list is empty.
  if (!list->tail) return -1;

  // We're removing this node from the list.
  Node* popped = list->tail;

  // If this was the last node in the list, nullify the other end of the list.
  if (popped == list->head) list->head = NULL;
  // Adjust pointers in the list and newly promoted node to remove popped node
  list->tail = popped->prev;
  list->tail->next = NULL;

  // Set the output variable
  *value = popped->value;
  // Deallocate our popped node, we don't need it anymore.
  free(popped);
  // Decrement our tracking size variable
  --list->size;

  return 0;
}

// Find node
Node* list_find(DoublyLinkedList* list, char* value) {
  // Make sure we're given a valid list
  if (!list) return NULL;

  // Error if our list is empty.
  if (!list->size) return NULL;

  // Start at the top
  Node* curr = list->head;

  // Iterate over the list, comparing strings, until there are no more.
  // If you find one, return it. Otherwise, return null.
  while(curr) {
    if(strcmp(value, curr->value)) return curr;
    curr = curr->next;
  }

  return NULL;
};

Node* list_reverse_find(DoublyLinkedList* list, char* value) {
  // Make sure we're given a valid list
  if (!list) return NULL;

  // Error if our list is empty.
  if (!list->size) return NULL;

  // Start at the end
  Node* curr = list->tail;

    // Iterate over the list, comparing strings, until there are no more.
  // If you find one, return it. Otherwise, return null.
  while(curr) {
    if(strcmp(value, curr->value)) return curr;
    curr = curr->prev;
  }

  return NULL;
};

// Print out stuff verbosely, iterating over the list
// in both directions to manually verify consistency.
void list_debug(DoublyLinkedList* list) {
  size_t ctr = 0;
  Node* curr = list->head;
  printf("List size: %zu\n", list->size);
  while(curr) {
    printf("Node %zu: %s\n", ctr++, curr->value);
    curr = curr->next;
  };
  curr = list->tail;
  while(curr) {
    printf("Node %zu: %s\n", --ctr, curr->value);
    curr = curr->prev;
  };
}

// Test Harness
int main(int argc, char** argv) {
  // My terrible testing scaffold

  int res; // We will use this to store our result statuses.

  // Let's create our list.
  DoublyLinkedList* list = list_create();
  // Error out if list creation fails.
  if (!list) return 1;

  // Remember, when we allocate strings, we need to give room for the
  // termination character \0;
  char* str1 = malloc(sizeof(char) * 10); str1 = "Hello";
  char* str2 = malloc(sizeof(char) * 10); str2 = "There";
  char* str3 = malloc(sizeof(char) * 10); str3 = "Cruel";
  char* str4 = malloc(sizeof(char) * 10); str4 = "World";

  // Prepopulate my testing list
  res = list_push_front(list, str1);
  if (res) return 1;
  res = list_push_front(list, str2);
  if (res) return 1;
  res = list_push_back(list, str3);
  if (res) return 1;
  res = list_push_back(list, str4);
  if (res) return 1;

  printf("I'm a little doubly-linked list, short and stout!\n");
  // Does my list look right?
  list_debug(list);

  // Test finding values in both directions
  printf("Was able to find the string %s in list\n", list_find(list, str3)->value);
  printf("Was able to find the string %s in list\n", list_reverse_find(list, str2)->value);


  // Test popping/deletion
  char* value;

  res = list_pop_front(list, &value);
  if (res) return 1;
  printf("Front popped value: %s\n", value);
  //free(value);
  list_debug(list);

  res = list_pop_back(list, &value);
  if (res) return 1;
  printf("Rear popped value: %s\n", value);
  //free(value);
  list_debug(list);

  // Deallocate everything remaining in the list
  list_delete(list);

  return 0;
}
