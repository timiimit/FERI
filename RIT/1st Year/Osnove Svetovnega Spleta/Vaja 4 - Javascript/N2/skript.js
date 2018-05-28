var width = parseInt(window.prompt("Enter width:"));
var height = parseInt(window.prompt("Enter height:"));

var elementCount = width * height;
var table = document.getElementById("t");
for (var y = 0; y < height; ++y)
{
	var row = "<tr>";
	for (var x = 0; x < width; ++x)
	{
		var rndNum = Math.floor(Math.random() * (elementCount-2)) + 2;
		row += "<td onclick='clicked(this);'>" + rndNum + "</td>";
	}
	row += "</tr>";
	table.innerHTML += row;
}

function clicked(element)
{
	element.style.backgroundColor = "red";
	alert(element.innerText);
}