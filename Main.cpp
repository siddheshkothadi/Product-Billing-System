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

enum class UserState
{
	CUSTOMER,
	SHOP,
	LOGGED_OUT
};

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
		cout << "\nEnter Name of Item: ";
		cin >> name;
		cout << "\nEnter Price of Item: ";
		cin >> price;
		cout << "\nEnter Quantity of Item: ";
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
		ItemFile.open("db/Items.txt", ios::app);
		item.addItem();
		ItemFile << item;
		ItemFile.close();
	}
	bool SearchItem(string &nam)
	{
		ifstream fileItem;
		fileItem.open("db/Items.txt", ios::in);

		Item item;

		while (fileItem >> item)
		{
			if (item.name == nam)
			{
				fileItem.close();
				return 0;
			}
		}

		fileItem.close();
		return 1;
	}
	void modifyItem(Item &i)
	{
		bool flag = SearchItem(i.name);
		if (!flag)
		{
			deleteItem(i);
			AddItems();
		}
		else
		{
			cout << "item not found";
		}
	};

	void deleteItem(Item &i)
	{
		ifstream old_file;
		ofstream new_file;
		Item item;

		old_file.open("db/Items.txt");
		new_file.open("db/Temp.txt");

		while (old_file >> item)
		{
			if (item.name != i.name)
			{
				new_file << item;
			}
		}

		old_file.close();
		new_file.close();

		remove("db/Items.txt");
		rename("db/Temp.txt", "db/Items.txt");
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

	Customer *searchCustomer(string &username, string &password, UserState &state)
	{
		ifstream file;
		Customer *customer = new Customer();

		file.open("db/Customers.txt", ios::in);

		while (file >> *customer)
		{
			if (customer->areValidCredentials(username, password))
			{
				state = UserState::CUSTOMER;
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
	// Item *item = NULL;
	Items i_obj;
	// Initializing [Customer] pointer to null
	Customer *customer = NULL;

	// Initializing [ShopAccount] pointer
	ShopAccount *shop = new ShopAccount();

	// Creating an object of class [Customers]
	Customers c_obj;

	// Object of enum class [UserState]
	UserState state = UserState::LOGGED_OUT;

	// Initializing choice to -1
	int choice = -1;

	// Variables for storing the credentials entered by the user
	string username, password, shopID;

	// For reading files
	ifstream file;

	// Authentication Interface
	while (choice)
	{
		if (state == UserState::LOGGED_OUT)
		{
			// Show Login Screen
			cout << "\n\t1. Sign Up [Customer]"
				 << "\n\t2. Login [Customer]"
				 << "\n\t3. Login [Shop]"
				 << "\n\t0. Exit"
				 << "\n\n\tEnter your choice : ";
			cin >> choice;

			switch (choice)
			{
			case 1: // Sign-Up [Customer]
				c_obj.signUpCustomer() ? cout << "\n\tSign-Up successful!\n\tPlease Login to continue\n" : cout << "\n\tSign-Up failed :(\n";
				break;

			case 2: // Login [Customer]

				// Take input from the user
				cout << "\n\tEnter your username : ";
				cin >> username;
				cout << "\n\tEnter your pasword : ";
				cin >> password;

				//Search if the customer exists
				//If found, save the customer in the customer pointer
				customer = c_obj.searchCustomer(username, password, state);

				if (state != UserState::CUSTOMER)
				{
					cout << "\n\tIncorrect username or password! Please try again\n";
					customer = NULL;
				}

				break;

			case 3: // Login [Shop]

				// Input credentials from user
				cout << "\n\tEnter the Shop ID : ";
				cin >> shopID;
				cout << "\n\tEnter the password : ";
				cin >> password;

				// Read credentials from file
				file.open("db/ShopAccount.txt");
				file >> *shop;
				file.close();

				if (shop->areValidCredentials(shopID, password))
				{
					state = UserState::SHOP;
				}
				else
				{
					cout << "\n\tIncorrect Shop ID or Password! Please try again\n";
					shop = NULL;
				}

				break;

			default:
				cout << "\n\tPlease enter a valid choice!";
				break;
			}
		}
		else if (state == UserState::CUSTOMER)
		{
			// Show home screen
			cout << "\n\t1. Available items"
				 << "\n\t2. Cart"
				 << "\n\t3. Profile"
				 << "\n\t4. Logout"
				 << "\n\t0. Exit"
				 << "\n\n\tEnter your choice : ";
			cin >> choice;
			/** TODO: Add the required functions for the items **/
		}
		else if (state == UserState::SHOP)
		{
			// Show Home Screen
			cout << "\n\t1. Add item"
				 << "\n\t2. Remove item"
				 << "\n\t3. Modify item"
				 << "\n\t4. Logout"
				 << "\n\t0. Exit"
				 << "\n\n\tEnter your choice : ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				i_obj.AddItems();
				break;
			case 2:
				cout << "Enter the item name to be deleted ";
				cin >> i_obj.name;
				i_obj.deleteItem(i_obj);
				break;
			case 3:

				cout << "Enter the name of item to be modify: ";
				cin >> i_obj.name;
				i_obj.modifyItem(i_obj);
				break;

			default:
				break;
			}

			/** TODO: Add required functions **/
		}
	}

	return 0;
}
