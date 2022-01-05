//Gleb Zvonkov 
//November 1, 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void RRcalculations(int p, int bt[], int at[], int tq, int wt[], int tt[] );


int main(int argc, char *argv[]){
    
    FILE *fp;
    char line[5]; // intake for process number
    int  i; //intake arrival time variable
    int j; //intake burst time variable
    
    int p = 0;   // p is the number of processes  in one line
    int at[100];   // array for all arrival times
    int bt[100];   // array for all burst times
    
    int wt[100];  // array for all wait times
    int tt[100]; // array for all turnaround times
    int ttt=0;  // total turnaround time
    int twt=0;  // total wait time
    
    fp = fopen("input.txt", "r"); //open file
    printf("\n");
    
    while ( fscanf(fp, "%s", &line[0]) != EOF ){  //continue reading until end of file
        
        if ( line[0] != 'p' &&  line[0] != 'P'){   // if read value is not P or not p then value is time quantam, so line is complete
            RRcalculations (p, bt, at, atoi(&line[0]), wt, tt ); // run RR calculcation to get wait time and turn around time for each process
            for (int x = 0; x < p; ++x){ // for each process
                printf("Procces: P%d  Arrival Time: %d  Burst Time: %d  Waiting time: %d  Turnaround time: %d \n", x+1, at[x], bt[x], wt[x], tt[x] );
                ttt = ttt + tt[x]; //add together all turnaround times
                twt = twt + wt[x]; //add together all wait times
            }
            printf("\nTotal Turnaround Time: %d \nAverage waiting time = %.2f  \nAverage turnaround time = %.2f    \n\n", ttt, (float)twt/p, (float)ttt/p);
            p = 0;  // set process back to zero
            ttt = 0; // set total turn around time back to zero
            twt = 0; // set total wait time back to zero
        }
        else{
            fscanf(fp, "%d", &i); // intake arrival time
            fscanf(fp, "%d", &j); // intake burst time
            at[p] = i;  //set process arrival time
            bt[p] = j;  // set process burst time
            ++p;  // increment process
        }
        
    } //while loop
    return 0;
} //main


void RRcalculations(int p, int bt[], int at[], int tq, int wt[], int tt[] ){
    
    int i = 0;      // variable to get or set process i+1 info
    int time = 0;    // current time in roun robin algorithm
    int counterp = p; //counter for number of processes to be decremented when process is complete
    
    int rbt[p]; //remaning burst time
        for (int x = 0 ; x < p ; x++)  //copy burst time into remaining burst time
            rbt[x] = bt[x];
    
    while(counterp > 0){    // repeat until counterp is 0
        
        if (rbt[i] > 0) { // remaining burst time is greater then zero
            if(rbt[i] > tq){ // if burst time is greater then time quantam
                rbt[i] = rbt[i] - tq;    //remaining burst time is decreased by time quantam
                time = time + tq;    //time is incread by time quantam
            }
            else {  //if burst time is smaller then or equal to time quantam
                time = time + rbt[i];  // time is inceased by remaining burst time
                rbt[i] = 0; // since entire process is complete, remaining burst time for process is 0
                counterp--;   // since entire process is complete, decrement number of process
                tt[i] = time - at[i];   // turaround time is equal to time minus arrival time
                wt[i] =  time - at[i] - bt[i] ;    // wait time is equal to time minus arrival time minus burst time
            }
        }
        
        if(i+1 == p || at[i + 1] > time) // if all processes have been run or arrival time of next process > current time then start from beggining
            i = 0;
        else   // if arrival time is smaller then current time then go to next process
            i++;
                
    } // while loop
} //helper function








