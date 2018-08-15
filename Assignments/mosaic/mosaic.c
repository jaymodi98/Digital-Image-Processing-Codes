/*
Author: Jay D. Modi
Assignment - 4
Q.1 Take two images of the same size (preferably the boat image). Mosaic the two
images side by side. Ask the user from which scan line they would like to mosaic the
second image with the first one. The empty spaces should be padded properly.
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
   int fp1,fp2,fp3;
   char input_1[100],input_2[100],output[100],hv;
   unsigned char *image1,*image2,*image3;
   int npix_1,npix_2,pix,nscan_1,nscan_2,scan,i,j,shift,nscan_new,npix_new;

   //asking input image 1 name
   printf("Give input image 1 name: ");
   scanf("%s",input_1);

   //asking image 1's dimensions
   printf("enter a npix and nscan for image 1: ");
   scanf("%d%d",&npix_1,&nscan_1);

   printf("Input 1 Image is %s npix nscan %d %d \n",input_1,npix_1,nscan_1);

   //open input image 1 file in read only mode
   fp1 = open(input_1,O_RDONLY);
   if(fp1<0)
   {
       printf("Error in opening %s image \n",input_1);
     exit(1);
   }

   //asking input image 2 name
   printf("Give input image 2 name: ");
   scanf("%s",input_2);

   //asking input image 2's dimensions
   printf("enter a npix and nscan for image 2: ");
   scanf("%d%d",&npix_2,&nscan_2);

   printf("Input 2 Image is %s npix nscan %d %d \n",input_2,npix_2,nscan_2);

   //open input image 2 file in read only
   fp2 = open(input_2,O_RDONLY);
     if(fp2<0)
     {
         printf("Error in opening %s image \n",input_2);
       exit(1);
     }

   //asking if user wants to do horizontal moasaic or vertical
   printf("horizontal mosaic or vertical mosaic? (h/v): ");
   scanf("%c",&hv);
   scanf("%c",&hv);

   //if horizontal moasaic
   if(hv == 'h')
   {

    //asking line number from which user wants to start image2
     printf("second image starts from line number: ");
     scanf("%d",&shift);

     //calculate new npix and new nscan
     npix_new=npix_1+npix_2;
     nscan_new=max(nscan_1,nscan_2+shift);

     //output image's name '<input_image_1_name>_<input_image_2_name>_mosaic_<new_npix>_<new_nscan>'
     sprintf(output,"%s_%s_mosaic_%d_%d",input_1,input_2,npix_new,nscan_new);

     //allocating memory to image1,image2 and image3 pointers
     image1 = (unsigned char *)calloc(npix_1,sizeof(unsigned char));
     image2 = (unsigned char *)calloc(npix_2,sizeof(unsigned char));
     image3 = (unsigned char *)calloc(npix_1+npix_2,sizeof(unsigned char));

     //create output image file in write mode
     fp3 = creat(output,0667);
     if(fp3<0)
     {
         printf("Error in opening %s image \n",output);
       exit(1);
     }

     //iterate for each row of output image
     for(scan=0;scan<nscan_new;scan++)
     {
        //read image1 from image1 file if nscan value is in range
        if(scan<nscan_1)  read(fp1,image1,npix_1*sizeof(unsigned char));
        else //else make it zero
        {
          for(int i=0;i<npix_1;i++)
            image1[i]=0;
        }

        //read image2 from image2 file if nscan value is in range
        if(scan>=shift && scan<shift+nscan_2) read(fp2,image2,npix_2*sizeof(unsigned char));
        else  //else make it zero
        { 
          for(int i=0;i<npix_2;i++)
            image2[i]=0;
        }

         //write image1 and image2 to output image file
         write(fp3,image1,npix_1*sizeof(unsigned char)); 
         write(fp3,image2,npix_2*sizeof(unsigned char));   
     }
     //close file3
     close(fp3);
   }
   else if(hv == 'v')
   {
      
      //asking column number from which user wants to start image2
     printf("second image starts from column number: ");
     scanf("%d",&shift);

     //calculate new npix and new nscan
     npix_new=max(npix_1,shift+npix_2);
     nscan_new=nscan_1+nscan_2;
     
     //output image's name '<input_image_1_name>_<input_image_2_name>_mosaic_<new_npix>_<new_nscan>'
     sprintf(output,"%s_%s_mosaic_%d_%d",input_1,input_2,npix_new,nscan_new);

     //allocate memory to image1 pointer
     image1 = (unsigned char *)calloc(npix_new,sizeof(unsigned char));

     //create output image file in write mode
     fp3 = creat(output,0667);
     if(fp3<0)
     {
         printf("Error in opening %s image \n",output);
       exit(1);
     }

     //reading and writing input image 1
     for(scan=0;scan<nscan_1;scan++)
     {
        //read each row of input image 1
        read(fp1,image1,npix_1*sizeof(unsigned char));
        //fill remaing part with zero
        for(int i=npix_1;i<npix_new;i++)
          image1[i]=0;
        //write row to output image file
        write(fp3,image1,npix_new*sizeof(unsigned char)); 
     }

     //reading and writing input image 2
     for(scan=0;scan<nscan_2;scan++)
     {  
        //fill inital necessary part with zero
        for(int i=0;i<shift;i++)
          image1[i]=0;
        //read each row of input image 2
        read(fp2,&image1[shift],npix_2*sizeof(unsigned char));
        //fill remaining part with zero
        for(int i=shift+npix_2;i<npix_new;i++)
          image1[i]=0;
        //write row to output image file
        write(fp3,image1,npix_new*sizeof(unsigned char)); 
     }
     
     //close file3
     close(fp3);
   }

   //close all other files
   close(fp1);
   close(fp2);

   

}   