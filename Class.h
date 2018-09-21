#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class SimplePerson { // ��ȭ��ȣ�ο� ����Ǵ� ���
public:
	SimplePerson(string _name, string _ph, string _de = "");
	void output();

	string getName() const {
		return this->name;
	}
	string getPhonenum() const {
		return this->phonenum;
	}
	string getDescription() const {
		return this->description;
	}
private:
	string name;
	string phonenum;
	string description;
};

class PhoneBook { // ��ȭ��ȣ��
public:
	PhoneBook();
	void addPerson(string _name, string _ph, string _de); // ����ó �߰�
	void output();
	void search(string _data); // �˻�
	void save_Data(string _pa); // ����ó ����
	void del_Person(string _data); // ����ó ����

private:
	map<string, SimplePerson> persons;
};

class Message { // �޼���
public:
	Message(string _addresser, string _document);
	void output();
	string getDocument() {
		return document;
	}

	string getAddresser() {
		return addresser;
	}

private:
	string document;
	string addresser; // �߽���
};

class MessageBox { // �޼�����
public:
	MessageBox();
	void addMessage(Message m);
	void outputMessage();
	void delMessage(int _index);
	void save_Data(string _pa);

private:
	vector<Message> messages;
};

class Member { // ȸ��
public:
	Member(string _name, string _ph, string _id, string _pw, string _pa);
	Member();
	void addPerson();
	void addPerson(string _name, string _ph, string _de);
	void output();
	void search();
	void save_Data(); // ������ ����
	void del_Person();
	void send_Message(string _pa);
	void addMessage(string _na, string _docu);
	void outputMessage();
	void delMessage(int _index);

	string getName() const {
		return this->name;
	}
	string getPhonenum() const {
		return this->phonenum;
	}
	string getId() const {
		return this->id;
	}
	string getPassword() const {
		return this->password;
	}
	string getPath() const {
		return this->path;
	}
private:
	string name;
	string phonenum;
	string id;
	string password;
	string path; // ȸ���� ���� ���丮 ���
	MessageBox messagebox; // �޼�����
	PhoneBook phonebook; // ��ȭ��ȣ��
};

class Manager { // ����Ŵ���
public:
	Manager();
	~Manager();
	void login();
	void logout();
	void make_Account(); // ȸ������
	void load_Data(string _id); // ȸ�� �����͸� �ҷ��´�
	void make_Path(string _id); // ���丮 ��θ� �����
	void beginning_Screen(); // �ʱ�ȭ��
	void login_Screen(); // �α��� �� ȭ��
	bool search(string _id, string _pw, string _ph, string _type); // ȸ���˻�

private:
	Member* user; // ���� �α��� �ϰ��ִ� ȸ��
	string path; // �ڵ尡 ����� ���丮 ���
	ofstream out; // ���������
	ifstream in;
};