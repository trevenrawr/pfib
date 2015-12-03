#include <time.h>
#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "BlockingQueue.h"

struct BlockingQueueStruct {
    size_t head, tail;
    pthread_mutex_t lock;
    sem_t entrySem, slotSem;
    void *entries[QUEUE_SIZE];
};

BlockingQueue *BlockingQueue_create() {
    BlockingQueue *q = calloc(1, sizeof(BlockingQueue));
    sem_init(&q->entrySem, 0, 0);
    sem_init(&q->slotSem, 0, QUEUE_SIZE);
    pthread_mutex_init(&q->lock, NULL);
    return q;
}

void BlockingQueue_destroy(BlockingQueue *q) {
    free(q);
}

void BlockingQueue_add(BlockingQueue *q, void *entry) {
    sem_wait(&q->slotSem);
    // START CRITICAL SECTION
    pthread_mutex_lock(&q->lock);
    q->entries[q->head++] = entry;
    if (q->head >= QUEUE_SIZE) q->head = 0;
    pthread_mutex_unlock(&q->lock);
    // END CRITICAL SECTION
    sem_post(&q->entrySem);
}

static inline void *_BlockingQueue_doRemove(BlockingQueue *q) {
    // ASSUMING SEMAPHORE WAIT!
    // START CRITICAL SECTION
    pthread_mutex_lock(&q->lock);
    void *result = q->entries[q->tail++];
    if (q->tail >= QUEUE_SIZE) q->tail = 0;
    pthread_mutex_unlock(&q->lock);
    // END CRITICAL SECTION
    sem_post(&q->slotSem);
    return result;
}

void *BlockingQueue_remove(BlockingQueue *q) {
    sem_wait(&q->entrySem);
    return _BlockingQueue_doRemove(q);
}

void *BlockingQueue_tryRemove(BlockingQueue *q) {
    // return if not ready
    return (sem_trywait(&q->entrySem) == 0)
        ? _BlockingQueue_doRemove(q) : NULL;
}

void *BlockingQueue_timedRemove(BlockingQueue *q, uint32_t milliseconds) {
    // set up delay
    uint32_t s  = milliseconds / 1000;
    uint32_t ns = (milliseconds % 1000) * 1000000;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec  += s;
    ts.tv_nsec += ns;
    // await sem or timeout
    int res;
    do  {
        res = sem_timedwait(&q->entrySem, &ts);
        // restart if interrupted by handler
    } while (res == -1 && errno == EINTR);
    // return NULL on timeout, otherwise get an item
    assert(res != -1 || errno == ETIMEDOUT);
    return (res == -1) ? NULL : _BlockingQueue_doRemove(q);
}

/* -------------------------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------------------------- */


void startFinish() {
// Declares what needs to be finished before moving on.
}

void endFinish() {
// Blocks until everything in the finish scope is done.
}

void async() {
// Schedules work on the queue for threads to take.
}

void work() {
// Loops and pulls work from the queue until the queue is empty
	
}


int main() {
	BlockingQueue *q = BlockingQueue_create();

	
	return 0;
}
