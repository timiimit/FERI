#include <limits.h>
#include <Windows.h>

#include <vector>
#include <iostream>
#include <string>

#define PRINT
//#define PRINT_ERROR

using namespace std;

#define _D_BOARDSIZE 8
#define minValue 4
#if _D_BOARDSIZE <= minValue

typedef signed char Vector;
typedef unsigned int CountType;

#elif _D_BOARDSIZE <= minValue << 4

typedef signed short Vector;
typedef unsigned int CountType;

#elif _D_BOARDSIZE <= minValue << 12

typedef signed int Vector;
typedef unsigned int CountType;

#else // cant be larger type than this

typedef signed long long Vector;
typedef unsigned long long CountType;

#endif

//typedef unsigned int CountType;
typedef Vector ValueType;

inline bool IsBounded(Vector pos);
void Skaci2(Vector pos);

const ValueType boardSize = _D_BOARDSIZE;
const CountType boardFieldCount = boardSize * boardSize;
const CountType bitsPerCoordinate = sizeof(Vector) * 8 / 2; // half of all bits
const CountType rightBitMask = CountType(-1) >> (sizeof(CountType) * 8 - bitsPerCoordinate);

const CountType shortMove = 1;
const CountType longMove = 2;
const CountType possibleMoveCount = 8;

CountType filledCount = 1;
CountType board[boardSize] = {};
vector<Vector> history;

inline bool IsBounded(Vector pos)
{
	return ((pos & rightBitMask) < boardSize && ((pos >> bitsPerCoordinate) & rightBitMask) < boardSize) && ((pos & rightBitMask) >= 0 && ((pos >> bitsPerCoordinate) & rightBitMask) >= 0);
}

bool IsOn(Vector location)
{
	return (board[(location >> bitsPerCoordinate) & rightBitMask] >> (location & rightBitMask)) & 1;
}

void SetOn(Vector location)
{
	board[(location >> bitsPerCoordinate) & rightBitMask] |= 1 << (location & rightBitMask);
}


void PrintBoard(Vector current)
{
	for (Vector y = 0; y < boardSize; ++y)
	{
		for (Vector x = 0; x < boardSize; ++x)
		{
			Vector pos = x | (y << bitsPerCoordinate);
			if (pos == current)
			{
				cout << "# ";
			}
			else if (IsOn(pos))
			{
				cout << "- ";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

Vector GetDistance(Vector v1, Vector v2)
{
	Vector x = abs(ValueType(v1 & rightBitMask) - ValueType(v2 & rightBitMask));
	Vector y = abs(ValueType((v1 >> bitsPerCoordinate) & rightBitMask) - ValueType((v2 >> bitsPerCoordinate) & rightBitMask));
	return x + y;
}

Vector Subtract(Vector v1, Vector v2, Vector& rx, Vector& ry)
{
	rx = (v1 & rightBitMask) - (v2 & rightBitMask);
	ry = (ValueType((v1 >> bitsPerCoordinate) & rightBitMask) - ValueType((v2 >> bitsPerCoordinate) & rightBitMask));
	return rx | (ry << bitsPerCoordinate);
}

Vector MoveTo(Vector pos, Vector target)
{
	Vector x;
	Vector y;
	Subtract(target, pos, x, y);
	Vector longerMove;
	Vector shorterMove;

	if ((abs(x) + abs(y) <= 3))
	{
		longerMove = shortMove;
		shorterMove = longMove;
	}
	else
	{
		longerMove = longMove;
		shorterMove = shortMove;
	}

	if (abs(x) > abs(y)) // if delta x is larger than y
	{
		//move by 2 across x and 1 across y
		x = (x > 0 ? longerMove : -longerMove);
		y = (y > 0 ? shorterMove : -shorterMove);

		ValueType f = ValueType((pos & rightBitMask) + x);
		if (f > boardSize)
			x -= longerMove * 2;
		else if (f < 0)
			x += longerMove * 2;

		f = ValueType(((pos >> bitsPerCoordinate) & rightBitMask) + y);
		if (f > boardSize)
			y -= shorterMove * 2;
		else if (f < 0)
			y += shorterMove * 2;
	}
	else
	{
		//move by 2 across y and 1 across x
		x = (x > 0 ? shorterMove : -shorterMove);
		y = (y > 0 ? longerMove : -longerMove);

		ValueType f = ValueType((pos & rightBitMask) + x);
		if (f >= boardSize)
			x -= shorterMove * 2;
		else if (f < 0)
			x += shorterMove * 2;

		f = ValueType(((pos >> bitsPerCoordinate) & rightBitMask) + y);
		if (f >= boardSize)
			y -= longerMove * 2;
		else if (f < 0)
			y += longerMove * 2;
	}

	return pos + x + y * (1 << bitsPerCoordinate);
}

bool MakeMove(Vector next, bool mustBeNew)
{
	if (IsBounded(next))
	{
		bool on = IsOn(next);
		if (!on)
		{
			SetOn(next);
			filledCount++;
		}
		if (!mustBeNew || !on)
		{
			history.push_back(next);
			return true;
		}
	}
	return false;
}

Vector FindNearestEmpty(Vector pos)
{
	Vector nearest = pos;
	for (Vector y = 0; y < boardSize; ++y)
	{
		for (Vector x = 0; x < boardSize; ++x)
		{
			Vector xy = x | (y << bitsPerCoordinate);
			if (!IsOn(xy))
			{
				Vector a = GetDistance(pos, xy);
				Vector b = GetDistance(pos, nearest);
				if ((a < b || nearest == pos) && xy != history[history.size() - 1])
				{
					nearest = xy;
				}
			}
		}
	}
	return nearest;
}

Vector FindFarthestEmpty(Vector pos)
{
	Vector nearest = pos;
	for (Vector y = 0; y < boardSize; ++y)
	{
		for (Vector x = 0; x < boardSize; ++x)
		{
			Vector xy = x | (y << bitsPerCoordinate);
			if (!IsOn(xy))
			{
				Vector a = GetDistance(pos, xy);
				Vector b = GetDistance(pos, nearest);
				if ((a > b || nearest == pos) && xy != history[history.size() - 1])
				{
					nearest = xy;
				}
			}
		}
	}
	return nearest;
}

Vector FindSmartMove(Vector pos)
{
	Vector nearest = FindNearestEmpty(pos);

	Vector next = MoveTo(pos, nearest);
	if (next == history[history.size() - 2] && next == history[history.size() - 4])
	{
		next = Subtract(pos, next, nearest, next); // FindFarthestEmpty(pos);
		next = MoveTo(pos, next);
	}
	return next;
}

void Skaci2(Vector pos)
{
#ifdef PRINT
	system("cls");
	cout << filledCount << '/' << boardFieldCount << endl;
	PrintBoard(pos);
	Sleep(100);
#endif

	if (filledCount >= boardFieldCount)
	{
		// knight was on all coordinates
		return;
	}

	for (int r = 0; r < possibleMoveCount; ++r)
	{
		Vector val = (r & 0b10 ? (r & 0b01) + 1 : -((r & 0b01) + 1));
		Vector val2 = (r & 0b100 ? 1 : -1) * (abs(val) == 2 ? 1 << bitsPerCoordinate : 1 << (bitsPerCoordinate+1));
		Vector next = pos + (val + val2);

		if (MakeMove(next, true))
		{
			Skaci2(next);
			return;
		}
	}
	Vector next = FindSmartMove(pos);
	if (MakeMove(next, false))
	{
		Skaci2(next);
	}
	else
	{
		for (int r = 0; r < possibleMoveCount; ++r)
		{
			Vector val = (r & 0b10 ? (r & 0b01) + 1 : -((r & 0b01) + 1));
			Vector val2 = (r & 0b100 ? 1 : -1) * (abs(val) == 2 ? 1 << bitsPerCoordinate : 1 << (bitsPerCoordinate + 1));
			Vector next = pos + (val + val2);

			if (MakeMove(next, false))
			{
				for (int r = 0; r < possibleMoveCount; ++r)
				{
					Vector val = (r & 0b10 ? (r & 0b01) + 1 : -((r & 0b01) + 1));
					Vector val2 = (r & 0b100 ? 1 : -1) * (abs(val) == 2 ? 1 << bitsPerCoordinate : 1 << (bitsPerCoordinate + 1));
					Vector next = pos + (val + val2);

					if (MakeMove(next, false))
					{
						for (int r = 0; r < possibleMoveCount; ++r)
						{
							Vector val = (r & 0b10 ? (r & 0b01) + 1 : -((r & 0b01) + 1));
							Vector val2 = (r & 0b100 ? 1 : -1) * (abs(val) == 2 ? 1 << bitsPerCoordinate : 1 << (bitsPerCoordinate + 1));
							Vector next = pos + (val + val2);

							if (MakeMove(next, false))
							{
								Skaci2(next);
								return;
							}
						}
						return;
					}
				}
				return;
			}
		}
#ifdef PRINT_ERROR
		system("cls");
		cout << filledCount << '/' << boardFieldCount << endl;
		PrintBoard(pos);
		Sleep(100);
#endif
		//Vector next = FindSmartMove(pos);
	}

}

void main()
{
	cout << "Enter position on a chess board: ";
	string read;

	Vector start;

	while (true)
	{
		cin >> read;

		if (read.length() == 2)
		{
			start = (read[0] - 'A') | ((read[1] - '1') << bitsPerCoordinate);
			if (IsBounded(start))
			{
				break;
			}
		}
		cout << "Please enter a valid position. between A1 and H8." << endl;
	}



	SetOn(start);
	history.push_back(start);

	Skaci2(start);

	cout << history.size() << '/' << boardFieldCount << endl << endl;

	for (CountType i = 0; i < history.size(); ++i)
	{
		int x = history[i] & rightBitMask;
		int y = (history[i] >> bitsPerCoordinate) & rightBitMask;
		cout << char('A' + x) << (y + 1) << endl;
	}
	system("pause");
}