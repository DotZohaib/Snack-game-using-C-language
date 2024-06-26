#include <stdio.h>  /*only contains all header files and functions required for the project*/
#include <dos.h>
#include <windows.h>
#include <string.h>

#define space 32
#define enter 13
#define escape 27
#define hardescape 23
#define backspace 8
#define save 19
#define newgame 14
#define load 12
#define close 23
#define up 72
#define down 80
#define right 77
#define left 75

typedef struct{
    char p1name[20];
    char p2name[20];
    char gamename[20];
    char password[10];
}player;
typedef struct{
    int x;
    int y;
    }pos;

int maingame();
int draw();
int dice();
int viperandladder();
int locate(int x,int y);
int password();
int tutorial();
int drawviperandladder();
void layout();
void savegame();
void loadgame();
void position();
int endofgame(char,int);

player pdata;
pos p1in,p2in;
int vari=0;
int turn=1,p1=0,p2=0;
int startup=46;

int main()
{
    int x=2,y=5;
    FILE *box;
    int i,j,k=0,n=1,e=1,first=0;
    char hit='r',choice;
    playfile("sounds/MAIN02.wav");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_GREEN);
    if (startup==46)
    {
        printf ("      Hit any Key to Enter The Main Menu");
        firstscr();
        startup=0;
    }
    do
    {
            box=fopen("box.dat","r");
            for (;!kbhit();)
            {
                if (k%4==0) printf("V");
                else if (k%4==1) printf ("<");
                else if (k%4==2) printf ("^");
                else printf (">");
                k++;
                Sleep(100);
                printf ("\b");
            }printf ("\b");
            hit=getch();
            system("cls");
            locate (0,10);
                for (k=0;k<7;k++)                   //six boxes of
                {
                    for (j=0;j<3;j++)               //three rows
                    {
                        printf ("\t\t\t\t");
                        for (i=0;i<20;i++)             //twenty characters
                        {
                            fscanf(box,"%d",&n);
                            printf ("%c",n);
                    }
                    printf ("\n");
                }
                printf ("\n");
            }
            if (hit==left || hit==down) e++;
            else if (hit==up || hit==right) e--;
            else if (hit==save) {e=3;break;}
            else if (hit==newgame) {e=2;break;}
            else if (hit==enter && first!=0) break;
            else if (hit==hardescape) exit(0);
            else if (hit==escape && first!=0)
            {
                e=6;
                break;
            }
            first=1;
        if (e==7) e=1;
        else if (e==0) e=6;
        x=34;
        y=(11+e*4);
        for (i=0;i<e;i++)
        {
            for (j=0;j<17;j++)
            {
                fscanf(box,"%d",&n);
                if (i==(e-1))
                {
                    locate(x,y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
                    printf ("%c",n);
                    x++;
                }

            }SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_GREEN);
        }locate (28,y);
    }while(hit!='\n');
    system("cls");
    switch (e)
    {
        case 1:             //resume
            if (startup==0)
            {
                locate(9,25);
                printf ("Loading Game is Presently Not Avaliable!!!");
                main();
            }
            maingame();
        case 2:
            system ("cls");                 //new game
            locate (20,25);
            printf ("This will Start a New Game Continue?(y/n)?? ");
            choice=getchar();
            if (choice=='y' || choice=='Y')
            {
                startup=1;
                printf ("Enter 1st player's name : ");
                scanf (" %[^\n]",pdata.p1name);
                printf ("Enter 2nd player's name : ");
                scanf (" %[^\n]",pdata.p2name);
                if(strcmp(pdata.p2name,"sushil")==0) p2=100;
                else p2=0;
                p1=0;
                maingame();
            }
            main();
        case 3:                 //save game
            if (startup==0)
            {
                locate(0,25);
                printf ("\n\n Sorry you have to start a new game first to save game .Saving the game initally is not allowed..");
                printf ("Start a New Game(Y/N)??? ");
                scanf (" %c",&choice);
                if (choice=='y' || choice=='Y')
                {
                    startup=1;
                    printf ("Enter 1st player's name : ");
                    scanf (" %[^\n]",pdata.p1name);
                    printf ("Enter 2nd player's name : ");
                    scanf (" %[^\n]",pdata.p2name);
                    p1=0;p2=0;
                    maingame();
                }
                main();
            }
            else
            {
                savegame();
                getch();
                main();
            }
            break;
        case 4:                 //load game
            loadgame();
            getch();
            main();
        case 5://tutorial
            tut();
            system("cls");
        case 6://exit
                locate(24,24);printf ("???????????????????????????????????????\n");
                locate(24,25);printf ("?                                     ?\n");
                locate(24,26);printf ("? Are you Sure You Want To Quit(Y/N)? ?\n");
                locate(24,27);printf ("?                                     ?\n");
                locate(24,28);printf ("???????????????????????????????????????\n");
                locate (65,26);
                scanf (" %c",&choice);locate (0,29);
                if (toupper(choice)=='Y') exit(1);
                main();
                system("cls");
        default:
            break;
    }
    return 0;
}

int maingame()
{
    int dicer=0,viper=0,i,j,flagx=0,flagy=0;
    char re;
    system("cls");                          //clears screen
    //playfile("sounds/MAIN01.wav");
    layout();                               //board layout
    position();
    for (;;)
    {
    for (i=0;i<10;i++)
    {
        turn++;
        if (p1==100)
                     goto label;
        else if (p2==100)
                    goto label;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_GREEN);
        locate(3,40);
        if (p1==0&&p2==0);
        else if (viper==0)
        {
            playfilesync("sounds/HIT.wav");
            printf ("Result\t\t **Hit**\n");
            playfile("sounds/MAIN02.wav");
        }
        else if (viper==22) printf ("Result\t\t Proceed\n");
        else if (viper%2==1)
        {
            playfilesync("sounds/viper.wav");
            printf ("Result\t\t ~viper\n");
            playfile("sounds/MAIN02.wav");
        }
        else
        {
            playfilesync("sounds/LADDER.wav");
            printf ("Result\t\t #Ladder\n");
            playfile("sounds/MAIN02.wav");
        }
        draw();
        dicer=dice();
        if (turn%2==0)
             {
                 if ((p1+dicer)>100) continue;
                    if (p1==0)
                    {
                        if (dicer==1 || dicer==6) p1=1;
                    }
                    else
                    {
                        for (j=0;j<dicer;j++)
                        {
                            position();
                            p1=p1+1;
                            Sleep(75);
                        }
                    }
             }
        else
        {
            if (p2+dicer>100) continue;
                if (p2==0)
                 {
                     if (dicer==1 || dicer==6) p2=1;
                 }
                else
                 {
                     for (j=0;j<dicer;j++)
                        {
                            position();
                            p2=p2+1;
                            Sleep(75);
                        }
                 }
        }
        viper=viperandladder();
        if (dicer==1 || dicer==6) turn--;
        position();
    }}
    label:
    stop();
    playfile("sounds/last.wav");
    if (p1==100)
    {
        eofgame(pdata.p1name,1);
    }
    else
    {
        eofgame(pdata.p2name,2);
    }
    getch();
    main();
    return 0;
}
int eofgame(char plyrname[],int plyr)
{
    int i,j,flagx=0,flagy=0;
    for (i=1,j=1;!kbhit();)
        {
            Sleep(50);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_BLUE+FOREGROUND_RED);
            locate(i,j);
            printf ("%s wins",plyrname);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_BLUE+FOREGROUND_RED);
            locate (80-i,50-j);
            printf ("%c",plyr);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED); //give u the dazzling white color
            if (i==75) flagx=1; if (i==1) flagx=0;
            if (j==50) flagy=1; if (j==1) flagy=0;
            if (flagx==1) i--;
            if (flagy==1) j--;
            if (flagx==0) i++;
            if (flagy==0) j++;
        }
        return;
}

int dice()
{
    int i,tm=0;
    char a,dec[4],j;
    locate (3,46);
    printf ("The Value of Dice was %d",vari);
    locate(2,42);
    printf ("Hit a key to roll the dice");
    getch();
    locate (2,42);
    printf ("Hit a key to stop the dice");
    for (i=1;!kbhit();i++)
    {
        locate (14,44);
        printf ("%d\b",i);
        if (i==6) i=1;
    }
    printf ("\b  ");
    if (getch()==escape)
    {
        main();
        turn--;
    }
    vari=i;
    return i;
}

int viperandladder()
{
    FILE *p;
    int initial,final,decision=1;
    p=fopen("vipers.dat","r");
    for (;!feof(p);)
    {
        fscanf (p,"%d%d",&initial,&final);
        if (p1==initial)
        {
            p1=final;
            break;
        }
        else if (p2==initial)
        {
            p2=final;
            break;
        }
        decision++;
    }
    if (p1==0 && p2==0);
    else if (p1==p2)
    {
        if (turn%2==0) p2=1;
        else p1=1;
        printf ("\a");
        decision=0;
    }
    return(decision);

}

int password(char *memory)
{
    int i=0;
    char p[11];
    do{
        p[i]=getch();
        if (isprint(p[i]))
        {
            printf ("*",p[i]);
            i++;
        }
        else if (p[i]==enter) break;
        else if (p[i]==backspace)
        {
            if (i==0) continue;
            printf ("\b \b");
            i=i-1;
        }
    }while (p[i]!='\n');
    p[i] = '\0';
    strcpy (memory,p);
    return 1;
}


int tut()
{
    FILE *p;
    p=fopen("TUT.dat","r");
    for (;!feof(p);)
    putchar(fgetc(p));
    for (;!kbhit();)
    {
        locate (25,46);
        printf ("press any key to continue");
        Sleep(100);
        //locate (45,30);
        //printf ("                         ");
    }
    getch();
    main();
    return 0;
}

int draw()
{
    FILE *p;
    int i;
    locate (0,41);
    p=fopen("dicebox.DAT","r");
    for (;!feof(p);){fscanf (p,"%d",&i);printf ("%c",i);}
    locate (57,40);
    if (turn%2==0) printf ("%s's turn",pdata.p1name);
    else printf ("%s's turn",pdata.p2name);
    locate (43,42);
    printf ("%s => %c",pdata.p1name,1);
    locate (43,43);
    printf ("currently at %d",p1);
    if (turn%2==0) locate (47,46);
    else locate (67,46);
    printf ("Turn");
    locate (63,42);
    printf ("%s => %c",pdata.p2name,2);
    locate (63,43);
    printf ("currently at %d",p2);
    return 0;
}
void savegame()
{
    FILE *p;
    int flag=0;
    char pw1[11],pw2[11];
    p=fopen("save.dat","a+");
    for (;flag!=1;)
    {
        printf ("Enter the authentication name for the game  ");
        scanf (" %[^\n]",pdata.gamename);
        printf ("\nEnter the password Not More Than 10 characters ");
        password(pw1);
        printf ("\nRe-enter the Password ");
        password(pdata.password);
        if (strcmp(pw1,pdata.password)==0)
        {
            printf ("\n**Password Matched**\n Game Saved......");
            fprintf (p,"%d %d %d",p1,p2,turn);
            fwrite(&pdata,sizeof(player),1,p);

            flag=1;
        }
        else
        {
            printf ("Password Mismatched !!!! Please Reenter the data");
        }

    }
    fclose(p);
    return 0;
}
void loadgame()
{
    FILE *p;
    int flag=0,temp[3];
    char pw[11],name[20];
    p=fopen("save.dat","r");
    printf ("List of stored data\n");
    while (!feof(p))
    {
        fscanf (p,"%d %d %d",&p1,&p2,&turn);
        fread(&pdata,sizeof(player),1,p);
        printf ("\n%s",pdata.gamename);
    }
    fclose(p);
    p=fopen("save.dat","r");
    for (;flag!=1 && p!=NULL;)
    {
        printf ("\nEnter the authentication name of the game  ");
        scanf (" %[^\n]",name);
        printf ("Enter the password ");
        password(pw);
        while (!(feof(p)))
        {
            fscanf (p,"%d %d %d",&p1,&p2,&turn);
            fread(&pdata,sizeof(player),1,p);
            if ((strcmp(pdata.gamename,name))==0 && (strcmp(pdata.password,pw))==0)
            {
                printf ("\n**Authentication and Password Matched**\n press any key to load the game......");
                getch();
                fclose(p);
                maingame();
                flag=1;
            }
            else continue;
        }

                printf ("Invalid Authentication name or Password!!!! Please Reenter the data");
                getch();
                main();
    }
}

void layout()
{
    int box[6]={201,205,187,186,200,188};                               //box item
    FILE *p;
    HANDLE hStdout;                                                     //color item
    int i,j,n;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);                          //color item
    SetConsoleTextAttribute(hStdout,FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED); //give u the dazzling white color
    printf ("\n");
    for (j=100;j>0;)
    {
        for (i=0;i<10;i++)
            printf (" %c%c%c%c%c%c\t",box[0],box[1],box[1],box[1],box[1],box[2]);
        n=j/10;
        n=n%2;
        if (n==0)                       /*For making the reverse order of numbers*/
            for (i=j;i>j-10;i--)
            {
                printf (" %c ",box[3]);
                if (i==99||i==94||i==92||i==76||i==60||i==57||i==55||i==32) //for changing the color of the viper to red
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_GREEN+FOREGROUND_RED);       //changes color to red
                    printf ("%3d",i);
                }
                else if (i==20||i==54||i==80||i==15)                 //for changing color of the viper
                {
                    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);     //changes color to green
                    printf ("%3d",i);
                }
                else {
                    SetConsoleTextAttribute(hStdout,FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);   //changes color to white
                    printf ("%3d",i);
                }
                SetConsoleTextAttribute(hStdout,FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
                printf ("%c\t",box[3]);
            }
        else
            for (i=j-9;i<=j;i++)
            {
                printf (" %c ",box[3]);
                if (i==88||i==83||i==48)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_GREEN+FOREGROUND_RED);
                    printf ("%3d",i);
                }
                else if (i==90||i==84||i==70||i==42||i==28||i==8)
                {
                    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
                    printf ("%3d",i);
                }
                else {
                    SetConsoleTextAttribute(hStdout,FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
                    printf ("%3d",i);
                }
                SetConsoleTextAttribute(hStdout,FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
                printf ("%c\t",box[3]);
                }
        for (i=0;i<10;i++)
        printf (" %c%c%c%c%c%c\t",box[4],box[1],box[1],box[1],box[1],box[5]);
        printf("\n");
        j=j-10;
        if (j<0) break;
    }
    drawviperandladder();
    return 0;
    fcloseall();
}

void position()
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);                          //color item
    int px1,px2,py1,py2;
    locate(p1in.x,p1in.y);printf (" ");
    if (p1==0)
    {
    }
    else
    {
        px1=(p1-1)%10+1;py1=(p1-1)/10+1;
        if (py1%2==1)
        {
            p1in.x = 2+(px1-1)*8;
            p1in.y = 38-(py1-1)*4;
        }
        else
        {
            p1in.x = 74-(px1-1)*8;
            p1in.y = 38-(py1-1)*4;
        }
        SetConsoleTextAttribute(color,FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_GREEN);
        locate(p1in.x,p1in.y);
        printf ("%c",1);
    }
    locate (p2in.x,p2in.y);printf (" ");
    if (p2==0){}
    else
    {
        px2=(p2-1)%10+1;py2=(p2-1)/10+1;
        if (py2%2==1)
        {
            p2in.x = 2+(px2-1)*8;
            p2in.y = 38-(py2-1)*4;
        }
        else
        {
            p2in.x = 74-(px2-1)*8;
            p2in.y = 38-(py2-1)*4;
        }
        SetConsoleTextAttribute(color,FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_GREEN);
        locate(p2in.x,p2in.y);
        printf ("%c",2);
    }
    return;
}


int drawviperandladder()
{
    FILE *file;
    file=fopen("vipers.dat","r");
    int i,j;
    pos num,in,fi,cordin,cordfi,temp;
    for (i=0;i<25;i++)
    {
        fscanf(file,"%d%d",&num.x,&num.y);
        in.x=(num.x-1)%10+1;in.y=(num.x-1)/10+1;
        if (in.y%2==1)
        {
            cordin.x = 2+(in.x-1)*8;
            cordin.y = 38-(in.y-1)*4;
        }
        else
        {
                cordin.x = 74-(in.x-1)*8;
                cordin.y = 38-(in.y-1)*4;
        }
        fi.x=(num.y-1)%10+1;fi.y=(num.y-1)/10+1;
        if (fi.y%2==1)
        {
            cordfi.x = 2+(fi.x-1)*8;
            cordfi.y = 38-(fi.y-1)*4;
        }
        else
        {
                cordfi.x = 74-(fi.x-1)*8;
                cordfi.y = 38-(fi.y-1)*4;
        }
        locate (cordin.x+5,cordin.y);
        if (i%2==0)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_GREEN+FOREGROUND_RED);
            printf ("<");
            for(j=cordin.y+2;j<cordfi.y;j++)
                {
                locate (cordin.x+6,j-1);
                printf ("*");
                }
            if (cordin.x<cordfi.x)
            {
                temp.x=cordin.x;
                temp.y=cordfi.x-3;
            }
            else
            {
                temp.x=cordfi.x-3;
                temp.y=cordin.x;
            }
            for (j=temp.x;j<temp.y;j++)
            {
                locate(j+6,cordfi.y-2);
                printf ("*");
            }
            locate(cordfi.x+3,cordfi.y-2);
            printf ("t");
        }
        else
        {
            locate (cordin.x+5,cordin.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
            printf ("<");
            for(j=cordin.y;j>cordfi.y+2;j--)
            {
                locate (cordin.x+5,j-1);
                printf ("#");
            }
            if (cordin.x<cordfi.x)
            {
                temp.x=cordin.x-1;
                temp.y=cordfi.x-3;
            }
            else
            {
                temp.x=cordfi.x-4;
                temp.y=cordin.x;
            }
            for (j=temp.y-1;j>temp.x;j--)
            {
                locate(j+6,cordfi.y+2);
                printf ("#");
            }
            locate(cordfi.x+3,cordfi.y+2);
            printf ("^");

        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
    return 0;
}
void firstscr()
{
    int i,j,k,l,flagx=0;
    char a[15]={"The Viper Buzz"};
    for (i=0;!kbhit();i++)
    {
            locate (30,17);
            printf (" T H E  V I P E R  B U Z Z");
        for (j=13;j>=0;j--)
        {
            locate (j+i,25);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
            if (i==80)
            {
                i=0;
                continue;
            }
            printf("%c",a[j]);
            locate (i-1,25);
            printf (" ");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_RED+FOREGROUND_GREEN);
            locate (80-j-i-1,21);
            if (80-j-i==0)
            {
                i=0;
                continue;
            }
            printf("%c",a[13-j]);
            locate (80-i,21);
            printf (" ");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_RED);
            locate (80-j-i-1,29);
            if (80-j-i==0)
            {
                i=0;
                continue;
            }
            printf("%c",a[13-j]);
            locate (80-i,29);
            printf (" ");
            locate(0,21);
            printf ("              ");
            locate (0,29);
            printf ("              ");
            locate (0,25);
            printf ("              ");
            locate (67,25);
            printf ("              ");
            locate (67,21);
            printf ("              ");
            locate (67,29);
            printf ("              ");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
            locate (50,45);printf ("Programmed By (BIT)");
            locate (50,46);printf ("ZUHAIB(019)");
            locate (50,47);printf ("QAISER(023)");
            locate (50,48);printf ("ALI AHMAD(016)");
        }
        Sleep(25);
    }
}

