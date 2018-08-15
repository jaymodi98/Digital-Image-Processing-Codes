/*
Author: Jay D. Modi
Assignment - 3
Q.2 Take the boat image as your input. Now, draw and fill an ellipse on that image,
keeping the centre of the image as the centre for the ellipse that you draw.
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
   int fp1,fp2;
   char input_1[100],output[100];
   unsigned char *image1;
   int npix,pix,nscan,scan,i,j,major,minor,centx,centy,x,y;

   //asking input image name
   printf("Give input image name: ");
   scanf("%s",input_1);

   //asking input image size
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

   //asking for the major axis of ellipse to be drawn
   printf("Enter the major axis of the ellipse: ");
   scanf("%d",&major);

   //assuring that the user enters a valid major axis
   while(major>(min(nscan,npix)/2))
   {
      printf("Enter major axix between 0 and %d: ",(min(nscan,npix)/2));
      scanf("%d",&major);
   }

   //asking for the major axis of ellipse to be drawn
   printf("Enter the minor axis of the ellipse: ");
   scanf("%d",&minor);

   //assuring that the user enters a valid major axis
   while(minor>(min(nscan,npix)/2))
   {
      printf("Enter minor axix between 0 and %d: ",(min(nscan,npix)/2));
      scanf("%d",&minor);
   }

   //output image's name '<input_image_name>_ellipse(<major_axis>,<minor_axis>)_<npix>_<nscan>'
   sprintf(output,"%s_ellipse(%d,%d)_%d_%d",input_1,major,minor,npix,nscan);

   //creating output image file in write mode
   fp2 = creat(output,0667);
   if(fp2<0)
   {
       printf("Error in opening %s image \n",output);
     exit(1);
   }

   //finding center of the image
   centx=(npix+1)/2;
   centy=(nscan+1)/2;

   //allocating memory to image1
   image1 = (unsigned char *)calloc(npix,sizeof(unsigned char));
   for(scan=0;scan<nscan;scan++)
   {
    //read each row of image
    read(fp1,image1,npix*sizeof(unsigned char));
    for(pix=0;pix<npix;pix++)
    {
      x=pix-centx;
      y=scan-centy;
      //for each pixel,if that pixel falls inside the ellipse, make it white
      if(((float)x*x)/(major*major)+((float)y*y)/(minor*minor)<=1){
        image1[pix]=255;
      }
    }
     //write each row in the output image file
     write(fp2,image1,npix*sizeof(unsigned char)); 

   }
   //close both the files
   close(fp1);
   close(fp2);

   

}   