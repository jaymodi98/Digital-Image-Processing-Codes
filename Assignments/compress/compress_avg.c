/*
Author: Jay D. Modi
Assignment - 2
Q.3 Reduce the image dimensions. Take any image as your input, also take in the image
size as your input. Ask the user by what factor they want to reduce the image
dimensions. Note that this factor will be an integer. You may achieve this by skipping
over pixels or by averaging them.
*/
#include<stdio.h>
#include<math.h>
#include<fcntl.h>
#include<malloc.h>
#include <stdlib.h>

int main()
{

   //variable declarations
   int fp1,fp2;
   char input[100],output[100];
   unsigned char *image1,*image2;
   int npix,pix,nscan,scan,cf,i,j;

   //asking input image name
   printf("Give input image name: ");
   scanf("%s",input);

   //asking input image size
   printf("Enter npix and nscan: ");
   scanf("%d%d",&npix,&nscan);

   printf("Input Image is %s npix nscan %d %d \n",input,npix,nscan);

   //asking for compression factor
   printf("Enter compression factor: ");
   scanf("%d",&cf);

   //output image's name '<input_image_name>_compress_avg(<compression_factor>)_<new_npix>_<new_nscan>'   
   sprintf(output,"%s_compress_avg(%d)_%d_%d",input,cf,npix/cf,nscan/cf);

   //allocate memory to image1 and image2
   image2 = (unsigned char *)calloc((npix/cf),sizeof(unsigned char));
   image1 = (unsigned char *)calloc(npix,sizeof(unsigned char));

   //open input image file in read-only modde
   fp1 = open(input,O_RDONLY);
   if(fp1<0)
   {
   	   printf("Error in opening %s image \n",input);
	   exit(1);
   }

   //open output image file in write mode
   fp2 = creat(output,0667);

   if(fp2<0)
   {
   	   printf("Error in opening %s image \n",output);
	   exit(1);
   }

   //declare 2-D array of input image size
   int image[nscan][npix];
   for(scan=0;scan<nscan;scan++)
   {
       //read each row of input image
       read(fp1,image1,npix*sizeof(unsigned char));
       for(pix=0;pix<npix;pix++)
       {  
          //store image pixels in 2-D array
          image[scan][pix]=image1[pix];
       }
       
   }
   int temp=0;
   //logic of compression using average starts from here
   for(scan=0;scan<nscan;scan+=cf)
   {
       for(pix=0;pix<npix;pix+=cf)
       {
          temp=0;
          //loop to get sum of pixels whom we want to average
          for(i=0;i<cf;i++)
          {
            for(j=0;j<cf;j++)
            {
              if((scan+i)<nscan && (pix+j)<npix)
              temp+=image[scan+i][pix+j];
            }
          }
          //divide sum by cf*cf
          temp= temp/(cf*cf);
          image2[pix/cf]=(unsigned char)temp;
       }
       //write a row of pixels in output image file
       write(fp2,image2,(npix/cf)*sizeof(unsigned char));

   }

   //close both the files
   close(fp1);
   close(fp2);


}   