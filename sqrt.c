/****************************************************
 * @author - John Sunday(AKA jscriptural);          *
 * @email - isonguyojohndeveloper@gmail.com         *
 * @file sqrt.c                                     *
 * @brief Return squareroot of a non-negative  num  *
 * **************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define EPSILON_1 1e-1
#define EPSILON_2 1e-2
#define EPSILON_3 1e-3
#define EPSILON_4 1e-4
#define EPSILON_5 1e-5
#define EPSILON_6 1e-6
#define EPSILON_7 1e-7
#define EPSILON_8 1e-8
#define EPSILON_9 1e-9
#define EPSILON_10 1e-10
#define EPSILON_11 1e-11
#define EPSILON_12 1e-12
#define EPSILON_13 1e-13
#define EPSILON_14 1e-14
#define EPSILON_15 1e-15

#define THRESHOLD 100000000
#define ABS(x) ((x) < 0? (-1*(x)): (x))

double to_fixed(double num,size_t dp);
static void die(char *errmsg, int print_usage);

double sqroot(double num, int eps)
{
  if(eps  <  1 || eps  >  15)
    die("INVALID OPTION VALUE",1);

  double x = 4;
  double epsilon;
  switch(eps)
  {
    case 1:epsilon = EPSILON_1;break;
    case 2:epsilon = EPSILON_2;break;
    case 3: epsilon = EPSILON_3; break;
    case 4: epsilon = EPSILON_4; break;
    case 5: epsilon = EPSILON_5; break;
    case 6: epsilon = EPSILON_6; break;
    case 7: epsilon = EPSILON_7; break;
    case 8: epsilon = EPSILON_8; break; 
    case 9: epsilon = EPSILON_9; break;
    case 10: epsilon = EPSILON_10; break;
    case 11: epsilon = EPSILON_11; break;
    case 12: epsilon = EPSILON_12; break;
    case 13: epsilon = EPSILON_13; break;
    case 14: epsilon = EPSILON_14; break;
    case 15: epsilon = EPSILON_15; break; 
  }


  long i=0;
  while(1)
  {
    double y = x*x - num;
    double d = 2*x;
    x -= (y/d);
    ++i;
    if(ABS((x*x-num)) < epsilon)
      break;
    if( i > THRESHOLD)
      break;
  }

  //printf("iterarions: %ld\n",i);
  return to_fixed(x,eps);
}






int main(int argc, char *argv[])
{
  setvbuf(stdout,NULL,_IONBF,0);
  setvbuf(stderr,NULL,_IONBF,0);
  setvbuf(stdin,NULL,_IONBF,0);

  if(argc < 2)
    die("ARGUMENT REQUIRED",1);

  char *endptr = NULL;
  int eps = 6;
  double num =0;

  if(strcmp(argv[1],"-d"))
  {
     errno = 0;
     num = strtod(argv[1],&endptr);
     if(strcmp(endptr,""))
       die("INVALID ARGUMENT",1);
     else if( errno != 0)
       die(strerror(errno),0);
     else if(argc >= 4)
     {

       if(!strcmp(argv[2],"-d"))
       {
	 endptr = NULL;
	 eps = (int) strtod(argv[3],&endptr);
	 if(strcmp(endptr,""))
	   die("INVALID OPTION VALUE",1);
	 else if( errno != 0)
	   die(strerror(errno),0);
       }
       else
	 die("UNKNOWN OPTION",1);
     }

  }
  else
  {
    errno = 0;
    if(argc < 4)
      die("INVALID ARGUMENT",1);

     eps  = (int) strtod(argv[2],&endptr);
     if(strcmp(endptr,""))
       die("INVALID OPTION VALUE",1);
     else if( errno != 0)
       die(strerror(errno),0);
     else
     {
       endptr = NULL;
       num = strtod(argv[3],&endptr);
       if(strcmp(endptr,""))
	 die("INVALID ARGUMENT",1);
     }
  }
  
  num = ABS(num);
  double root;
  if(num ==  0 || num == 1)
    root = num;
  else
    root = sqroot(num, eps);

   printf("%.16g\n",root);

  exit(0);
}






static void die(char *errmsg, int print_usage)
{
  fprintf(stderr,"\033[1;31merror:\033[0m%s\n",errmsg);
  if(print_usage)
  {
    fprintf(stderr,"USAGE: sqrt <num> [-d epsilon]\n");
    fprintf(stderr,"where: \n\tnum - (Compulsory) The number whose square root is required.\n");
    fprintf(stderr,"\t-d <epsilon> - (optional) Accuracy to <epsilon> decimal places. <epsilon> must  be an integer  between 0 and 15(both inclusive).\n");
  }
  exit(1);
}


double to_fixed(double num,size_t dp)
{
  double retval;
  
  size_t ind;
  char *num_str = calloc(100,sizeof(char));
  snprintf(num_str,100,"%.18lf",num);
  ind = strcspn(num_str,".");
  num_str[dp+ind+1] = '\0';
  retval = strtod(num_str,NULL);
  
  free(num_str);
  return retval;
}

