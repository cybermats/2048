#include "board.h"

#include <sstream>
#include <assert.h>
#include <chrono>


Board::Board()
	: Board(std::chrono::system_clock::now().time_since_epoch().count())
{}

Board::Board(unsigned seed)
	: m_generator(seed)
{
	for(int i = 0; i < 16; ++i)
		m_state[i] = 0;
	add();
	add();
}

Board::Board(unsigned seed, const int state[])
	: m_generator(seed)
{
	for(int i = 0; i < 16; ++i)
		m_state[i] = state[i];
}

std::string Board::str() const
{
	std::stringstream ss;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			ss << "\t" << m_state[i*4 + j];
		}
		ss << std::endl;
	}
	return ss.str();
}

void Board::add()
{
	int empties = 0;
	for(int i = 0; i < 16; ++i)
	{
		if(m_state[i] == 0)
			empties++;
	}

	if(empties == 0)
		return;

	std::uniform_int_distribution<int> distribution(0,empties - 1);
	int location = distribution(m_generator);

	int counter = 0;
	for(int i = 0; i < 16; ++i)
	{
		if(m_state[i] != 0)
			continue;

		if(counter == location)
		{
			m_state[i] = 2;
			break;
		}
		counter++;
	}
}
int Board::next(Direction dir, int current)
{
	if(nextRow(dir, current)>=0)
		return -1;

	switch(dir)
	{
	case up:
		if(current > 0)
			return current - 4;
		else 
			return -1;
	case down:
		if(current < 15)
			return current + 4;
		else 
			return -1;
	case left:
		if(current < 15)
			return current + 1;
		else 
			return -1;
	case right:
		if(current > 0)
			return current - 1;
		else 
			return -1;
	}
	return -1;
}


int Board::nextRow(Direction dir, int current)
{
	switch(dir)
	{
	case up:
		if (current > 0 && current < 4)
			return current + 11;
		else 
			return -1;
	case down:
		if (current >= 12 && current < 15)
			return current - 11;
		else 
			return -1;
	case left:
		if (current % 4 == 3 && current != 15)
			return current + 1;
		else 
			return -1;
	case right:
		if (current % 4 == 0 && current != 0)
			return current - 1;
		else 
			return -1;
	}
	return -1;
}

int Board::initPos(Direction dir)
{
	switch(dir)
	{
	case left:
	case down:
		return 0;
	case right:
	case up:
		return 15;
	}
	return -1;
}

Board::Direction Board::reversePosition(Direction dir)
{
	switch(dir)
	{
	case left:
		return right;
	case down:
		return up;
	case right:
		return left;
	case up:
		return down;
	}
	return up;
}

void Board::swap(int a, int b)
{
	int temp = m_state[b];
	m_state[b] = m_state[a];
	m_state[a] = temp;
}

void Board::turn(int idir)
{
	assert(dir < 4 && dir >= 0);

	Direction dir;
	switch(idir)
	{
		case 0:	dir = up; break;
		case 1:	dir = right; break;
		case 2:	dir = down; break;
		case 3:	dir = left; break;
	}
	turn(dir);
}

void Board::turn(Direction dir)
{
	Board original = *this;
	move(dir);
	collapse(dir);
	move(dir);

	if(original != *this)
		add();
}

void Board::move(Direction dir)
{
	// simple move
	int currLoc;
	int nextLoc = initPos(dir);

	for(int i = 0; i < 4; ++i)
	{
		bool swapped;
		int initNext = nextLoc;
		do
		{
			swapped = false;
			for(int j = 0; j < 3; ++j)
			{
				currLoc = nextLoc;
				nextLoc = next(dir, nextLoc);
				if(m_state[nextLoc] == 0 && m_state[currLoc] != 0)
				{
					swap(currLoc, nextLoc);
					swapped = true;
				}
			}
			nextLoc = initNext;
		} 
		while(swapped);
		nextLoc = nextRow(dir, next(dir, currLoc));
	}
}

void Board::collapse(Direction dir)
{
	dir = reversePosition(dir);
	int currLoc;
	int nextLoc = initPos(dir);

	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			currLoc = nextLoc;
			nextLoc = next(dir, nextLoc);
			if((m_state[nextLoc] != 0) && (m_state[currLoc] == m_state[nextLoc]))
			{
				m_state[nextLoc] *= 2;
				m_state[currLoc] = 0;
			}
		}
		nextLoc = nextRow(dir, next(dir, currLoc));
	}
}

bool Board::complete() const
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			int a = (i * 4) + j;
			int an = (i * 4) + j + 1;
			int b = (j * 4) + i;
			int bn = ((j + 1) * 4) + i;
			if(m_state[a] == 0)
				return false;

			if(m_state[a] == m_state[an])
				return false;

			if(m_state[b] == m_state[bn])
				return false;
		}
	}
	return true;
}

int Board::operator[](int index) const
{
	assert(0 <= index && index < 16);
	return m_state[index];
}

std::vector<int> Board::GetValues() const
{
	std::vector<int> outputs;
	for(int i = 0; i < 16; ++i)
		outputs.push_back(m_state[i]);
	return outputs;
}


int Board::max() const
{
	int value = 0;
	for(int i = 0; i < 16; ++i)
	{
		if (m_state[i] > value)
			value = m_state[i];
	}
	return value;
}

bool Board::operator==(const Board& other) const
{
	for(int i = 0; i < 16; ++i)
	{
		if(m_state[i] != other.m_state[i])
			return false;
	}
	return true;
}

bool Board::operator<(const Board& other) const
{
	for(int i = 0; i < 16; ++i)
	{
		if(m_state[i] < other.m_state[i])
			return true;
		if(m_state[i] > other.m_state[i])
			return false;
	}
	return false;
}

std::ostream& operator<< (std::ostream& stream, const Board board)
{
	stream << board.str();
	return stream;
}
