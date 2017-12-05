#ifndef DEFINES_H
#define DEFINES_H

//-----------------------------------------------
//  used in main
//-----------------------------------------------

#define WINDOW_WIDTH        400
#define WINDOW_HEIGHT       400

//define a custom msg we can use to send to the windproc
//to train the network
#define UM_TRAIN (WM_USER + 0)


//-----------------------------------------------
//  used in CData/CMouse
//-----------------------------------------------

//total number of built in patterns
#define NUM_PATTERNS        2



//how many vectors each pattern contains
#define NUM_VECTORS         2

//added for the number of input
#define NUM_DATAS			0

//output has to be above this value for the program
//to agree on a pattern. Below this value and it
//will try to guess the pattern
#define MATCH_TOLERANCE     0.5



//-----------------------------------------------
//  used in CNeuralNet
//-----------------------------------------------
#define ACTIVATION_RESPONSE 1.0
#define BIAS                -1

//the learning rate for the backprop.
#define LEARNING_RATE       0.5

//when the total error is below this value the 
//backprop stops training
#define ERROR_THRESHOLD     0.001

#define NUM_HIDDEN_NEURONS  6

#define MOMENTUM            0.9







#endif