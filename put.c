/*
 * put.c
 *
 * Wrapper of the MatLab Engine API engPutVariable
 * for call from Mathematica
 *
 * Revision 2003.3.11
 *
 * Robert
 *	
 */
#include <string.h>
#include "stdlib.h"
#include "mathlink.h"
#include "engine.h"

#include "Eng.h"
// extern Engine* Eng;

extern void msg(const char* m);

// put a real array to the MatLab workspace
void engputr(const char* VarName,
		     const int* Dim, int Depth,
		     const double* Val, int ValLen)
{
    // mwSize *newDim;
    // newDim = (mwSize*)Dim;
    // mwSize newDim[]={1,3};
    mwSize newDim[Depth];
    int i;
    for(i = 0; i < Depth; ++i)
    {
        newDim[i] = (mwSize)Dim[i];
    }
    mwSize newDepth;
    newDepth = (mwSize)Depth;
	mxArray* MxVar = NULL;		//the variable to be put
	bool SUCCESS = true;		//success flag
	if (NULL == Eng)	//if not opened yet
	{
		msg("eng::noMLB");	//message 
		SUCCESS = false;
		goto epilog;
	}
	
	//create mxArray 
    // MxVar = mxCreateNumericArray(Depth, Dim, mxDOUBLE_CLASS, mxREAL);
    // char stuff[100] = "B;a ;alsj asldjasdf ";
    // stuff[1] = "T";
    // MLPutInteger(stdlink, newDepth);
	MxVar = mxCreateNumericArray(newDepth, newDim, mxDOUBLE_CLASS, mxREAL);
	if (NULL == MxVar)
	{
		msg("engPut::ercrt");
		SUCCESS = false;
		goto epilog;
	}
	//and populate
	
	unsigned char *start_of_pr;
    start_of_pr = (unsigned char *)mxGetData(MxVar);
    size_t bytes_to_copy;
    bytes_to_copy = ValLen * mxGetElementSize(MxVar);
    memcpy(start_of_pr,Val,bytes_to_copy);
	
    // memcpy((void *)(mxGetPr(MxVar)), (void *)Val, ValLen * sizeof(double));
	
	//put
	if(engPutVariable(Eng, VarName, MxVar))	//not successful
	{
		msg("engPut::erput");
		SUCCESS = false;
		goto epilog;
	}
	
epilog:
	if (MxVar != NULL)
		mxDestroyArray(MxVar);

	if(SUCCESS)
		MLPutString(stdlink, VarName);
	else
		MLPutSymbol(stdlink, "$Failed");
}

//put a complex array
void engputc(const char* VarName,
		     const int* Dim, int Depth,
		     const double* Re, int ReLen,
		     const double* Im, int ImLen)
{
    mwSize newDim[Depth];
    int i;
    for(i = 0; i < Depth; ++i)
    {
        newDim[i] = (mwSize)Dim[i];
    }
	mxArray* MxVar = NULL;		//the variable to be put
	bool SUCCESS = true;		//success flag

	if (NULL == Eng)	//if not opened yet, open it
	{
		msg("eng::noMLB");	//message 
		SUCCESS = false;
		goto epilog;
	}
	
	//create mxArray 
	MxVar = mxCreateNumericArray(Depth, newDim, mxDOUBLE_CLASS, mxCOMPLEX);
	if (NULL == MxVar)
	{
		msg("engPut::ercrt");
		SUCCESS = false;
		goto epilog;
	}
	
	unsigned char *start_of_pr;
    size_t bytes_to_copy;
	start_of_pr = (unsigned char *)mxGetData(MxVar);
    bytes_to_copy = ReLen * mxGetElementSize(MxVar);
    memcpy(start_of_pr,Re,bytes_to_copy);

	start_of_pr = (unsigned char *)mxGetImagData(MxVar);
    bytes_to_copy = ImLen * mxGetElementSize(MxVar);
    memcpy(start_of_pr,Im,bytes_to_copy);
	
	
	//and populate
    // memcpy((void *)(mxGetPr(MxVar)), (void *)Re, ReLen * sizeof(double));
    // memcpy((void *)(mxGetPi(MxVar)), (void *)Im, ImLen * sizeof(double));

	//put
	if(engPutVariable(Eng, VarName, MxVar))	//not successful
	{
		msg("engPut::erput");
		SUCCESS = false;
		goto epilog;
	}
	
epilog:
	if (MxVar != NULL)
		mxDestroyArray(MxVar);

	if(SUCCESS)
		MLPutString(stdlink, VarName);
	else
		MLPutSymbol(stdlink, "$Failed");
}

