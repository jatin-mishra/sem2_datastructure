#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct tree_node tree;

struct tree_node{
	char student_name[20];
	int income;
	int index;
	int height;
	struct tree_node* left_child;
	struct tree_node* right_child;
	struct tree_node* parent;
};


int rotation_required(tree* violator, tree* instance){
	int p[2];
    for(int i=0;i<2;i++){
		if(violator->index > instance->index){
			p[i]=0;
			violator = violator->left_child;
		}
		else{
			p[i]=1;
			violator = violator->right_child;
		}
   	}
	int q = 10* p[1] + p[0];
	return q;
}

// this function will return address of the index, make sure index should exist before using this function
tree* get_me_address(tree** head,int index_to_find){
	tree* iterator;
	iterator = *head;

	while(true){
		if(iterator->index < index_to_find)
			iterator = iterator->right_child;
		else if(iterator->index > index_to_find)
			iterator = iterator->left_child;
		else{
			return iterator;
		}
	}
}



void left_rotate(tree** head,tree* violator){
    tree* header;
    int flag=0;
	if(violator == *head){
		flag=1;
		header = violator->right_child;
	}
 	tree* transfering;
  	transfering = violator->right_child->parent;  // saving k as parent of x
  	violator->right_child->parent = violator->parent;
  	violator->parent = violator->right_child;
  	if(violator != *head){
  		if(violator->right_child->parent->index <= violator->index)
  	  		violator->right_child->parent->right_child = violator->right_child;
  		else
  	  		violator->right_child->parent->left_child = violator->right_child;
  	}
  	violator->right_child = violator->right_child->left_child;
  	transfering->parent->left_child = transfering;
  	if(transfering->right_child != NULL)
  	transfering->right_child->parent = transfering;
	if(flag==1)
	*head = header;
}

// complete
void right_rotate(tree**  head,tree* violator){
	int flag=0;
	tree* header;
	if(violator == *head){
		flag=1;
		header = violator->left_child;
	} 
	tree* transfering;
 	transfering = violator->left_child->parent;  
 	violator->left_child->parent = violator->parent;
 	violator->parent = violator->left_child;
	if(violator != *head){
  		if(violator->left_child->parent->index > violator->index )
  			violator->left_child->parent->left_child = violator->left_child;
  		else
  	    	violator->left_child->parent->right_child = violator->left_child;
    }
    violator->left_child = violator->left_child->right_child;
    transfering->parent->right_child = transfering;
    if(transfering->left_child != NULL)
    transfering->left_child->parent = transfering;
	if(flag==1)
		*head = header;
}


int max_height(int a,int b){
	if(a>b)
		return a;
	return b;
}


int update_height(tree* head,int want){
	if(head==NULL){
	 	return -1;
	}     
	else{
 		if(want)
 			head->height = max_height(update_height(head->left_child,1),update_height(head->right_child,1)) + 1;
 		return head->height;
	}
}




tree* is_violating(tree* head, tree* instance){
 	tree* capture;
 	capture = instance;
	instance = instance->parent;
	// also see if any of them is null then ?
	int h;
	if(instance != NULL){
		h = update_height(instance->left_child,0) - update_height(instance->right_child,0);
    }
 	while(instance != NULL && h<=1 && h>= -1){
		instance = instance->parent;
		if(instance != NULL)
			h = update_height(instance->left_child,0) - update_height(instance->right_child,0);
 		}
 	if(instance == NULL)
 		return capture;
 	return instance;

}


void add(tree** head,tree* instance){
	tree* iterator;
	iterator = (tree*)malloc(sizeof(tree));
	iterator = *head;
	if(*head == NULL)
		*head = instance;
	else{
		if(iterator->index <= instance->index){
			if(iterator->right_child != NULL){
				add(&((*head)->right_child),instance);
			}
			else{
				(*head)->right_child = instance;
				instance->parent = *head;
			}
		}
		else{
			if(iterator->left_child != NULL){
				add(&((*head)->left_child),instance);
			}
			else{
				(*head)->left_child = instance;
				instance->parent = *head;
			}
		}
	}
}






// returns true if index exists else returns false
bool is_exist(tree** head,int number){
	if(*head != NULL){
    	if((*head)->index > number)
     			return is_exist(&((*head)->left_child),number);
     	else if((*head)->index < number)
     			return is_exist(&((*head)->right_child),number);
     	else{
     		   printf("this index exists\n");
     			return true;
		}
	}

	else{
		return false;
	}
}



void get_instance(tree** head){   
	tree* instance;
	instance = (tree*) malloc(sizeof(tree));
	printf("\n enter the name of the student\n");
	scanf("%s",instance->student_name);
	printf("\n enter his income\n ");
	scanf("%d",&instance->income);
	bool satisfied = true;
	instance->parent=NULL;
	while(satisfied){
		printf("\n enter any unique index \n");
		scanf("%d",&instance->index);
    	if(!is_exist(head,instance->index)){
    		satisfied = false;
    	}
   	}
	add(head,instance);
	int height = update_height(*head,1);
	tree* violator;
	violator = is_violating(*head,instance);
	if(violator != instance){
      int p = rotation_required(violator,instance);

      if(p==11){
      	// rr
      	left_rotate(head,violator);
      }
      else if(p==0){
      	// ll
      	right_rotate(head,violator);
      }
      else if(p==1){
      	
      		// right left rotation
      	right_rotate(head,violator->right_child);
      	left_rotate(head,violator);

      }
      else{
      // left right rotation
      	left_rotate(head,violator->left_child);
      	right_rotate(head,violator);
      }
      height = update_height(*head,1);
	}
}


void print(tree* instance){
	printf("\n");
	printf("\nname : %s\n",instance->student_name);
	printf("income is : %d\n",instance->income);
	printf("index is : %d\n",instance->index);
	printf("height is : %d\n",instance->height);
	if(instance->parent != NULL)
	{
		printf("parent is : %s\n",instance->parent->student_name);
	}
	printf("\n");
}

void print_all(tree* head){
if(head != NULL){
	print(head);
	print_all(head->left_child);
	print_all(head->right_child);
	}
}


tree* get_larger_than_but_smallest(tree* starting_point){
  int flag=0;
  tree* iterator = starting_point->right_child;
  while(iterator->left_child != NULL){
  	flag=1;
  	iterator = iterator->left_child;
  }
  if(flag==1)
  iterator->parent->left_child = NULL;
  else
  iterator->parent->right_child = NULL;
  iterator->parent = NULL;

return iterator;
}


tree* get_smaller_than_but_largest(tree* starting_point){
 int flag=0;
  tree* iterator = starting_point->left_child;
  while(iterator->right_child != NULL){
  	flag=1;
  	iterator = iterator->right_child;
  }
  if(flag==1)
  iterator->parent->right_child = NULL;
  else
  iterator->parent->left_child = NULL;
  iterator->parent = NULL;
return iterator;
}


void print_with_height(tree* head,int h){
    if(head != NULL){   
      if(head->height == h){
      	printf(" (index : %d. name- %s : height-  %d  ,parent: %s)               ",head->index,head->student_name,head->height,head->parent->student_name);
      }
      else{
      	print_with_height(head->left_child,h);
      	print_with_height(head->right_child,h);
      }
  }

}



void print_as_tree(tree* head){

	int p = update_height(head,0);
	for(int i=p;i>=0;i--){
      print_with_height(head,i);
      printf("\n\n\n");
	}

}



void deletebyindex(tree** head, int index_to_delete){
 if(is_exist(head,index_to_delete)){
    tree* address_of_index = get_me_address(head,index_to_delete);
    if((address_of_index->left_child != NULL && address_of_index->right_child != NULL) || address_of_index->right_child != NULL){
          tree* copy_me_to_index = get_larger_than_but_smallest(address_of_index); // also disconnect that
          strcpy(address_of_index->student_name,copy_me_to_index->student_name);
          address_of_index->index = copy_me_to_index->index;
          address_of_index->income = copy_me_to_index->income;
          update_height(*head,1);
    }
    else if(address_of_index->left_child != NULL){
          tree* copy_me_to_index = get_smaller_than_but_largest(address_of_index); // also disconnect that
    	  strcpy(address_of_index->student_name,copy_me_to_index->student_name);
          address_of_index->index = copy_me_to_index->index;
          address_of_index->income = copy_me_to_index->income;
          update_height(*head,1);

    	}
    else{

          if(address_of_index == *head){
          	*head = NULL;
          	printf("\n making null \n");
          }
          else{
           if(address_of_index->index < address_of_index->parent->index){
           		address_of_index->parent->left_child = NULL;
           }
           else{
           		address_of_index->parent->right_child = NULL;
           }
           address_of_index->parent=NULL;
           update_height(*head,1);
	    }
	}

          

	    
   }
   else{
   	printf("\n this index doesnot exist\n");
   }
}


void get_heightofindex(tree** head,int index){
 if(is_exist(head,index)){
  tree* address=get_me_address(head,index);
  printf("\nheight of the index is : %d\n",address->height);
}
else{
	printf("\n this number does not exist\n");
	}
}

void  search(tree**  head,int index){
  if(is_exist(head,index)){
  	tree* address = get_me_address(head,index);
  	print(address);
  }else{
  	printf("\ndoes not exist\n");
  }
}


int main(){


	printf("-------------------------------welcome to the avl tree---------------------------\n");

	bool choice = true;
	int number,index;
	char more,agreement;
	struct tree_node* head;
	head = (struct tree_node*)malloc(sizeof(struct tree_node));
	head=NULL;

	while(choice){

		printf("select any choice or enter -1 to get the list of options\n");
		scanf("%d",&number);

		if(number == -1){
			printf("\n1. get_instance \n2. get_heightofindex \n3. search \n4.deletebyindex\n5. print_all \n6. print_as_tree\n\n");
		}
		else{

			switch(number){
				case 1:
				   printf("\n you are going to insert an instance \n");
				   get_instance(&head);
				   break;
				case 2: 
				      printf("\nenter the index whose height you want to know\n");
				      scanf("%d",&index);
				      get_heightofindex(&head,index);
				      break;

				case 3:
				      printf("\nenter the index  you want to search\n");
				      scanf("%d",&index);
				      search(&head,index);
				      break;

				case 4:
					getchar();
				   printf("\n are you sure to delete anything \n");
				   scanf("%c",&agreement);
				   if(agreement == 'n')
				   	break;
				   printf("\nenter the index\n");
				   scanf("%d",&index);
				   deletebyindex(&head,index);
				   break;

				case 5:
				   print_all(head);
				   break;
				
				case 6:
					print_as_tree(head);
					break;
			}

		}

		getchar();

		printf("\n do you want more y/n \n");
		scanf("%c",&more);
		if(more == 'n')
			choice = false;
	}

	return 0;

}