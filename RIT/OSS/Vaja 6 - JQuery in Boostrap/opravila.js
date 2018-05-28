"use strict"

var txtNewCategoryName;
var txtNewTaskName;
var listCategories;
var listTasks;

var selectedCategory;

var taskCounter = 0;

function AddCategory(categoryName)
{
	if (categoryName == undefined)
	{
		var cName = txtNewCategoryName.val();
		AddCategory(cName);
		txtNewCategoryName.val("");
	}
	else if (categoryName == "")
	{
		alert("Napiši ime kategorije!");
		return;
	}
	else
	{
		var nCategory = $("<li>");
		nCategory.addClass("list-group-item");
		nCategory.click(function () { SelectCategory(nCategory); });

		var text = $("<span>");
		text.addClass("category-name");
		text.html(categoryName);

		nCategory.append(text);
		listCategories.append(nCategory);
	}
}

function RemoveCategory(category)
{
	category.remove();
}

function SelectCategory(categoryItem)
{
	if (categoryItem == selectedCategory)
	{
		selectedCategory.removeClass("active");
		$(".glyphicon-trash").remove();
		return;
	}
	if (selectedCategory)
	{
		selectedCategory.removeClass("active");
		$(".glyphicon-trash").remove();
	}
	selectedCategory = categoryItem;
	selectedCategory.addClass("active");

	var badge = $("<span>");
	badge.addClass("badge");

	var glyphicon = $("<span>");
	glyphicon.addClass("glyphicon glyphicon-trash");
	glyphicon.click(function () { RemoveCategory(selectedCategory); });

	badge.append(glyphicon);
	selectedCategory.append(badge);
}

function ToggleSelectTask(task)
{
	task.toggleClass("danger");
}

function AddTask()
{
	if (selectedCategory == undefined)
	{
		alert("Najprej izberi kategorijo!");
		return;
	}
	var taskName = txtNewTaskName.val();
	txtNewTaskName.val("");
	if (taskName == "")
	{
		alert("Napiši ime opravila!");
		return;
	}
	var tr = $("<tr>");
	tr.append($("<td>").html(taskCounter));
	tr.append($("<td>").html(taskName));
	tr.append($("<td>").html(selectedCategory.find(".category-name")[0].innerHTML));
	tr.append($("<td>").html(new Date()));

	tr.click(function () { ToggleSelectTask(tr) });

	listTasks.append(tr);

	taskCounter++;
}

function RemoveSelectedTasks()
{
	var deleted = false;
	var tasks = listTasks.children();
	for (var i = 0; i < tasks.length; ++i)
	{
		if ($(tasks[i]).hasClass("danger"))
		{
			deleted = true;
			tasks[i].remove();
		}
	}
	if (!deleted)
	{
		alert("Izberi opravilo, ki ga želiš zbrisat!");
	}
}

onload = function ()
{
	txtNewCategoryName = $("#txtNewCategoryName");
	txtNewTaskName = $("#txtNewTaskName");
	listCategories = $("#listCategories");
	listTasks = $("#listTasks");

	AddCategory("Šola");
	AddCategory("Stanovanje");
	AddCategory("Zabava");
};