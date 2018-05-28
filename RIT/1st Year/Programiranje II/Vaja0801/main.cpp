#include <iostream>

#include "Frame.h"
#include "Button.h"
#include "TextField.h"

using namespace std;

int main()
{
	Frame* frame = new Frame("mainFrame");
	TextField* textbox = new TextField(100, 23, "enter text");
	Button* btn = new Button(50, 30, "Click me!");
	textbox->addToFrame(frame);
	cout << "ORG textbox: " << textbox << endl << "SAME textbox: " << ((TextField*)frame->getX(0)) << endl;
	bool deleted = frame->brisiX(2);
	deleted = frame->brisiX(0);
	btn->addToFrame(frame);
	Button* btn2 = (Button*)frame->pop();
	delete frame;
	return 0;
}