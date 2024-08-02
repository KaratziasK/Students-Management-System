#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"students.h"

Result main(int argc,char **argv){      //MAIN
  int input=10;
  unsigned long id=0,res;
  student st;
  node n;
  short i=0;
  srand(time(NULL));


  char name[MAXSTRING];


  list l = malloc(sizeof(struct listR)); //Δημιουργεί Διπλά συνδεδεμένη λίστα
    if(l == NULL){
      return isError(MALLOC_ERR);
    }
  l->head = NULL;
  l->tail = NULL;

    //function load
    load(argv[1],&l);

  while(input!=0){
    printMenu();
    scanf("%d",&input);
    while(input>6 || input<0){
      while(getchar()!='\n');
        printf("Wrong input! Try again:");
        scanf("%d",&input);
    }
switch(input){

  case 1:
    printf("Give the name of the student: ");
    scanf("%s",st.name);
    st.id = generateId();
    printf("Student's given id is: %lu\n",st.id);
    isError(addStudent(st,l));
    break;

  case 2:
    printf("Give the id of student that you want to search:\n");
    scanf("%lu",&id);
    isError(findStudent(id,l,&st));
    break;

  case 3:
    printf("Give the id of student that you want to delete:\n");
    scanf("%lu",&id);
    isError(deleteStudentById(id,l));
    break;

  case 4:
    printf("Give the id of student that you want to update:\n");
    scanf("%lu",&st.id);
    isError(updateStudent(st,l));
    break;

  case 5:
    printf("Give the id of student that you want to print:\n");
    scanf("%lu",&id);
    if(isError(findStudent(id,l,&st)) != NON_INIT_LIST){
      printStudent(st);
    }
    break;

  case 6:
      printStudents(l);
      break;
      
    }
  }
    //function save
    save(argv[1],l);
	node currentNode = l->head; //Καταστρέφει την λίστα
	while(currentNode != NULL){
		node tmp = currentNode->next;
		free(currentNode);
		currentNode = tmp;
    }
	free(l);

return NO_ERR;
}