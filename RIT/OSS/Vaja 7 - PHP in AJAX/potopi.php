<?php
	function Setup()
	{
		$_SESSION["boardSize"] = 5;
		$_SESSION["count"] = 0;
		$_SESSION["ships"] = array();
		$_SESSION["allHits"] = 0;
		$_SESSION["goodHits"] = 0;
		$_SESSION["tryCount"] = 0;
		$_SESSION["hit"] = 0;

		//if (!PlaceShip(RandomShipOrientation(array(1, 5))))
		//			echo "<p>1, 5 failed</p>";
		PlaceShip(RandomShipOrientation(array(1, 5)));
		//if (!PlaceShip(RandomShipOrientation(array(1, 4))))
		//			echo "<p>1, 4 failed</p>";
		PlaceShip(RandomShipOrientation(array(1, 4)));
		//if (!PlaceShip(RandomShipOrientation(array(2, 3))))
		//			echo "<p>2, 3 failed</p>";
		PlaceShip(RandomShipOrientation(array(2, 3)));
		//if (!PlaceShip(RandomShipOrientation(array(1, 2))))
		//			echo "<p>1, 2 failed</p>";
		PlaceShip(RandomShipOrientation(array(1, 2)));
	}
	
	if (isset($_GET["restart"]))
	{
		if ($_GET["restart"] == 1)
		{
			Setup();
			PrintTable();
			exit();
		}
	}

?>
<html>
<head>
	<link rel="stylesheet" type="text/css" href="style.css" />
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
	<?php

	if (!isset($_SESSION))
	{
		session_start();
		Setup();
	}

	echo "<script>var boardSize = " . $_SESSION["boardSize"] . ";</script>";
	?>
	<script>
		function SinkShip(sender, x, y)
		{
			$.ajax(
				{
					url: "preveri.php",
					type: "GET",
					data: { x: x, y: y },
					success: function (res)
					{
						sender.click = null;
						var obj = JSON.parse(res);
						if (obj.hit)
							$(sender).addClass("hit");
						else
							$(sender).addClass("miss");
						
						if (obj.finished)
							alert("Zmagal si v " + obj.tryCount + " potezah.");
					}
				});
		}
		
		function ResetGame()
		{
			$.ajax(
				{
					url: "potopi.php",
					type: "GET",
					data: { restart: 1 },
					success: function (res)
					{
						$("#game table tr td").removeClass("hit");
						$("#game table tr td").removeClass("miss");
						Hack();
					}
				});
		}

		var doTheHack = false;
		function Hack()
		{
			if (doTheHack)
			{
				var tds = $("#game table tr td.colored");
				for (var i = 0; i < tds.length; ++i)
				{
					SinkShip(tds[i], i % boardSize, (i - i % boardSize) / boardSize);
				}
			}
		}
		
		onload = function ()
		{
			Hack();
		}
	</script>
</head>
<body>
	<h1>Potapljanje ladjic</h1>
	<div id="game">
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

		function PlaceShip($size)
		{
			$startPos = new Point(rand(0, $_SESSION["boardSize"] - $size->X), rand(0, $_SESSION["boardSize"] - $size->Y));
			$ship = new Ship($startPos, $size);


			while (!CanPlaceShip($ship))
			{
				$ship->Position->X++;
				if ($ship->Position->X >= $_SESSION["boardSize"] - $ship->Size->X)
				{
					$ship->Position->X = 0;
					$ship->Position->Y++;
					if ($ship->Position->Y >= $_SESSION["boardSize"] - $ship->Size->Y)
					{
						$ship->Position->X = 0;
						$ship->Position->Y = 0;
					}
				}

				if ($ship->Position->X == $startPos->X && $ship->Position->Y == $startPos->Y)
					return false;
			}

			$_SESSION["count"] += $size->X * $size->Y;
			//print_r($ship);
			array_push($_SESSION["ships"], $ship);
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

		PrintTable();
		?>
	</div>
	<button onclick="ResetGame()">Ponastavi igro</button>
</body>
</html>