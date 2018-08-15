/*
Author: Jay D. Modi
Assignment - 2
Q.2 Rotate an image. Take any image as your input, also take in the image size as your
input. Ask the user for the rotation angle. Your output should be the rotated version
of the image.
*/
#include<stdio.h>
#include<malloc.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
void main()
{
  //variable declarations
  int fp1,fp2,a;
  float theta,deg;
  char input_image_file[100],output_image_file[100];
  unsigned char * image;
  int npix,nscan,pix,scan,i1,i2;
  int nscan_new,npix_new,p1x,p1y,p2x,p2y,p3x,p3y,p4x,p4y,left,right,up,down;

  //asking input image name
  printf("Give input image name: ");
  scanf("%s",input_image_file);

  //asking input image size
  printf("Give size of image: ");
  scanf("%d%d",&npix,&nscan);

  //allocating memory to image pointer
  image=(unsigned char *)calloc(npix,sizeof(unsigned char));
  printf("Input Image is %s npix nscan %d %d \n",input_image_file,npix,nscan);

  //asking user for angle of rotation in degrees in clockwise direction
  printf("Enter the angle(in degrees) by which you want to rotate image in clockwise direction: ");
  scanf("%f",&theta);
  //storing angle in degrees only in deg variable
  deg=theta;
  //converting theta to radians from degrees
  theta=(-1)*((((float)22.0)/7)*theta)/180; 

  //open input image file in read-only mode
  fp1= open(input_image_file,O_RDONLY);
  if (fp1<0)
  {
    printf("Error in opening %s image \n",input_image_file);
    exit(1);
  }

   //declare 2-D array of the size of input image
   unsigned char image_in[npix][nscan];
   for(scan=0;scan<nscan;scan++)
   {
     //read each row of original image
     read(fp1,image,npix*sizeof(unsigned char));
     for(pix=0;pix<npix;pix++)
     {
       //store current row of image in 2-D array
       image_in[scan][pix] = image[pix];
     }

   }

   //calulating x co-ordinates of all 4 vertices after rotation
   p1x=((0-(npix/2))*cos(theta)-(0+(nscan/2))*sin(theta));
   p2x=((npix-(npix/2))*cos(theta)-(0+(nscan/2))*sin(theta));
   p3x=((npix-(npix/2))*cos(theta)-(-nscan+(nscan/2))*sin(theta));
   p4x=((0-(npix/2))*cos(theta)-(-nscan+(nscan/2))*sin(theta));
   
   //calulating y co-ordinates of all 4 vertices after rotation
   p1y=(((0-(npix/2))*sin(theta))+(0+(nscan/2))*cos(theta));
   p2y=(((npix-(npix/2))*sin(theta))+(0+(nscan/2))*cos(theta));
   p3y=(((npix-(npix/2))*sin(theta))+(-nscan+(nscan/2))*cos(theta));
   p4y=(((0-(npix/2))*sin(theta))+(-nscan+(nscan/2))*cos(theta));

   //co-ordinate of left-most point
   left=min(p1x,min(p2x,min(p3x,p4x)));
   //co-ordinate of right-most point
   right=max(p1x,max(p2x,max(p3x,p4x)));
   //calculate new npix value
   npix_new = right-left+1;

   //co-ordinate of down-most point
   down=min(p1y,min(p2y,min(p3y,p4y)));
   //co-ordinate of up-most point
   up=max(p1y,max(p2y,max(p3y,p4y)));
   //calculate new nscan value
   nscan_new=up-down+1;

  //output image's name '<Input_image_name>_rotate(<angle_of_rotation>)_<new_npix>_<new_nscan>'
  sprintf(output_image_file,"%s_rotate(%f)_%d_%d",input_image_file,deg,npix_new,nscan_new);

  //create output image file in write mode
  fp2=creat(output_image_file,0667);
  if (fp2<0)
  {
    printf("Error in creating output %s image\n",output_image_file);
    exit(1);
  }

   //create 2-D array of output image's size
   unsigned char image_out[npix_new][nscan_new];
   int xnew,ynew,xrot,yrot;
   //dsiplay size of rotated image
   printf("Size of new image--> nscan=%d npix=%d\n",nscan_new,npix_new );   

   //core logic of rotation
   //shift origin to center of the image and then iterate from y to -y (top to bottom)
   for(scan=(up-(nscan/2));scan>=(down-(nscan/2));scan--)
   {
      //iterate from -x to x (left to right) for each row
     for(pix=(left+(npix/2));pix<=(right+(npix/2));pix++)
     {  

        //finding co-ordinates of points after shifting of origin
        xnew=pix-(npix/2);
        ynew=scan+(nscan/2);
        //finding co-ordinates of points after rotation of axis
        xrot=(xnew*cos(theta)+ynew*sin(theta))+(npix/2);
        yrot=(-(xnew*sin(theta))+ynew*cos(theta))-(nscan/2);
        
        //mapping back to original image and assigning 0 if point if from outside of the image
        if(xrot<npix && xrot>=0 && yrot>-nscan && yrot<=0)
        {
          image_out[-scan+(up-(nscan/2))][pix-(left+(npix/2))]=image_in[-yrot][xrot];
        }
        else
        {
          image_out[-scan+(up-(nscan/2))][pix-(left+(npix/2))]=0;
        }
     }
   }

   //write whole image into the output image file
   write(fp2,&image_out,(npix_new)*(nscan_new)*sizeof(unsigned char));

   //close both the files
   close(fp1);
   close(fp2);
}