/*! \mainpage Mexipol library Documentation
 *
 * \section intro_sec Introduction
 *
 * This is the Mexipol library documentation.
 *
 * \section what_sec What is it ?
 * \section how_to_sec How to use it ?
 *	To use this library, just copy the libmexipol.h and libmexipol.c files in your project's directory and add them to your project.
 *
 * \section copyright Copyright and License
 *  Copyright (c) 2014 Paul-Darius Sarmadi <sarmadipauldarius@yahoo.fr>
 *
 * <BR><BR>
 *
 */



/**
 * \file      libmexipol.h
 * \author    Paul-Darius Sarmadi
 * \version   1.0
 * \date      August 21, 2014
 * \brief     Mexipol's functions
 * \details   This .h document contains all the mexipol's functions prototypes.
 */

#ifdef __APPLE__
typedef char* char16_t;
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"


/* input/output handling */


/*! \fn void numberio(int nlhs, int i, int nrhs, int j)
    \brief
     Goal : Prints an error message if the number of output or the number of input is not the required one.<BR>
 	 Output : None.<BR>
    \param nlhs The number of output.
    \param i The number of output required by the algorithm.
    \param nrhs The number of input.
    \param j The number of input required by the algorithm.
*/
void numberio(int nlhs, int i, int nrhs, int j);

/*! \fn void type(char *type, const mxArray *prhs[], int i)
    \brief
     Goal : Prints an error message if the type is not the one required.<BR>
 	 Output : None.<BR>
    \param type type required : must be "string", "double" or "structure"
    \param prhs The function's prhs
    \param nrhs The element number of prhs which is the number as an input.
    \param j The number of input required by the algorithm.
*/

void type(char *type, const mxArray *prhs[], int i);

/*! \fn int isCorrectString( char* requiredString, mxArray *prhsi)
 \brief
 Goal : The goal is to compare a string to an element of prhs which must be a string.<BR>
 Output : O if the strings are different. 1 if they are the same.<BR>
 \param requiredString The required string
 \param prhsi The string which is an element of prhs
 */
int isCorrectString( char* requiredString, mxArray *prhsi);


/* String functions */


/*! \fn int get_string_length(mxArray* prhsi)
 \brief
 Output :Size of the string.<BR><BR>
 Typical code :<BR>
 char *message = malloc(sizeof(char)*(get_string_length(prhs[X])+1));<BR>
 message = get_string(prhs[X]);<BR>
 (...) using the variable message (...)<BR>
 free(message);<BR>

 \param a string element from prhs
 */

int get_string_length(mxArray* prhsi);

/*! \fn char* get_string(mxArray* prhsi)
 \brief
 Output : The string as a char*.<BR>
 \param prhsi a string element from prhs
 */

char* get_string(mxArray* prhsi);

/*! \fn set_string(char* message, mxArray* plhsi)
 \brief
 Output : none
 Other informations : The function sets the value of plhs[i] as the one of message.
 \param message The message you want as an output
 \param plhsi The element of plhs you want as the previous string.
 */

void set_string(char* message, mxArray* plhsi);


/* Array functions */


/*! \fn float* imageMatlabToC_malloc(mxArray *prhsi, int *nx, int *ny, int *nz)
 \brief
 Goal : prhsi is column-major image because of matlab's norm. The function creates a row-major image containing the same informations. Those are used by a majority of C-programs.<BR>
 Output : Pointer to the first element of the array.
 \param prhsi The element of prhs the user gets the image from.
 \param nx Pointer to the number of columns.
 \param ny Pointer to the number of rows.
 \param nz Pointer to the number of channels.
 */

float* imageMatlabToC_malloc(mxArray *prhsi, int *nx, int *ny, int *nz);

/*! \fn void imageCToMatlab(float* image, int nx, int ny, int number_of_channels, mxArray *plhs[], int i)
 \brief
 Goal : The function sends a row-major float array as a usable output within Matlab.<BR>
 Output : None.<BR>
 NOTE : As its names underlines it, the function allocates space for the float array. You must free it when you do not need it anymore.<BR>

 \param image The float-type image which must be sent to Matlab
 \param nx Pointer to the number of columns.
 \param ny Pointer to the number of rows.
 \param number_of_channels Number of channels of the image.
 \param plhs The plhs.
 \param i The element number of the image as an output.
 */


void imageCToMatlab(float* image, int nx, int ny, int number_of_channels, mxArray *plhs[], int i);

/*! \fn void imageMatlabToC(mxArray *prhsi, int number_of_channels, float* image)
 \brief
 Goal : prhsi is column-major image because of matlab's norm. The function creates a row-major image containing the same informations. Those are used by a majority of C-programs.<BR>
 Output : None.<BR>
 Other informations : It is a modified version of imageMatlabToC_malloc which is a void type function. The result is returned within the image variable.
 Example :<BR>
 
 I want to take an image from Matlab -the input argument- and send it back to Matlab -the output argument-.<BR>
 
 #include <stdio.h><BR>
 #include <stdlib.h><BR>
 #include "libmexipol.h"<BR>
 #include "mex.h"<BR>
 
 void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])<BR>
 {<BR>
     int nx, ny, nz;<BR>
     float *image = imageMatlabToC_malloc(prhs[0],&nx,&ny,&nz);<BR>
 	  //Here, the programmer has to use his algorithm with the pointer "image" : algorithm(image);<BR>
 	  //This part is only necessary if the programmer wants to get back the image as an output. For example if he made modifications on it.<BR>
     imageCToMatlab(image, nx, ny, nz, plhs,0);<BR>
     free(image);<BR>
 }

 \param prhsi The element of prhs the user gets the image from.
 \param nomber_of_channels Number of channels of the image.
 \param image Pointer to the image which is given by Matlab.
  */
void imageMatlabToC(mxArray *prhsi, int number_of_channels, float* image);

/* Structure functions */

/**
 * \struct getStruct
 * An array of getStruct can contain a full matlab's double structure. For example : [{one,1},{two,2}].
 * For more informations, take a look at get_structure_malloc.
 *
 */
struct getStruct {
	char* name;/*!< Name of the field. */
	double value;/*!< Double value within the field. */
};

typedef struct getStruct getStruct;

/*! \fn getStruct* get_structure_malloc(const mxArray* prhsi, int *numb_fields)
 \brief
 * \brief A necessary array vision of the structure
 * Goal : How to deal with the various and numerous parameters the user may need in order to use his algorithm properly ?<BR>
 * In a shell it is very easy to use optional parameters. However, within Matlab it is largely harder to manage it.<BR>
 * A solution is to use matlab's structures. It is very easy to create a structure within Matlab. A name is easily linked to a value.<BR>
 * For example in Matlab :<BR>
 * ---------------
 * option.one = 1;
 * option.two = 2;
 * option
 * -> option=
 * -> one: 1
 * -> two: 2
 * output=algorithm(input,option) (for example)
 * ---------------
 *
 * All the fields do not have to be explicited, and any of the optional values can be declared in any order. This is a good way to manage optional parameters.
 * The getStruct structure contains a fieldname and a value.
 * An array of getStruct can contain a full matlab's structure. For example : [{one,1},{two,2}].
 * Thus, the get_structure_malloc function has been designed to take a structure from matlab as an input, and give a getStruct array as an output. The mex-programmer can then easily deal with all the options the user choose, and with those the user does not choose.<BR>
 * As an example, the option input of the previous Matlab example would be : [{one,1},{two,2}].
 * The programmer can now easily use matlab's structures as he wish -mainly to manage optionnal parametres.
 * NOTE : As its names underlines it, the function allocates space for the getStruct array. You must free it when you do not need it anymore.<BR>
 
 \param prhsi The element of prhs the user gets the image from.
 \param nomber_of_channels Number of channels of the image.
 \param image Pointer to the image which is given by Matlab.
 */

getStruct* get_structure_malloc(const mxArray* prhsi, int *numb_fields);

/*! \fn getStruct* get_structure_malloc(const mxArray* prhsi, int *numb_fields)
 * \brief Goal : Transform a getStruct array into a structure given as a Matlab output.<BR>
 Here is an example of perfectly working code. The function takes a struct as an input and gives the same struct as an output.<BR>
 int n;<BR>
 getStruct* structure=get_structure_malloc(prhs[0], &n);<BR>
 // The getStruct array structure can be modified here
 set_structure(structure, plhs,0, n);<BR>
 free(structure);<BR>
 \param structure The getStruct array.
 \param plhs The plhs.
 \param i The output number.
 \param numb_fields The size of the array, i.e. the size of the structure.
 */

void set_structure(getStruct* structure, const mxArray* plhs[], int i, int numb_fields);


