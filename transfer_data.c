#include "testsdram.h"
//#include "globals.h"
#include "transfer_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_param(uint32_t* av_slave, uint32_t* u_ocram, uint32_t* w_ocram, uint32_t* data_ptr)
{
	uint32_t i, j;
	//first 2 words are conv2D parameters
	*(av_slave+4) = *(data_ptr);
	*(av_slave+5) = *(data_ptr+1);
	printf("Conv-2D parameters stored\n");
	//next words are Wz, Wr, Wh parameters
	for( i = 0; i < WOCRAM_SIZE; i++)
	{
		j = (uint32_t)(i/20*32 + i%20);
		*(w_ocram + j) = *(data_ptr+i+2);
	}
	//rest are all to be stored in the UOCRAM (including dense layer' parameters)
	printf("Wz, Wr, Wh parameters stored\n");
	for( i = 0; i < UOCRAM_SIZE-19; i++)
	{
		j = (uint32_t)(i/20*32 + i%20);
		*(w_ocram + j) = *(data_ptr+i+2+WOCRAM_SIZE);
	}
	printf("Uz, Ur, Uh, Bz, Br, Bh, Wlin, Blin parameters stored\n");
}

void ocram_init(uint32_t* u_ocram, uint32_t* w_ocram, uint32_t* x_ocram){
	ocram_empty(u_ocram, UOCRAM_SIZE);
	ocram_empty(w_ocram, WOCRAM_SIZE);
	ocram_empty(x_ocram, XOCRAM_SIZE);
}

void xocram_fill_RT(uint32_t* x_ocram, uint32_t* data_ptr){
	uint32_t i, j;
	for( i = 0; i < RTDATA_CHUNK_SIZE; i++)
	{
		j = (uint32_t)(i/20*32 + i%20);
		*(x_ocram + j) = *(data_ptr+i);
	}

}
void ocram_empty(uint32_t* ocram, uint32_t RAM_SIZE){
	uint32_t i, j;
	for( i = 0; i < RAM_SIZE; i ++){
		j = (uint32_t)(i/20*32 + i%20);
		*(ocram + j) = 0;
	}
}