#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 1024

static int sh_buf[N];
static int pd_ptr = 0;
static int cs_ptr = 0;

static long long int total;

pthread_mutex_t buf_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_sem;
sem_t full_sem;

void init_buf(int *buf)
{
	int i;
	for (i = 0; i < N; i++) {
		buf[i] = -1;
	}
}

int produce()
{	
	static int i = 1;
	return i++;
}

int consume(int data)
{
	/* consumed ...*/
	total += data;

	return 0;
}

void put_data(int *buf, int data)
{
	if (buf[pd_ptr] != -1) {
		printf("ERROR: buf[%d] is NOT consumed yet\n", pd_ptr);
		exit(-1);
	}

	buf[pd_ptr++] = data;
	if (pd_ptr == N)
		pd_ptr = 0;

	return ;
}

int get_data(int *buf)
{
	int data;
	if (buf[cs_ptr] == -1) {
		printf("ERROR: buf[%d] does NOT have data yet\n", cs_ptr);
		exit(-1);
	}

	data = buf[cs_ptr];
	buf[cs_ptr++] = -1;
	if (cs_ptr == N)
		cs_ptr = 0;	

	return data;
}

void* producer(void* arg)
{
    int data, i;

    for (i = 0; i < 10000; i++) {
        data = produce();

        sem_wait(&empty_sem); // 空きスロット数確認
        pthread_mutex_lock(&buf_lock); // Lock
        
        put_data(sh_buf, data);

        pthread_mutex_unlock(&buf_lock); // Unlock
        sem_post(&full_sem); // データ数カウント
    }

    return NULL;
}

void* consumer(void* arg)
{
    int data, i;

    for (i = 0; i < 10000; i++) {
        sem_wait(&full_sem); // データ有無確認
        pthread_mutex_lock(&buf_lock); // Lock

        data = get_data(sh_buf);

        pthread_mutex_unlock(&buf_lock); // Unlock
        sem_post(&empty_sem); // 空きスロット数カウント

        consume(data);
    }

    return NULL;
}

int main()
{
    int ret;
    pthread_t a, b;

    init_buf(sh_buf);

    sem_init(&empty_sem, 0, N); // セマフォ初期化
    sem_init(&full_sem, 0, 0); // セマフォ初期化

    pthread_create(&a, NULL, &producer, NULL);
	pthread_create(&b, NULL, &consumer, NULL);  

    pthread_join(a, NULL);
    pthread_join(b, NULL);

    printf("%lld\n", total);

    sem_destroy(&empty_sem); // セマフォ破棄
    sem_destroy(&full_sem); // セマフォ破棄

    return 0;
}