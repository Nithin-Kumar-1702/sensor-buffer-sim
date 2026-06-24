#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BUFFER_MAX 200
#define MIN_RAND_VAL 0
#define MAX_RAND_VAL 255

unsigned char buffer[BUFFER_MAX];

unsigned int byte_count = 0;

int rand_byte_count(void);      // returns random count (0-5) of bytes for this tick.

int rand_byte_data(void);       // returns one random byte value (0-255).

void producer_tick(void);       // simulates sensor producing 0-5 random bytes for one second.

void consumer_tick(void);       // checks buffer, prints+removes latest 50 bytes if threshold met.

void run_simulation(int);       // runs the producer/consumer simulation for given total seconds.

int main()
{
    srand(time(NULL));

    run_simulation(60);
}

int rand_byte_count()
{
    int rand_byte = rand() % 6;

    return rand_byte;
}

int rand_byte_data()
{
    int rand_data = rand() % (MAX_RAND_VAL - MIN_RAND_VAL + 1) + MIN_RAND_VAL;

    return rand_data;
}

void run_simulation(int total_sec)
{
    int sec=0;

    for(sec=1; sec<=total_sec; sec++)
    {
        producer_tick();
        printf("t= %d sec ",sec);
        printf("Added %d Bytes\n",byte_count);


        if((sec % 10) == 0)
        {
            consumer_tick();
            printf("\n");
        }
    }
}

void producer_tick(void)
{
    int i=0;
    int r = rand_byte_count();

    for(i=0; i<r; i++)
    {
        if(byte_count < BUFFER_MAX)
        {
        buffer[byte_count] = rand_byte_data();
        byte_count++;
        }   
    }
}

void consumer_tick(void)
{
    int i=0;
    int original_count = byte_count;
    if(original_count >= 50)
    {
        printf("Printing 50 Bytes in Hex: \n");
        for(i=original_count-1; i >= (original_count-50); i--)
        {
            printf("%x ", buffer[i]);
        }
        byte_count = i+1;
        printf("\n%d\n", byte_count);
    }
}