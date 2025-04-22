#include "rbtree.h"

#include <stdio.h>

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t)); 
  // 트리 구조체 sentinel node(nil) 메모리 할당

  // sentinel은 항상 BLACK이며, 자식과 부모는 NULL로 설정
  nil_node->color = RBTREE_BLACK;
  nil_node->left = nil_node;
  nil_node->right = nil_node;
  nil_node->parent = nil_node;

  // tree 구조체에 sentinel 설정
  p->nil = nil_node;

  // 초기에는 root도 nil을 가리킴 (비어있는 트리 상태)
  p->root = p->nil;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

void print_tree(rbtree *t, node_t* node){
  if(node == t->nil) return;
  printf("%d, %s, parent = %d\n", node->key, node->color == RBTREE_BLACK ? "BLACK" : "RED", node->parent->key);
  print_tree(t, node->left);
  print_tree(t, node->right);
}
int main() {
  rbtree *t = new_rbtree();
  //10, 5, 8, 34, 67, 23, 156, 24, 2, 12
  rbtree_insert(t, 10);
  rbtree_insert(t, 5);
  rbtree_insert(t, 8);
  rbtree_insert(t, 34);
  rbtree_insert(t, 67);
  rbtree_insert(t, 23);
  rbtree_insert(t, 156);
  rbtree_insert(t, 24);
  rbtree_insert(t, 2);
  rbtree_insert(t, 12);
  // 중위 순회 출력으로 key 정렬 확인
  // node_t* cur = t->root;
  // printf("Root: %d, Color: %s\n", cur->key, cur->color == RBTREE_BLACK ? "BLACK" : "RED");
  // printf("Left: %d, Right: %d\n", cur->left->key, cur->right->key);
  // if (cur->left != t->nil)
  //   printf("Left: %d\n", cur->left->key);
  // if (cur->right != t->nil)
  // printf("Right: %d\n", cur->right->key);
  print_tree(t, t->root);
  return 0;
}
