/*
Practice problem


Use dynamic array or stack?

Dynamic arrays have ability to access any index directly,
however, this is not needed with stack.

Dynamic arrays must be resized which can be slow (as old
elements are copied to the new array)

While linked lists allocate memory for each individual element,
not the entire list.  

However, the dynamic array usually is faster than the mem allocation
of the linked list.

However, the linked list implementation is more simple.



Stack needs:
	Push() -- add to front
	Pop()  -- remove head
	init()
	
Linked_List:
	private add_first //adds first element to the list
	public push
	
*/

#include <stdio.h>
#include <stdlib.h>


typedef enum bool{
	false = 0,
	true = 1
} bool;

typedef struct Element{
	struct Element* next;
	void* data;

} Element;

bool createStack(Element** stack){
	*stack = NULL; //set stack pointer to null
	return true;
}

/*
similar to an add to front method
return 1 if failure to add, 0 if all works.

Paramaters:
stack: pointer to head of stack
data:  The data to be pushed onto the end of the stack
*/
bool push(Element** stack, void* in_data){

	Element* ele_to_add = malloc(sizeof(Element));
  if(!ele_to_add) return false;
	
	ele_to_add->data = in_data;
	ele_to_add->next = *stack;
	*stack = ele_to_add;
	return true;

}

/*
Decided to take a double pointer for the data
in order to give the user the top of the stack
instead of returning it.  This way an error code
can be returned

must be a double pointer because we will pass it
a pointer to fill with the popped data
Will return null if list is empty
*/
bool pop(Element **stack, void **data){
	Element* elem;
	if( !(elem = *stack)) 
		return false; //if the stack is empty, return false
	
	*data = elem->data;
	*stack = elem->next;
	free( elem );
	return true;
}

/*
callback function, user can write
their own print function that will be
used when print_list is called
*/
void print_int(void *to_print){ printf(" %d", *(int*)to_print); }
void print_char(void *to_print){ printf(" %c", *(char*)to_print); }

/*
takes a function pointer to the users print function
*/
void print_list(Element **stack, void fptr_print(void *)){
	Element* iter = *stack;
	while(iter != NULL){
	  (*fptr_print)(iter->data);	
		iter = iter->next;
	}
}

/*
deletes the entire stack.
Could have also poped off every element
*/
bool delete_list(Element **stack){
	//error check for empty list
	if (!(*stack)) return false;
	Element* iter = *stack;
	Element* tmp_next = iter;
	while(*stack){
		printf("\n");
		print_list(stack, &print_char);
		tmp_next = (*stack)->next;
		free(*stack);
		*stack = tmp_next;
	}
	
	return true;
}

int main(){
	Element* my_stack;	

	//int a = 6;
	//int b = 8;	
	char a = 'a';
	char b = 'b';
	char c = 'c';
	void* popped;


	push(&my_stack, &a);
	push(&my_stack, &b);
	push(&my_stack, &c);
	
  print_list(&my_stack, print_char);
	
	delete_list(&my_stack);
	printf("\nafter deleted list(should be empty):\n");
  print_list(&my_stack, print_char);

  //put the list back
	push(&my_stack, &a);
	push(&my_stack, &b);
	push(&my_stack, &c);
	
	pop(&my_stack, &popped);
	pop(&my_stack, &popped);
	pop(&my_stack, &popped);
	bool result = pop(&my_stack, &popped);
	printf("popped char (should be a): %c \n", *(char*)popped);
	printf("result(should be 0): %d", result );
	
	
}

