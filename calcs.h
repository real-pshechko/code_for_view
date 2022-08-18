#ifndef CALCS_H
#define CALCS_H

#include "vars.h"

class OperatingWithNeibs
{
private:
	int m_my_num, m_num_proc, m_NeibsM;
	double m_r_view, m_Lx, m_Ly, m_Lz;

public:
	OperatingWithNeibs(int my_num, int num_proc, double rView, double Lx, double Ly, double Lz);

	~OperatingWithNeibs();


	int SearchNeibAmount(NullPtrsReal &rMax, NullPtrsVecR &Cent, Period &prd);
	
	NullPtrsInt *SearchNeibNumb(NullPtrsReal &rMax, NullPtrsVecR &Cent, Period &prd, NullPtrsInt &Neibs_num);
	
};


/**************************************************/

class NatTo
{
private:
	double RR[7], Cx[7], Cy[7], Cz[7];
	int N1, N2;

public:

	NatTo();

	~NatTo();

	void setValueRR(int index, double value); 
	void setValueCx(int index, double value); 
	void setValueCy(int index, double value); 
	void setValueCz(int index, double value); 

	void setValueN1(int value); 
	void setValueN2(int value); 


	double getValueRR(int index) const; 
	double getValueCx(int index) const; 
	double getValueCy(int index) const; 
	double getValueCz(int index) const; 

	int getValueN1() const; 
	int getValueN2() const; 

	friend void DirCos(int k, int n, double Rx, double Ry, double Rz, std::vector<NatTo>&Nat);

	NatTo MpPair(std::vector<NatTo>&Nat, int my_num, int n, NullPtrsVecR &Cent, CalcSpace Space);
	
};

void DirCos(int k, int n, double Rx, double Ry, double Rz, std::vector<NatTo>&Nat)
{
	double qq;
	qq = sqrt(Rx * Rx + Ry * Ry + Rz * Rz);
	Nat[n].setValueRR(k, qq);

	if (qq > 0)
	{
		Nat[n].setValueCx(k, -Rx/qq);
		Nat[n].setValueCy(k, -Ry/qq);
		Nat[n].setValueCz(k, -Rz/qq);
	}
	else
	{
		Nat[n].setValueCx(k, -1);
		Nat[n].setValueCy(k,  0);
		Nat[n].setValueCz(k,  0);
	}
}





#endif