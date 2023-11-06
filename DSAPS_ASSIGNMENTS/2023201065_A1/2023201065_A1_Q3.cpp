#include<iostream>
#include<cmath>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;


//Function to calculate energy is below

double Energy(const Mat& image, int x, int y){
    double redGrad = 0.0;
    double greenGrad = 0.0;
    double blueGrad = 0.0;
    double result=0.0;
    int x_axis_energy=0;
    int y_axis_energy=0;
    int row=image.rows;
    int column=image.cols;
    if(x>0 && x< row-1){
        blueGrad=abs(image.at<Vec3b>(x-1,y)[0]-image.at<Vec3b>(x+1,y)[0]);
        greenGrad=abs(image.at<Vec3b>(x-1,y)[1]-image.at<Vec3b>(x+1,y)[1]);
        redGrad=abs(image.at<Vec3b>(x-1,y)[2]-image.at<Vec3b>(x+1,y)[2]);
    }
    x_axis_energy=(pow(blueGrad,2)+pow(greenGrad, 2)+pow(redGrad, 2));
    if (y > 0 && y < column - 1) {
        blueGrad=abs(image.at<Vec3b>(x,y-1)[0]-image.at<Vec3b>(x,y+1)[0]);
        greenGrad=abs(image.at<Vec3b>(x,y-1)[1]-image.at<Vec3b>(x,y+1)[1]);
        redGrad=abs(image.at<Vec3b>(x,y-1)[2]-image.at<Vec3b>(x,y+1)[2]);
    }
    y_axis_energy=(pow(blueGrad,2)+pow(greenGrad, 2)+pow(redGrad, 2));
    result=sqrt(x_axis_energy+y_axis_energy);
    return result;
}


//Function to that finds seam is below

void findSeam(const Mat& image, int seam[]){
    int no_of_row=image.rows;
    int no_of_column=image.cols;
    for(int i=0;i<no_of_row;i++){
        seam[i]=i;
    }
    for(int i=1; i<no_of_row;i++){
        for(int j=0; j<no_of_column;j++){
            int minColumn=j;
            double minEnergy=Energy(image, j, i);
            for(int k=-1;k<=1;k++){
                if(j+k>=0 && j+k<no_of_column){
                    double energy=Energy(image, j+k, i);
                    if(energy<minEnergy){
                        minEnergy=energy;
                        minColumn=j+k;
                    }
                }
            }
            seam[j]=minColumn;
        }
    }
}


//Function to that removes seam is below

void removeSeam(Mat& image, int seam[]){}


int main(){
    int width_size=500, height_size=500;
    Mat input_image=imread("");
    if(input_image.empty()){
        cout<<"Image not found"<<endl;
        return 0;
    }
    while (input_image.cols>width_size || input_image.rows>height_size)
    {   Mat gray_color;
        cvtColor(input_image, gray_color, COLOR_BGR2GRAY);
        int* seam= new int[gray_color.rows];
        findSeam(gray_color, seam);
        removeSeam(input_image, seam);
        delete[] seam;

    }
    resize(input_image, input_image, Size(width_size, height_size));
    imshow("Resized Image", input_image);
    waitKey(0);
    return 0;
    
}