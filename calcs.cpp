#include "calcs.h"

OperatingWithNeibs::OperatingWithNeibs(int my_num, int num_proc, double rView, double Lx, double Ly, double Lz)
{
	m_my_num = my_num;
	m_num_proc = num_proc;
	m_r_view = rView;
	m_Lx = Lx;
	m_Ly = Ly;
	m_Lz = Lz;
}


OperatingWithNeibs::~OperatingWithNeibs();
{
}

OperatingWithNeibs::SearchNeibAmount(NullPtrsReal &rMax, NullPtrsVecR &Cent, Period &prd)
{
	int Np1, Np2, i;
	double RM, Rx, Ry, Rz;
	double bb;

	m_NeibsM = 0;

	Np1 = m_my_num - 1;
	Np2 = m_my_num + 1;
	
	if (Np1 == 0) Np1 = m_num_proc - 1;
	if (Np2 > (m_num_proc - 1)) Np2 = 1;

	for (i = 1; i < m_num_proc; i++)
	{
		if (i != m_my_num)
		{
			RM = rMax.getValue(m_my_num) + rMax.getValue(i) + m_r_view * 5;
			RM = RM * RM;

			Rx = prd.Xa(Cent.getValueX(m_my_num), Cent.getValueX(i), m_Lx, 0, m_Lx);
			Ry = prd.Ya(Cent.getValueY(m_my_num), Cent.getValueY(i), m_Ly, 0, m_Ly);
			Rz = prd.Za(Cent.getValueZ(m_my_num), Cent.getValueZ(i), m_Lz, 0, m_Lz);
			
			bb = Rx * Rx + Ry * Ry + Rz * Rz;

			if (bb < RM || i == Np1 || i == Np2) m_NeibsM += 1;
		}
	}
	return m_NeibsM;
}


OperatingWithNeibs::*SearchNeibNumb(NullPtrsReal &rMax, NullPtrsVecR &Cent, Period &prd, NullPtrsInt &Neibs_num)
{
	int Np1, Np2, i, j;
	double RM, Rx, Ry, Rz;
	double bb;
	
	Np1 = m_my_num - 1;
	Np2 = m_my_num + 1;
	
	if (Np1 == 0) Np1 = m_num_proc - 1;
	if (Np2 > (m_num_proc - 1)) Np2 = 1;
	
	j = 0;
	
	for (i = 1; i < m_num_proc; i++)
	{
		if (i != m_my_num)
		{
			RM = rMax.getValue(m_my_num) + rMax.getValue(i) + m_r_view * 5;
			RM = RM * RM;
				
			Rx = prd.Xa(Cent.getValueX(m_my_num), Cent.getValueX(i), m_Lx, 0, m_Lx);
			Ry = prd.Ya(Cent.getValueY(m_my_num), Cent.getValueY(i), m_Ly, 0, m_Ly);
			Rz = prd.Za(Cent.getValueZ(m_my_num), Cent.getValueZ(i), m_Lz, 0, m_Lz);
	
			bb = Rx * Rx + Ry * Ry + Rz * Rz;
	
			if (bb < RM || i == Np1 || i == Np2) {Neibs_num.setValue(j, i); j += 1;}
		}
	}
	
	return &Neibs_num;
}


/**************************************************/

NatTo::NatTo()
{
}

NatTo::~NatTo()
{
}

NatTo::setValueRR(int index, double value)
{ RR[index] = value; }

NatTo::setValueCx(int index, double value)
{ Cx[index] = value; }

NatTo::setValueCy(int index, double value)
{ Cy[index] = value; }

NatTo::setValueCz(int index, double value)
{ Cz[index] = value; }

NatTo::setValueN1(int value)
{ N1 = value; }

NatTo::setValueN2(int value)
{ N2 = value; }

NatTo::getValueRR(int index) const
{ return RR[index]; }

NatTo::getValueCx(int index) const
{ return Cx[index]; }

NatTo::getValueCy(int index) const
{ return Cy[index]; }

NatTo::getValueCz(int index) const
{ return Cz[index]; }

NatTo::getValueN1() const
{ return N1; }

NatTo::getValueN2() const
{ return N2; }

NatTo::MpPair(std::vector<NatTo>&Nat, int my_num, int n, NullPtrsVecR &Cent, CalcSpace Space)
{
	int k; 
	double Wx, Wy, Wz; 
	double Rx, Ry, Rz, qq;
	
	for (k = 0; k < 8; k++)
	{
		Nat[n].setValueRR(k, (Space.Lx * Space.Lx + Space.Ly * Space.Ly + Space.Lz * Space.Lz));
		Nat[n].setValueCx(k, -1);
		Nat[n].setValueCy(k,  0);
		Nat[n].setValueCz(k,  0);
	}

	Wx =- (Cent.getValueX(n) - Cent.getValueX(my_num)) / 2;
	Wy =- (Cent.getValueY(n) - Cent.getValueY(my_num)) / 2;
	Wz =- (Cent.getValueZ(n) - Cent.getValueZ(my_num)) / 2;
		
	if (Wx >  0) Rx = Wx;				else Rx = Wx + Space.Lx;	//1 quadrant
	if (Wy >= 0) Ry = Wy;				else Ry = Wy + Space.Ly;
	if (Wz >= 0) Rz = Wz;				else Rz = Wz + Space.Lz;
		
	DirCos(0, n, Rx, Ry, Rz, Nat);

	if (Wx >  0) Rx = Wx - Space.Lx;	else Rx = Wx;				//2 quadrant
	if (Wy >= 0) Ry = Wy;				else Ry = Wy + Space.Ly;
	if (Wz >= 0) Rz = Wz;				else Rz = Wz + Space.Lz;
		
	DirCos(1, n, Rx, Ry, Rz, Nat);

	if (Wx >  0) Rx = Wx;				else Rx = Wx + Space.Lx;	//3 quadrant
	if (Wy >= 0) Ry = Wy - Space.Ly;	else Ry = Wy;
	if (Wz >= 0) Rz = Wz;				else Rz = Wz + Space.Lz;
		
	DirCos(2, n, Rx, Ry, Rz, Nat);

	if (Wx >  0) Rx = Wx - Space.Lx;	else Rx = Wx;				//4 quadrant
	if (Wy >= 0) Ry = Wy - Space.Ly;	else Ry = Wy;
	if (Wz >= 0) Rz = Wz;				else Rz = Wz + Space.Lz;
		
	DirCos(3, n, Rx, Ry, Rz, Nat);

	if (Wx >  0) Rx = Wx;				else Rx = Wx + Space.Lx;	//5 quadrant
	if (Wy >= 0) Ry = Wy;				else Ry = Wy + Space.Ly;
	if (Wz >= 0) Rz = Wz - Space.Lz;	else Rz = Wz;
		
	DirCos(4, n, Rx, Ry, Rz, Nat);

	if (Wx >  0) Rx = Wx - Space.Lx;	else Rx = Wx;				//6 quadrant
	if (Wy >= 0) Ry = Wy;				else Ry = Wy + Space.Ly;
	if (Wz >= 0) Rz = Wz - Space.Lz;	else Rz = Wz;
		
	DirCos(5, n, Rx, Ry, Rz, Nat);

	if (Wx >  0) Rx = Wx;				else Rx = Wx + Space.Lx;	//7 quadrant
	if (Wy >= 0) Ry = Wy - Space.Ly;	else Ry = Wy;
	if (Wz >= 0) Rz = Wz - Space.Lz;	else Rz = Wz;
		
	DirCos(6, n, Rx, Ry, Rz, Nat);

	if (Wx >  0) Rx = Wx - Space.Lx;	else Rx = Wx;				//8 quadrant
	if (Wy >= 0) Ry = Wy - Space.Ly;	else Ry = Wy;
	if (Wz >= 0) Rz = Wz - Space.Lz;	else Rz = Wz;
		
	DirCos(7, n, Rx, Ry, Rz, Nat);

	for (k = 0; k < 7; k++)
	{
		if (Nat[n].getValueRR(k) > Nat[n].getValueRR(k + 1))
		{
			qq = Nat[n].getValueRR(k);
			Rx = Nat[n].getValueCx(k);
			Ry = Nat[n].getValueCy(k);
			Rz = Nat[n].getValueCz(k);

			Nat[n].setValueRR(k, Nat[n].getValueRR(k + 1));
			Nat[n].setValueCx(k, Nat[n].getValueCx(k + 1));
			Nat[n].setValueCy(k, Nat[n].getValueCy(k + 1)); 
			Nat[n].setValueCz(k, Nat[n].getValueCy(k + 1));

			Nat[n].setValueRR(k + 1, qq);
			Nat[n].setValueCx(k + 1, Rx);
			Nat[n].setValueCy(k + 1, Ry);
			Nat[n].setValueCy(k + 1, Rz);
		}
	}
	return Nat[n];
}