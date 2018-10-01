#ifndef PAIR_HPP
#define PAIR_HPP

class Pair
{
public:
	unsigned int m_a;

	unsigned int m_b;

public:

	Pair() :
		m_a(0), m_b(0)
	{

 	}

	Pair(unsigned int a, unsigned int b) :
		m_a(a), m_b(b)
	{

	}

	// put the lesser value into a and the greater value into b
	void order()
	{
		if(m_b < m_a)
		{
			unsigned int tmp = m_a;

			m_a = m_b;

			m_b = tmp;	
		}
	}

	bool operator==(const Pair& other)
	{
		return (m_a == other.m_a && m_b == other.m_b) ||
			(m_a == other.m_b && m_b == other.m_a);
	}
};

#endif
