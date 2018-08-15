%%%%%%%%%%%%%%%%%%%%%%%
% Name: Jay Modi
% Roll no: 201501059
% DIP - Assignment - 05
% Q3 - DFT
%%%%%%%%%%%%%%%%%%%%%%%
clc;
clear all;
close all;

img_1=imread('barbara.png');        %read image 1
img_2=imread('lenaTest3.jpg');      %read image 2

ft_img1=fft2(img_1);                %FT of image 1
ft_img2=fft2(img_2);                %FT of image 2
amplitude_img1=abs(ft_img1);        %get amplitude of image 1
amplitude_img2=abs(ft_img2);        %get amplitude of image 2
phase_img1=angle(ft_img1);          %get phase of image 1
phase_img2=angle(ft_img2);          %get phase of image 2

swap_amp2_phase1=amplitude_img2.*exp(1i*phase_img1);    %swap amplitudes in image 1
swap_reconstucted_img1=ifft2(swap_amp2_phase1);         %reconstruct image 1
swap_reconstucted_img1=uint8(swap_reconstucted_img1);   
swap_amp1_phase2=amplitude_img1.*exp(1i*phase_img2);    %swap amplitudes in image 2
swap_reconstucted_image2=ifft2(swap_amp1_phase2);       %reconstruct image 2
swap_reconstucted_image2=uint8(swap_reconstucted_image2);


imshow(img_1); title('Image 1');    %display image 1
figure; 
imshow(img_2); title('Image 2');    %display image 2
figure;
imshow(swap_reconstucted_img1); title('Image 1 with amplitudes of image 2');    %display swapped image 1
figure;
imshow(swap_reconstucted_image2); title('Image 2 with amplitudes of image 1');  %display swapped image 2
