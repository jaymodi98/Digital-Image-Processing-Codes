/*
Author: Jay D. Modi
Assignment - 4
Q.2 Shear an image. Take any image and the shearing angle as an input. Your output
should be the sheared version of the input image.
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
  //variable declaration
   int fp1,fp2;
   float theta,deg;
   char input_1[100],output[100],hv;
   unsigned char *image1;
   int npix,pix,nscan,scan,i,j,npix_new,start;

   //asking input image name
   printf("Give input image name: ");
   scanf("%s",input_1);

   //asking input image's dimensions
   printf("Enter npix and nscan: ");
   scanf("%d%d",&npix,&nscan);

   //open input image file in read-only mode
   fp1 = open(input_1,O_RDONLY);
   if(fp1<0)
   {
       printf("Error in opening %s image \n",input_1);
     exit(1);
   }
   printf("Input Image is %s npix nscan %d %d \n",input_1,npix,nscan);

   //asking angle of shear
   printf("Enter theta: ");
   scanf("%f",&theta);
   //store angle in degrees
   deg=theta;
   //convert angle into radians
   theta=((((float)22.0)/7)*theta)/180;   

   //calculate new npix value
   npix_new=npix+fabs(nscan*tan(theta));
  
   //output image's name '<input_image_name>_shear(<angle_of_shear>)_<new_npix>_<nscan>'
   sprintf(output,"%s_shear(%f)_%d_%d",input_1,deg,npix_new,nscan);

   //creating output image file in write mode
   fp2 = creat(output,0667);
   if(fp2<0)
   {
       printf("Error in opening %s image \n",output);
     exit(1);
   }

   //allocate memory to image1
   image1 = (unsigned char *)calloc(npix_new,sizeof(unsigned char));
   for(scan=0;scan<nscan;scan++)
   {
    //calculating the point from which our image will start for any particular scan value
    start=(nscan-scan)*tan(theta);
    if(theta<0) start=fabs(nscan*tan(theta))+start;
    
    //initial parts fill with zero
    for(int i=0;i<start;i++)
      image1[i]=0;
    //read a row in image1
    read(fp1,&image1[start],npix*sizeof(unsigned char));
    //fill later part with zero
    for(int i=start+npix;i<npix_new;i++)
      image1[i]=0;

    //write each row to output file
     write(fp2,image1,npix_new*sizeof(unsigned char)); 
   }
   //close all 2 files
   close(fp1);
   close(fp2);

   

}   