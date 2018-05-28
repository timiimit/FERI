#include <iostream>

#include "Frame.h"
#include "Button.h"
#include "TextField.h"
#include <string>

using namespace std;

bool operator>(const Frame& a, const Frame& b)
{
	int ac = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a.getX(i)->getVisible())
			ac++;
	}
	int bc = 0;
	for (size_t i = 0; i < b.size(); i++)
	{
		if (b.getX(i)->getVisible())
			bc++;
	}
	return ac > bc;
}

bool operator<(const Frame& a, const Frame& b)
{
	int ac = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a.getX(i)->getVisible())
			ac++;
	}
	int bc = 0;
	for (size_t i = 0; i < b.size(); i++)
	{
		if (b.getX(i)->getVisible())
			bc++;
	}
	return ac < bc;
}

bool operator==(const Frame& a, const Frame& b)
{
	int ac = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a.getX(i)->getVisible())
			ac++;
	}
	int bc = 0;
	for (size_t i = 0; i < b.size(); i++)
	{
		if (b.getX(i)->getVisible())
			bc++;
	}
	return ac == bc;
}

Frame& operator++(Frame& a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		Component* c = a.getX(i);
		c->setPositionX(c->getPositionX() + 1);
	}
	return a;
}



template<class T>
T daljsi(T a, T b, T c);

template<>
std::string daljsi<std::string>(std::string a, std::string b, std::string c)
{
	return a.length() > b.length() && a.length() > c.length() ? a : (b.length() > c.length() ? b : c);
}

template<>
TextField daljsi<TextField>(TextField a, TextField b, TextField c)
{
	return a.getWidth() > b.getWidth() && a.getWidth() > c.getWidth() ? a : (b.getWidth() > c.getWidth() ? b : c);
}

template<>
Frame* daljsi<Frame*>(Frame* a, Frame* b, Frame* c)
{
	return a->size() > b->size() && a->size() > c->size() ? a : (b->size() > c->size() ? b : c);
}

template<class T>
class A
{
public:
	T var;

	A() : var() {}
	A(const A& a) : var(a.var) {}
	A(T var) : var(var) {}

	void print()
	{
		cout << var << endl;
	}
};

int main()
{
	cout << daljsi<string>("dolg", "daljsi", "najdaljsi") << endl;


	Frame* frame = new Frame("mainFrame");
	Frame* frame2 = new Frame("secondaryFrame");

	TextField* textbox = new TextField(100, 23, "enter text");
	TextField* textbox2 = new TextField(10, 23, "enter text again");

	cout << daljsi(*textbox, *textbox2, *textbox).getText() << endl;
	Button* btn = new Button(50, 30, "Click me!");
	textbox->addToFrame(frame);

	frame->contains(textbox);

	cout << "ORG textbox: " << textbox << endl << "SAME textbox: " << ((TextField*)frame->getX(0)) << endl;
	bool deleted = frame->brisiX(2);
	deleted = frame->brisiX(0);
	btn->addToFrame(frame);

	++(*frame);
	cout << "frame == frame2: " << (*frame == *frame2) << endl;
	cout << "frame < frame2: " << (*frame < *frame2) << endl;
	cout << "frame > frame2: " << (*frame > *frame2) << endl;
	
	cout << *daljsi(frame, frame, frame2) << endl;

	Button* btn2 = (Button*)frame->pop();

	
	delete textbox2;
	delete frame2;
	delete frame;

	A<string> test("hello");
	test.print();
	return 0;
}