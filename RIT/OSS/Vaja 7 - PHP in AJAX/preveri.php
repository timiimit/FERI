<?php
session_start();

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

function AreShipsOverlapping($ship1, $ship2)
{
	return
		$ship1->Position->X < $ship2->Position->X + $ship2->Size->X &&
		$ship1->Position->Y < $ship2->Position->Y + $ship2->Size->Y &&
		$ship1->Position->X + $ship1->Size->X > $ship2->Position->X &&
		$ship1->Position->Y + $ship1->Size->Y > $ship2->Position->Y;
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


if (!isset($_GET) || !isset($_GET["x"]) || !isset($_GET["y"]) || !isset($_SESSION))
{
    echo "{ hit: \"error\" }";
	exit();
}

$x = $_GET["x"];
$y = $_GET["y"];
$aaaaaaa = new Ship(new Point($x, $y), new Point(1, 1));
$hit = !CanPlaceShip($aaaaaaa);
if ($hit)
	$_SESSION["goodHits"]++;
$_SESSION["allHits"]++;
$ok = array("hit" => $hit, "tryCount" => $_SESSION["allHits"]);
if ($_SESSION["count"] == $_SESSION["goodHits"])
{
	$ok["finished"] = true;
}
echo json_encode($ok);

?>