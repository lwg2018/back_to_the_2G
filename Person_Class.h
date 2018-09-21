#pragma once
#include "Class.h"
#include <io.h>
#include <fstream>
#include <map>
#include "Message_Class.h"

/*        Member Class            */
Member::Member(string _name, string _ph, string _id, string _pw, string _pa) : name(_name), phonenum(_ph), id(_id), password(_pw) {
	// 회원의 디렉토리 경로
	this->path = _pa;
	this->path += "/Members/";
	this->path += phonenum;

	ofstream out;

	if (_access((path + "/phonebook.txt").c_str(), 00) == -1) { // 파일이 존재하면 0, 없으면 -1
		out.open(path + "/phonebook.txt"); // 회원의 연락처 정보들을 저장하는 텍스트파일
		out << "연락처 목록" << endl;
		out.close();
	}

	if (_access((path + "/message.txt").c_str(), 00) == -1) { // 파일이 존재하면 0, 없으면 -1
		out.open(path + "/message.txt"); // 회원의 메세지들을 저장하는 텍스트파일
		out.close();
	}
}

Member::Member() {}

// Member의 전화번호부 관련 함수들은 PhoneBook 멤버변수의 같은 기능을 하는 함수에 입력받은 인자를 전달하는 역할을 한다
void Member::addPerson() {
	string _name = "", _ph = "", _de = "";

	cout << ">> Add Friend" << endl;
	cout << "이름을 입력하세요(동명이인은 불가): ";
	cin >> _name;
	while (getchar() != '\n');
	cout << "번호를 입력하세요(띄어쓰기와 -제외): ";
	cin >> _ph;
	while (getchar() != '\n');
	cout << "설명을 입력하세요: ";
	cin >> _de;
	while (getchar() != '\n');

	(this->phonebook).addPerson(_name, _ph, _de);
}

void Member::addPerson(string _name, string _ph, string _de) {
	(this->phonebook).addPerson(_name, _ph, _de);
}

void Member::save_Data() { // 데이터 저장
	phonebook.save_Data(path);
	messagebox.save_Data(path);
}

void Member::output() {
	cout << ">> 전화번호부 목록" << endl;
	phonebook.output();
}

void Member::search() {
	string data = "";
	cout << ">> 검색" << endl;
	cout << "검색할 이름이나 번호를 입력하세요: ";
	cin >> data;
	while (getchar() != '\n');

	cout <<endl<< ">> 검색 결과" << endl;
	phonebook.search(data);
}

void Member::del_Person() {
	string _name;
	cout << ">> 데이터 삭제" << endl;
	cout << "삭제할 이름을 입력하세요: ";
	cin >> _name;
	while (getchar() != '\n');

	phonebook.del_Person(_name);
}

void Member::send_Message(string _pa) { // 메세지보내기
	string _document;
	ofstream out;

	cout << "보낼 간단한 내용을 입력하세요" << endl;
	getline(cin, _document);
	out.open(_pa+"/message.txt", ios::app); // 이어쓰기
	out << this->name << endl;
	out << _document << endl;
	out.close();
}

void Member::addMessage(string _na, string _docu) { // 메세지 추가
	this->messagebox.addMessage(Message(_na, _docu));
}

void Member::outputMessage() { // 메세지 출력
	this->messagebox.outputMessage();
}

void Member::delMessage(int _index) { // 메세지 삭제
	this->messagebox.delMessage(_index);
}



/*        SimplePerson Class      */
SimplePerson::SimplePerson(string _name, string _ph, string _de) : name(_name), phonenum(_ph), description(_de) {}

void SimplePerson::output() {
	cout << name << " " << phonenum << " " << description << endl;
}






/*        PhoneBook Class         */
PhoneBook::PhoneBook() {}

void PhoneBook::addPerson(string _name, string _ph, string _de) { // map은 key값을 바탕으로 자동 정렬된다(오름차순)
	SimplePerson s(_name, _ph, _de);
	persons.insert(pair<string, SimplePerson>(_name, s)); // 연락처 추가
	cout << endl;
}

void PhoneBook::del_Person(string _name) {
	map<string, SimplePerson>::iterator it;
	for (it = persons.begin(); it != persons.end(); it++) {
		if (it->first == _name) { // 입력받은 이름이 연락처에 존재한다면 삭제
			persons.erase(persons.find(_name));
			cout << _name << " 삭제 성공..." << endl;

			return;
		}
	}

	cout << _name << "이(가) 존재하지 않습니다. 정확한 이름을 입력해주세요." << endl;
}

void PhoneBook::output() {
	map<string, SimplePerson>::iterator it;

	for (it = (this->persons).begin(); it != (this->persons).end(); it++)
		(it->second).output();
}

void PhoneBook::save_Data(string _pa) { // 로그아웃시 데이터를 저장한다
	ofstream out;
	out.open(_pa + "/phonebook.txt");
	out << "연락처 목록" << endl;

	map<string, SimplePerson>::iterator it;
	for (it = persons.begin(); it != persons.end(); it++)
		out << it->first << " " << (it->second).getPhonenum() << " " << (it->second).getDescription() << endl;

	out.close();
}

void PhoneBook::search(string _data) {
	map<string, SimplePerson>::iterator it;

	it = persons.begin();
	while (it != persons.end()) { //strstr을 사용한 부분검색
		if (strstr(it->first.c_str(), _data.c_str()) != NULL || strstr((it->second).getPhonenum().c_str(), _data.c_str()) != NULL) {
			(it->second).output(); // 이름이나 번호중 일부가 _data와 일치한다면 출력
			++it;
		}
		else
			++it;
	}

	cout << endl;
}
