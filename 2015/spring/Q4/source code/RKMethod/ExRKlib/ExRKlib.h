/*
RK serial methods for systems of ODE.
*/
#pragma once

#include "export.h"

namespace ExRKM
{

typedef  void (*YFunc)(double, double*, double*); //f(t,y)

class ExRKMDLL ExRKMethod
{
public:
	ExRKMethod();
	virtual ~ExRKMethod();
	//define several default methods
	enum RK_Method
	{
		ForwardEuler = 0,
		MidPoint,
		Heun_Method,
		Stage_3_Method,
		Stage_4_Method,
		Stage_6_Method
	};
	//using default methods and coefficients
	void InitCoeff(RK_Method rk);
	/* define stage of method and coefficients by users
	*  iStage is the stage of RK method
	*  A[iStage*iStage], B[iStage], C[iStage]
	*/
	void InitCoeff(int iStage, double *A, double *B, double *C);
	//input function 'f(t,y)' and exact solution 'y(t)'
	void InitFunc(YFunc funcYPrime, YFunc funcYExact = NULL)
	{
		m_FuncYPrime = funcYPrime;
		m_FuncYExact = funcYExact;
	}
	//check coefficients in array of m_A,m_B,m_C
	bool CheckCoefficient();

	//compute the result
	bool Run(int iN, double t0, double *y0, double deltaT, double T, double *fResult, char *&strLog);

protected:
	void AllocateArray(int iStage);
	//default methods initiation
	void InitCoeff_FE();
	void InitCoeff_MidPoint();
	void InitCoeff_Heun();
	void InitCoeff_Stage_3();
	void InitCoeff_Stage_4();
	void InitCoeff_Stage_6();

	bool CheckSettings(char *&strLog);

	bool Calc(double *fResult, char *&strLog);
	void CalcOneStep(double tCurr, double tDelta, double *yCurr);
	double EuclideanNorm(double *p);
private:
	YFunc m_FuncYPrime;
	YFunc m_FuncYExact;

	int m_iStage;

	double *m_A;
	double *m_B;
	double *m_C;

	int m_iN;//length of vector W
	double m_tT0;
	double *m_fY0;
	double m_tDeltaT;
	double m_tT;







};

}
