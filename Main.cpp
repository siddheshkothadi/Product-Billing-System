/** 	=== Contributors ===
 * 1. Siddhesh
 * 2. Mayank
 * 3. 
 * 4. 
**/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Item
{
public:
	string name;
	float price;
	unsigned int quantity;

public:
	Item()
	{
		name = "NULL";
		price = 0;
		quantity = 0;
	}

	Item(string n, float p, int q)
	{
		name = n;
		price = p;
		quantity = q;
	}

	void addItem()
	{
		cout << "Enter Name of Item";
		cin >> name;
		cout << "Enter Price of Item";
		cin >> price;
		cout << "Enter Quantity of Item";
		cin >> quantity;
	}
};

class Customer
{
private:
	string username;
	string password;
	string address;
	unsigned long long contactNumber;

public:
	string getUsername()
	{
		return username;
	}

	void takeInput()
	{
		cout << "\n\tEnter Username: ";
		//cin.ignore('\n');
		//getline(cin,username);
		cin >> username;
		cout << "\n\tEnter password: ";
		//cin.ignore('\n');
		//getline(cin,password);
		cin >> password;
		cout << "\n\tEnter address: ";
		//cin.ignore('\n');
		//getline(cin,address);
		cin >> address;
		cout << "\n\tEnter your contact number: ";
		cin >> contactNumber;
		//cin.ignore();
	}

	// Current Cart
	//vector<Item> currentCart;

	// Order History
	//vector<vector<Item>> orderHistory;

	// Default Constructor
	Customer()
	{
		//currentCart = vector<Item>();
		//orderHistory = vector<vector<Item>>();
		username = "NULL";
		password = "NULL";
		address = "NULL";
		contactNumber = 0;
	}

	void show()
	{
		cout << username << " " << password << " " << address << " " << contactNumber << endl;
	}
};

class Items : public Item
{
	// File operations here
public:
	//Add Items
	void AddItems()
	{
		Item item;
		ofstream ItemFile;
		ItemFile.open("/db/Items.txt", ios::app);
		item.addItem();
		ItemFile.write((char *)&item, sizeof(item));
		ItemFile.close();
	}

	int SearchItem(string nam)
	{
		ifstream fin;
		Item item;
		fin.open("/db/Items.txt");
		fin.read((char *)&item, sizeof(item));

		while (!fin.eof())
		{
			if (nam == item.name)
			{
				return 1;
			}
		}
		fin.close();
		return 0;
	}
	void ModifyItem()
	{
		string nam;
		int flag;
		cout << "Enter the name Of the item which you want to modify";
		cin >> nam;
		flag = SearchItem(nam);
		if (flag == 0)
		{
			cout << "Item Not Found!! Enter Vaild Name";
		}
		else
		{
			fstream fout;
			ifstream fin;
			Item item;
			fin.open("/db/Items.txt");
			fout.open("/db/text.txt", ios::trunc | ios::out | ios::in);
			fin.seekg(0, ios::beg);
			fin.read((char *)&item, sizeof(item));
			while (fin)
			{
				if (nam != item.name)
				{
					fout.write((char *)&item, sizeof(item));
				}
				else
				{
					item.addItem();
					fout.write((char *)&item, sizeof(item));
				}
			}
			fout.close();
			fin.close();
			ifstream fpt;
			fstream fpo;
			fpo.open("/db/Items.txt", ios::trunc | ios::out | ios::in);
			fpt.open("/db/text.txt");
			while (!fpt.eof())
			{
				fpo.write((char *)&item, sizeof(item));
			}
			fpo.close();
			fpt.close();
			remove("/db/text.txt");
		}
	}
};

class Customers : public Items
{
	// File operations here

public:
	void showFile()
	{
		ifstream fin;
		Customer customer;

		fin.open("db/Customers.txt", ios::in | ios::binary);

		fin.read((char *)&customer, sizeof(customer));

		fin.close();
	}

	void signUp()

	{
		ofstream customersFile;
		Customer customer;

		// Opening the file in append mode
		customersFile.open("db/Customers.txt", ios::app);

		customer.takeInput();

		customersFile.write((char *)&customer, sizeof(customer));

		customersFile.close();
	}
};

int main()
{
	fstream customersFile;
	Customer customer;
	Customers cs;
	Items it;
	it.AddItems();
	it.AddItems();
	cout
		<< "Modify items";
	it.ModifyItem();

	// cs.signUp();

	// cs.showFile();

	return 0;
}
