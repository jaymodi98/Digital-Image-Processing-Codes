% Name: Jay Modi
% Roll no: 201501059
% Date: 4/4/2018
% DIP Assignment - 6
% Q1. Face recognition

clear all;
close all;

% logic to read all images from folder 'training_data'
myFolder = 'training_data';
filePattern = fullfile(myFolder, 'sub*');
jpegFiles = dir(filePattern);
total_images=length(jpegFiles);
images = cell(total_images,1);
for k = 1:total_images
    baseFileName = jpegFiles(k).name;
    fullFileName = fullfile(myFolder, baseFileName);
    images{k} = imread(fullFileName);
end

% Flattening all images (column-wise) and storing them in matrix 'A'
[m,n]=size(images{1});
A=zeros(m*n,total_images);
for i=1:total_images
    A(:,i)=images{i}(:);
end

% doing mean-shifting of matrix 'A'
% avg = zeros(m*n,1);
% for i=1:total_images
%    avg = avg + A(:,i); 
% end    
% avg = avg/total_images;
% 
% for i=1:total_images
%    A(:,i) = A(:,i) - avg; 
% end 

% find rank of 'A'
r=rank(A);
[U,S,V]=svd(A,'econ');

% take first r vector of U, becase rank of A is r
U=U(:,1:r);

% taking input/test image name (test images are in folder 'test_data')
in=input('Enter test image name: ','s');
test_image=imread(['test_data/' in]);

% this loop finds co-ordinates of all test images using r basis
fc=zeros(total_images,r);
for i=1:total_images
    f=A(:,i);
    for j=1:r
       fc(i,j)= sum(f.*U(:,j));
    end
end

% the following logic finds co-ordinates of test_image using r basis
G=double(test_image(:));
g=zeros(1,r);
for i=1:r
    g(1,i)=sum(G.*U(:,i));
end

% logic to find the image which nearest to test_image
dist=zeros(total_images,1);
for i=1:total_images
    dist(i)=immse(g,fc(i,:));
end
ind=find(dist==min(dist));

%plot and compare both images
subplot(121),imshow(test_image),title('test image');
subplot(122),imshow(images{ind(1)}),title('real image');