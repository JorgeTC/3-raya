#pragma once

class Position {
public:
	Position(int nRow = 0, int nColumn = 0);

	bool Valid();

	void operator++();

	int Row;
	int Column;
};
