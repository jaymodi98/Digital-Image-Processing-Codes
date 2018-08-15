/*
Author: Jay D. Modi
Assignment - 3
Q.1 Take the boat image as your input. Now, draw a circle on that image keeping the
centre of the image as the centre for the circle that you draw.
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
   int npix,pix,nscan,scan,i,j,radii,centx,centy,x,y;

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

   //asking for the radius of the circle to be drawn
   printf("Enter the radii of the circle: ");
   scanf("%d",&radii);

   //assuring that the user enters a valid radius
   while(radii>(min(nscan,npix)/2))
   {
      printf("Enter radii between 0 and %d: ",(min(nscan,npix)/2));
      scanf("%d",&radii);
   }

   //output image's name '<input_image_name>_circle(<radii>)_<npix>_<nscan>'
   sprintf(output,"%s_circle(%d)_%d_%d",input_1,radii,npix,nscan);

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
      //for each pixel,if that pixel falls on the circle, make it white
      if((x*x+y*y < (radii+1)*(radii+1)) && (x*x+y*y > (radii-1)*(radii-1))){
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