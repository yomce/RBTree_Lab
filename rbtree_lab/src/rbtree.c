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
  } else if (x == x->parent->left) { // 8. x가 부모의 왼쪽 자식인 경우
    x->parent->left = y;             // 9. y가 왼쪽 자식이 됨
  } else {                           // 10. x가 오른쪽 자식인 경우
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
  } else if (y == y->parent->left) {
      y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  x->left = y;
  y->parent = x;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  while (z->parent->color == RBTREE_RED) {  // Case 1, 2, 3에 해당하는 반복 조건
    if (z->parent == z->parent->parent->left) {  // z의 부모가 조부모의 왼쪽 자식인 경우
      node_t *y = z->parent->parent->right;      // y는 삼촌 노드 (오른쪽 자식)

      if (y->color == RBTREE_RED) {
        // Case 1: 부모와 삼촌 모두 RED인 경우
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;  // z를 조부모로 올려서 반복
      } else {
        if (z == z->parent->right) {
          // Case 2: z가 오른쪽 자식이면 왼쪽 회전 필요
          z = z->parent;
          left_rotate(t, z);
        }
        // Case 3: 부모는 RED, 삼촌은 BLACK, z는 왼쪽 자식
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }

    } else {  // 부모가 조부모의 오른쪽 자식인 경우 (위의 대칭)
      node_t *y = z->parent->parent->left;  // 삼촌 노드는 왼쪽 자식

      if (y->color == RBTREE_RED) {
        // Case 1 (대칭)
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          // Case 2 (대칭)
          z = z->parent;
          right_rotate(t, z);
        }
        // Case 3 (대칭)
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;  // 루트는 항상 BLACK이어야 함
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = (node_t *)malloc(sizeof(node_t)); // 새 노드 z를 생성
  z->key = key;
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  node_t *x = t->root;   // x는 트리를 탐색하며 내려가는 현재 노드
  node_t *y = t->nil;    // y는 z의 부모 노드

  while (x != t->nil) {  // 리프까지 내려가며 삽입 위치 탐색
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;         // z의 부모를 y로 설정

  if (y == t->nil) {
    t->root = z;         // 트리가 비어있다면 z가 루트
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }

  // 삽입된 노드는 항상 RED로 시작 (위에서 설정됨)
  // 왼쪽, 오른쪽 자식은 이미 t->nil로 설정됨

  rbtree_insert_fixup(t, z);  // 특성 위반을 수정하기 위한 fixup 호출
  return z;                   // 삽입된 노드를 반환
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *cur = t->root;

  // 트리를 순회하면서 key를 탐색
  while (cur != t->nil) {
    if (key == cur->key) {
      return cur;  // key를 찾은 경우 해당 노드 반환
    } else if (key < cur->key) {
      cur = cur->left;  // key가 작으면 왼쪽 서브트리 탐색
    } else {
      cur = cur->right; // key가 크면 오른쪽 서브트리 탐색
    }
  }

  // 끝까지 탐색해도 없으면 NULL 반환
  return NULL;
}

// node_t *rbtree_min(const rbtree *t) {
//   // TODO: implement find
//   return t->root;
// }

// node_t *rbtree_max(const rbtree *t) {
//   // TODO: implement find
//   return t->root;
// }

// int rbtree_erase(rbtree *t, node_t *p) {
//   // TODO: implement erase
//   return 0;
// }

// int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
//   // TODO: implement to_array
//   return 0;
// }

// void print_tree(rbtree *t, node_t* node){
//   if(node == t->nil) return;
//   printf("%d, %s, parent = %d\n", node->key, node->color == RBTREE_BLACK ? "BLACK" : "RED", node->parent->key);
//   print_tree(t, node->left);
//   print_tree(t, node->right);
// }
// int main() {
//   rbtree *t = new_rbtree();
//   //10, 5, 8, 34, 67, 23, 156, 24, 2, 12
//   rbtree_insert(t, 10);
//   rbtree_insert(t, 5);
//   rbtree_insert(t, 8);
//   rbtree_insert(t, 34);
//   rbtree_insert(t, 67);
//   rbtree_insert(t, 23);
//   rbtree_insert(t, 156);
//   rbtree_insert(t, 24);
//   rbtree_insert(t, 2);
//   rbtree_insert(t, 12);
//   // 중위 순회 출력으로 key 정렬 확인
//   // node_t* cur = t->root;
//   // printf("Root: %d, Color: %s\n", cur->key, cur->color == RBTREE_BLACK ? "BLACK" : "RED");
//   // printf("Left: %d, Right: %d\n", cur->left->key, cur->right->key);
//   // if (cur->left != t->nil)
//   //   printf("Left: %d\n", cur->left->key);
//   // if (cur->right != t->nil)
//   // printf("Right: %d\n", cur->right->key);
//   print_tree(t, t->root);
//   return 0;
// }
