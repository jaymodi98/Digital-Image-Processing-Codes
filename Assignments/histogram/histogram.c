/*
Author: Jay D. Modi
Assignment - 4
Q.3 Take any image as your input. Calculate its histogram and display it on GNU Plot.
*/
#include<stdio.h>
#include<math.h>
#include<fcntl.h>
#include<malloc.h>
#include <stdlib.h>

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

int main()
{
   //variable declarations
   int fp1;
   char input_1[100];
   unsigned char *image1;
   int npix,pix,nscan,scan;
   int hash[256];

   //filepointer
   FILE *fptr = fopen("histogram.txt", "w");

   //asking input image name
   printf("Give input image name: ");
   scanf("%s",input_1);

   //asking input image's size
   printf("Enter npix and nscan: ");
   scanf("%d%d",&npix,&nscan);

   //openning input image file in read-only mode
   fp1 = open(input_1,O_RDONLY);
   if(fp1<0)
   {
       printf("Error in opening %s image \n",input_1);
     exit(1);
   }
   printf("Input Image is %s npix nscan %d %d \n",input_1,npix,nscan);

   //allocate memory to image1
   image1 = (unsigned char *)calloc(npix,sizeof(unsigned char));

   //initialize hash array with 0 for all 256 values
   for (int i = 0; i < 256; ++i)
   {
   	hash[i]=0;
   }

   //start reading image
   for(scan=0;scan<nscan;scan++)
   {
    //read each row of image in image1
    read(fp1,image1,npix*sizeof(unsigned char));
    
    //for each value in image1, increase corrosponding hash value
    for(pix=0;pix<npix;pix++)
    {
      hash[image1[pix]]++;
    }
   }

   //write hash array's data to file 'histogram.txt'
   for (int i = 0; i < 256; ++i)
   {
   	fprintf(fptr, "%d %d\n",i,hash[i] );
   }
   
   //close both the files
   close(fp1);
   fclose(fptr);

   

}   