#include <string>
#include <random>

class Board
{
public:
	enum Direction {
		up = 0,
		right,
		down,
		left,
	};

	Board();
	explicit Board(unsigned seed);
	Board(unsigned seed, const int state[]);

	void turn(int dir);
	void turn(Direction dir);

	std::vector<int> GetValues() const;
	bool complete() const;
	int max() const;

	std::string str() const;

	friend std::ostream& operator<< (std::ostream& stream, const Board board);



	int operator[](int index) const;


	bool operator==(const Board& other) const;
	bool operator!=(const Board& other) const { return !this->operator==(other); }

	bool operator<(const Board& other) const;
	bool operator>(const Board& other) const { return other.operator<(*this);}
	bool operator<=(const Board& other) const { return !this->operator>(other);}
	bool operator>=(const Board& other) const { return !this->operator<(other);}

private:

	void move(Direction dir);
	void collapse(Direction dir);
	void add();

	static int next(Direction dir, int current);
	static int nextRow(Direction dir, int current);
	static int initPos(Direction dir);
	static Direction reversePosition(Direction dir);
	void swap(int a, int b);

	int m_state[16];
	std::default_random_engine m_generator;
};

