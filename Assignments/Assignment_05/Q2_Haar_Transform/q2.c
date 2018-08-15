/*
Name: Jay Modi
Roll no: 201501059
DIP - Assignment_05
Q2 - Haar Transfor basis images
*/
#include<stdio.h>
#include<math.h>

int main()
{

	//initializing variables
    int n=8;
    float haar[n][n]; 	//haar matrix	
    int temp=0;
    int k,i,j,srt;
    int p = log(n)/log(2),q;
    float P,Q,T,N;
    N=(float)n;

   	//logic to generate haar matrix
	for(i=0;i<p;i++)
	{
        //for H0
        if(i==0)
        {	q=pow(2,i);
        	srt=0;
        }
        //for 2^p + 0
        else
        {	q=pow(2,i);
        	srt=1;
        }	
		for(j=srt;j<=q;j++)
		{
			P=(float)i;
			Q=(float)j;
			temp = pow(2,i)+j-1;//find n in 2^p + n;
		    for(k=0;k<n;k++)
		    {
		    	T=(float)k;
		    	//different conditions used to assign values to haar matrix
                if(temp==0)
                {
                	haar[temp][k]= 1/sqrt(N);
                }  
                else if(temp==1)
                {
                	if(0<=(T/N) && (T/N)<0.5)
                	   haar[temp][k]= 1/sqrt(N);
                	else if(0.5<=(T/N) && (T/N)<1)
                	    haar[temp][k]= (-1)*(1/sqrt(N));	
                }
    			else if(((Q-1)/pow(2,P))<=(T/n) && (T/n)<((Q-0.5)/pow(2,P)))
    			{
    				haar[temp][k]= (sqrt(pow(2,P)))/sqrt(N);
    			}	
    		    else if((((Q-0.5)/pow(2,P))<=T/n) && ((T/n)<(Q/pow(2,P))))
    		    {
    		        haar[temp][k]= (-1)*((sqrt(pow(2,P)))/sqrt(N));
    		    }   
    		    else
    		    haar[temp][k]= 0;
		    }
		}
	}

	int basis_matrix[64][64];
	float temp1[64];
    

    for(i=0;i<64;i++)
    {
    	for(j=0;j<64;j++)
    		basis_matrix[i][j]=5;
    }

    //to flatten the haar matrix and store it in an array
    for(i=0;i<8;i++)
    {
    	for(j=0;j<8;j++)
    	{
    		temp1[i*8+j]=haar[i][j];
    	}
    }
    

    //loop to put the flattened values of haar matrix in first eight rows of basis matrix
    //and to map values of basis matrix
    //ans this loop will give us first 8 basis images
    for(i=0;i<64;i++)
    {
    	for(j=0;j<8;j++)
    	{
           if(temp1[i]>0)//if positive value, then map to 1
    	    basis_matrix[j][i]=1;
	       else if(temp1[i]<0)//if negative value then map to -1
	     	basis_matrix[j][i]=-1;
	       else					//else zero
	    	basis_matrix[j][i]=0;	
    	}
    }
    
    //to get first 8 columns of basis matrix as transpose of first 8 rows of basis matrix
    //and this loop will give us remaining 7 basis images of first column
    for(i=0;i<64;i++)
    {   
        for(j=0;j<8;j++)
        {
        	basis_matrix[i][j]=basis_matrix[j][i];
        }  
    } 

    int l;
    //loop to get all remaining basis images
    /*to get basis image of row x and col y:
		-take basis image of row 0 and col x
		-take basis image of row x and col 0
		-do multiplication
	*/
    for(l=1;l<8;l++)
    {
    	for(k=1;k<8;k++)
	    {
	    	for(i=0;i<8;i++)
		    {
		         for(j=0;j<8;j++)
		         {
		         	if((basis_matrix[i+l*8][j]*basis_matrix[i][8*k+j])>0)
		         	{
		         		basis_matrix[i+l*8][8*k+j]=1;
		         	}
		         	else if((basis_matrix[i+l*8][j]*basis_matrix[i][8*k+j])<0)
		            {
		                basis_matrix[i+l*8][8*k+j]= -1;	
		            }
		            else
		            {
		                basis_matrix[i+l*8][8*k+j]=0;
		            }
		         }
		    }   
	    }
    }

    //remaining part of code stores the basis matrix image in a file
	int fp1,fp2,a;
	char input_image[100],output_image[100];
	int npix,nscan,pix,scan,i1,i2;	
	unsigned char image[71][71];
	
	//create file haar_basis in write mode
	fp2=creat("haar_basis_71_71.raw",0667);
	if (fp2<0)
	{
	printf("Error in creating output %s image\n",output_image);
	exit(1);
	}

	i=0;
	j=0;
	int cnt1=0,cnt2=0;	
	for (scan=0;scan<72;scan++)
	{
	    j=0;
        cnt2=0;
	    
	    if(cnt1==8)//to create partision between different basis images
	    {

	    	for(pix=0;pix<72;pix++)
	    		image[scan][pix]=200;

	    	cnt1=0;
	    }
	    else
	    {
	    	for (pix=0;pix<72;pix++)
		    {
		        if(cnt2==8)//to create partision between different basis images
		        {
		         	image[scan][pix]=(unsigned char)200;
		         	cnt2=0;
		        }	
			    else if(basis_matrix[i][j]==1)//map 1 to 255
		     	{
		     		image[scan][pix]=(unsigned char)255;
		     		j++;
		     		cnt2++;
		     	}	
		     	else if(basis_matrix[i][j]==-1)//map -1 to 0
		     	{
		     		image[scan][pix]=(unsigned char)0;
		     		j++;
		     		cnt2++;
		     	}
		     	else//else map to 128
		     	{
		     		image[scan][pix]=(unsigned char)128;
		     		j++;
		     		cnt2++;
		     	}
		    }
		    i++;
		    cnt1++;
	    }
	}
	//write whole image in file
	write(fp2,&image[0],71*71*sizeof(unsigned char));
	close(fp2);
	printf("Haar transform basis images successfully stored!!\n");
}