#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;


class Bank_Account
{
	int account_number;
	char name[50];
	char type;
	int money_Deposit;
public:
	void dep(int x) {
		money_Deposit += x;
	}
	void draw(int x)
	{
		money_Deposit -= x;
	}
	int retdeposite() const
	{
		return money_Deposit;
	}
	void modify();
	void report()const;
	void create_account();
	void display_account();
	int retno() const {
		return account_number;
	}

};

void Bank_Account::create_account()
{
	system("cls");
	cout << "\tEnter the Account Number: ";
	cin >> account_number;
	cout << "\tEnter the Name of the account holder: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\tEnter the type of the account (C/S): ";
	cin >> type;
	type = toupper(type);
	cout << "\tEnter the intial amount (>=500 for saving and >=1000 for current): ";
	cin >> money_Deposit;
	cout << "\n\tAccount Created.... :)\n";

}
void Bank_Account::display_account()
{
	cout << "\n";
	cout << "\t Bank Account Number: " << account_number << '\n';
	cout << "\t Acount Holder Name: " << name << '\n';
	cout << "\t Type of Account: " << type << '\n';
	cout << "\t Balance Account: " << money_Deposit << '\n';
}

void Bank_Account::modify()
{
	cout << "\t Bank Account Number: " << account_number << '\n';
	cout << "\t Modify Acount Holder Name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\t Modify Type of Account: ";
	cin >> type;
	type = toupper(type);
	cout << "\t Modify Balance Account: ";
	cin >> money_Deposit;


}

void Bank_Account::report()const
{
	cout << account_number << setw(10) << " " << name << setw(10) << type << setw(10) << money_Deposit << '\n';
}
void write_account();
void delete_account(int);
void display_details(int);
void money_deposite_withdraw(int, int);
void update_bank_account(int);

void display_all();
int main() {

	char ch;
	int num;
	do {
		cout << "\t\t .........................................\n";
		cout << "\t\t | Welcome to the Bank Management System |\n";
		cout << "\t\t .........................................\n";
		cout << "\t --- Main Menu ---\n";
		cout << "\t 1.Create Account\n";
		cout << "\t 2.Deposite Money\n";
		cout << "\t 3.Withdraw Money\n";
		cout << "\t 4.Balance Enquiry\n";
		cout << "\t 5.All Acount Holders List\n";
		cout << "\t 6.Close an Account\n";
		cout << "\t 7.Modify Account\n";
		cout << "\t 8.Exit\n";
		cout << '\n';

		cout << "\t Enter you choice: ";
		cin >> ch;
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("cls");
			cout << "\t Enter the account number: ";
			cin >> num;
			money_deposite_withdraw(num, 1);
			break;
		case '3':
			system("cls");
			cout << "\t Enter the account number: ";
			cin >> num;
			money_deposite_withdraw(num, 2);
			break;
		case '4':
			system("cls");
			cout << "\t Enter the account number: ";
			cin >> num;
			display_details(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("cls");
			cout << "\t Enter the account number: ";
			cin >> num;
			delete_account(num);
			break;
		case '7':
			system("cls");
			cout << "\t Enter the account number: ";
			cin >> num;
			update_bank_account(num);
			break;
		case '8':
			cout << "\t Thanks for using the Bank Mangament System\n";
			break;
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');


	return 0;
}

void write_account() {
	Bank_Account ac;
	ofstream outfile;
	outfile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outfile.write(reinterpret_cast<char*>(&ac), sizeof(Bank_Account));
	outfile.close();
}

void delete_account(int n) {
	Bank_Account ac;
	ifstream infile;
	ofstream outfile;
	infile.open("account.dat", ios::binary);
	if (!infile)
	{
		cout << "File could not be open || Press any key...";
		return;
	}
	outfile.open("temp.dat", ios::binary);
	infile.seekg(0, ios::beg);
	while (infile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_Account)))
	{
		if (ac.retno() != n)
		{
			outfile.write(reinterpret_cast<char*>(&ac), sizeof(Bank_Account));
		}
	}
	infile.close();
	outfile.close();
	remove("account.dat");
	rename("temp.dat","account.dat");
	cout << "\t Account Deleted...\n";
}

void display_details(int n)
{
	Bank_Account ac;
	bool flag = false;
	ifstream infile;
	infile.open("account.dat", ios::binary);
	if (!infile)
	{
		cout << "File could not be open || Press any key...";
		return;
	}
	cout << "\t Bank Account Details";
	while (infile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_Account)))
	{
		if (ac.retno() == n)
		{
			ac.display_account();
			flag = true;
			break;
		}
	}
	infile.close();
	if (flag == false)
	{
		cout << "\t Account number does not exist\n";
	}
}

void display_all()
{
	system("cls");
	Bank_Account ac;
	ifstream infile;
	infile.open("account.dat", ios::binary);
	if (!infile)
	{
		cout << "File could not be open || Press any key...";
		return;
	}
	cout << "\t Bank Account Holders List\n";
	cout << "#####################################################\n";
	cout << "A/c no.          Name          Type          Balance\n";
	cout << "#####################################################\n";
	while (infile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_Account)))
	{
		ac.report();
	}
	infile.close();
}

void money_deposite_withdraw(int n, int option)
{
	int amount;
	bool found = false;
	Bank_Account ac;
	fstream file;
	file.open("account.dat", ios::binary | ios::in | ios::out);
	if (!file)
	{
		cout << "File could not be open || Press any key...";
		return;
	}
	while (!file.eof() && found == false)
	{
		file.read(reinterpret_cast<char*>(&ac), sizeof(Bank_Account));
		if (ac.retno() == n)
		{
			ac.display_account();
			if (option == 1)
			{
				cout << "\t Enter the amount of money to be deposited: ";
				cin >> amount;
				ac.dep(amount);
			}
			if (option == 2)
			{
				cout << "\t Enter the amount of money to be withdraw: ";
				cin >> amount;
				int balance = ac.retdeposite() - amount;
				if (balance < 0)
				{
					cout << "\t insufficient balance\n";
				}
				else
				{
					ac.draw(amount);
				}
			}
			int pos = (-1) * static_cast<int>(sizeof(Bank_Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char*>(&ac), sizeof(Bank_Account));
			cout << "\t Account updated\n";
			found = true;
		}
	}
	file.close();
	if (found == false)
	{
		cout << "\t account not found\n";
	}
}

void update_bank_account(int n)
{
	bool found = false;
	Bank_Account ac;
	fstream file;
	file.open("account.dat", ios::binary | ios::in | ios::out);
	if (!file)
	{
		cout << "File could not be open || Press any key...";
		return;
	}
	while (!file.eof() && found == false)
	{
		file.read(reinterpret_cast<char*>(&ac), sizeof(Bank_Account));
		if (ac.retno() == n)
		{
			ac.display_account();
			cout << "\n\t Enter the new details of the account\n";
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(Bank_Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char*>(&ac), sizeof(Bank_Account));
			cout << "\t Account updated\n";
			found = true;
		}
	}
	file.close();
	if (found == false)
	{
		cout << "\t account not found\n";
	}
}