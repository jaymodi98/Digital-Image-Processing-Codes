/*
Author: Jay D. Modi
Assignment - 1
Q.2: Create a gradient of grayscale intensities (0 to 255). Take the image size as your
input. The size of the image, given as input, should still produce a proper gradient.
*/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>
void main()
{
	//variable declaratioins
	int pix,npix,scan,nscan;
	int *fp1;
	unsigned char *image,*image2;
	char first_image[100];

	//asking the size of the gradient image
	printf("npix: ");
	scanf("%d",&npix);
	printf("nscan: ");
	scanf("%d",&nscan);

	//name of the output image: 'gradient_<npix>_<nscan>'
	sprintf(first_image,"gradient_%d_%d",npix,nscan);

	//open file in write mode
	fp1=creat(first_image,0666);
	if(fp1<0)
	{
		printf("error in creating %s\n",first_image);
		exit(1);
	}

	//allocate memory to image and image2
	image=(unsigned char *)calloc(nscan,sizeof(unsigned char));
	image2=(unsigned char *)calloc(npix,sizeof(unsigned char));

	//fill image array with values of graycode of first pixel in each row
	for(scan=0;scan<nscan;scan++)
		image[scan]=scan*256/nscan;

	
	for(scan=0;scan<nscan;scan++){
		//for all scan values, fill image2 array with image[scan]
		for(pix=0;pix<npix;pix++)
			image2[pix]=image[scan];

		//write each row one by one
		write(fp1,&image2[0],npix*sizeof(unsigned char));
	}


	free(image);
	//close file pointer
	close(fp1);
	printf("%s successfully stored!!\n\n", first_image);
}