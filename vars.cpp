#include "vars.h"

NullPtrsInt::NullPtrsInt(int leight, int numb)
{
	m_ptr.resize(leight, numb);
}

NullPtrsInt::~NullPtrsInt()
{
	m_ptr.clear();
}

NullPtrsInt::setValue(int index, int value)
{ 
	m_ptr.at(index) = value;
}

NullPtrsInt::getValue(int index) const
{
	return m_ptr.at(index);
}

/**************************************************/

NullPtrsVecR::NullPtrsVecR(int leight, int numb)
{
	m_ptr.resize(leight, numb);
}

NullPtrsVecR::~NullPtrsVecR()
{
	m_ptr.clear();
}

NullPtrsVecR::setValueX(int index, double value)
{
	m_ptr.at(index).x = value;
}

NullPtrsVecR::setValueY(int index, double value)
{
	m_ptr.at(index).y = value;
}

NullPtrsVecR::setValueZ(int index, double value)
{
	m_ptr.at(index).z = value;
}

NullPtrsVecR::getValueX(int index) const
{
	return m_ptr.at(index).x;
}

NullPtrsVecR::getValueY(int index) const
{
	return m_ptr.at(index).y;
}

NullPtrsVecR::getValueZ(int index) const
{
	return m_ptr.at(index).z;
}