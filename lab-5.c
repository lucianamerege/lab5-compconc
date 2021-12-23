#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  5

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
pthread_cond_t x_condDois;

/* Thread 1 */
void *Um (void *t) {

  pthread_mutex_lock(&x_mutex);
  if(x<(NTHREADS-1)){
    pthread_cond_wait(&x_condDois, &x_mutex); 
  }
  printf("Volte sempre!\n");
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void *Dois (void *t) {

  pthread_mutex_lock(&x_mutex);
  if (x<1) {
    pthread_cond_wait(&x_cond, &x_mutex); 
  }
  printf("Fique a vontade.\n");
  x++;
  pthread_cond_signal(&x_cond);
  if(x==(NTHREADS-1)){
    pthread_cond_signal(&x_condDois);
  }
  pthread_mutex_unlock(&x_mutex);
  pthread_exit(NULL);
}

void *Tres (void *t) {

  pthread_mutex_lock(&x_mutex);
  if (x<1) {
    pthread_cond_wait(&x_cond, &x_mutex); 
  }
  printf("Sente-se por favor.\n");
  x++;
  pthread_cond_signal(&x_cond);
  if(x==(NTHREADS-1)){
    pthread_cond_signal(&x_condDois);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void *Quatro (void *t) {
  pthread_mutex_lock(&x_mutex);
  if (x<1) {
    pthread_cond_wait(&x_cond, &x_mutex); 
  }
  printf("Aceita um copo dagua?\n");
  x++;
  pthread_cond_signal(&x_cond);
  if(x==(NTHREADS-1)){
    pthread_cond_signal(&x_condDois);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

/* Thread 5 */
void *Cinco (void *t) {

  printf("Seja bem-vindo!\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  if(x==1){
    pthread_cond_signal(&x_cond);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);
  pthread_cond_init (&x_condDois, NULL);
  
  /* Cria as threads */
  pthread_create(&threads[4], NULL, Um, NULL);
  pthread_create(&threads[3], NULL, Dois, NULL);
  pthread_create(&threads[2], NULL, Tres, NULL);
  pthread_create(&threads[1], NULL, Quatro, NULL);
  pthread_create(&threads[0], NULL, Cinco, NULL);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  pthread_cond_destroy(&x_condDois);
}
