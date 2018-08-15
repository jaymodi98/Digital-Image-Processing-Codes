/*
Name: Jay Modi
Roll no: 201501059
DIP - Assignment_05
Q1 - Histogram Equalisation
*/
#include<stdio.h>
#include<math.h>
#include<fcntl.h>
#include<malloc.h>
#include <stdlib.h>


int main()
{

  //initial variables declaration
   int fp1,fp2;
   char input[100],output[100];
   unsigned char *image1,*image2;
   int npix,pix,nscan,scan,cf,i,j;
   FILE * fp;

  //asking user to enter the input image name
   printf("Give input image name \n");
   scanf("%s",input);

   //asking user to enter the size of the image
   printf("enter a npix and nscan\n");
   scanf("%d%d",&npix,&nscan);

   //generating output image name
   sprintf(output,"%s_equalised_%d_%d",input,npix,nscan);

   //allocating memory to 2 pointers to read and write rows of image
   image2 = (unsigned char *)calloc(npix,sizeof(unsigned char));
   image1 = (unsigned char *)calloc(npix,sizeof(unsigned char));

   //opening input image file in read only mode
   fp1 = open(input,O_RDONLY);
   //checking if file opened properly or not
   if(fp1<0)
   {
       printf("Error in opening %s image \n",input);
     exit(1);
   }
   //opening output image file in write mode
   fp2 = creat(output,0667);
   //checking if file opened properly or not
   if(fp2<0)
   {
       printf("Error in opening %s image \n",output);
     exit(1);
   }

   //hist variable to store histogram values
   int hist[256],hist_equal[256];
   //variable to store values of equalised histogram 
   int equalised[256];

   //open "histogram_equalised.txt" file in write mode to write equalised histogram values
  fp = fopen ("histogram_equalised.txt", "w+");

    //initialize original hist variable with zero
   for(i=0;i<256;i++){
      hist[i]=0;
      hist_equal[i]=0;
   }
   
   //loop to get the histogram values of the image
   for(scan=0;scan<nscan;scan++)
   {
        //read each row
       read(fp1,image1,npix*sizeof(unsigned char));
       for(pix=0;pix<npix;pix++)
       {
          //update histogram values
          hist[image1[pix]]++;  
       }
       
   }

   float sum=0;
   //loop to get the equalised histogram values
   for(i=0;i<256;i++)
   {
        sum+=hist[i];//find cumulative histogram values
        equalised[i]=round((sum/(npix*nscan))*255);//logic to store equalised histogram values
   }

   //re-open input image file to go to its start
   close(fp1);
   fp1 = open(input,O_RDONLY);

   //loop to update the original image pixels with equalised histogram
   for(scan=0;scan<nscan;scan++)
   {
        //read rows of input image
       read(fp1,image1,npix*sizeof(unsigned char));
       for(pix=0;pix<npix;pix++)
       {  
          //generate output image by using equalised histogram values
          image2[pix]=(unsigned char)equalised[image1[pix]];
          hist_equal[image2[pix]]++;
       }
       //write rows of output image
       write(fp2,image2,npix*sizeof(unsigned char));
   } 

   //store equalised histogram values in a file
   for(i=0;i<256;i++)
     fprintf(fp, "%d\t%d\n",i,hist_equal[i]);

   close(fp1);
   close(fp2);
   fclose(fp);

}