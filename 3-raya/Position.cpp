#include "Position.h"

Position::Position(int nRow /*= 0*/, int nColumn /*= 0*/) {
	Row = nRow;
	Column = nColumn;
}

bool Position::Valid()
{
	return (Column >= 0 && Column < 3 &&
		    Row >= 0 && Row < 3);
}

void Position::operator++()
{
	// Last element of the current row
	if (Column == 2) {
		// Last row, undefined Position
		if (Row == 2) {
			Column = -1;
			Row = -1;

			return;
		}
		else {
			// Next Row
			Row++;
			// Go back to the first column
			Column = 0;

			return;
		}
	}
	// General case
	else {
		Column++;
	}
}
