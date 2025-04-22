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

// 후위 순회로 모든 노드 메모리 해제
void delete_node(node_t *node, node_t *nil) {
  if (node == nil) return;  // nil은 트리의 끝 (리프 역할)

  delete_node(node->left, nil);   // 왼쪽 서브트리
  delete_node(node->right, nil);  // 오른쪽 서브트리
  free(node);                     // 현재 노드
}

// 전체 트리 삭제 함수
void delete_rbtree(rbtree *t) {
  if (t == NULL) return;

  delete_node(t->root, t->nil);  // 루트부터 후위 순회로 삭제
  free(t->nil);                  // sentinel node 해제
  free(t);                       // 트리 구조체 해제
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;               // 1. y는 x의 오른쪽 자식
  x->right = y->left;                 // 2. y의 왼쪽 서브트리를 x의 오른쪽으로 이동

  if (y->left != t->nil) {           // 3. y의 왼쪽 서브트리가 존재하면
    y->left->parent = x;             // 4. 그 서브트리의 부모를 x로 설정
  }

  y->parent = x->parent;             // 5. y의 부모를 x의 부모로 설정

  if (x->parent == t->nil) {         // 6. x가 루트인 경우
    t->root = y;                     // 7. y가 트리의 새로운 루트가 됨
  } 
  else if (x == x->parent->left) { // 8. x가 부모의 왼쪽 자식인 경우
    x->parent->left = y;             // 9. y가 왼쪽 자식이 됨
  } 
  else {                           // 10. x가 오른쪽 자식인 경우
    x->parent->right = y;            //     y가 오른쪽 자식이 됨
  }

  y->left = x;                       // 11. x를 y의 왼쪽 자식으로 설정
  x->parent = y;                     // 12. x의 부모를 y로 설정
}

void right_rotate(rbtree *t, node_t *y) {
  node_t *x = y->left;
  y->left = x->right;

  if (x->right != t->nil) {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == t->nil) {
    t->root = x;
  }  
  else if (y == y->parent->left) {
      y->parent->left = x;
  }
  else {
    y->parent->right = x;
  }

  x->left = y;
  y->parent = x;
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
