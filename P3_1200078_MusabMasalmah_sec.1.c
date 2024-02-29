#include <stdio.h>
#include <stdlib.h>

typedef struct course * Course;

struct course{
    char courseName[150];
    int creditHours;
    char courseCode[150];
    char courseDepartment[150];
    char courseTopics[150];
    char status1;
    char status2;
};

Course *courses = NULL;      //Array to implement the first function
Course *courses_2 = NULL;    //Array to implement the secound function
float Num_In_One = 0;        //Number of nodes in first array
float Num_In_Two = 0;        //Number of nodes in secouned array
int size = 0;                //size the the first array
int size_2 = 0;              //size the the secouned array
int collision_in_one = 0;    //Number of collisions in the first function
int collision_in_two = 0;    //Number of collisions in the secouned function

int NOC(char fileName[20]){  //function to get number of lines from file
    int count = 0;
    FILE *f;
    f = fopen(fileName,"r");
    char *token;
    char line[200];
    while(fgets(line,sizeof(line),f)){
       if(strcmp(line,"") == 10){        //cut the courses about the spaces
        count++;
       }
    }
    fclose(f);
    return count+1;
}

int ascii_Value(char courseName[150]){   //Function to get the ascii value of a string
    int asciiVal = 0;
    int i = 0;
    while(courseName[i] != '\0'){
        asciiVal += courseName[i];
        i++;
    }
    return asciiVal;
}

int isPrime(int key){   //Function to check if the number is prime
    if (key <= 1)
        return 0;

    for (int i = 2; i <= key/2; i++)
        if (key % i == 0)
            return 0;

    return 1;
}

int Table_Size(int key){        //Function to get the table size by check the first prime number after the given number
    while(!isPrime(key))
        key++;

    return key;
}

int Hash_Value_For_One(char CourseName[150],int number_of_try){    //get the hash value for from the first function
    int key = ascii_Value(CourseName);
    int HashVal = ((key%size) + number_of_try*(7-(key%7))) % size;

    return HashVal;
}

int Hash_Value_For_Two(char CourseName[150],int number_of_try){     //get the hash value for from the secouned function
    int key = ascii_Value(CourseName);
    int HashVal = ((key % size_2) + number_of_try) % size_2;

    return HashVal;
}

void insert_to_one(Course node,char CourseName[150]){     //function to insert node the the first array
    int number_of_try = 0;
    int index = Hash_Value_For_One(CourseName,0);         //get the index to add the node at this index

    if(courses[index] == NULL){   //if there  null space add the node to it
        courses[index] = node;
        printf("Insert to \"one\" node with code %s to index %d. \n",node->courseCode,index);
        Num_In_One = Num_In_One + 1;
    }
    else{                                          //else get a new index and add the node to it
            number_of_try = 1;
        while(courses[index] != NULL){
            index = Hash_Value_For_One(CourseName,number_of_try);
            number_of_try++;
            collision_in_one++;
        }
        courses[index] = node;
        printf("Insert to \"one\" node with code %s to index %d. \n",node->courseCode,index);

        Num_In_One = Num_In_One + 1 ;
    }

    int flag = 0;
    float numOfNodes = 0;
    while(flag < size){
        if(courses[flag] != NULL)
            numOfNodes++;

        flag++;
    }
    if(numOfNodes/size > 0.7 ){                 //if the load factor more than 0.7 make a rehash

        int newSize = Table_Size(size*2);       //get a new size
        int numOfTry = 0;
        int tempSize = size;
        size = newSize;
        Course *temp = (Course *) malloc(newSize*sizeof(Course));    //new array to put values on it
        for(int i=0 ; i<newSize ; i++)
            temp[i] = NULL;

        for(int j=0 ; j<tempSize ; j++){
            if(courses[j] == NULL)
                continue;
            else{                                  //insert as the above code
                index = Hash_Value_For_One(courses[j]->courseName,numOfTry);
                if(temp[index] == NULL)
                    temp[index] = courses[j];
                else{
                    number_of_try = 1;
                    while(temp[index] != NULL){
                    index = Hash_Value_For_One(CourseName,number_of_try);
                    number_of_try++;
                    collision_in_one++;
                }
                temp[index] = courses[j];
    }
            }
        }

        free(courses);
        courses = temp;
        temp = NULL;


    }
    printf("Collisin in one: %d\n",collision_in_one);
}

void insert_to_two(Course node,char CourseName[150]){       //function to insert node the the secouned array
    int number_of_try = 0;
    int index = Hash_Value_For_Two(CourseName,0);           //get the index to add the node at this index

    if(courses_2[index] == NULL){                           //if there  null space add the node to it
        courses_2[index] = node;
        printf("Insert to \"two\" node with code %s to index %d. \n",node->courseCode,index);
        Num_In_Two++;
    }
    else{                                                      //else get a new index and add the node to it
            number_of_try = 1;
        while(courses_2[index] != NULL){
            index = Hash_Value_For_Two(CourseName,number_of_try);
            number_of_try++;
            collision_in_two++;
        }
        courses_2[index] = node;
        printf("Insert to \"two\" node with code %s to index %d. \n",node->courseCode,index);
        Num_In_Two++;
    }


    int flag = 0;
    float numOfNodes = 0;
    while(flag < size_2){
        if(courses_2[flag] != NULL)
            numOfNodes++;

        flag++;
    }
    if(numOfNodes/size_2 > 0.7 ){                //if the load factor more than 0.7 make a rehash
        int newSize = Table_Size(size_2*2);       //get a new size
        int numOfTry = 0;
        int tempSize = size_2;
        size_2 = newSize;
        Course *temp = (Course *) malloc(newSize*sizeof(Course));    //new array to put values on it
        for(int i=0 ; i<newSize ; i++)
            temp[i] = NULL;

        for(int j=0 ; j<tempSize ; j++){
            if(courses_2[j] == NULL)
                continue;
            else{
                index = Hash_Value_For_Two(courses_2[j]->courseName,numOfTry);
                if(temp[index] == NULL)
                    temp[index] = courses_2[j];
                else{                                     //insert as the above code
                    number_of_try = 1;
                    while(temp[index] != NULL){
                    index = Hash_Value_For_Two(CourseName,number_of_try);

                    number_of_try++;
                    collision_in_two++;
                }
                temp[index] = courses_2[j];
    }
            }
        }

        free(courses_2);
        courses_2 = temp;
        temp = NULL;


    }
    printf("Collisin in two: %d\n",collision_in_two);
}

void creat_hash_for_one(){                           //creat a hash array by set all elements to null for first
    courses =(Course *) malloc(size*sizeof(Course));
    for(int i=0 ; i<size ; i++)
        courses[i] = NULL;
}

void creat_hash_for_two(){                            //creat a hash array by set all elements to null for secouned
    courses_2 =(Course *) malloc(size*sizeof(Course));
    for(int i=0 ; i<size_2 ; i++)
        courses_2[i] = NULL;
}

void readFile(){
    int NumOfCourse = NOC("courses.txt");      //function to read bus file
    FILE *f;
    f = fopen("courses.txt","r");
    char *token;
    char line[200];
    char courseInfo[NumOfCourse][750];
    for(int i=0 ; i<NumOfCourse ; i++)
        strcpy(courseInfo[i],"");

    int i = 0;
    while(fgets(line,sizeof(line),f)){

       if(strcmp(line,"") != 10){  //read the lines to the first space
        strcat(courseInfo[i],line);
       }
       else{
        i++;
       }
    }

    int j=0;
    printf("-The file read:\n");
    while(j < NOC("courses.txt")){     //get the lines line by line
        int i=0;
        token = strtok(courseInfo[j],":#/");  //cut the line to words
        char take[5][150];
        strcpy(take[0],"");

        while(token != NULL){

            strcpy(take[i],token);
            token = strtok(NULL,":#/");
            i++;
            }
           Course node = malloc(sizeof(struct course));

           strcpy(node->courseName,take[0]);
           int courseHoure = atoi(take[1]);
           node->creditHours = courseHoure;
           strcpy(node->courseCode,take[2]);
           strcpy(node->courseDepartment,take[3]);
           strcpy(node->courseTopics,take[4]);
           insert_to_one(node,node->courseName);         //add the node to the first function
           insert_to_two(node,node->courseName);         //add the node to the secouned function

            j++;
    }
    fclose(f);
}

void print_for_one(){                             //print the hash table for the first function
    printf("The first table:\n");
    printf("%-15s %-30s %-40s\n","index","status","value");
    for(int i=0 ; i<size ; i++){
        if(courses[i] == NULL)
            printf("%-15d %-30s %-40s\n",i,"E","NULL");
        else if(courses[i]->status1 == 'D')
            printf("%-15d %-30s %-40s\n",i,"D",courses[i]->courseName);
        else
            printf("%-15d %-30s %-40s\n",i,"O",courses[i]->courseName);
    }
}

void print_for_two(){                             //print the hash table for the secouned function
    printf("\nThe Secound table:\n");
    printf("%-15s %-30s %-40s\n","index","status","value");
    for(int i=0 ; i<size_2 ; i++){
        if(courses_2[i] == NULL)
            printf("%-15d %-30s %-40s\n",i,"E","NULL");
        else if(courses_2[i]->status2 == 'D')
            printf("%-15d %-30s %-40s\n",i,"D",courses_2[i]->courseName);
        else
            printf("%-15d %-30s %-40s\n",i,"O",courses_2[i]->courseName);
    }
}

void print_Size_LF(){                     //print the size and load factor

    printf("\nFor the first table:\n");
    printf("The size -> %d\n",size);
    printf("The load factor -> %.2f\n",Num_In_One/size);
    printf("\nFor the secound table:\n");
    printf("The size -> %d\n",size_2);
    printf("The load factor -> %.2f\n\n",Num_In_Two/size_2);
}

void print_function(){                        //print the function inforamtion

    printf("\nThe first function:\nThe name: Double Hashing.\nThe equation: hi(key) = [h(key) + i*hp(key)] mod tableSize , for i = 0, 1, . . . , tableSize \- 1.\nhp(key) = 7 - key mod 7\n\n");
    printf("The secound function:\nThe name: Linear Probing.\nThe equation: hi(key) = [h(key) + i] mod tableSize , for i = 0, 1, . . . , tableSize \- 1.\n\nWhere h(key)  = key mod 13.\n");
}

void Insert_node_to_both(){     //insert node to both functions
    char courseName[150],courseCode[150],courseDepartment[150],courseTopics[150];
    int creditHours;
    printf("Enter the course name: ");
    getchar();
    gets(courseName);
    printf("Enter the course code: ");             //get the information
    scanf("%s",courseCode);
    printf("Enter the course Department: ");
    getchar();
    gets(courseDepartment);
    printf("Enter the course topics with ',': ");
    getchar();
    gets(courseTopics);
    printf("Enter the course credit Hours: ");
    scanf("%d",&creditHours);
    Course node = malloc(sizeof(struct course));
           strcpy(node->courseName,courseName);
           node->creditHours = creditHours;
           strcpy(node->courseCode,courseCode);
           strcpy(node->courseDepartment,courseDepartment);
           strcpy(node->courseTopics,courseTopics);
           insert_to_one(node,node->courseName);               //add to the first functiom
           insert_to_two(node,node->courseName);               //add to the secouned function

}

void search(){          //function to search about to a node

    printf("Search opration:\n1. Search in the first table.\n2. Search in secound table.\nEnter your choice: ");
    int choice;
    scanf("%d",&choice);
    int index = 0,number_of_try = 0;
    char temp[150];
    char name[150];
    switch(choice){
    case 1:
        printf("Enter the name: ");           //get the name
        getchar();
        gets(name);

        index = Hash_Value_For_One(name,0);       //get the index that expect that the node in it
        if(courses[index] == NULL)                // if the index null then no node in it
             printf("No course with this name.\n");

        else if(strcmp(courses[index]->courseName,name) == 0){     //if there is the node print his name
            printf("%s exisit in index %d \n",name,index);
        }
        else{                             //if there is not but not the same name
                number_of_try = 1;
                index = Hash_Value_For_One(name,number_of_try);     //get the new index
                if(courses[index] == NULL)
                    printf("No course with this name.\n");
            while(courses[index] != NULL){                           //check
                if(strcmp(courses[index]->courseName,name) == 0){
                    printf("%s exisit in index %d \n",name,index);
                    break;
                }
                number_of_try++;
                index = Hash_Value_For_One(name,number_of_try);         //get index to check and get the value
                if(courses[index] == NULL)
                    printf("No course with this name.\n");
            }
        }
        break;

    case 2:
        printf("Enter the name: ");
        getchar();
        gets(name);

        index = Hash_Value_For_Two(name,0);
        if(courses_2[index] == NULL)
             printf("No course with this name1.\n");

        else if(strcmp(courses_2[index]->courseName,name) == 0){            //for the secouned function as the first function
            printf("%s exisit in index %d \n",name,index);
        }
        else{
                number_of_try = 1;
                index = Hash_Value_For_Two(name,number_of_try);
                printf("the index %d\n",index);
                if(courses_2[index] == NULL)
                    printf("No course with this name2.\n");
            while(courses_2[index] != NULL){
                if(strcmp(courses_2[index]->courseName,name) == 0){
                    printf("%s exisit in index %d \n",name,index);
                    break;
                }
                number_of_try++;
                index = Hash_Value_For_Two(name,number_of_try);
                if(courses_2[index] == NULL)
                    printf("No course with this name3.\n");
            }
        }
    break;


    }
}

void delete_rec(){
    char name[150],code[150];
     printf("Enter the name: ");
        getchar();
        gets(name);                     //get the informations
     printf("Enter the code: ");
        gets(code);

        int index = Hash_Value_For_One(name,0);   //get the index
        if(courses[index] == NULL){
             printf("First function: No course with this name.\n");
        }
        else if(strcmp(courses[index]->courseName,name) == 0 && strcmp(courses[index]->courseCode,code) == 0 && courses[index]->status1 != 'D'){ //check if it exist

                courses[index]->status1 = 'D';
                courses[index] = NULL;
                printf("First function: %s in index %d was deleted.\n",name,index);
        }
        else{  //else check another values
                int number_of_try = 1;
                index = Hash_Value_For_One(name,number_of_try);
                if(courses[index] == NULL)                                //if null then no nodes
                    printf("First function: No course with this name.");
            while(courses[index] != NULL ){
                if(strcmp(courses[index]->courseName,name) == 0 && strcmp(courses[index]->courseCode,code) == 0 && courses[index]->status1 != 'D'){ //check
                        courses[index]->status1 = 'D';
                        courses[index] = NULL;
                    printf("First function: %s in index %d was deleted.\n",name,index);
                    break;
                }
                number_of_try++;
                index = Hash_Value_For_One(name,number_of_try);
                if(courses[index] == NULL)                                 //if it null there is no node
                    printf("First function: No course with this name.\n");
            }
        }

        index = Hash_Value_For_Two(name,0);                 //the same of the first function
        if(courses_2[index] == NULL){
             printf("Secound function: No course with this name.\n");
        }
        else if(strcmp(courses_2[index]->courseName,name) == 0 && strcmp(courses_2[index]->courseCode,code) == 0 && courses_2[index]->status2 != 'D'){

                courses_2[index]->status2 = 'D';
                courses_2[index] = NULL;
                printf("Secound function: %s in index %d was deleted.\n",name,index);
        }
        else{
                int number_of_try = 1;
                index = Hash_Value_For_Two(name,number_of_try);
                if(courses_2[index] == NULL)
                    printf("Secound function: No course with this name.\n");
            while(courses_2[index] != NULL){
                if(strcmp(courses_2[index]->courseName,name) == 0 && strcmp(courses_2[index]->courseCode,code) == 0 && courses_2[index]->status2 != 'D'){
                    courses_2[index]->status2 = 'D';
                    courses_2[index] = NULL;
                    printf("Secound function: %s in index %d was deleted.\n",name,index);
                    break;
                }
                number_of_try++;
                index = Hash_Value_For_Two(name,number_of_try);
                if(courses_2[index] == NULL)
                    printf("Secound function: No course with this name.\n");
            }
        }
}

void compare_collision(){    //print the collisins
    printf("\n-The first function has %d collisions.\n",collision_in_one);
    printf("\n-The secound function has %d collisions.\n",collision_in_two);
}

void print_in_file(FILE *f){            //print the information to a file
    f = fopen("saved_courses.txt","w");

    fprintf(f,"%-15s %-30s %-40s\n","index","status","value");
    for(int i=0 ; i<size ; i++){
        if(courses[i] == NULL)
            fprintf(f,"%-15d %-30s %-40s\n",i,"E","NULL");
        else if(courses[i]->status1 == 'D')
            fprintf(f,"%-15d %-30s %-40s\n",i,"D",courses[i]->courseName);
        else
            fprintf(f,"%-15d %-30s %-40s\n",i,"O",courses[i]->courseName);
    }
     fprintf(f,"\n%-15s %-30s %-40s\n","index","status","value");
    for(int i=0 ; i<size_2 ; i++){
        if(courses_2[i] == NULL)
            fprintf(f,"%-15d %-30s %-40s\n",i,"E","NULL");
        else if(courses_2[i]->status2 == 'D')
            fprintf(f,"%-15d %-30s %-40s\n",i,"D",courses_2[i]->courseName);
        else
            fprintf(f,"%-15d %-30s %-40s\n",i,"O",courses_2[i]->courseName);
    }
    fclose(f);
}

int main()
{
    FILE *f;
    int key = NOC("courses.txt");
    size = Table_Size(key * 2);       //get size for the first function
    size_2 = Table_Size(key * 2);     //get size for the secouned function
    creat_hash_for_one();        //creat the first function
    creat_hash_for_two();        //creat the secouned function
    readFile();
    int choice;
    printf("-------------------------------------------------------MENU----------------------------------------------------\n");
    printf("\n1. Print hashed tables (including empty spots). \n2. Print out table size and the load factor. \n3. Print out the used hash functions. \n4. Insert a new record to hash table (insertion will be done on both hash tables). \n5. Search for a specific word (specify which table to search in). \n6. Delete a specific record (from both tables).\n7. Compare between the two methods in terms of number of collisions occurred.\n8. Save hash table back to a file named saved_courses.txt (of the double hashing).\nEnter your choice: ");
    scanf("%d",&choice);
    while(choice > 0 && choice < 9){
    switch(choice){                  //switch statment
        case 1:
            print_for_one();
            print_for_two();
            break;

        case 2:
            print_Size_LF();
            break;
        case 3:
            print_function();
            break;
        case 4:
            Insert_node_to_both();
            break;
        case 5:
            search();
            break;
        case 6:
            delete_rec();
            break;
        case 7:
            compare_collision();
            break;
        case 8:
            print_in_file(f);
            break;

    }
    printf("-------------------------------------------------------MENU-------------------------------------------------------");
    printf("\n\n1. Print hashed tables (including empty spots). \n2. Print out table size and the load factor. \n3. Print out the used hash functions. \n4. Insert a new record to hash table (insertion will be done on both hash tables). \n5. Search for a specific word (specify which table to search in). \n6. Delete a specific record (from both tables).\n7. Compare between the two methods in terms of number of collisions occurred.\n8. Save hash table back to a file named saved_courses.txt (of the double hashing).\nEnter your choice: ");
    scanf("%d",&choice);
    }

    return 0;
}





