#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 8U

typedef struct{
	uint8_t data[BUFFER_SIZE];
	uint8_t head,tail,count;
}data;

void init(data *object_1){
	object_1->head = 0;
	object_1->tail = 0;
	object_1->count = 0;
}
int is_full(data *object_1) {
    return object_1->count ==BUFFER_SIZE;
}

int is_empty(data *object_1) {
    return object_1->count ==0;
}

int write_buffer(data *object_1,uint8_t value){
	if(is_full(object_1)){
		return 0;
	}
	object_1->data[object_1->head]=value;
	object_1->head = (object_1->head +1 ) % BUFFER_SIZE;
	object_1->count++;
	return 1;
}

int read_buffer(data *object_1,uint8_t *value){
	if(is_empty(object_1)){
		return 0;
	}
	*value = object_1->data[object_1->tail];
	object_1->tail = (object_1->tail +1 ) % BUFFER_SIZE;
	object_1->count--;
	return 1;
}

int main(){

	data object_1;
	uint8_t value;
	init(&object_1);
	for(uint8_t i = 0x41;i<=0x48;i++){
		if(write_buffer(&object_1,i)){
			printf("[Write] 0x%X -> OK (count=%d)\n",i,object_1.count);
		}
	}
	if(!write_buffer(&object_1,0x99)){
		printf("[Write] 0x99 -> FAIL (buffer full)\n");
	}

	for(int i = 0;i<3;i++){
		if(read_buffer(&object_1,&value)){
			printf("[READ] -> 0x%X  (count=%d)\n",value,object_1.count);
		}
	}

	write_buffer(&object_1,0x49);
	write_buffer(&object_1,0x4A);
	write_buffer(&object_1,0x4B);	
	
	while(!is_empty(&object_1)){
		read_buffer(&object_1,&value);
		printf("[READ] ->0x%X (count=%d)\n",value,object_1.count);
	}
	if(!read_buffer(&object_1,&value)){
		printf("[READ] -> FAIL (buffer empty)\n");
	}
	return 0;
}
