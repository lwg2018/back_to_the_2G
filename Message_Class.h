#pragma once
#include "Class.h"
#include "Manager_Class.h"
#include "Person_Class.h"

/*        MessageBox Class        */
MessageBox::MessageBox() {}

void MessageBox::addMessage(Message m) { // �޼��� �߰�
	this->messages.push_back(m);
}

void MessageBox::outputMessage() { // �޼��� ���
	vector<Message>::iterator it;
	cout << ">> �޼��� ���" << endl;
	int i;
	for (i = 1, it = messages.begin(); it != messages.end(); it++, i++) { // vector���ִ� �޼��� ��� ���
		cout << i << ". ";
		it->output();
		cout << endl;
	}
}

void MessageBox::delMessage(int _index) { // �޼��� ����
	if (messages.size() < _index || _index <= 0) {
		cout << "�޼��� ���� ����..." << endl;
		return;
	}
	
	this->messages.erase(messages.begin() + _index - 1);
	cout << "���� ����..." << endl;
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
	cout << "�߽���: " << this->addresser << endl;
	cout << document << endl;
}