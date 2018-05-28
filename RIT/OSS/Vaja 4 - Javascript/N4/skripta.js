function test()
{
	var txtInput = document.getElementById("txtInput");
	var str = txtInput.value;

	var regex = new RegExp(/(^[0-9]+(,\s*[0-9]+)+$)/); // works for anywhitespace between comma and next number /(\d+)(,\s*(\d+))*/
	var matches = regex.exec(str);
	if (matches.length < 1)
	{
		alert("list does not contain comma separated numbers.");
		return;
	}

	var strnum = prompt("Enter a number to find in the list");
	if (typeof (parseInt(strnum)) != "number")
	{
		alert("You didn't enter a (valid) number.");
	}
	var num = parseInt(strnum);

	var numbers = new Array();
	{
		var strings = str.split(",");
		for (var i = 0; i < strings.length; ++i)
		{
			var currNum = parseInt(strings[i]);
			if (!isNaN(currNum))
				numbers.push(currNum);
			else
				alert("One of the entries ('" + strings[i] + "') isn't a number and it was ignored.");
		}
	}

	var index = numbers.indexOf(num);
	if (index < 0)
	{
		alert("There isn't number " + strnum + " in the list");
	}
	else
	{
		alert("There is number " + strnum + " in the list.");
	}
	txtInput.blur();

	var sum = 0;
	var max = Number.MIN_SAFE_INTEGER;
	var min = Number.MAX_SAFE_INTEGER;
	for (var i = 0; i < numbers.length; ++i)
	{
		sum += numbers[i];
		if (numbers[i] > max)
			max = numbers[i];
		if (numbers[i] < min)
			min = numbers[i];
	}
	var avg = sum / numbers.length;

	var output = document.getElementById("rezultati");
	output.innerHTML = "<p>";
	output.innerHTML += "Sum of nums: " + sum + "<br />";
	output.innerHTML += "max number: " + max + "<br />";
	output.innerHTML += "min number: " + min + "<br />";
	output.innerHTML += "average of numbers: " + avg + "<br />";
	output.innerHTML += "</p>";
}