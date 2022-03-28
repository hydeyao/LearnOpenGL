#include <iostream>
#include "ShowMainWindow.h"

int main() {
	ShowMainWindow* show = new ShowMainWindow();
	show->showWindow();
	delete show;

	return 0;
}