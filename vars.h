#ifndef VARS_H
#define VARS_H

class NullPtrsInt
{
private:
	std::vector<int> m_ptr;
	
public:
	
	NullPtrsInt(int leight, int numb);

	~NullPtrsInt();
	
	void setValue(int index, int value);

	int getValue(int index) const;
};


/**************************************************/

struct VecR
{
	double x, y, z;
};

class NullPtrsVecR
{
private:
	std::vector<VecR> m_ptr;
	
public:

	NullPtrsVecR(int leight);

	~NullPtrsVecR();

	void setValueX(int index, double value);
	void setValueY(int index, double value);
	void setValueZ(int index, double value);

	double getValueX(int index) const;
	double getValueY(int index) const;
	double getValueZ(int index) const;
};

#endif