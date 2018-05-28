var playing;
var topDiv;
var username;
var table;
var width = 4;
var height = 3;
var lastShownElement = null;
var pairsLeft;
var clickCount = 0;


function showResults()
{
	var key = username + "[" + width + "," + height + "]";
	var val = parseInt(localStorage.getItem(key));
	if (isNaN(val))
	{
		alert("Ta igralec še ni igral igre take težavnosti.");
	}
	else
	{
		alert(username + " [" + width + " x " + height + "] - " + val + " klikov");
	}
}

function resetGame()
{
	while (table.firstChild)
	{
		table.removeChild(table.firstChild);
	}
	playing = false;
}

function Clicked2(element)
{
	if (lastShownElement.src == element.src)
	{
		element.parentElement.onclick = lastShownElement.parentElement.onclick = null;
		pairsLeft--;
		if (pairsLeft == 0)
		{
			// game finished
			var key = username + "[" + width + "," + height + "]";
			var score = localStorage.getItem(key);
			if (score == "null")
				score = Number.MAX_SAFE_INTEGER;
			if (clickCount < score)
				score = clickCount;
			localStorage.setItem(key, score);
		}
	}
	else
	{
		var tmp = lastShownElement;
		setTimeout(function ()
		{
			element.className = tmp.className = "imgHidden";
		}, 1000);
	}
	lastShownElement = null;
}

function Clicked(element)
{
	clickCount++;
	element.firstChild.className = "imgVisible";
	if (lastShownElement == null)
	{
		lastShownElement = element.firstChild;
	}
	else
	{
		Clicked2(element.firstChild);
	}
}

function GetWithLeadingZeros(x, length)
{
	var str = x.toString();
	var remaining = length - str.length;
	for (var i = 0; i < remaining; ++i)
		str = "0" + str;
	return str;
}

function usernameChanged(element)
{
	username = element.value;
}

function difficultyChanged(element)
{
	var selection = document.getElementById("difficulty");
	var val = selection.options[selection.selectedIndex].value;
	width = parseInt(val[0]);
	height = parseInt(val[1]);
}

function GetRandomImages(count)
{
	// pick random indices of images
	var indices = [];
	while (indices.length < count)
	{
		var num = Math.floor(Math.random() * 23) + 1;
		if (indices.indexOf(num) == -1)
			indices.push(num);
		else
		{
			while (indices.indexOf(num) != -1)
			{
				num++;
				if (num > 24)
					num = 0;
			}
		}
	}

	// create array of strings for image sources
	var images = [];
	for (var i = 0; i < count; ++i)
	{
		images.push("image_part_" + GetWithLeadingZeros(indices[i], 3) + ".jpg");
	}

	return images;
}

function start()
{
	if (playing)
	{
		resetGame();
	}

	playing = true;

	pairsLeft = width * height / 2;
	if (pairsLeft - Math.ceil(pairsLeft) != 0)
	{
		return; // invalid cell count
	}

	var images = GetRandomImages(pairsLeft);
	var containers = [];

	// generate table
	for (var y = 0; y < height; ++y)
	{
		var row = document.createElement("tr");

		for (var x = 0; x < width; ++x)
		{
			var cell = document.createElement("td");
			cell.onclick = function () { Clicked(this); };

			var img = document.createElement("img");
			img.id = x.toString() + y.toString();
			containers.push(img.id);
			img.className = "imgHidden";

			cell.appendChild(img);
			row.appendChild(cell);
		}

		table.appendChild(row);
	}

	// place images
	while (images.length)
	{
		// choose image
		var imgIndex = Math.floor(Math.random() * images.length);

		// place to 1st random place
		var posIndex = Math.floor(Math.random() * containers.length);
		var element = document.getElementById(containers[posIndex]);
		element.src = images[imgIndex];
		containers.splice(posIndex, 1);

		// place to 2nd random place
		posIndex = Math.floor(Math.random() * containers.length);
		element = document.getElementById(containers[posIndex]);
		element.src = images[imgIndex];
		containers.splice(posIndex, 1);

		// remove image from thelist
		images.splice(imgIndex, 1);
	}
}

onload = function ()
{
	playing = false;
	topDiv = document.getElementById("top");
	table = document.getElementById("game");
}