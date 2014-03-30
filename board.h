#include <string>
#include <random>

class Board
{
public:
	enum Direction {
		up,
		right,
		down,
		left,
	};

	explicit Board(unsigned seed);
	Board(unsigned seed, const int state[]);

	void turn(Direction dir);

	void move(Direction dir);
	void collapse(Direction dir);

	std::string str() const;
	void add();

	bool complete() const;

	int operator[](int index) const;

	int max() const;

	bool operator==(const Board& other) const;
	bool operator!=(const Board& other) const { return !this->operator==(other); }

	bool operator<(const Board& other) const;
	bool operator>(const Board& other) const { return other.operator<(*this);}
	bool operator<=(const Board& other) const { return !this->operator>(other);}
	bool operator>=(const Board& other) const { return !this->operator<(other);}

private:

	static int next(Direction dir, int current);
	static int nextRow(Direction dir, int current);
	static int initPos(Direction dir);
	static Direction reversePosition(Direction dir);
	void swap(int a, int b);

	int m_state[16];
	std::default_random_engine m_generator;
};

