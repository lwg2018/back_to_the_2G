#pragma once
#include "Class.h"
#include "Manager_Class.h"
#include "Message_Class.h"
#include "Person_Class.h"

using namespace std;

int main() {
	system("mode con:cols=51 lines=38"); // 콘솔창 크기조절
	Manager manager;

	manager.beginning_Screen();

	return 0;
}