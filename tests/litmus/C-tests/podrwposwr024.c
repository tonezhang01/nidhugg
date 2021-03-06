/* Copyright (C) 2018 Magnus Lång and Tuan Phong Ngo
 * This benchmark is part of SWSC */

#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

atomic_int vars[6]; 
atomic_int atom_1_r1_1; 
atomic_int atom_1_r7_0; 
atomic_int atom_3_r1_1; 
atomic_int atom_3_r7_0; 

void *t0(void *arg){
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_seq_cst);

  atomic_store_explicit(&vars[1], 1, memory_order_seq_cst);
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v2_r1 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  atomic_store_explicit(&vars[2], 1, memory_order_seq_cst);
  int v4_r5 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v5_r6 = v4_r5 ^ v4_r5;
  int v8_r7 = atomic_load_explicit(&vars[3+v5_r6], memory_order_seq_cst);
  int v24 = (v2_r1 == 1);
  atomic_store_explicit(&atom_1_r1_1, v24, memory_order_seq_cst);
  int v25 = (v8_r7 == 0);
  atomic_store_explicit(&atom_1_r7_0, v25, memory_order_seq_cst);
  return NULL;
}

void *t2(void *arg){
label_3:;
  atomic_store_explicit(&vars[3], 1, memory_order_seq_cst);

  atomic_store_explicit(&vars[4], 1, memory_order_seq_cst);
  return NULL;
}

void *t3(void *arg){
label_4:;
  int v10_r1 = atomic_load_explicit(&vars[4], memory_order_seq_cst);
  atomic_store_explicit(&vars[5], 1, memory_order_seq_cst);
  int v12_r5 = atomic_load_explicit(&vars[5], memory_order_seq_cst);
  int v13_r6 = v12_r5 ^ v12_r5;
  int v16_r7 = atomic_load_explicit(&vars[0+v13_r6], memory_order_seq_cst);
  int v26 = (v10_r1 == 1);
  atomic_store_explicit(&atom_3_r1_1, v26, memory_order_seq_cst);
  int v27 = (v16_r7 == 0);
  atomic_store_explicit(&atom_3_r7_0, v27, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 

  atomic_init(&vars[3], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&vars[2], 0);
  atomic_init(&vars[1], 0);
  atomic_init(&vars[4], 0);
  atomic_init(&vars[5], 0);
  atomic_init(&atom_1_r1_1, 0);
  atomic_init(&atom_1_r7_0, 0);
  atomic_init(&atom_3_r1_1, 0);
  atomic_init(&atom_3_r7_0, 0);

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);
  pthread_create(&thr3, NULL, t3, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);
  pthread_join(thr3, NULL);

  int v17 = atomic_load_explicit(&atom_1_r1_1, memory_order_seq_cst);
  int v18 = atomic_load_explicit(&atom_1_r7_0, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_3_r1_1, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_3_r7_0, memory_order_seq_cst);
  int v21_conj = v19 & v20;
  int v22_conj = v18 & v21_conj;
  int v23_conj = v17 & v22_conj;
  if (v23_conj == 1) assert(0);
  return 0;
}
