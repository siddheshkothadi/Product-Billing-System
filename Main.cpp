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
private:
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

	void takeInput()
	{
		cout << "\n\tEnter Name of Item: ";
		cin >> name;
		cout << "\n\tEnter Price of Item: ";
		cin >> price;
		cout << "\n\tEnter Quantity of Item: ";
		cin >> quantity;
	}

	string getName()
	{
		return name;
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
	// Unique username and password
	string username;
	string password;

	// Contact details
	string address;
	unsigned long long contactNumber;

	// Current Cart
	vector<Item> currentCart;

	// Order History
	//vector<vector<Item>> orderHistory;

public:
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

	string getUsername()
	{
		return username;
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
	// Default Constructor to initialize the values
	ShopAccount()
	{
		shopID = "NULL";
		password = "NULL";
	}

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

class Items
{
public:
	bool searchItem(string &n)
	{
		ifstream fileItem;
		fileItem.open("db/Items.txt", ios::in);

		Item item;

		while (fileItem >> item)
		{
			if (item.getName() == n)
			{
				// Item Found
				fileItem.close();
				return 1;
			}
		}

		// Item Not Found
		fileItem.close();
		return 0;
	}

	//Add Item
	void addItem()
	{
		Item item;
		string itemName;
		ofstream itemFile;
		bool itemAlreadyExists = 1;

		itemFile.open("db/Items.txt", ios::app);

		while (itemAlreadyExists)
		{
			item.takeInput();
			itemName = item.getName();
			if (searchItem(itemName))
			{
				// Item already exists
				cout << "\n\tItem already exists!"
					 << "\n\tPlease add a unique item!\n";
			}
			else
			{
				// If the item name is unique, end the loop
				itemAlreadyExists = 0;
			}
		}

		itemFile << item;
		itemFile.close();
	}

	void modifyItem(string key)
	{
		bool found = searchItem(key);
		if (found)
		{
			deleteItem(key);
			addItem();
		}
		else
		{
			cout << "\n\tItem not found";
		}
	}

	void deleteItem(string key)
	{
		ifstream old_file;
		ofstream new_file;
		Item item;

		old_file.open("db/Items.txt");
		new_file.open("db/Temp.txt");

		while (old_file >> item)
		{
			if (item.getName() != key)
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
private:
	string key;

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
			if (customer.getUsername() == username)
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
			key = customer.getUsername();
			validUsername = isValidUsername(key);
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
			if (customer.getUsername() != c.getUsername())
			{
				new_file << customer;
			}
		}

		old_file.close();
		new_file.close();

		remove("db/Customers.txt");
		rename("db/Temp.txt", "db/Customers.txt");
	}

	// /** For debugging purpose only
	//  *  TODO: Delete the function below, before submitting
	//  */
	// void showFile()
	// {
	// 	ifstream file;
	// 	Customer customer;

	// 	file.open("db/Customers.txt", ios::in);

	// 	while (file >> customer)
	// 	{
	// 		customer.show();
	// 	}

	// 	file.close();
	// }
};

int main()
{
	// Object of class [Items]
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
	string username, password, shopID, key;

	// For reading files
	ifstream file;

	// Authentication Interface
	while (choice)
	{
		if (state == UserState::LOGGED_OUT)
		{
			// Welcome Screen
			cout << "\t\t================================================"
				 << "\n\t\t********\tWELCOME TO SHOPKART\t********"
				 << "\n\t\t================================================\n\n";
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
				else
				{
					cout << "\n\tWelcome \'" << username << "\', you're now logged in\n";
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
					cout << "\n\tWelcome \'" << shopID << "\', you're now logged in\n";
				}
				else
				{
					cout << "\n\tIncorrect Shop ID or Password! Please try again\n";
				}
				break;

			default:
				cout << "\n\tPlease enter a valid choice!\n";
				break;
			}
		}
		else if (state == UserState::CUSTOMER)
		{
			// Show home screen
			cout << "\n\t\t1. Available items"
				 << "\n\t\t2. Cart"
				 << "\n\t\t3. Profile"
				 << "\n\t\t4. Logout"
				 << "\n\t\t0. Exit"
				 << "\n\n\t\tEnter your choice : ";
			cin >> choice;

			switch (choice)
			{
			case 4:
				state = UserState::LOGGED_OUT;
				cout << "\n\tSuccessfully Logged Out!\n";
				break;

			default:
				cout << "\n\tPlease enter a valid choice!\n";
				break;
			}

			/** TODO: Add the required functions for the items **/
		}
		else if (state == UserState::SHOP)
		{
			// Show Home Screen
			cout << "\n\t\t1. Add item"
				 << "\n\t\t2. Remove item"
				 << "\n\t\t3. Modify item"
				 << "\n\t\t4. Logout"
				 << "\n\t\t0. Exit"
				 << "\n\n\t\tEnter your choice : ";
			cin >> choice;
			switch (choice)
			{

			case 1:
				i_obj.addItem();
				break;

			case 2:
				cout << "\n\tEnter the item name to be deleted ";
				cin >> key;
				i_obj.deleteItem(key);
				break;

			case 3:
				cout << "\n\tEnter the name of item to be modify: ";
				cin >> key;
				i_obj.modifyItem(key);
				break;

			case 4:
				state = UserState::LOGGED_OUT;
				cout << "\n\tSuccessfully Logged Out!\n";
				break;

			default:
				cout << "\n\tPlease enter a valid choice!\n";
				break;
			}
		}
	}

	return 0;
}
