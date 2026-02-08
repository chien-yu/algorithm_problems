// a ring buffer can have fixed size and just throw awa oldest data
// only take integer now? can it be more general?

// https://stackoverflow.com/questions/827691/how-do-you-implement-a-circular-buffer-in-c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ringbuffer
{
    size_t ele_size;
    // capacity
    int* buf;
    int* buf_end;
    size_t capacity;
/*
+ (1) A 'head' index - the point at which the producer inserts items into the
+     buffer.
+
+ (2) A 'tail' index - the point at which the consumer finds the next item in
+     the buffer.
*/
    int* tail;
    int* head;
    // bool* readFlagArr;
    // number of element in the ring buffer
    size_t size;
} RingBufferInt;

int setSize(RingBufferInt* rBuf, size_t capacity_, size_t size_)
{
    // https://stackoverflow.com/questions/2987207/why-do-i-get-a-c-malloc-assertion-failure
    rBuf->ele_size = size_;
    rBuf->capacity = capacity_;
    // const size_t incremented_capacity = capacity + 1;
    // void *buf = malloc(incremented_capacity * rBuf->size);
    void *buf = malloc(capacity_ * rBuf->ele_size);
    if (!buf)
    {
        return 1;
    }
    rBuf->buf = (int*)buf;
    // rBuf->buf_end = rBuf->buf + incremented_capacity;
    rBuf->buf_end = rBuf->buf + capacity_;

    memset(rBuf->buf, 0, capacity_ * rBuf->ele_size);
    rBuf->head = buf;
    rBuf->tail = buf;

    return 0;
}

int length(RingBufferInt* rBuf)
{
    // [    ******   ]
    //            ^head
    ///     ^tail
    if (rBuf->tail < rBuf->head)
    {
        return rBuf->head - rBuf->tail;
    }
    // [**     ******]
    //    ^head
    //         ^tail
    else if (rBuf->head < rBuf->tail)
    {
        return rBuf->head - rBuf->buf + rBuf->buf_end - rBuf->tail;
    }
    // [**************]
    //         ^tail
    //         ^head
    // [              ]
    //      ^tail
    //      ^head
    // [              _]
    // ^tail
    //                 ^head = tail+N+1
    //                ^tail+N
}

// size of int array
int push(RingBufferInt* rBuf, int* inArr, size_t inSize)
{
    if (inSize > rBuf->capacity)
    {
        printf("push error\n");
        return 1;
    }

    const size_t leftCapacity = rBuf->capacity - rBuf->size;
    if (inSize > leftCapacity)
    {
        printf("push error\n");
        return 1;
    }

    // [    ******   ]
    //            ^head
    //      ^tail
    // [**     ******]
    //    ^head
    //         ^tail
    // the size exceed the end
    size_t firstCpySize = inSize;
    size_t secondCpySize = 0;
    if (rBuf->head + inSize > rBuf->buf_end)
    {
        firstCpySize = rBuf->buf_end - rBuf->head;
        secondCpySize = inSize - firstCpySize;
    }

    // 1st cpy
    memcpy(rBuf->head, inArr, firstCpySize * rBuf->ele_size);
    rBuf->head += firstCpySize;
    if (rBuf->head == rBuf->buf_end)
    {
        rBuf->head = rBuf->buf;
    }

    // 2nd cpy
    if (secondCpySize)
    {
        memcpy(rBuf->head, inArr + firstCpySize, secondCpySize * rBuf->ele_size);
        rBuf->head += secondCpySize;
    }

    rBuf->size += inSize;

    return 0;
}

// mode?
// block on unread
// or we can allow to overwrite
int get(RingBufferInt* rBuf, int* outArr, size_t outSize)
{
    // [    ******   ]
    //            ^head
    //      ^tail
    // [**     ******]
    //    ^head
    //         ^tail
    if (!outArr || outSize == 0)
    {
        return 1;
    }
    // the size exceed the end
    if (outSize > rBuf->size)
    {
        outSize = rBuf->size;
    }
    size_t firstCpySize = outSize;
    size_t secondCpySize = 0;
    if (rBuf->head < rBuf->tail)
    {
        if (outSize > rBuf->buf_end - rBuf->tail)
        {
            firstCpySize = rBuf->buf_end - rBuf->tail;
            secondCpySize = outSize - firstCpySize;
        }
    }

    memcpy(outArr, rBuf->tail, firstCpySize * rBuf->ele_size);
    rBuf->tail += firstCpySize;
    if (rBuf->tail == rBuf->buf_end)
    {
        rBuf->tail = rBuf->buf;
    }

    if (secondCpySize)
    {
        memcpy(outArr + firstCpySize, rBuf->tail, secondCpySize * rBuf->ele_size);
        rBuf->tail += secondCpySize;
    }

    rBuf->size -= outSize;

    return 0;
}

void dump(RingBufferInt* rBuf)
{
    printf("dump:\n");
    for (int i = 0; i < rBuf->capacity; i++)
    {
        printf("%02d ", rBuf->buf[i]);
        // printf("%02d ", *(rBuf->buf + i));
        if (i%10 == 9)
        {
            printf("\n");
        }
    }
    printf("\n");
}

int main()
{
    RingBufferInt rBuf;
    setSize(&rBuf, 10, sizeof(int));
    int arr[20];
    for (int i = 0; i < sizeof(arr)/sizeof(int) ; i++)
    {
        arr[i] = i;
    }
    push(&rBuf, arr, 5);
    push(&rBuf, arr, 2);
    push(&rBuf, arr, 4);
    // push(&rBuf, arr, 40);

    int outBuf[10];
    get(&rBuf, outBuf, 7);
    push(&rBuf, arr, 4);

    dump(&rBuf);

    // int buffer[20];
    // get(&rBuf, buffer, 20);
    // for (int i = 0; i < 20; i++)
    // {
    //     printf("%d", buffer[i]);
    // }

    free(rBuf.buf);

    return 0;
}