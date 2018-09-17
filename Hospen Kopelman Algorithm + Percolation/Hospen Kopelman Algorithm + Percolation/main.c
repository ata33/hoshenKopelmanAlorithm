//
//  main.c
//  ClusterLastResort
//
//  Created by Andrew Ashley on 1/25/18.
//  Copyright © 2018 aaproduction. All rights reserved.
//


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    int sizei = 10, sizej = 10, p=1, array[10][10], largestlabel, array2[10][10], left, above, iterations = 0, cont = 1,/*labels[5],*/  array3[12][12]= {0}, array4[10][10], firstcol[10], lastcol[10], totalpaths = 0;
    /* dimension of label should be equal to number of possible clusters */
    int sizeLabel = sizei* sizej/2;
    int labels[sizeLabel]; // Allocating label arrays
    double time_spent;
    srand( time(NULL));
    clock_t begin = clock();
    while ( iterations < 1){
        for(int i = 0; i < sizei; i++){ //randomly places 1s in array
            for(int j=0; j < sizej; j++){
                int randomnumber;
                randomnumber = rand() % 10;
                if (randomnumber<=p){
                    array[i][j] = 1;}
                else {
                    array[i][j] = 0;
                }
                
            }
        }
       /* printf("\nPercolation Array\n");
        for(int i = 0; i < sizei; i++){ //prints array
            printf("\n");
            for(int j=0; j < sizej; j++){
                printf("\t%d", array[i][j]);
            }
        }
        printf("\n\n");*/
        largestlabel = 1;
        //Commented out since number of clusters assumed was less
        /*for ( int i = 0; i<=sizei; i++){
         labels[i] = i+1;
         }*/
        /*for (int i = 0; i <5; i++){
         printf("%d", labels[i]);
         }*/
        for ( int i = 0; i<sizeLabel; i++){
            labels[i] = i; //i+1;  //Labels[0] not used in code; could have used lables[0] for counting clusters
        }
       /* for (int i = 0; i < sizeLabel; i++){
            printf("%d ", labels[i]);
        }*/
        
        
        
        for (int i = 0; i<sizei; i++){
            for ( int j = 0; j<sizej; j++){
                if( i == 0 && j == 0){
                    if (array[0][0] == 1){
                        array2[0][0] = largestlabel;
                        largestlabel = largestlabel+1; //takes care of checking the [0][0] part of the matrix
                    }
                    else {
                        array2[0][0] = 0;
                    }
                }
                
                
                else if ( i ==0 && j !=0){
                    //takes care of checking the top row of the matrix
                    if (array[0][j] == 1){
                        if(array[0][j-1] != 0){
                            array2[0][j] = array2[0][j-1];
                        }
                        else{
                            array2[0][j] = largestlabel;
                            largestlabel = largestlabel +1;
                        }
                    }
                    else {
                        array2[0][j] = 0;
                    }
                }
                else if (i != 0 && j == 0){
                    if (array[i][0] == 1){
                        if(array[i-1][0] != 0){
                            array2[i][0] = array2[i-1][0];
                        }
                        else{
                            array2[i][0] = largestlabel;
                            //Added by Santidan Biswas since largest cluster label needs to be incremented
                            largestlabel = largestlabel +1;
                        }
                    }
                    else{
                        array2[i][0] = 0;
                    }
                }
                
                else {
                    left = array[i-1][j];
                    above = array[i][j-1];
                    if (array[i][j]== 1) {
                        if (left == 0 && above == 0){
                            array2[i][j] = largestlabel;
                            largestlabel = largestlabel + 1;
                        }
                        else if (left!=0 && above ==0){
                            array2[i][j] = array2[i-1][j];
                        }
                        else if (left == 0 && above != 0){
                            array2[i][j] = array2[i][j-1];
                            
                        }
                        else {
                            array2[i][j] = array2[i-1][j];
                            // Logic of Union-find
                            if (array2[i-1][j] != array2[i][j-1]) {  /*Check if left and above have different labels*/
                                if (array2[i-1][j] > array2[i][j-1])
                                    labels[array2[i-1][j]] = -1*labels[array2[i][j-1]]; /* Assign the cluster label to the biggger cluster using negative */
                                else
                                    labels[array2[i][j-1]] = -1*labels[array2[i-1][j]];
                            }
                        }
                        
                    }
                    else { array2[i][j] = 0;
                        
                    }
                }
            }}
        /*printf("\n First Cluster\n");
        for(int i = 0; i < sizei; i++){ //prints array 2
            printf("\n");
            for(int j=0; j < sizej; j++){
                printf("\t%d", array2[i][j]);
            }
            
        }*/
        
        // The entire array needs to be reassigned to a new array. Although this step is not necessary
        // You could have worked with array2 itself.
        //commented out since you are leaving the i=0 and j=0 arrays
        /* for ( int i = 1; i<=sizei; i++ ){
         for ( int j = 1; j<=sizej; j++){
         array3[i][j] = array2[i-1][j-1];
         }
         }*/
        // Although this is a redundant step;
        // still following the above commented codeblock
        // assigned array3 == array2
        for ( int i = 0; i<sizei; i++ ){
            for ( int j = 0; j<sizej; j++){
                array3[i][j] = array2[i][j];
            }
        }
        
        // Check Assigned labels
        /*printf("\n Check assigned Labels\n");
        for (int i = 0; i <sizeLabel; i++){
            printf("%d ", labels[i]);
        }
        printf("\n \n ");*/
        /////////////////union-find part/////////////////
        
        
        //Re-numbering the clusters
        for (int i = 0; i <sizei; i++){
            for (int j = 0; j < sizej; j++){
                //printf("%d ", labels[array3[i][j]]);
                // Check if the cluster contains a negative labels value
                // if yes, then re-assign the label to which the cluster belongs
                while(labels[array3[i][j]]<0)
                    array3[i][j]=-labels[array3[i][j]];
            }
        }
        
        // Good try!
        //
        // but you had to assign the array3 the new label and hence you were missing out
        //////finding the points of intersection of clusters/////
        /*for (int i = 1; i <=sizei; i++){
         for (int j = 1; j <= sizej; j++){
         if (array3[i][j] != 0){
         if (array3[i-1][j] != 0 && array3[i][j-1] !=0){
         if (array3[i-1][j]<array3[i][j-1]){
         array3[i][j] = array3[i-1][j];
         labels[array3[i][j-1]] = -labels[array3[i-1][j]];
         }
         else if (array3[i][j-1]< array3[i-1][j]) {
         array3[i][j] = array3[i][j-1];
         labels[array3[i-1][j]] = -labels[array3[i][j-1]];
         
         }
         }
         }
         }
         }
         
         
         for (int i = 0 ; i < sizei; i++){ //eliminates zero matrix
         for (int j = 0; j<sizej; j++){
         array4[i][j] = array3[i+1][j+1];
         }
         }
         ///////////////union////////////////
         for (int i = 0; i < sizei; i++){
         for (int j = 0; j < sizej; j++){
         if (labels[array4[i][j]] < 0){
         array4[i][j] = -1*(labels[array[i][j]]);
         }
         }
         }*/
        // No need of array4 but since used in the last part
        // re-assigning array3 to array4
        for (int i = 0 ; i < sizei; i++){ //eliminates zero matrix
            for (int j = 0; j<sizej; j++){
                array4[i][j] = array3[i][j];
            }
        }
      /*  printf("\n\n");
        for (int i = 0 ; i < sizei; i++){
            printf("\n");
            for (int j = 0; j<sizej; j++){
                printf("\t%d", array4[i][j]);
            }}*/
        
        int l = 0;
        ////finding if there is a path////
        for (int i = 0; i <sizei; i++){ //checks the first row of the finished matrix
            if (abs(array4[i][1]>0)){
                firstcol[l] = array4[i][1];
                l = l+1;
            }
            
        }
        int m = 0;
        for (int i = 0; i <sizei; i++){ //checks last row of the matrix
            if (abs(array4[i][sizej-1]>0)){
                lastcol[m] = array4[i][sizej-1];
                l = l+1;
            }
        }
        int path= 0; //if there is a number, n on the first and last columns, there is a path
        for (int i = 0; i <sizei; i++){
            for (int j = 0; j <sizej; j++){
                if (firstcol[i] == lastcol[j] && lastcol[j] !=0){
                    path =  1;
                }
            }
        }   //if there is a number, n on the first and last columns, there is a path
        for (int i = 0; i <sizei; i++){
            for(int j =0; j < sizej; j++){
                if (array4[1][i] == array4[sizei-1][j] && array4[sizei][j] !=0){
                    path =  1;
                }
            }
        }
        
        printf("\n Path: %d", path);
        //adds one to the number of total paths if running many iterations//
        if ( path == 1 ){
            totalpaths = totalpaths +1;
        }
        iterations = iterations +1;
    }
    printf("%d", totalpaths);
}








