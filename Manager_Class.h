#pragma once
#include "Class.h"
#include "Message_Class.h"
#include "Person_Class.h"
#include "print.h"
#include <conio.h>
#include <direct.h> // _mkdir �Լ�
#include <io.h> // _access �Լ�
#define _MAX_PATH 260

/*        Manager Class           */

Manager::Manager() {       // ������
	char strBuffer[_MAX_PATH] = { 0, };
	char *pstrBuffer = NULL;
	pstrBuffer = _getcwd(strBuffer, _MAX_PATH);
	//             ���    ����       ����ũ��

	for (int i = 0; pstrBuffer[i] != '\0'; i++) {
		if (pstrBuffer[i] == '\\') // \������ü�� ����ϱ����� \\���
			pstrBuffer[i] = '/';
	}

	this->path = pstrBuffer; // ���� ����� ���
	this->user = nullptr; // ���� �α��ε� ����� ����

	if (_access("account_list.txt", 00) == -1) { // ������ �����ϸ� 0, ������ -1
		out.open("account_list.txt");
		out << "���� ���" << endl;
		out.close();
	}
}

Manager::~Manager() {       // �Ҹ���
	delete user;
}

void Manager::login() {      // �α���
	string _id = "", _pw = "";
	char ch = NULL;

	do {
		_id = _pw = "";
		cout << ">> Login" << endl;
		cout << "ID: ";
		cin >> _id;
		while (getchar() != '\n'); // ���Ⱑ �Էµ� ���� ����� ���۸� ����
		cout << "Password: ";  // password�� *�� ���
		ch = _getch();
		while (ch != 13) {  // ch�� Enter(13)�� ����
			if (ch == 8) {  // ch�� �齺���̽�(8)�̸� �����
				if (_pw.length() != 0) { // _pw�� ���̰� 0�϶��� �������ʴ´�
					_pw.pop_back();
					cout << "\b \b";
				}
			}
			else {
				_pw.push_back(ch);
				cout << "*";
			}
			ch = _getch();
		}
		cout << endl;

		if (search(_id, _pw, "", "login")) { // id�� password�� ��ġ�ϴ��� Ȯ��
			cout << "�α��� ����! ������ �ε���.." << endl << endl;
			load_Data(_id);
			break;
		}
		else
			cout << "ID�� ��й�ȣ�� �߸� �ԷµǾ����ϴ�." << endl << endl;
	} while (1);

	login_Screen();
}

void Manager::logout() {
	user->save_Data(); // �α׾ƿ� ���� ������ �����͸� ����

	delete this->user;
	this->user = nullptr; // user �ʱ�ȭ

	cout << "�α׾ƿ� ����..." << endl;
	cout << "�޴��� ������ �ƹ�Ű�� ��������..";
	getchar();
	beginning_Screen();
}

void Manager::make_Account() {
	string _id = "", _pw = "", _name = "", _ph = "";
	char ch = NULL;

	while (1) {
		_id = _pw = _name = _ph = "";
		cout << ">> Create account" << endl;
		// id
		cout << "ID�� �Է��ϼ���: ";
		cin >> _id;
		while (getchar() != '\n');

		// password
		cout << "�н����带 �Է��ϼ���: ";
		ch = _getch();
		while (ch != 13) {  // ch�� Enter(13)�� ����
			if (ch == 8) {  // ch�� �齺���̽�(8)�̸� �����
				if (_pw.length() != 0) { // _pw�� ���̰� 0�϶��� �������ʴ´�
					_pw.pop_back();
					cout << "\b \b";
				}
			}
			else {
				_pw.push_back(ch);
				cout << "*";
			}
			ch = _getch();
		}
		cout << endl;

		// name
		cout << "�̸��� �Է��ϼ���: ";
		cin >> _name;
		while (getchar() != '\n');

		// phone number
		cout << "�ڵ��� ��ȣ�� �Է��ϼ���(����� -�� ����): ";
		cin >> _ph;
		while (getchar() != '\n');

		if (search(_id, "", _ph, "make"))
			cout << "�̹� �����ϴ� ID�̰ų� ��ϵ� �ڵ��� ��ȣ�Դϴ�." << endl << endl;
		else
			break;
	}

	out.open("account_list.txt", ios::app); // �̾��
	out << _id << " " << _pw << " " << _name << " " << _ph << endl;
	out.close();

	make_Path(_ph);
}

bool Manager::search(string _id, string _pw, string _ph, string _type) {
	in.open("account_list.txt");
	string search_id = "", search_pw = "", search_name = "", search_ph = "";
	string tem_data = "";
	getline(in, tem_data); // ù��ǳʶٱ�


	while (!in.eof()) {   //���� ���� �˻�
		in >> search_id >> search_pw >> search_name >> search_ph;

		if (_type == "make" && (_id == search_id || _ph == search_ph)) { // ���� ������ ��ȣ�� ���̵� ��ģ�ٸ�
			in.close();
			return true;
		}
		else if (_type == "login" && _id == search_id && _pw == search_pw) { // �α��ν� id�� password�� ��ġ�Ѵٸ�
			in.close();
			return true;
		}
		else if (_type == "message" && _ph == search_ph) { // �޼��� ���۽� ��ȣ�� ��ġ�Ѵٸ�
			in.close();
			return true;
		}
	}

	in.close();
	return false;
}

void Manager::make_Path(string _ph) {
	string _path = this->path;
	_path += "/Members/"; // Members ���丮 �������
	if (_access(_path.c_str(), 00) == -1) // ���丮�� �����ϸ� 0, ������ -1
		_mkdir(_path.c_str());

	_path += _ph; // ������� ���丮 �������(���丮 �̸��� id��)
	int making = _mkdir(_path.c_str()); // .c_str(): string -> char* ����ȯ

	if (making == 0) {
		cout << "���� ���� �Ϸ�..." << endl << endl;
		beginning_Screen();
	}
	else
		cout << "[ERROR] ���� ���� ����" << endl << endl;
}

void Manager::beginning_Screen() {
	int select = 0;

	do {
		print_menu();
		cout << "��ȣ�� �Է��ϼ���: ";
		cin >> select;
		cout << endl;
		while (getchar() != '\n');

		if (cin.fail() || select>4) { // ����ó��
			cout << "�߸��� �Է��Դϴ�." << endl << endl;
			cin.clear();
		}
		else {
			if (select == 3) { // ���α׷� ����
				print_information();
				cout << "�޴��� ������ �ƹ�Ű�� ��������..";
				getchar();
			}
			else break;
		}
	} while (1);

	switch (select) {
	case 1: // �α���
		system("cls");
		login();
		break;
	case 2: // ȸ������
		system("cls");
		make_Account();
		break;
	case 4: // ����
		print_exit();
		cout << "�����Ϸ��� �ƹ�Ű�� ��������..";
		getchar();
		exit(1);
		break;
	}
}

void Manager::login_Screen() {
	int select = 0;
	int del_index = 0;
	string _phonenum;
	do {
		print_myPhone();
		cout << "��ȣ�� �Է��ϼ���: ";
		cin >> select;
		while (getchar() != '\n');

		if (cin.fail()) {
			cout << "�߸��� �Է��Դϴ�." << endl << endl;
			cin.clear();
			continue;
		}

		switch (select) {
		case 1: // ��ȣ�߰�
			system("cls"); // ȭ�������
			user->addPerson();
			cout << "��ȣ�߰� ����.." << endl;
			cout << "�޴��� ������ �ƹ�Ű�� ��������..";
			getchar();
			break;
		case 2: // ��ȣ�˻�
			system("cls");
			user->search();
			cout << "�޴��� ������ �ƹ�Ű�� ��������..";
			getchar();
			break;
		case 3: // ��ȣ���
			system("cls");
			user->output();
			cout << endl;
			cout << "�޴��� ������ �ƹ�Ű�� ��������..";
			getchar();
			break;
		case 4: // ��ȣ����
			system("cls");
			user->del_Person();
			cout << endl;
			cout << "�޴��� ������ �ƹ�Ű�� ��������..";
			getchar();
			break;
		case 5: // �޼��� ������
			system("cls");
			while (1) {
				cout << "�޼����� ���� ��ȣ�� �Է��ϼ���: ";
				cin >> _phonenum;
				while (getchar() != '\n');
				if (search( "", "", _phonenum, "message")) { // ��ϵ� ��������� �˻�
					user->send_Message(this->path + "/Members/" + _phonenum); // �޼����� ���� �������
					break;
				}
				else {
					cout << "���� ��ȣ�Դϴ�. �޼����� ���� �� �����ϴ�." << endl;
				}
			}
			cout << "�޼��� ������ ����..." << endl;
			cout << "�޴��� ������ �ƹ�Ű�� ��������..";
			getchar();
			break;
		case 6: // �޼��� ���
			system("cls");
			user->outputMessage();
			cout << "�޴��� ������ �ƹ�Ű�� ��������..";
			getchar();
			break;
		case 7: // �޼��� ����
			system("cls");
			user->outputMessage();
			
			while (1) {
				cout << "������ �޼��� ��ȣ�� �Է����ּ���: ";
				cin >> del_index;
				if (cin.fail()) {
					cout << "�߸��� �Է��Դϴ�." << endl << endl;
					cin.clear();
					while (getchar() != '\n');
					continue;
				}
				else
					break;
			}
			
			while (getchar() != '\n');
			user->delMessage(del_index);
			cout << "�޴��� ������ �ƹ�Ű�� ��������..";
			getchar();
			break;
		case 8: // �α׾ƿ�
			system("cls");
			logout();
			break;
		}
	} while (1);
}

void Manager::load_Data(string _id) {
	in.open("account_list.txt");
	string search_id = "", search_pw = "", search_name = "", search_ph = "", search_de = "";
	string tem_data = "";
	string tem_data2 = "";
	getline(in, tem_data); // ù��ǳʶٱ�

	while (!in.eof()) { // id ã��
		in >> search_id >> search_pw >> search_name >> search_ph;
		if (search_id == _id) {
			user = new Member(search_name, search_ph, search_id, search_pw, path);
			break;
		}
	}

	in.close();
	in.open(user->getPath() + "/phonebook.txt"); // ����ó ���� ����
	getline(in, tem_data);

	search_name = search_ph = search_de = ""; // �ʱ�ȭ
	while (!in.eof()) { // ������ �ҷ�����
		in >> search_name >> search_ph >> search_de;

		if (search_name != "") // �������� �ƴ϶��
			user->addPerson(search_name, search_ph, search_de); // ������ �߰�
	}
	in.close();

	in.open(user->getPath() + "/message.txt"); // ����ó ���� ����
	while (!in.eof()) { // ������ �ҷ�����
		getline(in, tem_data);
		getline(in, tem_data2);
		if (tem_data == "") // ������ �̶��
			break;
		else {
			user->addMessage(tem_data, tem_data2); // �������߰�
		}
	}
	in.close();

}