   /*
Author: Jay D. Modi
Assignment - 2
Q.1 Zoom an image. Take any image as your input, also take in the image size as your
input. Ask the user for the zoom factor of the image. Your output should be the
zoomed version of the image. Make sure that your code works even with a fractional
zoom factor.
*/
#include<stdio.h>
#include<math.h>
#include<fcntl.h>
#include<malloc.h>
#include <stdlib.h>


int main()
{
   //variable declaratioins
   int fp1,fp2;
   char input[100],output[100];
   unsigned char *image1;
   int npix,pix,nscan,scan,i,j;
   float zf;

   //asking name of input image
   printf("Give input image name: ");
   scanf("%s",input);

   //asking size of input image
   printf("enter npix and nscan: ");
   scanf("%d%d",&npix,&nscan);

   printf("Input Image is %s npix nscan %d %d \n",input,npix,nscan);
   

   //asking for zooming factor
   printf("Enter a zooming factor: ");
   scanf("%f",&zf);

   //output image's name '<input_image_name>_zoom(<zoom_factor>)_<output_npix>_<output_nscans>'
   sprintf(output,"%s_zoom(%f)_%d_%d",input,zf,(int)(npix*zf),(int)(nscan*zf));

   //allocate memory to image1
   image1 = (unsigned char *)calloc(npix,sizeof(unsigned char));

   //open input image file in read-only mode
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
   unsigned char image_in[npix][nscan];
   for(scan=0;scan<nscan;scan++)
   {
     //read each row from input image
     read(fp1,image1,npix*sizeof(unsigned char));
     //store each row into 2-D array
     for(pix=0;pix<npix;pix++)
     {
       image_in[scan][pix] = image1[pix];
     }

   }

   //declare 2-D array of the size of output image
   unsigned char image_out[(int)(nscan*zf)][(int)(npix*zf)];
   for(scan=0;scan<nscan*zf;scan++)
   {  
      i=scan/zf;
      //fill output image array's each row based on zooming factor and input image pixels
      for(pix=0;pix<npix*zf;pix++)
      {
        
        j=pix/zf;
        image_out[scan][pix]=image_in[i][j];
      }  
      

   }

   //write output image array in output image file
   write(fp2,&image_out,(int)(npix*zf*nscan*zf*sizeof(unsigned char)));   

   //close input file and output file
   close(fp1);
   close(fp2);


}   

