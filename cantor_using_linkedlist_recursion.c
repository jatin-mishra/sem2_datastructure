#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

struct cantor{
	int index;
	double start_point;
	double end_point;
	struct cantor* next_set;
};


void create_node(struct cantor* first_cantor,int level,int i){
printf("%d\n",i );
struct cantor* iterator;
iterator = first_cantor;

	
	while(iterator != NULL){
		// printf("i am here\n");
    	struct cantor* creating_node;
    	creating_node = (struct cantor*) malloc(sizeof(struct cantor));
    	creating_node->end_point=iterator->end_point;
		creating_node->start_point = (double)((2*(creating_node->end_point) + (iterator->start_point))/3);
		iterator->end_point = (double)(((creating_node->end_point) + 2*(iterator->start_point))/3);
	 	creating_node->index=1;
		creating_node->next_set=iterator->next_set;
		iterator->next_set=creating_node;
		iterator=creating_node->next_set;

	}


if(i==level){
struct cantor* iterate;
iterate = first_cantor;

int index_here = 1;
while(iterate!=NULL){
		// printf("no here\n");
iterate->index=index_here;
index_here++;
printf("index : %d  start_point : %f end_point : %f \n",iterate->index,iterate->start_point,iterate->end_point );
iterate=iterate->next_set;
  }
}

if(i<level){
	create_node(first_cantor,level,++i);
}

}



int main(){
    bool choice = true;
    int number,fetcher,chance=1;

    struct cantor* first_cantor;
    first_cantor=(struct cantor*)malloc(sizeof(struct cantor));
    first_cantor->start_point=0;
    first_cantor->end_point=1;
    first_cantor->index=1;
    first_cantor->next_set=NULL;


  
   		printf("enter the number of level you want in cantor\n");
   		scanf("%d",&number);
   		create_node(first_cantor,number-1,0);

   


return 0;

}