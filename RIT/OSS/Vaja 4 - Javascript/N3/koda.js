var debug = false;

var r; 
var g;
var b;
var color;

if (debug)
{
	r = 255;
	g = 255;
	b = 255;
	count = 255;
}
else
{
	r = parseInt(window.prompt("Enter starting red color component:"));
	g = parseInt(window.prompt("Enter starting green color component:"));
	b = parseInt(window.prompt("Enter starting blue color component:"));
	count = parseInt(window.prompt("Enter how many lines to output:"));
}

function lerp(x, y, t)
{
	return (1 - t) * x + t * y;
}

function AddLeadingZeros(digits, str)
{
	var ret = "";
	var missingDigits = digits - str.length;
	for (var i = 0; i < missingDigits; ++i)
	{
		ret += "0";
	}
	return ret + str;
}

// has a problem at grey color
function GetInverseColor(color)
{
	return 0xffffff - color;
}

// perfect in any case (samo ne po navodilih)
function GetContrastColor(r, g, b)
{
    var brightness = ( 0.299 * r + 0.587 * g + 0.114 * b) / 255;
	return brightness < 0.5 ? 0xffffff : 0x0;
}

for (var i = 0; i < count; ++i)
{
	var humanindex = i+1;
	var percent = i / count;
	var lR = Math.floor(lerp(r, 0, percent));
	var lG = Math.floor(lerp(g, 0, percent));
	var lB = Math.floor(lerp(b, 0, percent));
	var color = (lR << 16) | (lG << 8) | lB;
	var strHexColor = "#" + AddLeadingZeros(6, color.toString(16));
	var strFontHexColor = "#" + AddLeadingZeros(6, GetInverseColor(color).toString(16));
	document.write("<div><div style='display:inline-block;text-align:right;width:50px;'>" + humanindex + ". </div><div style='display:inline-block;width:300px;background-color:" + strHexColor + ";color:" + strFontHexColor + "'> R:" + lR + " G:" + lG + " B:" + lB + "</div></div>");
}