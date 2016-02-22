#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "pixy.h"

string itos(int number);

static bool run_flag = true;


//response to the action of CTRL+C, to abort the capturing application.
void handle_SIGINT(int unused)
{
  // On CTRL+C - abort //
  run_flag = false;
  printf("\nBye!\n");
  exit(0);
}

int main(int argc, char * argv[])
{

  if (argc != 3) {
        printf("usage: %s <port> <ip>\n", argv[0]);
        exit(1);  //terminate the program
    }

  int      index;
  int      blocks_copied;
  int      pixy_init_status;
  int      return_value;
  uint16_t major;
  uint16_t minor;
  uint16_t build;

   // getFrame Example //
  unsigned char *pixels;
  int32_t response, fourcc;
  int8_t renderflags;
  uint16_t width, height;
  uint32_t  numPixels;


  // Catch CTRL+C (SIGINT) signals //
  signal(SIGINT, handle_SIGINT);


  // Connect to Pixy //
  pixy_init_status = pixy_init();
  printf("initialized Pixy - %d\n", pixy_init_status);

  // Was there an error initializing pixy? //
  if(!pixy_init_status == 0)
  {
    // Error initializing Pixy //
    printf("pixy_init(): ");
    pixy_error(pixy_init_status);
    return pixy_init_status;
  }

    return_value=pixy_command("stop", END_OUT_ARGS, &response, END_IN_ARGS);
    printf("STOP returned %d reponse %d\n", return_value, response);

    response = 0;

   // display the whole block
   unsigned int i,j,ind;

   printf("Hello, Baoyou is here...");
   printf("Detecting blocks...\n");

   //int pixy_blocks_are_new()
   //returns:
   //1 New data: block data has been updated.
   //0 Stale data: block data has not changed since pixy_get_blocks() was last called.
  int frame=0;
  while(run_flag)
  {
       // Display received blocks //
       printf("frame %d:\n", frame);

       return_value = pixy_command("cam_getFrame",    // String id for remote procedure
                                 0x01, 0x21,       // mode
                                 0x02,   0,        // xoffset
                                 0x02,   0,        // yoffset
                                 0x02, 318,        // width
                                 0x02, 198,        // height
                                 0,                // separator
                                 &response,        // pointer to mem address for return value
                                 &fourcc,          //for some reason these 5 args are needed, contrary to the docs
                                 &renderflags,
                                 &width,
                                 &height,
                                 &numPixels,       //the total number of pixels=width*height
                                 &pixels,          // pointer to mem address for returned frame
                                 0);

      // check success:
      if (return_value)
      {
            // Error //
            pixy_error(return_value);
            return return_value;
      } else {
                if(frame==0)
                {
                printf("Pixy Firmware Version: %d.%d.%d\n", major, minor, build);
                fprintf(stderr,"getFrame return value %d response %d\n", return_value, response);
                printf("returned w %d h %d npix %d \n",width,height,numPixels);
                // Success //
                }
            }


//save the pixel value in the image to the image[frame].txt file.
unsigned ind;
ofstream myfile;
myfile.open("image"+itos(frame)+".txt");
if(myfile.is_open())
{
    for(unsigned i=0; i<198; i++)
    {
         for(unsigned j=0; j<318; j++)
         {
            ind=i*318+j;
            if(j==318)
              myfile<<pixel[ind];
            else
              myfile<<pixel[ind]<<",";
         }
         myfile<<";\n";
    }
    myfile.close();
}
else cout<<"Unable to open file";

/*
//save the pixel value in the image to matrix for futher processing.
unsigned ind;
matrix image(198,318);
for(unsigned i=0; i<198; i++)
{
    for(unsigned j=0; j<318; j++)
    {
        ind=i*318+j;
        image.setvalue(i,j,pixel[ind]);
    }
}

*/


//image processing section


//send the parameter to PC processing software, and display the result.


/*
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    portno=atoi(argv[2]);
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
         perror("ERROR opening socket");
    server=gethostbyname(argv[1]);
    if(server==NULL)
    {
       fprintf(stderr, "ERROR, no such host\n");
       exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port=htons(portno);
   if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
       perror("ERROR connecting");

   n=write(sockfd, "hello, CBY!", 12);
   if(n<0)
        perror("ERROR writing to socket");
   bzero(buffer, 256);
   n=read(sockfd, buffer, 255);
   if(n<0)
        perror("ERROR reading form socket");
   printf("%s\n",buffer);
   close(sockfd);
*/


  if(frame==30)
  {
    run_flag = false;
    printf("\ndone!\n");
    exit(0);
  }

  frame++;
  // Sleep for 1/10 sec //
  //while(1) usleep(100000);
  //(exit on ^C)
}
  pixy_close();
  return 0;
}











string itos(int number)
{
  ostringstream oss;
  oss<<number;
  return oss.str();

}