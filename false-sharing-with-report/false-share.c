#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <syscall.h>
#include <sys/time.h>

#define LOOP 1000000000
//#define USE_PADDING

struct test_s {
	long l1;
#ifdef USE_PADDING
	long padding[7];
#endif
	long l2;
};

static struct test_s test;

int set_affinity(int cpu)
{
	cpu_set_t set;

	CPU_ZERO(&set);
	CPU_SET(cpu, &set);
	return sched_setaffinity(syscall(SYS_gettid), sizeof(set), &set);
}

static void *func1(void *arg)
{
	printf("enter %s\n", __FUNCTION__);

	long l = 0;
	struct timeval start, end;

	set_affinity(2);
	gettimeofday(&start, NULL);
	for (l = 0; l < LOOP; l++)
		__sync_fetch_and_add(&test.l1, 1);
	gettimeofday(&end, NULL);

	printf("%s time : %ld\n", __FUNCTION__, (end.tv_sec - start.tv_sec) * 1000 * 1000 + end.tv_usec - start.tv_usec);
	printf("leave %s\n", __FUNCTION__);
	return NULL;
}

static void *func2(void *arg)
{
	printf("enter %s\n", __FUNCTION__);

	long l = 0;
	struct timeval start, end;

	set_affinity(4);
	gettimeofday(&start, NULL);
	for (l = 0; l < LOOP; l++)
		__sync_fetch_and_add(&test.l2, 1);
	gettimeofday(&end, NULL);

	printf("%s time : %ld\n", __FUNCTION__, (end.tv_sec - start.tv_sec) * 1000 * 1000 + end.tv_usec - start.tv_usec);
	printf("leave %s\n", __FUNCTION__);
	return NULL;
}

static void *func_yield(void *arg)
{
	printf("enter %s\n", __FUNCTION__);

	while(1)
		sched_yield();

	printf("leave %s\n", __FUNCTION__);
	return NULL;
}



int main()
{
	pthread_t thread[2];
	pthread_attr_t attr;
	int num = 0;

	pthread_attr_init(&attr);

	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread[0], &attr, func1, NULL);
	pthread_create(&thread[1], &attr, func2, NULL);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);

	return 0;
}
