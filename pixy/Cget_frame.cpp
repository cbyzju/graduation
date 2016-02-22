#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "pixy.h" 
#include "tcpconnector.h"

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




//image processing section




//send the parameter to PC processing software, and display the result.
    int len;
    string message;
    char line[256];
    TCPConnector* connector = new TCPConnector();
    TCPStream* stream = connector->connect(argv[2], atoi(argv[1]));
    if (stream) {
        message = "Is there life on Mars?";
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        len = stream->receive(line, sizeof(line));
        line[len] = 0;
        printf("received - %s\n", line);
        delete stream;
    }




//FILE *fp;
//fp=fopen("image.txt","w");
//if(fp!=NULL)
//{
//store pixel for each frame into jpg or png.
//      fwrite(pixels,1,1,fp);
//       fclose(fp);
//}else perror("file allocation failure");


       
       if(frame==3)
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
}