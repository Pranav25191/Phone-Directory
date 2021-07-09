/* Author : Balijapelly Pranav
   Roll No: 1903108
   Date   : 23/10/2020
   Description: This code is phone directory
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Numbers                      //defininng structure which has mobile number and comment 
{                                   //both datatypes are characters
    char mobnum[15];                //declaring character array which takes mobile number as input
    char comment[50];               //declaring character array which stores comment related above mobile number
};
struct directory                    //Defining structure with data type character and integer
{
    char Name[50];                  //character array takes name of the input
    int numofnumbers;               //integer taks number of numbers uesr want to give
    struct Numbers *numbers;        //structure pointer point to Number a stucture(which declared above)
};
struct directory_Modify             //Defining structure with data type character and integer
{
    char Name[50];                  //caharacter array takes name of the input
    int numofnumbers;               //integer takes number of numbers uesr want to give
    struct Numbers numbers[15];     //A structure array to Number a stucture(which declared above)
};
/*Function description : This function takes user inputs and stores it in the form of a structures which we defined above.let us describe this function 
with an example.we want give input the person's to enter into directory the the input we take looks like lets say our structure name is phn
            phn.Name          = Jhonny Depp
            phn.numofnumbers  = 2 --> then a structure array of length phn.numofnumbers is created
            ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
           | comment       / mobnum     | comment          / mobnum   |    ==>structure array 
           | mobile number/ 9209283738  | whats app number/ 9209283739|
            ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Input: Name,number of numbers user want to give,comment,number
Output: Returns a structure with all user input data*/
struct directory readfromuser(){  
    struct directory phn;
    printf("Enter name:");
    scanf(" %[^\n]",phn.Name);                                  //Giving name input.
    printf("How many multiple numbers do you want to give:");   
    scanf(" %d",&(phn.numofnumbers));                          //Giving input how may numbers user want to give.
    phn.numbers = (struct Numbers*)calloc(phn.numofnumbers,sizeof(struct Numbers));   //Creating structure:-number array of size above given input.
    for(int i=0;i<phn.numofnumbers;i++)
    {
        printf("Enter the number %d:",i+1);
        scanf(" %s",phn.numbers[i].mobnum);                      //Giving number as input.
        printf("Enter the comment for the above number:");      
        scanf(" %[^\n]",phn.numbers[i].comment);                //Giving comment as input to above number.
    }
    return phn;
}
/*Function Description: This function opens a file with name phn.txt in write mode. Then it writes all details from structure like name,number of numbers 
comment, number in the following format. let us consider above example then the file looks like

                 '''        Jhonny Depp, These are your contact details
                            Jhonny Depp 2
                            Mobile Number   9209283738
                            whats app Number    9209283739    '''

Input  : takes structure directory 
Output : returns nothing
*/
void writetofile(struct directory phn){
    char k[50]=", This are your contact details";
    FILE *fp= fopen("phnone_directory.txt","a");         // opening file 
    fprintf(fp,"%s%s\n",phn.Name,k);        // from here the all below steps are writing into file as mentioned above 
    fprintf(fp,"%s\t",phn.Name);                
    fprintf(fp,"%d\n",phn.numofnumbers);
    for(int i=0;i<phn.numofnumbers;i++)
    {
        fprintf(fp,"%s\t%s\n",phn.numbers[i].comment,phn.numbers[i].mobnum);
    }
    fclose(fp);                              // closing file 
}
/* Functon Description: This functon takes file pointer as input and reads from file. It reads all structure variables in this function. And stores
   it a structure pointer array. while adding contact details what inputs it takes adds into file that same is read from the file in the same manner 
   as it is added.
   Input: takes file pointer
   Output: returns a pointer of type structure directory*/
struct directory* readfromfile(FILE *fp){
    struct directory *p=(struct directory*) calloc(1,sizeof(struct directory));  //intialising structure array dynamically of length 1
    if (fp==NULL) return NULL;                                                   
    fscanf(fp,"%[^\t]%d\n",p->Name,&p->numofnumbers);                             //reading name and how many numbers he gave from file
    p->numbers=(struct Numbers*)calloc(p->numofnumbers,sizeof(struct Numbers));   //intialising structure array of length number of numbers
    for(int i=0;i<p->numofnumbers;i++){
        fscanf(fp,"%[^\t]%s\n",p->numbers[i].comment,p->numbers[i].mobnum);       // reading number and comment asosiated with it
    }
    return p;
}
/*Function Description: this functon clear dynamically allocated memory
  Input: structure directory
  Output: returns nothing */
void clearmemory(struct directory phn){
    free(phn.numbers);
}
/*Function description: This function takes structure directory as input and prints all the details the structure contains.
  Input: structure directory
  Output: returns nothing 
*/
void printstruct(struct directory p){
    printf("Contact Found. Details are:\n");
    printf(" ====================================================================\n");
    printf("| Name      :  %s",p.Name);                                             //prints name
    for(int k=0;k<(54-strlen(p.Name));k++)
            printf(" ");
    printf("|\n");
    printf("|====================================================================|\n");
    printf("| S.NO      |    NUMBER          |   COMMENT                         |\n");
    printf("|--------------------------------------------------------------------|\n");
    for(int i=0;i<p.numofnumbers;i++)
    {
        printf("| Number %d  |   %s",i+1,p.numbers[i].mobnum);                      //prints number
        for(int k=0;k<(17-strlen(p.numbers[i].mobnum));k++)
            printf(" ");
        printf("|");
        printf("   %s",p.numbers[i].comment);                                       //prints comment associated with above number
        for(int k=0;k<(32-strlen(p.numbers[i].comment));k++)
            printf(" ");
        printf("|\n");
    }
    printf(" ====================================================================\n");
}
/*Function Description: This function compares each and every character of given input strings if all characters matches then it reurns 1 else 0.
  Input: 2 strings 
  Output: Integer 1 or 0
*/
int compare_str(char a[],char b[]){
    int index=0;
    while(a[index]!='\0' && b[index]!=0){         //This while runs till index reaches length of string
        if(a[index]!=b[index])                    //comparing each character
            return 0;
        index++;
    }
    if(a[index]=='\0' && b[index]=='\0')         //If both strings are same then if conditins is satisfied and returns 1
        return 1;
    return 0;
}
/*Function Description: This function is used for searching a persons contact details. This functions reads the data from file as structure. if the given 
  input string(which user want to search)  matches with the name of the person in particular structure then structre get printed
  Input: String,File
  Output: Inter either 0 or 1
*/
int search(char temp_str[],FILE *fp){
    struct directory *std=readfromfile(fp);        // Reading the data from file and stores it strucure pointer
    int strcmp=compare_str(temp_str,std->Name);    // comparing input string with the person name in structure
    if (compare_str(temp_str,std->Name)==1)
    {
        printstruct(*std);                        // prints structure if the name is found
        clearmemory(*std);                        // clearmemory function clears memory as mentioned above
        return 1;
    }
    clearmemory(*std);
    free(std);
    return 0;
}
/* Function Description: This function is used to modify the details which are added into the file. This function modifies Name, Number, Comment, 
   removes a number, add a number. This function opens file in read mode and reads all the data as structures directory from file and stores it in array of type structure 
   directory_modify. Then it again opens the same file in write mode so it opens as empty file. Then all the dta from array expext the details 
   which we want to modify are written into the file. After modifing the details then those details are appended to tha same file. 
   Input: No input is taken
   returns: returns nothing
*/
void modify(){
    FILE *fp1=fopen("phnone_directory.txt","r");                         //opening required file in read mode
    char Name_M[50],ss[50],k[50];
    int i=0,M=0,j,struct_count;
    struct directory *trail;                               //intialising struct directory pointer
    struct directory_Modify people[100];                   //intialising arrary of type structure directory_modify
    printf("enter the name you want modify:");
    scanf(" %[^\n]",Name_M);
    while (fscanf(fp1,"%s %[^\n]\n",ss,k)!=EOF)             //This while loop runs till end of the file
    {   
        trail=readfromfile(fp1);                            //The structure pointer which returns from readfrom file is stored trail pointer 
        for(j=0;trail->Name[j]!='\0';j++)                   //As all the data are strings we can cannot assign an array to an array so each character 
            people[i].Name[j]=trail->Name[j];               //is read and stored into people array. so this for loop takes Name and store it in array
        people[i].Name[j]='\0';
        people[i].numofnumbers=trail->numofnumbers;
        for(int q=0;q<(trail->numofnumbers);q++)
        {   int count_c=0,count_m=0;
            for(int k=0;trail->numbers[q].comment[k]!='\0';k++)      //This for loop takes Comment and stores it in array
            {
                count_c++;
                people[i].numbers[q].comment[k]=trail->numbers[q].comment[k];
            }
            people[i].numbers[q].comment[count_c]='\0';
            for(int w=0;trail->numbers[q].mobnum[w]!='\0';w++)       //This for loop takes number and stores it in array
            {
                count_m++;
                people[i].numbers[q].mobnum[w]=trail->numbers[q].mobnum[w];
            }
            people[i].numbers[q].mobnum[count_m]='\0';
        }
        if (compare_str(people[i].Name,Name_M)==1)       //If the input string matches with the name of person in strucutre th m value becomes 1
            M=i+1; 
        i++;
    }
    fclose(fp1);
    if(M==0){                                            //If m value is 0 this implies there is no contcat found from file
        printf("No entries found with name:%s\nPlease make sure the name you entered is correct(check capital letters...etc)\n",Name_M);
        return;
    }
    struct_count=i;
    FILE *fp2=fopen("phnone_directory.txt","w");       // opening file in write mode
    char type[50]=", This are your contact details";
    for(i=0;i<struct_count;i++)                        //From here all data from array is written to file expect the details which we want to modify 
    {   if (i+1==M)                                    //are added into the file
            continue;                         
        else
        {
            fprintf(fp2,"%s%s\n",people[i].Name,type);
            fprintf(fp2,"%s\t",people[i].Name);
            fprintf(fp2,"%d\n",people[i].numofnumbers);
            for(int j=0;j<people[i].numofnumbers;j++)
                fprintf(fp2,"%s\t%s\n",people[i].numbers[j].comment,people[i].numbers[j].mobnum);
        }
    }
    fclose(fp2);
    char choice,check;
    printf("what changes are u willing to make.\n==>For modifing Name choose 'N'\n==>For modifing Comment choose 'C'\n==>For modifing Mobile Number..etc choose 'M'\n==>For removing a number choose 'R'\n==>For adding extra number choose 'A'\n==>And enter 'Q' for Quit\n");
    printf("Enter your choice here:");
    scanf(" %c",&choice);
    if(choice=='M' || choice=='m')         //if input for modifing is M then number is modified from here
    {   int value_number;
        printf("Enter which number you want to modify(Ex: 1st,2nd,3rd......):");
        scanf(" %d",&value_number);
        if(value_number>people[M-1].numofnumbers)       //If user want to modify the number which doesn't exist then it prints following and returns from this function 
        {
            printf("you entered the number of mobile number to modify which does not exist.\nPlease enter a valid number");
            return;
        }
        printf("Enter the new number:");
        scanf(" %s",people[M-1].numbers[value_number-1].mobnum);        //Asks to enter new mobile number 
    }
    if(choice=='C'||choice=='c')          //if input for modifing is C then comment is modified from here
    {   
        int value_number;
        printf("Enter which number you want to modify(Ex: 1st,2nd,3rd......):");
        scanf(" %d",&value_number);
        if(value_number>people[M-1].numofnumbers)       //If user want to modify the comment which doesn't exist then it prints following and returns from this function 
        {
            printf("you entered the number of comment to modify which does not exist.\nPlease enter a valid number");
            return;
        }
        printf("Enter the comment:");
        scanf(" %[^\n]",people[M-1].numbers[value_number-1].comment);
    }
    if(choice=='N'||choice=='n')         //if input for modifing is N then Name is modified from here
    { 
        printf("Enter the new Name:");
        scanf(" %[^\n]",people[M-1].Name);
    }
    if(choice=='A'||choice=='a')         //if input for modifing is A then a number and a comment are added to existinf details
    {
        people[M-1].numofnumbers++;
        printf("Enter the new number :");
        scanf(" %s",people[M-1].numbers[people[M-1].numofnumbers-1].mobnum);
        printf("Enter the comment:");
        scanf(" %[^\n]",people[M-1].numbers[people[M-1].numofnumbers-1].comment);
    }
    if(choice=='R'||choice=='r')        //if input for modifing is R then number is removedfrom here
    {
        int value_number=0;
        printf("which number you want to remove(Ex:1st,2nd,3rd......):");
        scanf(" %d",&value_number);
        if(value_number>people[M-1].numofnumbers) 
        {
            printf("The number you entered to remove does not exist in %s contact.\nPlease enter a valid number",people[M-1].Name);
            return;
        }
        FILE *fp3=fopen("phnone_directory.txt","a");        //Since all modifications are done file is opened in append mode and all
        fprintf(fp3,"%s%s\n",people[M-1].Name,type);        //modified things are added to file
        fprintf(fp3,"%s\t",people[M-1].Name);
        fprintf(fp3,"%d\n",(people[M-1].numofnumbers-1));
        for(int j=0;j<people[M-1].numofnumbers;j++)
        {   
            if(j==value_number-1) continue;
            else 
                fprintf(fp3,"%s\t%s\n",people[M-1].numbers[j].comment,people[M-1].numbers[j].mobnum);
        }
        fclose(fp3);
        printf("Changes were made successfully!!\n");
        return;
    }
    printf("Changes were made successfully!!\n");
    FILE *fp3=fopen("phnone_directory.txt","a");            //Since all modifications are done file is opened in append mode and all
    fprintf(fp3,"%s%s\n",people[M-1].Name,type);            //modified things are added to file
    fprintf(fp3,"%s\t",people[M-1].Name);
    fprintf(fp3,"%d\n",people[M-1].numofnumbers);
    for(int j=0;j<people[M-1].numofnumbers;j++)
        fprintf(fp3,"%s\t%s\n",people[M-1].numbers[j].comment,people[M-1].numbers[j].mobnum);
    fclose(fp3);
}
int main(){
    int i=0;
    printf("          ===================================================\n         |      ");
    printf("WELCOME TO PRANAV's PHONE DIRECTORY          |\n          ===================================================\n");
    char c,c_1,ss[50],k[200];
    while(1==1)
    {
        char c;
        printf("Enter a command(s-for Search, A-Add, M-Modify,Q-Quit):");
        scanf("%c",&c);
        if(c=='A'||c=='a'){                 // when given input is A the user inputs are added to file from here 
            struct directory phn = readfromuser();
            writetofile(phn);
            clearmemory(phn);
            printf("Contact added sucessfully!\n");
        }
        if(c=='S'||c=='s') 
        {   int q=0;
            char temp_str[50];
            printf("Enter the Name u want to search for:");
            scanf(" %[^\n]",temp_str);
            FILE *fp=fopen("phnone_directory.txt","r");
            if (fp==NULL)
            {
                printf("The file is not found"); 
                return 0;
            }
            while (fscanf(fp,"%s %[^\n]\n",ss,k)!=EOF)
            {     
                if (search(temp_str,fp)==1)
                    q=1; 
            }
            if(q==0) 
                printf("No entries found with name:%s\nPlease make sure the name you entered is correct(check capital letters...etc)\n",temp_str);
            fclose(fp);
        }
        if(c=='M'||c=='m') 
            modify();
        if(c=='Q'||c=='q') 
            return 0;
        scanf("%c",&c);
    }
}