#pragma once
#include "Class.h"
#include "Manager_Class.h"
#include "Person_Class.h"

/*        MessageBox Class        */
MessageBox::MessageBox() {}

void MessageBox::addMessage(Message m) { // 메세지 추가
	this->messages.push_back(m);
}

void MessageBox::outputMessage() { // 메세지 출력
	vector<Message>::iterator it;
	cout << ">> 메세지 목록" << endl;
	int i;
	for (i = 1, it = messages.begin(); it != messages.end(); it++, i++) { // vector에있는 메세지 모두 출력
		cout << i << ". ";
		it->output();
		cout << endl;
	}
}

void MessageBox::delMessage(int _index) { // 메세지 삭제
	if (messages.size() < _index || _index <= 0) {
		cout << "메세지 삭제 실패..." << endl;
		return;
	}
	
	this->messages.erase(messages.begin() + _index - 1);
	cout << "삭제 성공..." << endl;
}

void MessageBox::save_Data(string _pa) {
	ofstream out;
	out.open(_pa + "/message.txt");

	vector<Message>::iterator it;
	for (it = messages.begin(); it != messages.end(); it++) {
		out << it->getAddresser() << endl;
		out << it->getDocument() << endl;
	}

	out.close();
}

/*       Message Class        */
Message::Message(string _addresser, string _document) {
	this->addresser = _addresser;
	this->document = _document;
}

void Message::output() {
	cout << "발신인: " << this->addresser << endl;
	cout << document << endl;
}