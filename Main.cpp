/** 	=== Contributors ===
 * 1. Siddhesh
 * 2. Mayank
 * 3. Amrut
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

	void showItem()
	{
		cout << name << "\t" << price << "\t" << quantity << endl;
	}

	friend ostream &operator<<(ostream &out, Item &item)
	{
		out << item.name << "\n"
			<< item.price << "\n"
			<< item.quantity << endl;
		return out;
	}

	friend istream &operator>>(istream &in, Item &item)
	{
		in >> item.name;
		in >> item.price;
		in >> item.quantity;
		return in;
	}
};

class Customer
{
private:
	string password;

	// Contact details
	string address;
	unsigned long long contactNumber;

	// Current Cart
	vector<Item> currentCart;

	// Order History
	//vector<vector<Item>> orderHistory;

public:
	// Unique username
	string username;

	// Default Constructor
	Customer()
	{
		username = "NULL";
		password = "NULL";
		address = "NULL";
		contactNumber = 0;
		currentCart = vector<Item>();
		//orderHistory = vector<vector<Item>>();
	}

	void takeInput()
	{
		cout << "\n\tEnter Username: ";
		cin >> username;
		cout << "\n\tEnter password: ";
		cin >> password;
		cout << "\n\tEnter address: ";
		cin >> address;
		cout << "\n\tEnter your contact number: ";
		cin >> contactNumber;
	}

	void show()
	{
		cout << "\n\tUsername : " << username << "\n\tAddress : " << address << "\n\tContact Number : " << contactNumber << "\n";
		showCart();
	}

	void showCart()
	{
		if (currentCart.empty())
		{
			cout << "\n\tThe cart is empty :(";
			return;
		}
		cout << "Name"
			 << "\tPrice\t"
			 << "Quantity\t" << endl;
		for (Item i : currentCart)
		{
			i.showItem();
		}
	}

	bool areValidCredentials(const string name, const string pass)
	{
		return ((name == username) && (pass == password));
	}

	friend ostream &operator<<(ostream &out, Customer &customer)
	{
		out << customer.username << "\n"
			<< customer.password << "\n"
			<< customer.address << "\n"
			<< customer.contactNumber << "\n";
		for (size_t i = 0; i < customer.currentCart.size(); ++i)
		{
			out << customer.currentCart[i];
		}
		return out;
	}

	friend istream &operator>>(istream &in, Customer &customer)
	{
		in >> customer.username;
		in >> customer.password;
		in >> customer.address;
		in >> customer.contactNumber;
		for (Item i : customer.currentCart)
		{
			in >> i;
		}
		return in;
	}
};

class ShopAccount
{
private:
	string shopID;
	string password;

public:
	/** To validate the credentials entered by the user
	 *  @return true if credentials are correct
	 *  else @return false
	 */
	bool areValidCredentials(string &sID, string &p)
	{
		return ((sID == shopID) && (p == password));
	}

	// To read shopID and password from file
	friend istream &operator>>(istream &in, ShopAccount &shopAccount)
	{
		in >> shopAccount.shopID;
		in >> shopAccount.password;
		return in;
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
		ItemFile.open("Items.txt", ios::app);
		item.addItem();
		ItemFile.write((char *)&item, sizeof(item));
		ItemFile.close();
	}

	int SearchItem(string nam)
	{
		ifstream fin;
		fin.open("db/Items.txt", ios::in);

		Item item;

		fin.read((char *)&item, sizeof(item));

		while (!fin.eof())
		{
			cout << item.name;
			if (nam == item.name)
			{
				cout << "\nfound";
				return 1;
			}
			fin.read((char *)&item, sizeof(item));
		}
		cout << "\n not found";
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
			fin.open("db/Items.txt");
			fout.open("db/text.txt", ios::trunc | ios::out | ios::in);
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
			fpo.open("db/Items.txt", ios::trunc | ios::out | ios::in);
			fpt.open("db/text.txt");
			while (!fpt.eof())
			{
				fpo.write((char *)&item, sizeof(item));
			}
			fpo.close();
			fpt.close();
			remove("db/text.txt");
		}
	}
};

// Customer database file operations
class Customers
{
public:
	/** Checks if a username is valid or not
	 *  @return true if the username is not taken by anyone
	 *  @return false if the username is already taken
	**/
	bool isValidUsername(string &username)
	{
		ifstream file;
		Customer customer;

		file.open("db/Customers.txt", ios::in);

		while (file >> customer)
		{
			if (customer.username == username)
			{
				file.close();
				return 0;
			}
		}

		file.close();
		return 1;
	}

	Customer* searchCustomer(string username, string password, bool &LOGGED_IN)
	{
		ifstream file;
		Customer *customer = new Customer();

		file.open("db/Customers.txt", ios::in);

		while (file >> *customer)
		{
			if (customer->areValidCredentials(username, password))
			{	
				LOGGED_IN = 1;
				break;
			}
		}

		file.close();

		return customer;
	}

	// To add a new customer to the database
	bool signUpCustomer()
	{
		ofstream file;
		Customer customer;
		bool validUsername = 0;

		file.open("db/Customers.txt", ios::app);

		while (!validUsername)
		{
			customer.takeInput();
			validUsername = isValidUsername(customer.username);
			if (!validUsername)
			{
				cout << "\n\tUsername already taken... Please enter another username!";
			}
		}

		file << customer;

		file.close();

		return 1;
	}

	// To delete an account of a customer
	void deleteCustomer(Customer &c)
	{
		ifstream old_file;
		ofstream new_file;
		Customer customer;

		old_file.open("db/Customers.txt");
		new_file.open("db/Temp.txt");

		while (old_file >> customer)
		{
			if (customer.username != c.username)
			{
				new_file << customer;
			}
		}

		old_file.close();
		new_file.close();

		remove("db/Customers.txt");
		rename("db/Temp.txt", "db/Customers.txt");
	}

	/** For debugging purpose only
	 *  TODO: Delete the function below, before submitting
	 */
	void showFile()
	{
		ifstream file;
		Customer customer;

		file.open("db/Customers.txt", ios::in);

		while (file >> customer)
		{
			customer.show();
		}

		file.close();
	}
};

int main()
{
	// Initializing [Customer] pointer to null
	Customer *customer = NULL;

	// Initializing [ShopAccount] pointer to null
	ShopAccount *shop = NULL;

	// Creating an object of class [Customers]
	Customers c_obj;

	// @boolean denoting the registration state of the user
	// either logged in or logged out
	bool LOGGED_IN = 0;

	// Initializing choice to -1
	int choice = -1;

	// Variables for storing the credentials entered by the user
	string username, password, shopID;

	// Authentication Interface
	while (choice)
	{
		if (LOGGED_IN)
		{
			// Show home screen
			cout << "\n\t1. Available items\n\t2. Cart\n\t3. Profile\n\t4. Logout\n\t0. Exit\n\n\tEnter your choice : ";
			cin >> choice;
			/** TODO: Add the required functions for the items **/
		}
		else
		{
			// Show login screen
			cout << "\n\t1. Sign Up (Customer)\n\t2. Login (Customer)\n\t3. Login as Shop\n\t0. Exit\n\n\tEnter your choice : ";
			cin >> choice;
			switch (choice)
			{
			case 1: // Sign-Up [Customer]
				c_obj.signUpCustomer() ? cout << "\n\tSign-Up successful!\n\tPlease Login to continue" : cout << "\n\tSign-Up failed :(";
				break;

			case 2: // Login [Customer]

				// Take input from the user
				cout<<"\n\tEnter your username : ";
				cin>>username;
				cout<<"\n\tEnter your pasword : ";
				cin>>password;

				/** Search if the customer exists
				 * 	If found, save the customer in the customer pointer
				 */
				customer = c_obj.searchCustomer(username, password, LOGGED_IN);

				if(!LOGGED_IN){
					cout<<"\n\tIncorrect username or password! Please try again\n";
					customer = NULL;
				}

				break;

			case 3: // Login [Shop]
				cout<<"\n\tEnter the Shop ID : ";
				cin>>shopID;
				cout<<"\n\tEnter the password : ";
				cin>>password;
				/** TODO: complete this case **/
				break;

			default:
				cout<<"\n\tPlease enter a valid choice!";
				break;
			}
		}
	}

	return 0;
}
