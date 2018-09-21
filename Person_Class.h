#pragma once
#include "Class.h"
#include <io.h>
#include <fstream>
#include <map>
#include "Message_Class.h"

/*        Member Class            */
Member::Member(string _name, string _ph, string _id, string _pw, string _pa) : name(_name), phonenum(_ph), id(_id), password(_pw) {
	// ȸ���� ���丮 ���
	this->path = _pa;
	this->path += "/Members/";
	this->path += phonenum;

	ofstream out;

	if (_access((path + "/phonebook.txt").c_str(), 00) == -1) { // ������ �����ϸ� 0, ������ -1
		out.open(path + "/phonebook.txt"); // ȸ���� ����ó �������� �����ϴ� �ؽ�Ʈ����
		out << "����ó ���" << endl;
		out.close();
	}

	if (_access((path + "/message.txt").c_str(), 00) == -1) { // ������ �����ϸ� 0, ������ -1
		out.open(path + "/message.txt"); // ȸ���� �޼������� �����ϴ� �ؽ�Ʈ����
		out.close();
	}
}

Member::Member() {}

// Member�� ��ȭ��ȣ�� ���� �Լ����� PhoneBook ��������� ���� ����� �ϴ� �Լ��� �Է¹��� ���ڸ� �����ϴ� ������ �Ѵ�
void Member::addPerson() {
	string _name = "", _ph = "", _de = "";

	cout << ">> Add Friend" << endl;
	cout << "�̸��� �Է��ϼ���(���������� �Ұ�): ";
	cin >> _name;
	while (getchar() != '\n');
	cout << "��ȣ�� �Է��ϼ���(����� -����): ";
	cin >> _ph;
	while (getchar() != '\n');
	cout << "������ �Է��ϼ���: ";
	cin >> _de;
	while (getchar() != '\n');

	(this->phonebook).addPerson(_name, _ph, _de);
}

void Member::addPerson(string _name, string _ph, string _de) {
	(this->phonebook).addPerson(_name, _ph, _de);
}

void Member::save_Data() { // ������ ����
	phonebook.save_Data(path);
	messagebox.save_Data(path);
}

void Member::output() {
	cout << ">> ��ȭ��ȣ�� ���" << endl;
	phonebook.output();
}

void Member::search() {
	string data = "";
	cout << ">> �˻�" << endl;
	cout << "�˻��� �̸��̳� ��ȣ�� �Է��ϼ���: ";
	cin >> data;
	while (getchar() != '\n');

	cout <<endl<< ">> �˻� ���" << endl;
	phonebook.search(data);
}

void Member::del_Person() {
	string _name;
	cout << ">> ������ ����" << endl;
	cout << "������ �̸��� �Է��ϼ���: ";
	cin >> _name;
	while (getchar() != '\n');

	phonebook.del_Person(_name);
}

void Member::send_Message(string _pa) { // �޼���������
	string _document;
	ofstream out;

	cout << "���� ������ ������ �Է��ϼ���" << endl;
	getline(cin, _document);
	out.open(_pa+"/message.txt", ios::app); // �̾��
	out << this->name << endl;
	out << _document << endl;
	out.close();
}

void Member::addMessage(string _na, string _docu) { // �޼��� �߰�
	this->messagebox.addMessage(Message(_na, _docu));
}

void Member::outputMessage() { // �޼��� ���
	this->messagebox.outputMessage();
}

void Member::delMessage(int _index) { // �޼��� ����
	this->messagebox.delMessage(_index);
}



/*        SimplePerson Class      */
SimplePerson::SimplePerson(string _name, string _ph, string _de) : name(_name), phonenum(_ph), description(_de) {}

void SimplePerson::output() {
	cout << name << " " << phonenum << " " << description << endl;
}






/*        PhoneBook Class         */
PhoneBook::PhoneBook() {}

void PhoneBook::addPerson(string _name, string _ph, string _de) { // map�� key���� �������� �ڵ� ���ĵȴ�(��������)
	SimplePerson s(_name, _ph, _de);
	persons.insert(pair<string, SimplePerson>(_name, s)); // ����ó �߰�
	cout << endl;
}

void PhoneBook::del_Person(string _name) {
	map<string, SimplePerson>::iterator it;
	for (it = persons.begin(); it != persons.end(); it++) {
		if (it->first == _name) { // �Է¹��� �̸��� ����ó�� �����Ѵٸ� ����
			persons.erase(persons.find(_name));
			cout << _name << " ���� ����..." << endl;

			return;
		}
	}

	cout << _name << "��(��) �������� �ʽ��ϴ�. ��Ȯ�� �̸��� �Է����ּ���." << endl;
}

void PhoneBook::output() {
	map<string, SimplePerson>::iterator it;

	for (it = (this->persons).begin(); it != (this->persons).end(); it++)
		(it->second).output();
}

void PhoneBook::save_Data(string _pa) { // �α׾ƿ��� �����͸� �����Ѵ�
	ofstream out;
	out.open(_pa + "/phonebook.txt");
	out << "����ó ���" << endl;

	map<string, SimplePerson>::iterator it;
	for (it = persons.begin(); it != persons.end(); it++)
		out << it->first << " " << (it->second).getPhonenum() << " " << (it->second).getDescription() << endl;

	out.close();
}

void PhoneBook::search(string _data) {
	map<string, SimplePerson>::iterator it;

	it = persons.begin();
	while (it != persons.end()) { //strstr�� ����� �κа˻�
		if (strstr(it->first.c_str(), _data.c_str()) != NULL || strstr((it->second).getPhonenum().c_str(), _data.c_str()) != NULL) {
			(it->second).output(); // �̸��̳� ��ȣ�� �Ϻΰ� _data�� ��ġ�Ѵٸ� ���
			++it;
		}
		else
			++it;
	}

	cout << endl;
}
