<?php

class Point
{
	public $X;
	public $Y;

	public function __construct($x, $y)
	{
		$this->X = $x;
		$this->Y = $y;
	}
}

class Ship
{
	public $Position;
	public $Size;

	public function __construct($p, $s)
	{
		$this->Position = $p;
		$this->Size = $s;
	}
}

function RandomShipOrientation($xySize)
{
	$xSize = $xySize[rand(0, 1)];
	if ($xySize[0] == $xSize)
		$ySize = $xySize[1];
	else
		$ySize = $xySize[0];

	return new Point($xSize, $ySize);
}

function AreShipsOverlapping($ship1, $ship2)
{
	return
		$ship1->{$Position->x} < $ship2->{$Position->x} + $ship2->{$Size->x} &&
		$ship1->{$Position->y} < $ship2->{$Position->y} + $ship2->{$Size->y} &&
		$ship1->{$Position->x} + $ship1->{$Size->x} > $ship2->{$Position->x} &&
		$ship1->{$Position->y} + $ship1->{$Size->y} > $ship2->{$Position->y};
}

function CanPlaceShip($ship)
{
	$no = count($_SESSION["ships"]);
	for ($i = 0; $i < $no; ++$i)
	{
		if (AreShipsOverlapping($ship, $_SESSION["ships"][$i]))
			return false;
	}
	return true;
}

function PlaceShip($size)
{
	$startPos = new Point(rand(0, $_SESSION["boardSize"]-1), rand(0, $_SESSION["boardSize"]-1));
	$ship = new Ship($startPos, $size);


	while (!CanPlaceShip($ship))
	{
		$ship->Position->X++;
		if ($ship->Position->X >= 9)
		{
			$ship->Position->X = 0;
			$ship->Position->Y++;
			if ($ship->Position->Y >= 9)
			{
				$ship->Position->X = 0;
				$ship->Position->Y = 0;
			}
		}

		if ($ship->Position->X == $startPos->X && $ship->Position->Y == $startPos->Y)
			return false;
	}

	arraY_push($_SESSION["ships"], $ship);
	return true;
}

function PrintTable()
{
	echo "<table>";
	for ($y = 0; $y <= $_SESSION["boardSize"]; ++$y)
	{
		echo "<tr>";
		for ($x = 0; $x <= $_SESSION["boardSize"]; ++$x)
		{
			if ($x == $y && $x == 0)
			{
				echo "<td class='styled'>";
			}
			else if ($y == 0 && $x != 0)
			{
				echo "<td class='styled'>";
				echo chr($x + 0x41-1);
			}
			else if ($x == 0)
			{
				echo "<td class='styled'>";
				echo $y;
			}
			else
			{
				echo "<td class='styled colored' onclick='SinkShip(this, ".($x-1).", ".($y-1).")'>";


			}
			echo "</td>";
		}
		echo "</tr>";
	}
	echo "</table>";
}

?>