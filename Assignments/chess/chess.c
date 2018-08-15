/*
Author: Jay D. Modi
Assignment - 1
Q.1: Create a chessboard image. Take the image size as your input.
*/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>
int main()
{
	//variable declaratioins
	int pix,npix,scan,scan_top,nscan;
	int fp1;
	unsigned char *image,*image2;
	char first_image[100];

	//asking for dimensions of chessboard
	printf("npix: ");	
	scanf("%d",&npix);
	printf("nscan: ");
	scanf("%d",&nscan);

	//define output image's name as 'chess_<npix>_<nscan>'
	sprintf(first_image,"chess_%d_%d",npix,nscan);

	//open file in write mode
	fp1=creat(first_image,0666);
	if(fp1<0)
	{
		printf("error in creating %s\n",first_image);
		exit(1);
	}

	//allocate memory to image and image2
	image=(unsigned char *)calloc(npix,sizeof(unsigned char));
	image2=(unsigned char *)calloc(npix,sizeof(unsigned char));

	//generating 2 rows of chessboard
	for(pix=0;pix<npix;pix++){
		image[pix]=((pix*8/npix)&1)?0:255;
		image2[pix]=((pix*8/npix)&1)?255:0;
			
	}

	scan_top=0;
	//filling the whole chess board from the previously generated rows(image and image2)
	while(scan_top<nscan) //repeat untill all rows are filled
	{
		//dividing nscan in 8 parts and fill odd parts with image
		for(scan=0;scan<nscan/8;scan++){
			write(fp1,&image[0],npix*sizeof(unsigned char));
			scan_top++;	
		}

		//dividing nscan in 8 parts and fill even parts with image2
		for(scan=0;scan<nscan/8;scan++){
			write(fp1,&image2[0],npix*sizeof(unsigned char));
			scan_top++;	
		}
		
	}


	free(image);
	//close file pointer
	close(fp1);
	printf("%s successfully stored!!\n\n", first_image);
}