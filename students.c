#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"students.h"

void printMenu(){
    printf("\t  MENU\n");
    printf("_________________________________\n");
    printf("1. Add new student.\n");
    printf("2. Search by ID.\n");
    printf("3. Delete by ID.\n");
    printf("4. Change details of a student.\n");
    printf("5. Print details of a student.\n");
    printf("6. Print all students.\n");
    printf("Choose a number between 1 and 6! Or 0 to save and exit! \n");
}

//Εκτυπώνει το id και το όνομα ενός φοιτητή st
void printStudent(student st){
  printf("Id of student is:%lu\n",st.id);
  printf("Name of student is:%s\n",st.name);
}

//Εκτυπώνει το id και το όνομα όλων των φοιτητών σε μία λίστα l
void printStudents(list l) {
    if (l->head == NULL) {
        printf("List is empty\n");
    } else {
        node current = l->head;
        while (current != NULL) {
            printf("ID: %lu,\t Name: %s\n", current->data.id, current->data.name);
            current = current->next;
        }
    }
}

//ανάκτηση λίστας φοιτητών από αρχείο
Result load(char* filename, list* l) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return F_READ_ERR;
    }

    while (!feof(file)) {
        student st;
        if (fread(&st, sizeof(student), 1, file) != 1) {
            if (feof(file)) {
                return NO_ERR;
            } else {
                fclose(file);
                return F_READ_ERR;
            }
        }
        isError(addStudent(st, *l));
    }

    fclose(file);
    return NO_ERR;
}

//αποθήκευση λίστας φοιτητών σε αρχείο
Result save(char* filename, list l) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return F_WRITE_ERR;
    }

    node current = l->head;
    while (current != NULL) {
        if (fwrite(&(current->data), sizeof(student), 1, file) != 1) {
            fclose(file);
            return F_WRITE_ERR;
        }
        current = current->next;
    }

    fclose(file);
    return NO_ERR;
}

//προσθήκη νέου student στο τέλος της λίστας
Result addStudent(student st, list l) {
    node n = malloc(sizeof(struct nodeR));
    if (n == NULL) {
        return MALLOC_ERR;
    }
    n->data.id = st.id;
    strcpy(n->data.name, st.name);
    n->previous = NULL;
    n->next = NULL;                     

    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    } else {
        n->previous = l->tail;
        l->tail->next = n;
        l->tail = n;
    }
return NO_ERR;
}

//αναζήτηση του student από τη λίστα με βάση το id. Aνάθεση της δ/νσης του κόμβου που περιέχει το student με το σωστό id στο np. To np γίνεται NULL αν δε βρεθεί.
Result findStudentNode(unsigned long  ID, list l, node* np){
  node current = l->head;
  while(current != NULL){
    if(current->data.id == ID){
      *np = current;
      return NO_ERR;
    }
    current = current->next;
  }
  np = NULL;
return UNKNOWN_ERR;
}

//αναζήτηση του student από τη λίστα με βάση το id. Aνάθεση της δ/νσης του student με το σωστό id στο st. Το st.id γίνεται -1 αν δε βρεθεί
Result findStudent(unsigned long ID, list l, student *st){
  node current = l->head;
  while(current != NULL){
    if(current->data.id == ID){
      *st = current->data;
      return NO_ERR;
    }
    current = current->next;
  }
  st->id = -1;
return SYNTAX_ERR;
}

//διαγραφή από τη λίστα με βάση το id
Result deleteStudentById(unsigned long ID, list l) {
    node np;

    if(findStudentNode(ID, l, &np)){
        return SYNTAX_ERR;
    }
    //Αν έχουμε μόνο ένα κόμβο στην λίστα
    if (np == l->head && np == l->tail) {
        l->head = NULL;
        l->tail = NULL;
    //Αν ο κόμβος είναι στν αρχή της λίστας
    } else if (np == l->head) {
        // Node is the head of the list
        l->head = np->next;
        l->head->previous = NULL;
    //Αν ο κόμβος είναι στο τελος της λιστας
    } else if (np == l->tail) {
        l->tail = np->previous;
        l->tail->next = NULL;
    //Αν ο κόμβος είναι ενδιάμεσα απο άλλους κόμβους
    } else {
        np->previous->next = np->next;
        np->next->previous = np->previous;
    }
    printf("Student Deleted!\n");
    free(np);
    return NO_ERR;
}

//ανανέωση των στοιχείων του student στη λίστα l με βάση το st.id
Result updateStudent(student st, list l){
  char a='a';
  unsigned long id;
  char name[MAXSTRING];
  node current = l->head;
  while(current != NULL){
    if(current->data.id == st.id){
      printf("Do you want to change student's id?\n(Press y/n.)\n");
      scanf(" %c",&a);
      while(a !='y' && a != 'Y' && a!='n'&& a!='N'){
        printf("Wrong input! Try again:");
            while(getchar()!='\n');
              scanf("%c", &a);
      }
      if(a == 'y' || a == 'Y'){
        printf("Give the new id of the student:\n");
        scanf("%lu",&id);
        current->data.id = id;
      }
      printf("Do you want to change student's name?\n(Press y/n.)\n");
      scanf(" %c",&a);
      while(a!='y' && a!= 'Y' && a!='n' && a!='N'){
        printf("Wrong input! Try again:");
            while(getchar()!='\n');
              scanf("%c",&a);
      }
      if(a == 'y' || a == 'Y'){
        printf("Give the new name of the student:\n");
        scanf("%s",name);
        strcpy(current->data.name, name);
      }

    return NO_ERR;
    }
    current = current->next;

  }
return SYNTAX_ERR;
}

//Επιστρέφει TRUE αν το σφάλμα δεν είναι NO_ERR
int isError(Result r){
  switch (r){
    case NO_ERR:
      return FALSE;

    case MALLOC_ERR:
      printf("Allocation Error!\n");
      return TRUE;

    case F_READ_ERR:
      printf("Unable to read from file!\n");
      return TRUE;
    
    case F_WRITE_ERR:
      printf("Unable to write to file!\n");
      return TRUE;
    
    case NON_INIT_LIST:
      printf("Didn't found!\n");
      return TRUE;
    
    case SYNTAX_ERR:
      printf("Typographical Error!\n");
      return TRUE;

    case UNKNOWN_ERR:
      printf("Unknown Error!\n");
      return TRUE;

    default:
      break;
  }
}

//Παράγει ένα ψευδοτυχαίο και με μεγάλη πιθανότητα μοναδικό id
unsigned long generateId(){
  return rand();
}