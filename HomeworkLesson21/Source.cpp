#include <iostream>
#include <fstream>

using namespace std;

void WriteToFile(string name, int number) {
	ofstream fs("contacts.txt", ios::app);
	if (fs.is_open()) {
		fs << name << " - " << number << endl;
	}
	fs.close();
}

class Contact {
public:
	string name;
	int number;

	Contact() {
		name = "";
		number = 0;
	}

	Contact(string name, int number) {
		this->name = name;
		this->number = number;
	}

	string GetName() {
		return name;
	}

	int GetNumber() {
		return number;
	}
};

class Database {
	Contact** contacts;
	int size;

public:
	void ShowContacts() {
		for (int i = 0; i < size; i++) {
			cout << contacts[i]->GetName() << " - " << contacts[i]->GetNumber() << endl;
		}
		cout << endl;
	}

	void AddContact(const Contact* contact) {
		Contact** temp = new Contact * [size + 1];

		for (int i = 0; i < size; i++) {
			temp[i] = contacts[i];
		}

		delete[] contacts;
		temp[size] = new Contact(*contact);
		contacts = temp;
		temp = nullptr;
		size++;

		system("cls");
		cout << "Successfully added new contact.\n";
	}

	void DeleteByName(string name) {
		Contact** temp = new Contact * [size - 1];

		for (int i = 0; i < size; i++) {
			temp[i] = contacts[i];
		}

		delete[] contacts;
		temp[size] = nullptr;
		contacts = temp;
		temp = nullptr;
		size--;

		system("cls");
		cout << "The contact has been successfully deleted.\n";
	}

	void SearchByName(string name) {
		for (int i = 0; i < size; i++) {
			if (contacts[i]->GetName() == name) {
				system("cls");
				cout << "Contact found.\n";
				cout << contacts[i]->GetName() << " - " << contacts[i]->GetNumber() << endl;
			}
		}
	}

	int GetSize() {
		return size;
	}

	~Database() {
		for (int i = 0; i < size; i++) delete contacts[i];
		delete[] contacts;
	}
};

void start() {
	Database data;

	while (true) {
		cout << "======================" << endl;
		cout << "1. Show All Contacts" << endl;
		cout << "2. Add New Contact" << endl;
		cout << "3. Search Contact" << endl;
		cout << "4. Delete Contact" << endl;
		cout << "5. Quit" << endl;
		cout << "======================" << endl;
		cout << "SELECT: ";

		int select = 0;
		cin >> select;
		system("cls");

		if (select == 1) {
			if (data.GetSize() == 0)
				cout << "No such contacts.\n";

			else
				data.ShowContacts();
		}

		else if (select == 2) {
			string name;
			cout << "Enter name: ";
			cin >> name;

			int number;
			cout << "Enter number: ";
			cin >> number;

			Contact cnt(name, number);
			data.AddContact(&cnt);
			WriteToFile(name, number);
		}

		else if (select == 3) {
			if (data.GetSize() == 0)
				cout << "No such contacts.\n";

			else {
				string name;
				cout << "Enter the name you want to search: ";
				cin >> name;

				data.SearchByName(name);
			}
		}

		else if (select == 4) {
			if (data.GetSize() == 0)
				cout << "No such contacts.\n";

			else {
				string name;
				cout << "Enter the name you want to delete: ";
				cin >> name;

				data.DeleteByName(name);
			}
		}

		else if (select == 5) {
			cout << "Goodbye!\n";
			break;
		}

		else {
			cout << "Invilad select!\n";
		}
	}
}

void main() {
	start();
}