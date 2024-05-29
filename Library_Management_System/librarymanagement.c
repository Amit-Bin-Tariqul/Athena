#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>

typedef struct Book_info  //book profile 
{
    char id[15];
    char name[100];
    char author[100];
    char genre[100];
    int quantity;
    int shelf;

} book;

typedef struct _signin  //user profile
{
    char username[100];
    char pass[100];
    char phone[20];
    char address[100];
    char id[100];

} signin;
book b[1000] = {0};
signin sign[500];

typedef struct _Book_Count9 //keeping count of books and users from file system and in the structure
{
    int count;      // Count of books(different types) in library
    int users;      // Count of registered users of the system
} number;

number capacity;

enum Color
{
    black,
    gray = 8,
    blue,
    green,
    cyan,
    red,
    purple,
    light_yellow,
    white
};

int password(const char *name_input, const char *password_input);
int registration();
void heading();
void welcome();
int search();
void viewBook();
void mainMenu();
void edit();
void save();
int load(char *filepath);
void delete ();
int loadinfo(char *filepath, int n);
int saveinfo(char *filepath, int n);
void saveuserinfo(char *filepath);
void borrow();
void returnbook();
void help();
int loaduserinfo();
void setCord(int x, int y);
void setColor(int color);
void print_center(int row, char *s);
void setCord(int x, int y);
int printMenu();
int printSignin();
int printSearchMenu();
int printDeleteMenu();
int printSaveMenu();
int printEditMenu();
int printLoadMenu();
int printBorrowMenu();
int printReturnMenu();
int check(char *in);
int printCheckMenu();
void encrypt(char *FILENAME, char *key);

int main()
{
    system("COLOR 11");
    welcome();
    // heading();

    int choice, amount = 0;
    capacity.users = 1;


    char name_input[100], password_input[100];

    system("cls");


    choice = printSignin();//UI used for taking choice input

    choice++;

    if (choice == 1) //Log in system
    {
        int attempt=4;
        while(attempt--)
        {

            system("cls");
            setColor(red);
            printf("\n\n\t\t You have %d attempt(s) remaining!!\n\n",attempt);
            printf("\n\t\t\t ***************************************");
            setColor(light_yellow);
            printf("\n\t\t\t Enter Username :");
            scanf(" %[^\n]", name_input);
            printf("\n\t\t\t Enter Password :");
            int passCount = 0;
            while(1) {
                
                char ch = _getch();
                if (ch == 13){
                    password_input[passCount] = '\0';
                    break;
                }
                   
                else if(ch != 8){
                    setCursorPosition(42+passCount,8);
                    password_input[passCount] = ch;
                    passCount++;
                    printf("*");
                }
                else if(ch == 8){
                    passCount--;
                    setCursorPosition(42+passCount,8);
                    printf(" ");
                    
                }
               
            }
            //scanf(" %[^\n]", password_input);
            printf("\n\t\t\t ***************************************");

            int r;
            r = password(name_input, password_input);
            if (r!=-1 && r<1000) //if username and password matches
            {
                printf("\n\t\t\t< ...... Log in Success! ...... >\n");
                printf("\n\t\t\t  ~~~~~~ Welcome Mr. %s ~~~~~~ ", sign[r].username);
                printf("\n\n\t\t\t\t\t  < Before starting read the guidelines >");
                help();
                getchar();
                system("cls");
                mainMenu();
                break;
            }
            else
            {
                if(attempt==1)
                {
                    int i, len;
                    system("cls");
                    if(r>=1000) //When password is wrong then it resets
                    {
                        system("cls");
                        printf("\n\t\tUsername found but Password incorrect.Please input correct password or Register to gain access\n\n");
                        printf("\n\t\t\tWould you like to reset your Password ?(Enter Yes if so)\n\n");
                        char ans[4];
                        scanf("%s",ans);

                        if(strcmp(ans,"Yes")==0)
                        {
                            system("cls");
                            if(strcmp(name_input,sign[0].username)!=0)
                            {
                                printf("\n\t\t\tPlease enter your Username: ");
                                char username[100];
                                scanf(" %[^\n]",username);

                                len = loaduserinfo();
                                // printf("%d\n",len);
                                capacity.users = len;
                                for (i = 0; i < len; i++)
                                {
                                    int a;
                                    a = strcmp(username, sign[i].username);
                                    if (a == 0)
                                    {
                                        break;
                                    }
                                }
                                if(i==len) //when we dont have record of the users
                                {
                                    printf("\n\t\t\tSorry!Username does not exist.Please Register\n");
                                    int w;
                                    w = registration();
                                    if (w == 1)
                                    {
                                        system("cls");
                                        help();
                                        system("cls");
                                        mainMenu();
                                        break;
                                    }

                                    else exit(0);
                                }

                                else //verification system
                                {
                                    system("cls");
                                    printf("\n\t\t\tCongratulations!!Successful request for changing Password received!!\n\n");
                                    printf("\n\t\t\tYou will receive an authentication code within some time.\n\n");
                                    srand(time(NULL));
                                    int authentication=rand()%1000000;
                                    sleep(5);
                                    printf("\n\t\t\tYour verification code is %06d\n\n",authentication);
                                    fflush(stdin);
                                    int verify;
                                    printf("\n\t\t\tPlease enter your verification code: ");
                                    scanf(" %d",&verify);
                                    if(verify==authentication)
                                    {
                                        system("cls");
                                        printf("\n\t\t\tCongratulations!!You have successfully entered verification code.\n\n");
                                        printf("\n\t\t\tNow you can set new Password\n\n");
                                        char newpassword[100];
                                        scanf(" %s",newpassword);
                                        strcpy(sign[i].pass,newpassword);
                                        capacity.users--;
                                        saveuserinfo("user.bin");
                                        printf("\n\t\t\tPassword change Successful!!\n");
                                        system("cls");
                                        mainMenu();
                                        break;
                                    }
                                    else
                                    {
                                        system("cls");

                                        printf("\n\t\t\tWrong code!!Terminating!!!\n");
                                        exit(0);
                                    }
                                }
                            }
                            else
                            {
                                system("cls");
                                setColor(cyan);
                                printf("\n\n\t\t\tWhen is the Minotaur's owner as high as an elephant's eye?\n\n");
                                char answer[20];
                                scanf(" %s",answer);
                                if(strcmp(answer,"A maze")==0 || strcmp(answer,"Corn")==0)
                                    printf("\n\t\t\tCongratulations.Answer is correct.\n");
                                else exit(0);
                                system("cls");
                                setColor(blue);
                                printf("\n\t\tI have billions of eyes,yet I live in Darkness\n\n");
                                printf("\n\t\tI have millions of ears,yet only four Lobes\n\n");
                                printf("\n\t\tI have no muscle, yet I rule two Hemispheres.\n\n");
                                printf("\n\t\t\t\t\tWhat am I?\n\n");
                                scanf(" %s",answer);
                                if(strcmp(answer,"Brain")==0)
                                    printf("\n\t\t\tCongratulations!! Your answer is correct!!");
                                else exit(0);
                                system("cls");
                                setColor(green);
                                printf("\n\nCongratulations!!You have successfully answered the questions.You can reset your Password.\n");
                                char newpassword[100];
                                setColor(cyan);
                                scanf(" %s",newpassword);
                                strcpy(sign[0].pass,newpassword);
                                capacity.users--;
                                saveuserinfo("user.bin");
                                setColor(green);
                                printf("\n\t\t\tPassword change Successful!!\n");
                                system("cls");
                                mainMenu();
                                break;
                            }
                        }
                        else //when the use doesn't exist it takes to registration menu
                        {
                            system("cls");
                            setColor(red);
                            printf("\n\n\t\t\tUser does not exist.Please Register\n\n");
                            int w;
                            w = registration();
                            if (w == 1)
                            {
                                system("cls");
                                help();
                                system("cls");
                                mainMenu();
                                break;
                            }
                            else exit(0);
                        }

                    }
                    else
                    {
                        system("cls");
                            setColor(red);
                            printf("\n\n\t\t\tUser does not exist.Please Register\n\n");
                            int w;
                            w = registration();
                            if (w == 1)
                            {
                                system("cls");
                                help();
                                system("cls");
                                mainMenu();
                                break;
                            }
                            else exit(0);
                    }
                }
                setColor(red);
                printf("\n\t\t\tInvalid Information.Please retry!!!\n");
                getch();
            }

        }
    }

    else if (choice == 2)
    {
        system("cls");
        int r;
        r = registration();
        if (r == 1)
        {
            system("cls");
            help();
            system("cls");
            mainMenu();
        }
    }
}
//this function compares password present in the file 
int password(const char *name_input, const char *password_input) 
{
    int i, len;
    len = loaduserinfo();
    // printf("%d\n",len);
    capacity.users = len;

    for (i = 0; i < len; i++)
    {
        int a;
        a = strcmp(name_input, sign[i].username);
        if (a == 0)
        {
            int b;
            b = strcmp(password_input, sign[i].pass);
            if (b == 0)
            {
                return i;
            }
            else return 1000+i;
        }
    }
    return -1;
}
//this function is used in registration purpose
int registration()
{

    int f;
    f = loaduserinfo();

    f = capacity.users;
    if (f > 500)
    {
        f = 1;
        capacity.users = 1;
        saveuserinfo("user.bin");
    }
char a[100];
int g;
    // f=f+1;
    g=1;
    while(g)
    {
    printf("\n\t\t\t Enter Username(use unique username) :");
    scanf(" %[^\n]", &a);
    int gg,count=0;
    for(gg=0;gg<=f;gg++)//checking previous usernames
    {
       int jj;
        jj=strcmp(sign[gg].username,a);
        if(jj==0)count++;
    }
    if(count==0)
    {
        strcpy(sign[f].username,a);
        g=0;

    }
    else 
    {
        printf("\n\t\t Try new username....");
        g=1;
        printf("\n\t\t Enter any key to continue.....");
        getch();
        system("cls");
    }
    }
    printf("\n\t\t\t Enter Password         :");
    scanf(" %[^\n]", sign[f].pass);

    printf("\n\t\t\t Enter your ID          :");
    scanf(" %[^\n]", sign[f].id);

    printf("\n\t\t\t Enter your address     :");
    scanf(" %[^\n]", sign[f].address);

    printf("\n\t\t\tEnter your Phone number :");
    scanf(" %[^\n]", sign[f].phone);

    printf("\n\n\t\t\t< Registration successful to IUTLIB >\n");
    printf("\n\n\t\t\t ~~~~~~~~~~~ Welcome %s ~~~~~~~~~~~     ", sign[f].username);
    // f++;
    capacity.users++;
    saveuserinfo("user.bin");
    return 1;
}
//welcome menu
void welcome()
{
    system("cls");

    setColor(cyan);
    printf("\t\t\t\t$$\\      $$\\ $$$$$$$$\\ $$\\       $$$$$$\\   $$$$$$\\  $$\\      $$\\ $$$$$$$$\\ \n"
           "\t\t\t\t$$ | $\\  $$ |$$  _____|$$ |     $$  __$$\\ $$  __$$\\ $$$\\    $$$ |$$  _____|\n"
           "\t\t\t\t$$ |$$$\\ $$ |$$ |      $$ |     $$ /  \\__|$$ /  $$ |$$$$\\  $$$$ |$$ |      \n"
           "\t\t\t\t$$ $$ $$\\$$ |$$$$$\\    $$ |     $$ |      $$ |  $$ |$$\\$$\\$$ $$ |$$$$$\\    \n"
           "\t\t\t\t$$$$  _$$$$ |$$  __|   $$ |     $$ |      $$ |  $$ |$$ \\$$$  $$ |$$  __|   \n"
           "\t\t\t\t$$$  / \\$$$ |$$ |      $$ |     $$ |  $$\\ $$ |  $$ |$$ |\\$  /$$ |$$ |      \n"
           "\t\t\t\t$$  /   \\$$ |$$$$$$$$\\ $$$$$$$$\\\\$$$$$$  | $$$$$$  |$$ | \\_/ $$ |$$$$$$$$\\ \n"
           "\t\t\t\t\\__/     \\__|\\________|\\________|\\______/  \\______/ \\__|     \\__|\\________|\n"
           "                                                                           ");
    printf("\n\n\t\t\t\t\t\t\t\t");
    printf("$$$$$$$$\\  $$$$$$\\  \n"
           "\t\t\t\t\t\t\t\t\\__$$  __|$$  __$$\\ \n"
           "\t\t\t\t\t\t\t\t  $$ |   $$ /  $$ |\n"
           "\t\t\t\t\t\t\t\t  $$ |   $$ |  $$ |\n"
           "\t\t\t\t\t\t\t\t  $$ |   $$ |  $$ |\n"
           " \t\t\t\t\t\t\t\t  $$ |   $$ |  $$ |\n"
           " \t\t\t\t\t\t\t\t  $$ |    $$$$$$  |\n"
           "\t\t\t\t\t\t\t\t  \\__|    \\______/ \n"
           "                    ");

    printf("\n\t\t\t\t\t\t\t\t\t");
    printf(" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\$$$$$$\\ $$$$$$$$\\ $$\\   $$\\ $$$$$$$$\\ $$\\   $$\\  $$$$$$\\  \n"
           "\t\t\t\t\t\t\t\t\t\t\t\t$$  __$$\\\\__$$  __|$$ |  $$ |$$  _____|$$$\\  $$ |$$  __$$\\ \n"
           "\t\t\t\t\t\t\t\t\t\t\t\t$$ /  $$ |  $$ |   $$ |  $$ |$$ |      $$$$\\ $$ |$$ /  $$ |\n"
           "\t\t\t\t\t\t\t\t\t\t\t\t$$$$$$$$ |  $$ |   $$$$$$$$ |$$$$$\\    $$ $$\\$$ |$$$$$$$$ |\n"
           "\t\t\t\t\t\t\t\t\t\t\t\t$$  __$$ |  $$ |   $$  __$$ |$$  __|   $$ \\$$$$ |$$  __$$ |\n"
           "\t\t\t\t\t\t\t\t\t\t\t\t$$ |  $$ |  $$ |   $$ |  $$ |$$ |      $$ |\\$$$ |$$ |  $$ |\n"
           "\t\t\t\t\t\t\t\t\t\t\t\t$$ |  $$ |  $$ |   $$ |  $$ |$$$$$$$$\\ $$ | \\$$ |$$ |  $$ |\n"
           "\t\t\t\t\t\t\t\t\t\t\t\t\\__|  \\__|  \\__|   \\__|  \\__|\\________|\\__|  \\__|\\__|  \\__|\n"
           "                                                           \n"
          );
    setColor(red);
    printf("\n\n\n\t\t\t Enter any key to continue.....\n");
    getch();
}
//heading
void heading()
{
    // system("cls");

    printf("\n\n\t\t\t*********LIBRARY MANAGEMENT*********\n");

    
}
//this function manages the Main Menu
void mainMenu()
{
    int n = 1;
    int amount;
    amount = capacity.count;
    //
    int count = 0;
    int relen = 0;
    capacity.count = 0;
    while (n)
    {

        n = printMenu();
        n = n + 1;
        if (n == 1)
        {
            system("cls");
            setColor(light_yellow);
            printf("\n\t\t\t Enter Number of books :");
            scanf("%d", &relen);

            int j, s;
            s = 1;
            amount = capacity.count;
            fflush(stdin);
            setColor(cyan);
            printf("\n\t\t\t*********Add Book************");//Add book menu
            int c = 0;

            for (j = capacity.count; j < (amount + relen); j++)
            {
                s = 1;
                int l;
                while (s)//It compares ISBN uniquely
                {
                    char in[100];
                    system("cls");
                    printf("\n\t\t\t Enter ISBN :");
                    fgets(in, 15, stdin);
                    int g = strlen(in);
                    int f;
                    f = check(in);//It compares with other ISBN ids
                    if (g == 14 && f == 0)
                    {
                        strcpy(b[j].id, in);
                        printf("\n\t\t\t Enter Book Name :");

                        fgets(b[j].name, 100, stdin);

                        printf("\n\t\t\t Enter Author Name :");
                        fgets(b[j].author, 100, stdin);
                        printf("\n\t\t\t Enter Genre :");
                        fgets(b[j].genre, 100, stdin);
                        printf("\n\t\t\t Enter Number of quantity :");
                        scanf("%d", &b[j].quantity);
                        printf("\n\t\t\t Enter Shelf Number :");
                        scanf("%d", &b[j].shelf);
                        printf("\n\t\t\t Book adding success!!!");
                        printf("\n\t\t\t Enter any key to continue....");
                        capacity.count++;
                        system("cls");
                        s = 0;
                    }
                    else if (f == 0 && g != 14) //when ISBN isn't upto length and if its not unique
                    {
                        printf("\n\t\t\tYou entered wrong ID");
                    }
                    else if (f == 1&&g==14)//when ISBN ID exists
                    {
                        system("cls");
                        printf("\n\t\t\t< Your entered ISBN exists already >");
                        c = printCheckMenu();
                        c = c + 1;
                        if (c == 1)
                        {
                            system("cls");
                            int z;
                            for (z = 0; z < capacity.count + relen; z++)
                            {
                                if (strstr(b[z].id, in) != NULL)
                                {
                                    b[z].quantity = b[z].quantity + 1;
                                    s = 0;
                                    printf("\n\t\t\t Quantity Adding Success!!! ");//rises the quantity 
                                    printf("\n\t\t\t Enter any key to continue......");
                                    getch();
                                    system("cls");
                                    break;
                                }
                            }
                        }
                        else
                        {
                            system("cls");
                        }
                    }
                }
            }
        }
        else if (n == 2)
        {
            setColor(cyan);
            viewBook();
        }
        else if (n == 3)
        {
            setColor(light_yellow);
            printf("\n\t\t\t######### Welcome to Search Menu #########");
            setColor(cyan);
            search();
        }
        else if (n == 4)
        {
            
            setColor(light_yellow);
            printf("\n\t\t\t######### Welcome to Edit Menu #########");
            
            setColor(cyan);
            edit();
        }
        else if (n == 5)
        {
            // heading();
            setColor(red);
            delete ();
        }
        else if (n == 6)
        {
            // heading();
            save();
        }
        else if (n == 7)
        {
            int size, i;
            int choice;
            setColor(blue);
            heading();
            system("cls");
            setColor(light_yellow);
            printf("\n\t\t\t********Load File Menu***********");

            choice = printLoadMenu();
            choice = choice + 1;
            if (choice == 1)//this loads the file from user defined file name
            {
                system("cls");
                setColor(green);
                printf("\n\t\t\t Enter File name to Load from (Example-book.txt): ");
                char s[100];
                scanf(" %[^\n]", s);
                size = load(s);
                capacity.count = size;
                setColor(cyan);
                printf("\n\n\t\t<<<<<< Total count : %d >>>>>>", size);
                for (i = 0; i < size; i++)
                {
                    printf("\n\t\t\t ISBN     : %s   ", b[i].id);
                    printf("\n\t\t\t Name     : %s   ", b[i].name);
                    printf("\n\t\t\t Author   : %s   ", b[i].author);
                    printf("\n\t\t\t Genre    : %s   ", b[i].genre);
                    printf("\n\t\t\t Quantity : %d   ", b[i].quantity);
                    printf("\n\n\t\t\t Shelf    : %d   \n", b[i].shelf);
                }
                setColor(green);
                printf("\n\t\t\t< Loaded Successfully From Entered File : %s >", s);
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
            }
            else if (choice == 2)//loads from default file
            {
                system("cls");
                size = load("book.txt");
                capacity.count = size;
                setColor(cyan);
                printf("\n\n\t\t<<<<<< Total count : %d >>>>>>", size);
                for (i = 0; i < size; i++)
                {
                    printf("\n\t\t\t ISBN     : %s   ", b[i].id);
                    printf("\n\t\t\t Name     : %s   ", b[i].name);
                    printf("\n\t\t\t Author   : %s   ", b[i].author);
                    printf("\n\t\t\t Genre    : %s   ", b[i].genre);
                    printf("\n\t\t\t Quantity : %d   ", b[i].quantity);
                    printf("\n\t\t\t Shelf      : %d   \n\n", b[i].shelf);
                }
                setColor(green);
                printf("\n\t\t\t< Loaded Successfully from Default File(book.txt) >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
            }
            else
            {
                system("cls");
            }
        }
        else if (n == 8)
        {
            setColor(red);
            borrow();
        }
        else if (n == 10)
        {
            system("clr");
            setColor(green);
            returnbook();
        }
        else if (n == 9)
        {
            setColor(green);
            help();
        }

        else
        {
            // exit() ;
            // heading();
            system("cls");
            setColor(cyan);
            printf("\n\t\t\t>>>>>> Have a Nice Day! <<<<<<<");
            getch();
            break;
        }

    }
}
//this helps to print the currently loaded book list 
void viewBook()
{

    // int i = count;
    system("cls");
    setColor(light_yellow);
    printf("\n\n\t\t ********* View Book *********\n\n");
    setColor(cyan);
    int j, i;
    int c;
    // c = count;
    for (i = 0; i < capacity.count; i++)
    {
        printf("\n\t\t\t ISBN     : %s   ", b[i].id);
        printf("\n\t\t\t Name     : %s   ", b[i].name);
        printf("\n\t\t\t Author   : %s   ", b[i].author);
        printf("\n\t\t\t Genre    : %s   ", b[i].genre);
        printf("\n\t\t\t Quantity : %d   ", b[i].quantity);
        printf("\n\n\t\t\t Shelf    : %d   \n", b[i].shelf);
    }
    setColor(blue);
    printf("\n\n\t\t<<<<<< Total count :%d >>>>>>", capacity.count);
    printf("\n\t\t\t Enter any key to continue....");
    getch();
    system("cls");
}
//this helps to search through different criteria
int search()
{
    char bookname[100];
    char id[100];
    int choice;

    system("cls");
    // printf("\n\t\t\t Enter choice to proceed :");
    // scanf("%d", &choice);
    choice = printSearchMenu();
    choice = choice + 1;
    system("cls");
    if (choice == 1)//search by Book name
    {
        setColor(cyan);
        system("cls");
        int count = 0;
        printf("\n\t\t\t Enter Bookname :");
        scanf(" %[^\n]", bookname);
        int i, j;
        for (i = 0; i < capacity.count; i++)
        {
            // j = strcmp(bookname, b[i].name);
            if (strstr(b[i].name, bookname) != NULL)
            {
                printf("\n\t\t\t<      Book Found!!!         >");
                printf("\n\t\t\t< Your desired book's details >");
                printf("\n\t\t\t*************************");
                printf("\n\t\t\t ISBN     : %s   ", b[i].id);
                printf("\n\t\t\t Name     : %s   ", b[i].name);
                printf("\n\t\t\t Author   : %s   ", b[i].author);
                printf("\n\t\t\t Genre    : %s   ", b[i].genre);
                printf("\n\t\t\t Quantity : %d   ", b[i].quantity);
                printf("\n\n\t\t\t Shelf    : %d   ", b[i].shelf);
                printf("\n\t\t\t*************************");
                count++;
                // return 0;
            }
        }
        if (count == 0)
        {
            system("cls");
            setColor(red);
            printf("\n\t\t\t< Book Not Found!!! >");
        }
        printf("\n\t\t\t Enter any key to continue....");
        getch();
        system("cls");
        return 0;
    }
    else if (choice == 2)//search by ISBN
    {
        system("cls");
        int count = 0;
        setColor(cyan);
        printf("\n\t\t\t Enter ISBN :");
        scanf(" %[^\n]", id);
        int i, j;
        for (i = 0; i < capacity.count; i++)
        {
            // j = strcmp(id, b[i].id);
            if (strstr(b[i].id, id) != NULL)
            {
                setColor(cyan);
                printf("\n\t\t\t<------- Book Found!!! ------->");
                printf("\n\t\t\t< Your desired book's details >");
                printf("\n\t\t\t*************************");
                printf("\n\t\t\t ISBN   : : %s   ", b[i].id);
                printf("\n\t\t\t Name     : %s   ", b[i].name);
                printf("\n\t\t\t Author   : %s   ", b[i].author);
                printf("\n\t\t\t Genre    : %s   ", b[i].genre);
                printf("\n\t\t\t Quantity : %d   ", b[i].quantity);
                printf("\n\n\t\t\t Shelf    : %d   \n", b[i].shelf);
                printf("\n\t\t\t*************************");
                // return 0;
                count++;
            }
        }
        if (count == 0)
        {
            system("cls");
            setColor(red);
            printf("\n\t\t\t< Book Not Found!!! >");
        }
        printf("\n\t\t\t Enter any key to continue....");
        getch();
        system("cls");
        return 0;
    }
    else if (choice == 3)//search by genre
    {
        system("cls");
        int count = 0;
        setColor(light_yellow);
        printf("\n\t\t\t Enter Genre :");
        scanf("%s", &id);
        int i, j;
        for (i = 0; i < capacity.count; i++)
        {
            // j = strcmp(id, b[i].genre);
            if (strstr(b[i].genre, id) != NULL)
            {
                setColor(cyan);
                printf("\n\t\t\t<------- Book Found!!! ------->");
                printf("\n\t\t\t< Your desired book's details >");
                printf("\n\t\t\t*************************");
                printf("\n\t\t\t ISBN     : %s   ", b[i].id);
                printf("\n\t\t\t Name     : %s   ", b[i].name);
                printf("\n\t\t\t Author   : %s   ", b[i].author);
                printf("\n\t\t\t Genre    : %s   ", b[i].genre);
                printf("\n\t\t\t Quantity : %d   ", b[i].quantity);
                printf("\n\n\t\t\t Shelf    : %d   \n", b[i].shelf);
                printf("\n\t\t\t*************************");
                // return 0;
                count++;
            }
        }
        int f;
        f = 0;
        if (count == 0)
        {
            system("cls");
            setColor(red);
            printf("\n\t\t\t< Book Not Found!!! >");
        }
        printf("\n\t\t\t Enter any key to continue....");
        getch();
        system("cls");
        return 0;
    }
    else if (choice == 4)//search by author
    {
        system("cls");
        int count = 0;
        setColor(light_yellow);
        printf("\n\t\t\t Enter Author :");
        scanf("%s", &id);
        int i, j;
        for (i = 0; i < capacity.count; i++)
        {
            // j = strcmp(id, b[i].author);
            if (strstr(b[i].author, id) != NULL)
            {
                setColor(cyan);
                printf("\n\t\t\t<------- Book Found!!! ------->");
                printf("\n\t\t\t< Your desired book's details >");
                printf("\n\t\t\t*************************");
                printf("\n\t\t\t ISBN     : %s   ", b[i].id);
                printf("\n\t\t\t Name     : %s   ", b[i].name);
                printf("\n\t\t\t Author   : %s   ", b[i].author);
                printf("\n\t\t\t Genre    : %s   ", b[i].genre);
                printf("\n\t\t\t Quantity : %d   ", b[i].quantity);
                printf("\n\n\t\t\t Shelf    : %d   \n", b[i].shelf);
                printf("\n\t\t\t*************************");
                // return 0;
                count++;
            }
        }
        int f;
        f = 0;
        if (count == 0)
        {
            system("cls");
            setColor(red);
            printf("\n\t\t\t< Book Not Found!!! >");
        }
        printf("\n\t\t\t Enter any key to continue....");
        getch();
        system("cls");
        return 0;
    }
    else
    {
        system("cls");
        return 0;
    }
}
//this deletes the whole book profile through different criteria
void delete ()
{
    system("cls");
    setColor(light_yellow);
    printf("\n\t\t\t######### Welcome to Delete Menu #########");
    int choice, in;
    char input[100], change[100];

    system("cls");
    choice = printDeleteMenu();
    choice = choice + 1;
    system("cls");
    fflush(stdin);
    if (choice == 1)//this deletes by searching through ISBN
    {
        system("cls");
        setColor(light_yellow);
        printf("\n\t\t\t Enter ISBN  :");
        // scanf("%s", &input);
        gets(input);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h, j;
            // h = strcmp(input, b[i].id);
            if (strstr(b[i].id, input) != NULL)
            {
                for (j = i; j < capacity.count; j++)
                {
                    b[j] = b[j + 1];
                }
                capacity.count--;
                setColor(green);
                printf("\n\t\t\t< Deleting Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        setColor(red);
        printf("\n\t\t\t< Delete failed!!!Entered ISBN doesn't exist in the list >");
        printf("\n\t\t\t Enter any key to continue......");
        getch();
        system("cls");
        return;
    }
    else if (choice == 2)//this searches by book name and delete that profile
    {
        system("cls");
        setColor(light_yellow);
        printf("\n\t\t\t Enter Book Name :");
        gets(input);
        // scanf("%s", &input);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h, j;
            // h = strcmp(input, b[i].name);
            if (strstr(b[i].name, input))
            {
                for (j = i; j < capacity.count; j++)
                {
                    b[j] = b[j + 1];
                }
                capacity.count--;
                setColor(green);
                printf("\n\t\t\t< Deleting Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        setColor(red);
        printf("\n\t\t\t< Delete failed!!!Entered Book Name doesn't exist in the list >");
        printf("\n\t\t\t Enter any key to continue......");
        getch();
        system("cls");

        return;
    }
    else if (choice == 3)//search by author and delete that profile
    {
        system("cls");
        setColor(light_yellow);
        printf("\n\t\t\t Enter Author :");
        gets(input);
        // scanf("%s", &input);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h, j;
            // h = strcmp(input, b[i].author);
            if (strstr(b[i].author, input))
            {
                for (j = i; j < capacity.count; j++)
                {
                    b[j] = b[j + 1];
                }
                capacity.count--;
                setColor(green);
                printf("\n\t\t\t< Deleting Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        setColor(red);
        printf("\n\t\t\t< Delete failed!!!Entered Author doesn't exist in the list >");
        printf("\n\t\t\t Enter any key to continue......");
        getch();
        system("cls");

        return;
    }
    else
    {
        system("cls");
        // break;
        return;
    }
}
//this helps to edit book profile using different criteria
void edit()
{
    int choice, in;
    char input[100], change[100];
    system("cls");

    choice = printEditMenu();
    choice = choice + 1;
    fflush(stdin);
    if (choice == 1)//edit the ISBN
    {
        system("cls");
        printf("\n\t\t\t Enter ISBN  :");
        fgets(input, 100, stdin);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h;
            // h = strcmp(input, b[i].id);
            if (strstr(b[i].id, input) != NULL)
            {
                while (1)
                {
                    printf("\n\t\t\t Enter New ISBN  :");
                    fgets(change, 100, stdin);
                    strcpy(b[i].id, change);
                    int g = strlen(change);
                    if (g == 13)
                        break;
                    else
                        printf("\n\n\t\t You entered wrong ISBN");
                }
                printf("\n\t\t\t< Editing Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\t\t < Edit failed!!!Entered ISBN is invalid. >");
        printf("\n\n\t\t Enter any key to continue.....");
        getch();
        system("cls");
        return;
    }
    else if (choice == 2)//Edit the book name
    {
        char ch;
        system("cls");
        printf("\n\t\t\t Enter Book Name :");
        fgets(input, 100, stdin);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h;
            // h = strcmp(input, b[i].name);
            if (strstr(b[i].name, input) != NULL)
            {
                printf("\n\t\t\t Enter New Book Name :");
                fgets(change, 100, stdin);
                strcpy(b[i].name, change);
                printf("\n\t\t\t< Editing Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\t\t < Edit failed!!!Entered book name doesn't exist in the list >");
        printf("\n\n\t\t Enter any key to continue.....");
        getch();
        system("cls");
        return;
    }
    else if (choice == 3)//Edit author
    {
        //getchar();
        system("cls");
        printf("\n\t\t\t Enter Author :");
        fgets(input, 100, stdin);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h;
            // h = strcmp(input, b[i].author);
            if (strstr(b[i].author, input) != NULL)
            {
                printf("\n\t\t\t Enter New Author :");
                fgets(change, 100, stdin);
                strcpy(b[i].author, change);
                printf("\n\t\t\t< Editing Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\t\t < Edit failed!!!Entered Author doesn't exist in the list >");
        printf("\n\n\t\t Enter any key to continue.....");
        getch();
        system("cls");
        return;
    }
    else if(choice==4)
    {
        //getchar();
        system("cls");
        printf("\n\t\t\t Enter Genre :");
        fgets(input, 100, stdin);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h;
            // h = strcmp(input, b[i].author);
            if (strstr(b[i].genre, input) != NULL)
            {
                printf("\n\t\t\t Enter New Genre :");
                fgets(b[i].genre, 100, stdin);
                // strcpy(b[i].genre, change);
                printf("\n\t\t\t< Editing Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\t\t < Edit failed!!!Entered genre doesn't exist in the list >");
        printf("\n\n\t\t Enter any key to continue.....");
        getch();
        system("cls");
        return;
    }
    else if (choice == 5)
    {
        // getchar();
        system("cls");
        printf("\n\t\t\t Enter ISBN  :");
        fgets(input, 100, stdin);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h;
            // h = strcmp(input, b[i].name);
            if (strstr(b[i].id, input) != NULL)
            {
                printf("\n\t\t\t Enter New Quantity :");
                scanf("%d", &in);
                b[i].quantity = in;
                printf("\n\t\t\t< Editing Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\t\t < Edit failed!!!Entered book doesn't exist in the list >");
        printf("\n\n\t\t Enter any key to continue.....");
        getch();
        system("cls");
        return;
    }
    else if (choice == 6)
    {
        // getchar();
        system("cls");
        printf("\n\t\t\t Enter ISBN  :");
        fgets(input, 100, stdin);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h;
            // h = strcmp(input, b[i].name);
            if (strstr(b[i].id, input) != NULL)
            {
                printf("\n\t\t\t Enter New Shelf :");
                scanf("%d", &in);
                b[i].shelf = in;
                printf("\n\t\t\t< Editing Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\t\t < Edit failed!!!Entered book doesn't exist in the list >");
        printf("\n\n\t\t Enter any key to continue.....");
        getch();
        system("cls");
        return;
    }

    else
    {
        system("cls");
        return;
    }
}

void save()
{
    int choice;
    system("cls");
    printf("\n\t\t\t********Save File Menu***********");

    system("cls");
    choice = printSaveMenu();
    choice = choice + 1;
    if (choice == 1)
    {
        system("cls");
        printf("\n\t\t\t Enter File name to save as (Example-book.txt): ");
        char s[100];
        scanf("%s", s);
        printf("\n\t\t\t< Saved Successfully in New File : %s >", s);
        saveinfo(s, capacity.count);
        printf("\n\t\t\t Enter any key to continue....");
        getch();
        system("cls");
    }
    else if (choice == 2)
    {
        system("cls");
        printf("\n\t\t\t< Saved Successfully in Default File(book.txt) >");
        saveinfo("book.txt", capacity.count);
        printf("\n\t\t\t Enter any key to continue....");
        getch();
        system("cls");
    }
    else
    {
        system("cls");
        return;
    }
}

int saveinfo(char *filepath, int n) // serialization
{
    FILE *fp = fopen(filepath, "w+");
    if (fp==NULL)
        exit(1);
    int i;
    fprintf(fp, "\n\t\t\t********* Total Books  : %d *********\n", capacity.count);
    for (i = 0; i < n; i++)
    {

        b[i].id[strlen(b[i].id) - 1] = '\0';
        b[i].name[strlen(b[i].name) - 1] = '\0';
        b[i].author[strlen(b[i].author) - 1] = '\0';
        b[i].genre[strlen(b[i].genre) - 1] = '\0';
        fprintf(fp, "%s\n", b[i].id);
        fprintf(fp, "%s\n", b[i].name);
        fprintf(fp, "%s\n", b[i].author);
        fprintf(fp, "%s\n", b[i].genre);
        fprintf(fp, "%d\n", b[i].quantity);
        fprintf(fp, "%d\n\n", b[i].shelf);
    }

    fclose(fp);
   // encrypt(filepath,"Excallibur");

    return 0;
}
int loadinfo(char *filepath, int n) // deserialization
{

    FILE *fp = fopen(filepath, "r+");
    int i, len;
    if (!fp)
        exit(1);
        fscanf(fp, "\n\t\t\t********* Total Books  : %d *********", &len);
    fgetc(fp);
    for (i = 0; i < n; i++)
    {


        fgets(b[i].id, 15, fp);
        fgets(b[i].name, 100, fp);
        fgets(b[i].author, 100, fp);
        fgets(b[i].genre, 100, fp);
        fscanf(fp, "%d", &b[i].quantity);
        fscanf(fp, "%d\n", &b[i].shelf);

    }
    // free(b);
    fclose(fp);
    return 0;
}
int load(char *filepath) // deserialization
{
    
    FILE *fp = fopen(filepath, "r");
   // encrypt(filepath,"Excallibur");
    int i, len;
    if (!fp)
    {
        printf("\n\t\t\t< ERROR!!! >");
        exit(1);
    }
    else
    {
        fscanf(fp, "\n\t\t\t********* Total Books  : %d *********", &len);
    }
    fgetc(fp);
    if (!fp)
        return -1;

    for (i = 0; i < len; i++)
    {


        fgets(b[i].id, 15, fp);
        //  b[i].id[strlen(b[i].id) - 2] = '\0';
        fgets(b[i].name, 100, fp);
        //  b[i].name[strlen(b[i].name) - 2] = '\0';
        fgets(b[i].author, 100, fp);
        //  b[i].author[strlen(b[i].author) - 2] = '\0';
        fgets(b[i].genre, 100, fp);
        //  b[i].genre[strlen(b[i].genre) - 2] = '\0';

        fscanf(fp, "%d", &b[i].quantity);
        fscanf(fp, "%d\n", &b[i].shelf);
    }
    // free(b);
    fclose(fp);
    //encrypt(filepath,"Excallibur");
    return len;
}
void saveuserinfo(char *filepath) // serialization
{
    FILE *fp = fopen(filepath, "wb");
    int i;

    if (!fp)
        exit(1);
    
    fwrite(&(capacity.users),sizeof(capacity.users),1,fp);
   
            fwrite(&sign,sizeof(signin),capacity.users,fp);
    

    fclose(fp);

    return;
}

int loaduserinfo()
{

    FILE *fp = fopen("user.bin", "rb");
    int i, len;
    if (!fp)
    {
        printf("\n\t\t\t< ERROR!!! >");
        exit(1);
    }
  
    fread(&len,sizeof(len),1,fp);
    capacity.users = len;
  
        if (!fp)
            exit(1);

            fread(&sign,sizeof(signin),capacity.users,fp);
    

    fclose(fp);

    return len + 1;
}
void borrow()
{
    int choice, in;
    char input[100], change[100];
    system("cls");
    printf("\n\t\t\t$$$$$$$$$ Welcome to Borrow Menu $$$$$$$$$");

    choice = printBorrowMenu();
    choice = choice + 1;
    system("cls");
    fflush(stdin);
    if (choice == 1)
    {
        system("cls");
        printf("\n\t\t\t Enter ISBN  :");
        scanf("%s", &input);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h, j;
            
            if (strstr(b[i].id, input) != NULL)
            {
                if (b[i].quantity > 0)
                {
                    b[i].quantity = b[i].quantity - 1;
                    printf("\n\t\t\t< Borrow Success!!! >");
                    printf("\n\t\t\t Enter any key to continue....");
                    getch();
                    system("cls");
                    return;
                }
                else
                {
                    printf("\n\t\t\t< Sorry the book is out of stock!!! >");
                    printf("\n\t\t\t Enter any key to continue....");
                    getch();
                    system("cls");
                    return;
                }
            }
        }
        printf("\n\t\t\t< Borrow failed!!!Entered ISBN doesn't exist in the list >");
        printf("\n\t\t\t Enter any key to continue......");
        getch();
        system("cls");
        return;
    }
    else if (choice == 2)
    {
        system("cls");
        printf("\n\t\t\t Enter Book Name :");
        fgets(input, 100, stdin);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h, j;
            if (strstr(b[i].name, input) != NULL)
            {
                if (b[i].quantity > 0)
                {
                    b[i].quantity = b[i].quantity - 1;
                    printf("\n\t\t\t< Borrow Success!!! >");
                    printf("\n\t\t\t Enter any key to continue....");
                    getch();
                    system("cls");
                    return;
                }
                else
                {
                    printf("\n\t\t\t< Sorry the book is out of stock!!! >");
                    printf("\n\t\t\t Enter any key to continue....");
                    getch();
                    system("cls");
                    return;
                }
            }
        }
        printf("\n\t\t\t< Borrow failed!!!Entered Book Name doesn't exist in the list >");
        printf("\n\t\t\t Enter any key to continue......");
        getch();
        system("cls");
        return;
    }
    else
    {
        system("cls");
        return;
    }
}
void help()
{
    setColor(blue);

    printf("\n\t\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Guidelines >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    printf("\n\t\t********************************************************************************************");
    printf("\n\t\t*  -> Make sure the file you want to load is as per allignment provided by the system.     *");
    printf("\n\t\t*  -> Remember your Username and Password to get access to the system                      *");
    printf("\n\t\t*  -> Make sure you Follow the instructions of Menu on your screen.                        *");
    printf("\n\t\t*  -> User can use special symbol like [ _ . , * # @ ! ~ \\ / ]                            *");
    printf("\n\t\t*  -> Please be careful while naming the File.Avoid spaces while naming a file.            *");
    printf("\n\t\t********************************************************************************************");
    printf("\n\t\t\t\t< Thank you for choosing us.   Wish you a nice day >");
    printf("\n\n\t\t\t\t< Enter any key to continue...... >");
    getch();
    system("cls");
}
void setCursorPosition(int x, int y)
{
    COORD coordinate = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void print_center(int row, char *s)
{
    COORD c;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    c.X = row;
    c.Y = (columns - strlen(s)) / 2;
    ;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("%s", s);
}
void setCord(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int printMenu()
{
    char menu[][20] = {"Add Book", "Book List ", "Search a Book", "Edit Book", "Delete Book ",
                       "Save File", "Load from File", "Borrow", "Guideline", "Return", "Exit"
                      };
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 11; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 10) % 11; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 11; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(cyan);
        else if (selected == 4)
            setColor(red);
        else if (selected == 5)
            setColor(green);
        else if (selected == 6)
            setColor(blue);
        else if (selected == 7)
            setColor(light_yellow);
        else if (selected == 8)
            setColor(cyan);
        else if (selected == 9)
            setColor(blue);
        else if (selected == 10)
            setColor(green);
        
        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}
int printSignin()
{
    char menu[][20] =
    {
        "SignIn",
        "Register",
    };
    system("COLOR 11");
    int selected = 0;
    // system("cls");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 2; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 1) % 2; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 2; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //

        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

int printSearchMenu()
{
    char menu[][200] = {"Search by Bookname", "Search by ISBN", "Search by Genre", "Search by Author", "Back"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 5; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 4) % 5; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 5; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(cyan);
        else if (selected == 4)
            setColor(red);
        else if (selected == 5)
            setColor(red);

        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

int printDeleteMenu()
{
    char menu[][200] = {"ISBN", "Bookname", "Author", "Back"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 4; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 3) % 4; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 4; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(cyan);
        else if (selected == 4)
            setColor(red);
        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

int printSaveMenu()
{
    char menu[][200] = {"New File", "Default File", "Back"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 3; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 2) % 3; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 3; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(red);
        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

int printEditMenu()
{
    char menu[][200] = {"Edit ISBN", "Edit Bookname", "Edit Author","Edit Genre", "Edit Quantity", "Edit Shelf", "Back"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 7; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 6) % 7; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 7; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(cyan);
        else if (selected == 4)
            setColor(purple);
        else if (selected == 5)
            setColor(light_yellow);
        else if (selected == 6)
            setColor(green);
        else if (selected == 7)
            setColor(red);

        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

int printLoadMenu()
{
    char menu[][200] = {"New File", "Default File", "Back"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 3; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 2) % 3; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 3; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(red);
        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

int printBorrowMenu()
{
    char menu[][200] = {"ISBN", "Book Name", "Back"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 3; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 2) % 3; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 3; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(red);
        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

void returnbook()
{
    int choice, in;
    char input[100], change[100];
    system("cls");
    setColor(light_yellow);
    printf("\n\t\t\t$$$$$$$$$ Welcome to Return Menu $$$$$$$$$");

    choice = printReturnMenu();
    choice = choice + 1;
    system("cls");
    fflush(stdin);
    if (choice == 1)
    {
        system("cls");
        setColor(cyan);
        printf("\n\t\t\t Enter ISBN  :");
        scanf("%s", &input);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h, j;
            // h = strcmp(input, b[i].id);
            if (strstr(b[i].id, input) != NULL)
            {

                b[i].quantity = b[i].quantity + 1;
                setColor(green);
                printf("\n\t\t\t< Return Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        setColor(red);
        printf("\n\t\t\t < Return Failed!!!Entered ISBN doesn't exist in list ");
        printf("\n\t\t\t Enter any key to continue......");
        getch();
        system("cls");
        return;
    }
    else if (choice == 2)
    {
        system("cls");
        printf("\n\t\t\t Enter Book Name :");
        fgets(input, 100, stdin);
        // scanf("%s", &input);
        int i;
        for (i = 0; i < capacity.count; i++)
        {
            int h, j;
            // h = strcmp(input, b[i].name);
            if (strstr(b[i].name, input) != NULL)
            {

                b[i].quantity = b[i].quantity + 1;
                printf("\n\t\t\t< Return Success!!! >");
                printf("\n\t\t\t Enter any key to continue....");
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\t\t\t< Return failed!!!Entered book name doesn't exist in the list >");
        printf("\n\t\t\t Enter any key to continue......");
        getch();
        system("cls");
        return;
    }
    else
    {
        system("cls");
        return;
    }
}

int printReturnMenu()
{
    char menu[][200] = {"ISBN", "Book Name", "Back"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 3; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 2) % 3; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 3; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(blue);
        else if (selected == 2)
            setColor(light_yellow); //
        else if (selected == 3)
            setColor(red);
        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

int check(char *in)
{
    int i;
    for (i = 0; i < capacity.count; i++)
    {
        // j = strcmp(bookname, b[i].name);
        if (strstr(b[i].id, in) != NULL)
        {
            return 1;
        }
    }
    return 0;
}

int printCheckMenu()
{
    char menu[][200] = {"Do you want to Increase quantity?", "Do you want to Try again?"};
    int selected = 0;
    // system("cls");
    system("COLOR 11");
    setColor(green);
    setCursorPosition(41, 5);
    printf(">>> %s <<<", menu[0]);
    setColor(gray);
    for (int i = 1; i < 2; i++)
    {
        setCursorPosition(44, 5 + i);
        printf(" %s ", menu[i]);
    }

    while (1)
    {
        char ch = _getch();

        if (ch == -32)
            ch = _getch();

        setColor(gray);
        setCursorPosition(40, 5 + selected);
        printf("     %s    ", menu[selected]);

        if (ch == 72)
            selected = (selected + 1) % 2; // n-1 % n
        else if (ch == 80)
            selected = (selected + 1) % 2; //=1 ek hbe bt 10=n hbe

        else if (ch == 13)
            return selected;

        if (selected == 0)
            setColor(green);
        else if (selected == 1)
            setColor(green);
        else if (selected == 2)
            setColor(red); //

        setCursorPosition(41, 5 + selected);
        printf(">>> %s <<<", menu[selected]); // xyz[i]
    }
}

/*void encrypt(char *FILENAME, char *key)
{
    int *s = malloc(sizeof(char) * 20000);
    FILE *fp;
    fp = fopen(FILENAME, "r");
    int count = 0;
    while((s[count] = fgetc(fp)) != EOF)
        ++count;
    fclose(fp);
    fp = fopen(FILENAME, "w");
    int key_length = strlen(key);
    for (int i = 0; i < count; i += key_length)
    {
        int ch;
        for (int j = i; j < i + key_length && j < count; ++j)
        {
            ch = s[j] ^ key[j - i];
            fputc(ch, fp);
        }
    }
    fclose(fp);
}*/


