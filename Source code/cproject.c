#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char username[50],password[50],usernamepassword[100],datec[20],pickup[30],destination[30];
char type[30];
float bill_arr[15];
float *p=bill_arr;

void sign_up(FILE *signup,FILE *login);

void log_in(FILE *signup,FILE *login);

void log_ind(FILE *signup,FILE *login);

void after_signup(FILE *signup,FILE *login);

void settings(FILE *signup,FILE *login);

void activity(FILE *past,FILE *signup,FILE *login);

void pastrecord(char name_final[],float bill);

void advancebookings(FILE *signup,FILE *login);

void book(FILE *signup,FILE *login);

void booking(char type[],int p1,int p2,int d2,FILE *signup,FILE *login,float bill);

void confirmation(char name_final[],float max,FILE *signup,FILE *login,float bill);

void bill_payment(char name_final[],float bill);

void amount_ad(char pickup[],char destination[],float d2,float d3);

void amount(char pickup[],char destination[],int d2,int d3);

void ratings(char name_final[]);

struct past
{
    char history[30];
};

struct cars
{
    char modes[20];
    float cost;
};

struct map
{
    char place[50];
    int code;
};

int main()
{
    time_t t1;

    srand((unsigned) time(&t1));

    FILE *signup;
    FILE *login;

    printf("press 1 for signup\n");
    printf("press 2 for login\n");

    int register1=0;
    scanf("%d",&register1);

    if(register1==1)
    {
        sign_up(signup,login);
    }

    else if(register1==2)
    {
        log_ind(signup,login);
    }
    return 0;
}

void sign_up(FILE *signup,FILE *login)
{
    int c=0;

	printf("enter your username:");
	scanf("%s",username);

	printf("enter your password:");
	scanf("%s",password);

	signup=fopen("signup.txt","r");

	char line[100];
	if(signup==NULL)
    	{
        printf("sign up successful\n\n");
        printf("account created sucessfully\n\n");
        fclose(signup);

        signup=fopen("signup.txt","a");
        fprintf(signup,"%s\n",username);
        fclose(signup);

        login=fopen("login.txt","a");
        fprintf(login,"%s",username);
        fprintf(login,"%s\n",password);
        fclose(login);

        after_signup(signup,login);
    	}
    	else
    	{
        while (!feof(signup))
        {
            fscanf(signup,"%s",line);
            if (strcmp(line,username)==0)
            {
                c++;
            }
        }
        if(c==0)
        {
            printf("sign up successful\n\n");
            printf("account created sucessfully\n\n");
            fclose(signup);

            signup=fopen("signup.txt","a");
            fprintf(signup,"%s\n",username);
            fclose(signup);

            login=fopen("login.txt","a");
            fprintf(login,"%s",username);
            fprintf(login,"%s\n",password);
            fclose(login);
            after_signup(signup,login);
        }
        else
        {
            printf("already have account,login\n");
            log_in(signup,login);
        }
    }
}

void log_in(FILE *signup,FILE *login)
{
    int signup1=0,c=0,count=0,log=0;

    printf("press 1 to signup\n");
    printf("press 2 to login\n");
    scanf("%d",&signup1);

    if(signup1==1)
    {
        count++;
        sign_up(signup,login);
    }
    else if (signup1==2)
    {

        printf("enter your username:");
        scanf("%s",username);
        strcpy(usernamepassword,username);

        printf("enter your password:");
        scanf("%s",password);

        char line[50];

        signup=fopen("signup.txt","r");

	if(signup==NULL)
    	{
        	printf("user not found, sign up first\n");
       	 	log_in(signup,login);
    	}

        while(!feof(signup))
        {
            fscanf(signup,"%s",line);
            if (strcmp(line,username)==0)
            {
                log++;
            }
        }

        fclose(signup);


        strcat(usernamepassword,password);

        login=fopen("login.txt","r");

        char lines[100];

        if(log!=0)
        {
            while(!feof(login))
            {
                fscanf(login,"%s",lines);
                if (strcmp(lines,usernamepassword)==0)
                {
                    c++;
                }
            }
            fclose(login);

            if (c==0 && count==0)
            {
                printf("username and password don't match\n");
                log_in(signup,login);
            }

            else if (c!=0 && count==0)
            {
                printf("account logged in sucessfully\n\n");
			      after_signup(signup,login);
            }

        }
        else
        {
            printf("user not found,sign up first\n");
            log_in(signup,login);
        }
    }
}

void log_ind(FILE *signup,FILE *login)
{
    int count=0,c=0;

    printf("enter your username:");
    scanf("%s",username);
    strcpy(usernamepassword,username);

    printf("enter your password:");
    scanf("%s",password);

    signup=fopen("signup.txt","r");

    if(signup==NULL)
    {
        printf("user not found, sign up first\n");
        log_in(signup,login);
    }

    else
    {
        char lines[100];
        while (!feof(signup))
        {
            fscanf(signup,"%s",lines);
            if (strcmp(lines,username)==0)
            {
                count++;
            }
        }
    }
    fclose(signup);
    strcat(usernamepassword,password);
    login=fopen("login.txt","r");
    char line[100];

    if (count!=0)
    {
        while(!feof(login))
        {
            fscanf(login,"%s",line);
            if (strcmp(line,usernamepassword)==0)
            {
                c++;
            }
        }
        fclose(login);
        if (c!=0)
        {
            printf("logged in succesfully\n\n");
			  after_signup(signup,login);
        }
        else
        {
            printf("username and password don't match\n");
            log_in(signup,login);
        }
    }
    else
    {
        printf("user not found, sign up first\n");
        log_in(signup,login);
    }
}

void after_signup(FILE *signup,FILE *login)
{
	int home=0,point=0;

	FILE *past;

    printf("press 1 to go to settings\n");
    printf("press 2 to know your past activity\n");
    printf("press 3 to book a ride\n");
    printf("press 4 to know advance bookings\n");
    scanf("%d",&point);

		if (point==1)
        {
            settings(signup,login);
        }

		else if(point==2)
		{
			activity(past,signup,login);
		}
		else if(point==3)
        {
            book(signup,login);
        }
        else if(point==4)
        {
            advancebookings(signup,login);
        }
}

void settings(FILE *signup,FILE *login)
{
    int select;
    printf("press 1 to logout\n");
    printf("press 2 to go back\n");
    scanf("%d",&select);

    if(select==1)
    {
       log_in(signup,login);
    }

    else if(select==2)
    {
        after_signup(signup,login);
    }
}
void activity(FILE *past,FILE *signup,FILE *login)
{
	past=fopen("past.txt","r");
    char pastname[100];
    char date[20],time[20],start[20],end[20],driver[30],mode[30];
    float bill;
    struct past p[7];
    int count=0,next=0;

    strcpy(p[0].history,"Date:");
    strcpy(p[1].history,"Time:");
    strcpy(p[2].history,"Starting point:");
    strcpy(p[3].history,"Destination:");
    strcpy(p[4].history,"Driver:");
    strcpy(p[5].history,"Mode of travel:");
    strcpy(p[6].history,"Bill:");

	if(past==NULL)
	{
		printf("No records found\n");
	}

	else
	{
        while (fscanf(past,"%s %s %s %s %s %s %s %f",pastname,date,time,start,end,driver,mode,&bill)!=EOF)
        {
            if(strcmp(pastname,username)==0)
            {
                count++;
                printf("%s %s\n",p[0].history,date);
                printf("%s %s\n",p[1].history,time);
                printf("%s %s\n",p[2].history,start);
                printf("%s %s\n",p[3].history,end);
                printf("%s %s\n",p[4].history,driver);
                printf("%s %s\n",p[5].history,mode);
                printf("%s %f\n\n\n",p[6].history,bill);
            }
        }
        if(count==0)
        {
            printf("No records found\n");
        }
     }

     printf("press 1 to go back\n");
     printf("press 2 to close\n");
     scanf("%d",&next);

     if(next==1)
     {
         after_signup(signup,login);
     }

     else if(next==2)
     {
         exit(1);
     }
}

void advancebookings(FILE *signup,FILE *login)
{
    FILE *advance;
    int count=0,next=0;

    char namead[30],datead[20],timead[20],pickad[20],destad[20],mode[20];
    float d2ad,d3ad,billad;
    int modead;


    advance=fopen("advancebookings.txt","r");

    while(fscanf(advance,"%s %s %s %f %f %s %s %d %f",namead,datead,timead,&d2ad,&d3ad,pickad,destad,&modead,&billad)!=EOF)
    {
        if(modead==3)
        {
            strcpy(mode,"bike");
        }

        else if(modead==4)
        {
            strcpy(mode,"auto");
        }

        else if(modead==5)
        {
            strcpy(mode,"minisedan");
        }

        else if(modead==6)
        {
            strcpy(mode,"sedan");
        }

        else if(modead==7)
        {
            strcpy(mode,"SUV");
        }

        else if(modead==8)
        {
            strcpy(mode,"innova");
        }

        else if(modead==9)
        {
            strcpy(mode,"luxury");
        }
        if(strcmp(username,namead)==0)
        {
            count++;
            printf("Date:%s\n",datead);
            printf("Time:%s\n",timead);
            printf("Pickup:%s\n",pickad);
            printf("Destination:%s\n",destad);
            printf("Mode of travel:%s\n",mode);
            printf("Predicted bill:%f\n\n",billad);
        }
    }

    if(count==0)
    {
        printf("No advance bookings\n");
    }

    printf("press 1 to go back\n");
    printf("press 2 to close\n");
    scanf("%d",&next);

    if(next==1)
    {
        after_signup(signup,login);
    }

    else if(next==2)
    {
        exit(1);
    }
}

void book(FILE *signup,FILE *login)
{
    FILE *advance;
    FILE *mappp;

    struct map m[15];
    int ride,mode,confirm,p1,p2,c1,c2,d1,next;
    float d2,d3;
    float bill;
    float bill1;

    char date[20],time[20];

    printf("            9\n");
    printf("            |\n");
    printf("            |\n");
    printf("            |\n");
    printf("10----------7--------------8\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("11----------6      5\n");
    printf("|           |      |\n");
    printf("|           |      |\n");
    printf("|           |      |\n");
    printf("|           |      |\n");
    printf("12----------1------4\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           2\n");
    printf("13          |\n");
    printf("            |\n");
    printf("            3\n\n\n\n");

    for(int i=1;i<14;i++)
    {
        m[i-1].code=i;
    }

    strcpy(m[0].place,"kelambakkam");
    strcpy(m[1].place,"SSN");
    strcpy(m[2].place,"thiruporur");
    strcpy(m[3].place,"kovalam");
    strcpy(m[4].place,"ECR");
    strcpy(m[5].place,"sholinganallur");
    strcpy(m[6].place,"koyambedu");
    strcpy(m[7].place,"chennaicentral");
    strcpy(m[8].place,"annanagar");
    strcpy(m[9].place,"chromepet");
    strcpy(m[10].place,"tambaram");
    strcpy(m[11].place,"vandalur");
    strcpy(m[12].place,"kattankulathur");

    printf("Place code and Place\n");

    for(int j=0;j<13;j++)
    {
        printf("%d   %s\n",m[j].code,m[j].place);
    }

    printf("nearby places/connected points\n");
    printf("1-2\n2-3\n1-4\n4-5\n1-6\n6-7\n7-8\n7-9\n7-10\n10-11\n11-12\n12-13\n\n");

    mappp=fopen("mapp.txt","r");

    while(fscanf(mappp,"%d %d %d",&c1,&c2,&d1)!=EOF)
    {
        printf("Distance between the points %d and %d is %d Kms\n",c1,c2,d1);
    }
    printf("\n\n");


    printf("press 1 to book in advance\n");
    printf("press 2 for instant ride\n");

    scanf("%d",&ride);


    if (ride==1)
    {
        printf("enter the date(dd/mm/yyyy) of your ride:");
        scanf("%s",&date);

        printf("enter the time(hh:mm) of your ride:");
        scanf("%s",&time);

        printf("Around which region you want the driver to pick you up(code)(leavingplacecode headingplacecode):");
        scanf("%d %d",&p1,&p2);

        printf("how far you want the pick up from the point %d:",p1);
        scanf("%f",&d2);


        printf("enter the pick up point(leavingplace):");
        scanf("%s",pickup);

        printf("enter your destination(place):");
        scanf("%s",destination);

        printf("how far you want the drop from destination: ");
        scanf("%f",&d3);

        amount_ad(pickup,destination,d2,d3);

        printf("press 1 to continue booking\n");
        printf("press 2 to go to homepage\n");
        scanf("%d",&next);

        if(next==1)
        {
            printf("select your mode of travel\n\n\n");
            printf("press 3 for bike\n");
            printf("press 4 for auto\n");
            printf("press 5 for mini sedan\n");
            printf("press 6 for sedan\n");
            printf("press 7 for SUV\n");
            printf("press 8 for innova\n");
            printf("press 9 for luxury car\n");
            scanf("%d",&mode);
        }

        else if(next==2)
        {
            after_signup(signup,login);
        }


        printf("press 0 to confirm your booking\n");
        printf("press 1 to go to homepage\n");
        scanf("%d",&confirm);


        advance=fopen("advancebookings.txt","a");
        if(confirm==0)
        {
            fprintf(advance,"%s ",username);
            fprintf(advance,"%s ",date);
            fprintf(advance,"%s ",time);
            fprintf(advance,"%d ",p1);
            fprintf(advance,"%d ",p2);
            fprintf(advance,"%s ",pickup);
            fprintf(advance,"%s ",destination);
            fprintf(advance,"%d ",mode);
            for(int i=0;i<7;i++)
            {
                if((i+3)==mode)
                {
                    fprintf(advance,"%f\n",*(p+i));
                }
            }
            fclose(advance);
        }

        else if(confirm==1)
        {
            after_signup(signup,login);
        }
    }

    else if(ride==2)
    {
        printf("Around which region you want the driver to pick you up(code)(leavingplacecode headingplacecode):");
        scanf("%d %d",&p1,&p2);

        printf("how far you want the pick up from the point %d:",p1);
        scanf("%f",&d2);


        printf("enter the pick up point(leavingplace):");
        scanf("%s",pickup);

        printf("enter your destination(place):");
        scanf("%s",destination);

        printf("how far you want the drop from destination: ");
        scanf("%f",&d3);

        amount(pickup,destination,d2,d3);

        printf("press 1 to continue booking\n");
        printf("press 2 to go to homepage\n");
        scanf("%d",&next);

        if(next==1)
        {
            printf("select your mode of travel\n\n\n");
            printf("press 3 for bike\n");
            printf("press 4 for auto\n");
            printf("press 5 for mini sedan\n");
            printf("press 6 for sedan\n");
            printf("press 7 for SUV\n");
            printf("press 8 for innova\n");
            printf("press 9 for luxury car\n");
            scanf("%d",&mode);
        }

        else if(next==2)
        {
            after_signup(signup,login);
        }



        if(mode==3)
        {
            //printf("%f\n",bill_arr[0]);
            bill=bill_arr[0];
            strcpy(type,"bike");

            booking(type,p1,p2,d2,signup,login,bill);
        }

        else if(mode==4)
        {
            //printf("%f\n",bill_arr[1]);
            bill=bill_arr[1];
            strcpy(type,"auto");

            booking(type,p1,p2,d2,signup,login,bill);
        }

        else if(mode==5)
        {
            //printf("%f\n",bill_arr[2]);
            bill=bill_arr[2];
            strcpy(type,"minisedan");

            booking(type,p1,p2,d2,signup,login,bill);
        }

        else if(mode==6)
        {
            //printf("%f\n",bill_arr[3]);
            bill=bill_arr[3];
            strcpy(type,"sedan");

            booking(type,p1,p2,d2,signup,login,bill);
        }
        else if(mode==7)
        {
            //printf("%f\n",bill_arr[4]);
            bill=bill_arr[4];
            strcpy(type,"SUV");

            booking(type,p1,p2,d2,signup,login,bill);
        }

        else if(mode==8)
        {
            //printf("%f\n",bill_arr[5]);
            bill=bill_arr[5];
            strcpy(type,"innova");

            booking(type,p1,p2,d2,signup,login,bill);
        }

        else if(mode==9)
        {
            //printf("%f\n",bill_arr[6]);
            bill=bill_arr[6];
            strcpy(type,"luxury");

            booking(type,p1,p2,d2,signup,login,bill);
        }
    }
}

void pastrecord(char name_final[],float bill)
{
    FILE *past;
    FILE *date;
    char date1[20],time1[20];

    past=fopen("past.txt","a");
    date=fopen("date.txt","r");

    fscanf(date,"%s %s",date1,time1);

    fclose(date);

    fprintf(past,"%s %s %s %s %s %s %s %f\n",username,date1,time1,pickup,destination,name_final,type,bill);
    fclose(past);


}

void booking(char type[],int p1,int p2,int d2,FILE *signup,FILE *login,float bill)
{
    FILE *overallrating;
    FILE* drivermapp;
    FILE *samedistance;

    int confirm;

    char name[30],category[30],category1[30],driver[30],drivername[30],minname[30];
    char name_final[30];
    float rating,max,dr1,dr2,r1,r2,t,count=0;
    float min;
    drivermapp=fopen("drivermap.txt","r");
    while(fscanf(drivermapp,"%s %s %f %f %f %f %f",drivername,category1,&r1,&r2,&dr1,&t,&dr2)!=EOF)
    {
        if(strcmp(category1,type)==0 && ((r1==p1&&r2==p2)||(r1==p2 && r2==p1)))
        {
            count++;
            if(p1==r1)
            {
                if(d2>dr1)
                {
                    min=d2-dr1;
                }
                else if(dr1>d2)
                {
                    min=dr1-d2;
                }
                else
                {
                    min=dr1-d2;
                }
            }

            else if(p1==r2)
            {
                if(d2>dr2)
                {
                    min=d2-dr2;
                }
                else if(dr2>d2)
                {
                    min=dr2-d2;
                }
                else
                {
                    min=dr2-d2;
                }
            }
            break;
        }

    }
            //printf("%f\n",min);
            if(count==0)
            {
                printf("Drivers not found\n");
                printf("Please try again\n\n\n");
                book(signup,login);
            }
            fclose(drivermapp);

            drivermapp=fopen("drivermap.txt","r");

            while(fscanf(drivermapp,"%s %s %f %f %f %f %f",drivername,category1,&r1,&r2,&dr1,&t,&dr2)!=EOF)
            {
                if(strcmp(category1,type)==0 && ((r1==p1&&r2==p2)||(r1==p2 && r2==p1)))
                {
                    if(p1==r1)
                    {
                        if(d2>dr1)
                        {
                            if(d2-dr1<min)
                            {
                                min=d2-dr1;
                            }

                        }

                        else if(dr1>d2)
                        {
                            if(dr1-d2<min)
                            {
                                min=dr1-d2;
                            }
                        }
                        else
                        {
                            if(dr1-d2<min)
                            {
                                min=dr1-d2;
                            }
                        }
                    }

                    else if(p1==r2)
                    {
                         if(d2>dr2)
                        {
                            if(d2-dr2<min)
                            {
                                min=d2-dr2;
                            }

                        }

                        else if(dr2>d2)
                        {
                            if(dr2-d2<min)
                            {
                                min=dr2-d2;
                            }
                        }
                        else
                        {
                            if(dr2-d2<min)
                            {
                                min=dr2-d2;
                            }
                        }
                    }
                }
            }

            fclose(drivermapp);

            //printf("%f\n",min);

            drivermapp=fopen("drivermap.txt","r");
            samedistance=fopen("minimumdistance.txt","w");

            while(fscanf(drivermapp,"%s %s %f %f %f %f %f",drivername,category1,&r1,&r2,&dr1,&t,&dr2)!=EOF)
            {
                if(strcmp(category1,type)==0 && ((r1==p1&&r2==p2)||(r1==p2 && r2==p1)))
                {
                    if(p1==r1)
                    {
                        if(dr1>d2)
                        {
                            if(dr1-d2==min)
                            {
                                fprintf(samedistance,"%s\n",drivername);
                                //printf("%s\n",drivername);
                            }
                        }

                        else if(d2>dr1)
                        {
                            if(d2-dr1==min)
                            {
                                fprintf(samedistance,"%s\n",drivername);
                                //printf("%s\n",drivername);
                            }
                        }
                        else if(d2==dr1)
                        {
                            if(d2-dr1==min)
                            {
                                fprintf(samedistance,"%s\n",drivername);
                                //printf("%s\n",drivername);
                            }
                        }
                    }

                    else if(p1==r2)
                    {
                        if(dr2>d2)
                        {
                            if(dr2-d2==min)
                            {
                                fprintf(samedistance,"%s\n",drivername);
                                //printf("%s\n",drivername);
                            }
                        }

                        else if(d2>dr2)
                        {
                            if(d2-dr2==min)
                            {
                                fprintf(samedistance,"%s\n",drivername);
                                //printf("%s\n",drivername);
                            }
                        }
                        else if(d2==dr2)
                        {
                            if(d2-dr2==min)
                            {
                                fprintf(samedistance,"%s\n",drivername);
                                //printf("%s\n",drivername);
                            }
                        }
                    }
                }
            }
            fclose(drivermapp);
            fclose(samedistance);
            samedistance=fopen("minimumdistance.txt","r");

            while(fscanf(samedistance,"%s",minname)!=EOF)
            {
                overallrating=fopen("ratingsfinal.txt","r");
                while(fscanf(overallrating,"%s %s %f",name,category,&rating)!=EOF)
                {
                    if(strcmp(minname,name)==0)
                    {
                        max=rating;
                        break;
                    }
                }
                fclose(overallrating);
                break;
            }
            fclose(samedistance);
            fclose(overallrating);
            //printf("%f\n",max);

            samedistance=fopen("minimumdistance.txt","r");

            while(fscanf(samedistance,"%s",minname)!=EOF)
            {
                overallrating=fopen("ratingsfinal.txt","r");
                while(fscanf(overallrating,"%s %s %f",name,category,&rating)!=EOF)
                {
                    if(strcmp(minname,name)==0)
                    {
                        if(rating>max)
                        {
                           max=rating;

                        }
                    }
                }
                fclose(overallrating);
            }
            fclose(samedistance);
            fclose(overallrating);

            //printf("%f\n",max);

            samedistance=fopen("minimumdistance.txt","r");

            while(fscanf(samedistance,"%s",minname)!=EOF)
            {
                overallrating=fopen("ratingsfinal.txt","r");
                while(fscanf(overallrating,"%s %s %f",name,category,&rating)!=EOF)
                {
                    if(strcmp(minname,name)==0)
                    {
                        if(max==rating)
                        {
                            //printf("%s\n",name);
                            strcpy(name_final,name);
                        }

                    }
                }
                fclose(overallrating);
            }
            fclose(samedistance);
            fclose(overallrating);

            printf("sending notification to driver\n\n\n");
            sleep(5);

            confirmation(name_final,max,signup,login,bill);
}

void confirmation(char name_final[],float max,FILE *signup,FILE *login,float bill)
{
    FILE *cancelss;
    int conf;
    int cancel;
    char name1[30];
    FILE *temp;
    printf("Your ride is booked successfully\n\n\n");
    printf("Driver name: %s\n",name_final);
    printf("Ratings: %f\n\n\n",max);

    printf("press 1 to confirm your ride\n");
    printf("press 2 to cancel the ride\n");

    scanf("%d",&conf);

    if(conf==1)
    {
        printf("Ride starts\n");
        temp=fopen("temp.txt","w");
        cancelss=fopen("cancels.txt","r");

        while(fscanf(cancelss,"%s",name1)!=EOF)
        {
            if(strcmp(name1,username)!=0)
            {
                fprintf(temp,"%s\n",name1);
            }

            else
            {
                continue;
            }
        }

        fclose(cancelss);
        fclose(temp);

        remove("cancels.txt");
        rename("temp.txt","cancels.txt");
        sleep(5);
        printf("Your destination is reached\n\n\n");
        bill_payment(name_final,bill);
    }

    else if(conf==2)
    {
        cancelss=fopen("cancels.txt","a");
        fprintf(cancelss,"%s\n",username);
        fclose(cancelss);
        printf("press 1 to close\n");
        printf("press 2 to go to homepage\n");
        scanf("%d",&cancel);

        if(cancel==1)
        {
            exit(1);
        }

        else if(cancel==2)
        {
            after_signup(signup,login);
        }
    }
}

void bill_payment(char name_final[],float bill)
{
    FILE *ride;
    FILE *temp;
    char user[30],name[30];
    int count=0;
    float bill_final,points,point,sumpoints=0,billwrite;
    int next;

    ride=fopen("rides.txt","r");
    while(fscanf(ride,"%s %f",user,&points)!=EOF)
    {
        if(strcmp(user,username)==0)
        {
            count++;
            sumpoints=sumpoints+points;
        }
    }
    fclose(ride);

    if(count!=0)
    {

        printf("Your ride history shows previous bookings\n\n");
        printf("You will be discounted for it\n\n\n");
        bill_final=bill-(sumpoints);

        temp=fopen("temp.txt","w");
        ride=fopen("rides.txt","r");

        while(fscanf(ride,"%s %f",name,&point)!=EOF)
        {
            if(strcmp(name,username)!=0)
            {
                fprintf(temp,"%s ",name);
                fprintf(temp,"%f\n",point);
            }

            else
            {
                continue;
            }
        }

        fclose(ride);
        fclose(temp);

        remove("rides.txt");
        rename("temp.txt","rides.txt");

        printf("Bill: %f\n",bill_final);

        printf("press 1 to pay through online\n");
        printf("press 2 to pay with cash\n");

        scanf("%d",&next);

        if(next==1)
        {
            printf("BILL paid sucessfully through online\n\n");
        }

        else if(next==2)
        {
            printf("BILL paid successfully by cash\n\n");
        }

        pastrecord(name_final,bill_final);
    }

    else
    {
        bill_final=bill;
        printf("Bill: %f\n",bill_final);

        printf("press 1 to pay through online\n");
        printf("press 2 to pay with cash\n");

        scanf("%d",&next);

        if(next==1)
        {
            printf("BILL paid sucessfully through online\n\n\n");
        }

        else if(next==2)
        {
            printf("BILL paid successfully by cash\n\n\n");
        }
        pastrecord(name_final,bill_final);
    }

    billwrite=(bill_final)*0.05;

    ride=fopen("rides.txt","a");
    fprintf(ride,"%s ",username);
    fprintf(ride,"%f\n",billwrite);
    fclose(ride);

    ratings(name_final);
}

void amount_ad(char pickup[],char destination[],float d2,float d3)
{
    FILE *distancecalc;
    FILE *cancelss;
    FILE *temp;

    char start[30],end[30];
    float distance=0,rate=3,price,distance0;

    float fixed=15;
    float surge;
    float total;
    float advance=10;
    int random;
    int count;
    char users[30],name1[30];
    struct cars c[7];

    strcpy(c[0].modes,"Bike");
    strcpy(c[1].modes,"Auto");
    strcpy(c[2].modes,"Mini sedan");
    strcpy(c[3].modes,"Sedan");
    strcpy(c[4].modes,"SUV");
    strcpy(c[5].modes,"Innova");
    strcpy(c[6].modes,"Luxury car");

    c[0].cost=10;
    c[1].cost=20;
    c[2].cost=30;
    c[3].cost=35;
    c[4].cost=45;
    c[5].cost=60;
    c[6].cost=75;

    distancecalc=fopen("distance.txt","r");

    while(fscanf(distancecalc,"%s %s %f",start,end,&distance0)!=EOF)
    {
        if(strcmp(pickup,start)==0||strcmp(pickup,end)==0)
        {
            if(strcmp(destination,end)==0 || strcmp(destination,start)==0)
            {
                distance=distance0;
            }
        }
    }
    distance=distance-d2-d3;
    fclose(distancecalc);
    printf("calculated distance %f\n\n\n",distance);
    surge=5+(distance*2);
    random=rand()%2+1;


    if (random==1)
    {
        printf("no surge\n\n");
        price=fixed+(distance*rate);
    }

    if(random==2)
    {
        printf("surge\n\n");
        price=fixed+surge+(distance*rate);

    }

    cancelss=fopen("cancels.txt","r");

    while(fscanf(cancelss,"%s",users)!=EOF)
    {
        if(strcmp(users,username)==0)
        {
            count++;
        }
    }
    fclose(cancelss);

    if(count!=0)
    {
        printf("You have cancelled previous orders %d times\n",count);
        printf("You will be charged for that\n\n");

        printf("Car category and its cost of travel\n\n");
        fclose(cancelss);

        for(int i=0;i<7;i++)
        {
            total=c[i].cost+price+(count*10);
            *(p+i)=total+advance;
            printf("%s-%f\n",c[i].modes,*(p+i));
        }
    }

    else
    {
        printf("Car category and its cost of travel\n\n");
        for(int i=0;i<7;i++)
        {
            total=c[i].cost+price;
            *(p+i)=total+advance;
            printf("%s-%f\n",c[i].modes,*(p+i));
        }
    }
}

void amount(char pickup[],char destination[],int d2,int d3)
{
    FILE *distancecalc;
    FILE *cancelss;
    FILE *temp;
    char start[30],end[30];
    float distance=0,rate=3,price,distance0;

    float fixed=15;
    float surge;
    float total;
    int random;
    int count;
    char users[30],name1[30];
    struct cars c[7];

    strcpy(c[0].modes,"Bike");
    strcpy(c[1].modes,"Auto");
    strcpy(c[2].modes,"Mini sedan");
    strcpy(c[3].modes,"Sedan");
    strcpy(c[4].modes,"SUV");
    strcpy(c[5].modes,"Innova");
    strcpy(c[6].modes,"Luxury car");

    c[0].cost=10;
    c[1].cost=20;
    c[2].cost=30;
    c[3].cost=35;
    c[4].cost=45;
    c[5].cost=60;
    c[6].cost=75;

    distancecalc=fopen("distance.txt","r");

    while(fscanf(distancecalc,"%s %s %f",start,end,&distance0)!=EOF)
    {
        if(strcmp(pickup,start)==0||strcmp(pickup,end)==0)
        {
            if(strcmp(destination,end)==0 || strcmp(destination,start)==0)
            {
                distance=distance0;
            }
        }
    }
    distance=distance-d2-d3;
    fclose(distancecalc);
    printf("calculated distance %f\n\n\n",distance);
    surge=5+distance*2;


    random=rand()%2+1;


    if (random==1)
    {
        printf("no surge\n\n");
        price=fixed+distance*rate;
    }

    if(random==2)
    {
        printf("surge\n\n");
        price=fixed+surge+distance*rate;

    }

    cancelss=fopen("cancels.txt","r");

    while(fscanf(cancelss,"%s",users)!=EOF)
    {
        if(strcmp(users,username)==0)
        {
            count++;
        }
    }
    fclose(cancelss);

    if(count!=0)
    {
        printf("You have cancelled previous orders %d times\n",count);
        printf("You will be charged for that\n\n");

        printf("Car category and its cost of travel\n\n\n");
        fclose(cancelss);

        for(int i=0;i<7;i++)
        {
            total=c[i].cost+price+(count*10);
            bill_arr[i]=total;
            printf("%s-%f\n",c[i].modes,total);
        }
    }

    else
    {
        printf("Car category and its cost of travel\n\n\n");
        for(int i=0;i<7;i++)
        {
            total=c[i].cost+price;
            bill_arr[i]=total;
            printf("%s-%f\n",c[i].modes,total);
        }
    }

}

void ratings(char name_final[])
{
    FILE *allrating;
    FILE *overallrating;
    FILE *temp;
    float newrating=0,newratinginput=0,rating1=0;
    char name[50],name1[50],category[30];
    float ratingsum=0,calcrating=0;
    int count=0;
    int stop=0;

    printf("Do you want to rate the driver?\n\n");

    printf("press 1 if you don't want to rate the driver\n");
    printf("press 2 if you want to rate the driver\n");
    scanf("%d",&stop);

    if(stop==1)
    {
        exit(1);
    }

    else if(stop==2)
    {
        printf("enter your rating for the driver(0-5):");
        scanf("%f",&newratinginput);
    }


    allrating=fopen("eachratings.txt","a");
    fprintf(allrating,"%s",name_final);
    fprintf(allrating," %f\n",newratinginput);
    fclose(allrating);

    allrating=fopen("eachratings.txt","r");

    while(fscanf(allrating,"%s %f",name,&newrating)!=EOF)
    {
        if(strcmp(name,name_final)==0)
        {
            count++;
            ratingsum+=newrating;
        }
    }

    calcrating=ratingsum/count;
    printf("new calculated rating for the driver %f\n\n",calcrating);

    overallrating=fopen("ratingsfinal.txt","r+");
    temp=fopen("temporary.txt","w");


    while(fscanf(overallrating,"%s %s %f",name1,category,&rating1)!=EOF)
    {
        if(strcmp(name1,name_final)==0)
        {
            fprintf(temp,"%s ",name1);
            fprintf(temp,"%s ",category);
            fprintf(temp,"%f\n",calcrating);
        }

        else
        {
            fprintf(temp,"%s ",name1);
            fprintf(temp,"%s ",category);
            fprintf(temp,"%f\n",rating1);
        }
    }

    fclose(allrating);
    fclose(overallrating);
    fclose(temp);

    remove("ratingsfinal.txt");
    rename("temporary.txt","ratingsfinal.txt");

}
