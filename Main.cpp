/** == List of Contributors ==
 * 	1. Siddhesh
 * 	2. Mayank
 * 	3. Amrut
 * 	4. Ekta
**/

#include <iostream> // For Standard Input-Output Stream
#include <fstream>	// For File Handilng
#include <string>	// For String Operations
#include <vector>	// Container used for storing collection of [Item] and [OrderHistory]
#include <ctime>	// To generate Date and Time while Placing Order
using namespace std;

/** Enum class representing state of the User **/
enum class UserState
{
	CUSTOMER,
	SHOP,
	LOGGED_OUT
};

// [Item] class represents a single Item
class Item
{
private:
	string name;
	float price;
	unsigned int quantity;

public:
	// Default Constructor
	Item()
	{
		name = "NULL";
		price = 0;
		quantity = 0;
	}

	// Parameterized constructor
	Item(string n, float p, int q)
	{
		name = n;
		price = p;
		quantity = q;
	}

	// To take the input from the user
	void takeInput();
	/** Getters for Data Members **/
	string getName()
	{
		return name;
	}
	int getPrice()
	{
		return price;
	}
	int getQuantity()
	{
		return quantity;
	}

	// To display the item information
	void showItem();

	/** To reduce the quantity of item by the provided amount
	 * @return true if quantity can be reduced
	 * else @return false
	 */
	bool reduceQuantity(int amount)
	{
		if (quantity >= amount)
		{
			quantity -= amount;
			// Return true if quantity can be reduced
			return true;
		}
		cout << "\n\t\tRequested number of items exceeds the available quantity!";
		return false;
	}

	/** To incresase the quantity of item by the provided amount
	 * @return true if quantity can be increased
	 * else @return false
	 */
	bool increaseQuantity(int amount)
	{
		if (amount >= 0)
		{
			quantity += amount;
			return true;
		}
		return false;
	}

	/**Overloaded insertion operator
	 * Writes an item to the file
	 */
	friend ostream &operator<<(ostream &out, Item &item)
	{
		out << item.name << "\n"
			<< item.price << "\n"
			<< item.quantity << endl;
		return out;
	}

	/**Overloaded extraction operator
	 * Reads an item from the file
	 */
	friend istream &operator>>(istream &in, Item &item)
	{
		in >> item.name;
		in >> item.price;
		in >> item.quantity;
		return in;
	}
};

// To take the input from the user
void Item ::takeInput()
{
	cout << "\n\t\tEnter Name of Item: ";
	cin >> name;
	cout << "\n\t\tEnter Price of Item: ";
	cin >> price;
	cout << "\n\t\tEnter Quantity of Item: ";
	cin >> quantity;
}
// To display the item information
void Item::showItem()
{
	cout << "\t\t\t\t" << name << "\t" << price << "\t" << quantity << endl;
}

/**
 * [OrderHistory] represents the summary of the placed order
 */
class OrderHistory
{
private:
	int numberOfItems;
	int totalBillAmount;
	tm *localTime;
	time_t now;
	int day;
	int month;
	int year;

public:
	// Default Constructor

	OrderHistory()

	{
		numberOfItems = 0;
		totalBillAmount = 0;
		now = time(0);
		localTime = localtime(&now);
		day = localTime->tm_mday;
		month = localTime->tm_mon + 1;
		year = localTime->tm_year + 1900;
	}

	// Parameterized Constructor
	OrderHistory(int noOfItems, int billAmount)
	{
		numberOfItems = noOfItems;
		totalBillAmount = billAmount;
		now = time(0);
		localTime = localtime(&now);
		day = localTime->tm_mday;
		month = localTime->tm_mon + 1;
		year = localTime->tm_year + 1900;
	}
	// Displays the order history
	void showOrderHistory();

	/**Overloaded insertion(<<) operator
	 * Writes order summary to the file
	 */
	friend ostream &operator<<(ostream &out, OrderHistory &order)
	{
		out << order.numberOfItems << "\n"
			<< order.totalBillAmount << "\n"
			<< order.day << "\n"
			<< order.month << "\n"
			<< order.year << endl;
		return out;
	}

	/**Overloaded extraction(>>) operator
	 * Reads order summary from the file
	 */
	friend istream &operator>>(istream &in, OrderHistory &order)
	{
		in >> order.numberOfItems;
		in >> order.totalBillAmount;
		in >> order.day;
		in >> order.month;
		in >> order.year;
		return in;
	}
};

// Displays the order history
void OrderHistory ::showOrderHistory()
{
	cout << "\n\t\tDate : " << day << "/" << month << "/" << year;
	cout << "\n\t\t\tItems Ordered = " << numberOfItems;
	cout << "\n\t\t\tTotal Bill Amount = Rs. " << totalBillAmount;
}

// Class representing a Customer
class Customer
{
private:
	// Unique username and password
	string username;
	string password;

	// Contact details
	string address;
	unsigned long long contactNumber;

public:
	// Current Cart and its size
	// A vector representing the collection of [Item] i.e. cart
	vector<Item> currentCart;
	int CART_SIZE;

	// Previous Order History and its size
	// A vector representing the collection of [OrderHistory]
	vector<OrderHistory> orderHistory;
	int ORDER_HISTORY_SIZE;

	// Default Constructor
	Customer()
	{
		username = "NULL";
		password = "NULL";
		address = "NULL";
		contactNumber = 0;
		CART_SIZE = 0;
		currentCart = vector<Item>();
		ORDER_HISTORY_SIZE = 0;
		orderHistory = vector<OrderHistory>();
	}
	// To take input while signing up the user
	void takeInput();

	// Getter for username
	string getUsername()
	{
		return username;
	}

	// To verify credentials while logging in
	bool areValidCredentials(const string name, const string pass)
	{
		return ((name == username) && (pass == password));
	}

	// To show the customer profile
	void displayProfile();

	// To calculate the total bill amount and the total number of items in the cart
	vector<int> calculateBill()
	{
		int total = 0;
		int noOfItems = 0;
		if (currentCart.empty())
			return {0, 0};

		for (Item &i : currentCart)
		{
			noOfItems += i.getQuantity();
			total += i.getPrice() * i.getQuantity();
		}
		return {noOfItems, total};
	}

	/** ===CART OPERATIONS=== **/

	// To show the items inside the cart
	void showCart();

	// To clear the cart
	void emptyCart()
	{
		currentCart.clear();
		CART_SIZE = 0;
	}

	// To display the previous order history of the customer
	void viewPreviousOrderHistory();

	/**Overloaded insertion(<<) operator
	 * Writes customer information to the file
	 */
	friend ostream &operator<<(ostream &out, Customer &customer)
	{
		out << customer.username << "\n"
			<< customer.password << "\n"
			<< customer.address << "\n"
			<< customer.contactNumber << "\n"
			<< customer.CART_SIZE << "\n";

		// Cart
		for (int i = 0; i < customer.CART_SIZE; ++i)
		{
			out << customer.currentCart[i];
		}

		// Order History
		out << customer.ORDER_HISTORY_SIZE << "\n";
		for (int i = 0; i < customer.ORDER_HISTORY_SIZE; ++i)
		{
			out << customer.orderHistory[i];
		}
		return out;
	}

	/**Overloaded extraction(>>) operator
	 * Reads customer information from the file
	 */
	friend istream &operator>>(istream &in, Customer &customer)
	{
		in >> customer.username;
		in >> customer.password;
		in >> customer.address;
		in >> customer.contactNumber;
		in >> customer.CART_SIZE;
		customer.currentCart.resize(customer.CART_SIZE);
		for (int i = 0; i < customer.CART_SIZE; ++i)
		{
			in >> customer.currentCart[i];
		}
		in >> customer.ORDER_HISTORY_SIZE;
		customer.orderHistory.resize(customer.ORDER_HISTORY_SIZE);
		for (int i = 0; i < customer.ORDER_HISTORY_SIZE; ++i)
		{
			in >> customer.orderHistory[i];
		}
		return in;
	}
};
// To take input while signing up the user
void Customer ::takeInput()
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
// To show the customer profile
void Customer::displayProfile()
{
	cout << "\n\tUsername : " << username << "\n\tAddress : " << address << "\n\tContact Number : " << contactNumber << "\n";
}
// To show the items inside the cart
void Customer::showCart()
{
	if (currentCart.empty())
	{
		cout << "\n\t\tThe cart is empty :)\n";
		return;
	}
	cout << "\n\t\t\t\t======== CART ========"
		 << "\n\n\t\t\t\tName"
		 << "\tPrice\t"
		 << "Quantity\t" << endl;
	for (Item i : currentCart)
	{
		i.showItem();
	}
	vector<int> bill = calculateBill();
	cout << "\n\n\t\t\tTotal Items : " << bill[0];
	cout << "\n\t\t\tTotal Bill Amount : Rs. " << bill[1] << endl;
}
// To display the previous order history of the customer
void Customer::viewPreviousOrderHistory()
{
	if (orderHistory.empty())
	{
		cout << "\n\t\tNo previous order history found :)\n";
	}
	for (OrderHistory &order : orderHistory)
	{
		order.showOrderHistory();
		cout << "\n";
	}
}

// Class representing the account of the shop
// [ShopAccount] can modify the item database
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

	/**Overloaded extraction operator(>>)
	 * To read shop credentials from the file
	 */
	friend istream &operator>>(istream &in, ShopAccount &shopAccount)
	{
		in >> shopAccount.shopID;
		in >> shopAccount.password;
		return in;
	}
};

// This class handles all the database realted operations of Items database
class Items
{
public:
	/** In the database, search for the item with the provided name
	 * If found, @return the [Item]
	 * else @return NULL
	 */
	Item *searchItem(string &n)
	{
		ifstream fileItem;
		fileItem.open("db/Items.txt", ios::in);

		Item *item = new Item();

		while (fileItem >> *item)
		{
			if (item->getName() == n)
			{
				// Item Found
				fileItem.close();
				return item;
			}
		}

		// Item Not Found
		fileItem.close();
		return NULL;
	}

	// To add the item to the Items database
	void addItem();

	// To modify an item from the Items database
	void modifyItem(string key);

	// To delete an item from the Items database
	void deleteItem(string key);

	// To display a list of available items
	void displayItem();

	/** To reduce quantity of the provided [Item] by @param quantity
	 * If the quantity can be reduced, reduce the quantity and @return true
	 * else @return false
	 */
	bool reduceQuantity(Item *itemToReduce, int quantity);

	/** To increase quantity of the provided [Item] by @param quantity
	 * If the quantity can be increased, increase the quantity and @return true
	 * else @return false
	 */
	bool increaseQuantity(Item *itemToIncrease, int quantity);
};
// To add the item to the Items database
void Items ::addItem()
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
		if (searchItem(itemName) != NULL)
		{
			// Item already exists
			cout << "\n\t\tItem already exists!"
				 << "\n\t\tPlease add a unique item!\n";
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

// To modify an item from the Items database
void Items ::modifyItem(string key)
{
	//bool found = searchItem(key);
	bool found;
	if (searchItem(key) != NULL)
	{
		found = 1;
	}
	else
	{
		found = 0;
	}
	if (found)
	{
		deleteItem(key);
		addItem();
	}
	else
	{
		cout << "\n\t\tItem not found";
	}
}

// To delete an item from the Items database
void Items::deleteItem(string key)
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

// To display a list of available items
void Items::displayItem()
{
	ifstream fileItem;
	fileItem.open("db/Items.txt", ios::in);

	Item item;
	cout << "\n\t\t\t\tName"
		 << "\tPrice\t"
		 << "Quantity\t\n"
		 << endl;
	while (fileItem >> item)
	{
		item.showItem();
	}
	fileItem.close();
}

bool Items::reduceQuantity(Item *itemToReduce, int quantity)
{
	ifstream old_file;
	ofstream new_file;
	Item item;
	bool reduced = false;

	old_file.open("db/Items.txt");
	new_file.open("db/Temp.txt");

	while (old_file >> item)
	{
		if (item.getName() != itemToReduce->getName())
		{
			new_file << item;
		}
		else
		{
			reduced = item.reduceQuantity(quantity);
			new_file << item;
		}
	}

	old_file.close();
	new_file.close();

	remove("db/Items.txt");
	rename("db/Temp.txt", "db/Items.txt");

	return reduced;
}

bool Items::increaseQuantity(Item *itemToIncrease, int quantity)
{
	ifstream old_file;
	ofstream new_file;
	Item item;
	bool increased = false;

	old_file.open("db/Items.txt");
	new_file.open("db/Temp.txt");

	while (old_file >> item)
	{
		if (item.getName() != itemToIncrease->getName())
		{
			new_file << item;
		}
		else
		{
			increased = item.increaseQuantity(quantity);
			new_file << item;
		}
	}

	old_file.close();
	new_file.close();

	remove("db/Items.txt");
	rename("db/Temp.txt", "db/Items.txt");

	return increased;
}

// A class that handles all the database operations related to Customers database
class Customers
{
private:
	string key;

public:
	/** Checks if a username is valid or not
	 *  @return true if the username is not taken by anyone
	 *  @return false if the username is already taken
	**/
	bool isValidUsername(string &username);

	// Search and return the customer if found in the database else return NULL

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
	bool signUpCustomer();

	// To delete an account of a customer
	void deleteCustomer(Customer &c);

	// To add an item to the customer's cart from the items database
	void addItemToCart(Customer *currentCustomer);
	// To remove an item from the customer's cart and add it to the items database
	void removeItemFromCart(Customer *currentCustomer);

	/** Called when a customer places the order :
	 * 	1. Generate the bill
	 * 	2. Clear the cart
	 * 	3. Take the order summary and place the order
	 */
	void placeOrder(Customer *currentCustomer);
};
bool Customers::isValidUsername(string &username)
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
// To add a new customer to the database
bool Customers::signUpCustomer()
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
void Customers::deleteCustomer(Customer &c)
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
// To add an item to the customer's cart from the items database
void Customers::addItemToCart(Customer *currentCustomer)
{
	ifstream old_file;
	ofstream new_file;
	Customer customer;
	Items itemDB;
	Item *itemToAdd;
	bool reduced = false;

	string nameOfItem;
	int quantityOfItem;

	cout << "Enter the name of the item to add : ";
	cin >> nameOfItem;
	cout << "Enter the quantiy of the item to add : ";
	cin >> quantityOfItem;

	// Find the item in the item's database
	itemToAdd = itemDB.searchItem(nameOfItem);
	// Reduce that item's quantity from the item DB
	if (itemToAdd != NULL || itemToAdd->getQuantity() != 0)
	{
		reduced = itemDB.reduceQuantity(itemToAdd, quantityOfItem);
	}

	// If there's an exception while removing the item from the DB, do not add item to cart
	if (!reduced)
	{
		cout << "\n\t\tCan't add the requested item to cart!\n";
		return;
	}

	// If the item already exists in the cart, Increase the quantity in the cart
	bool found = false;
	for (Item &i : currentCustomer->currentCart)
	{
		if (i.getName() == nameOfItem)
		{
			found = true;
			i.increaseQuantity(quantityOfItem);
			break;
		}
	}

	// If not found, Use the parameterized constructor to create an object of class Item
	if (!found)
	{
		Item it = Item(nameOfItem, itemToAdd->getPrice(), quantityOfItem);
		currentCustomer->currentCart.push_back(it);
		currentCustomer->CART_SIZE++;
	}

	old_file.open("db/Customers.txt");
	new_file.open("db/Temp.txt");

	while (old_file >> customer)
	{
		if (customer.getUsername() != currentCustomer->getUsername())
		{
			new_file << customer;
		}
		else
		{
			// This pointer refers to the current [updated] instance of the class
			new_file << *currentCustomer;
		}
	}

	old_file.close();
	new_file.close();

	remove("db/Customers.txt");
	rename("db/Temp.txt", "db/Customers.txt");
	cout << "\n\t\t\tAdded the item to the cart!\n";
}

// To remove an item from the customer's cart and add it to the items database
void Customers::removeItemFromCart(Customer *currentCustomer)
{
	ifstream old_file;
	ofstream new_file;
	Customer customer;
	Items itemDB;
	Item *itemToRemove;
	bool increased = false;

	string nameOfItem;
	int quantityOfItem = 0;

	cout << "Enter the name of the item to remove : ";
	cin >> nameOfItem;

	// Erase all items with than name from the cart
	for (auto ptr = currentCustomer->currentCart.begin(); ptr != currentCustomer->currentCart.end(); ++ptr)
	{
		if (ptr->getName() == nameOfItem)
		{
			quantityOfItem += ptr->getQuantity();
			currentCustomer->currentCart.erase(ptr--);
			currentCustomer->CART_SIZE--;
		}
	}

	// Find the item in the item's database
	itemToRemove = itemDB.searchItem(nameOfItem);
	// Increase its quantity
	if (itemToRemove != NULL)
	{
		increased = itemDB.increaseQuantity(itemToRemove, quantityOfItem);
	}

	// If there's an exception while removing the item from the DB, do not add item to cart
	if (!increased)
		return;

	// Update the database
	old_file.open("db/Customers.txt");
	new_file.open("db/Temp.txt");

	while (old_file >> customer)
	{
		if (customer.getUsername() != currentCustomer->getUsername())
		{
			new_file << customer;
		}
		else
		{
			new_file << *currentCustomer;
		}
	}

	old_file.close();
	new_file.close();

	remove("db/Customers.txt");
	rename("db/Temp.txt", "db/Customers.txt");
}

void Customers::placeOrder(Customer *currentCustomer)
{
	ifstream old_file;
	ofstream new_file;
	Customer customer;

	// Generate the bill
	vector<int> bill = currentCustomer->calculateBill();
	if (bill[0] == 0)
	{
		cout << "\n\t\t\tYour cart is empty... can't place the order!\n";
		return;
	}

	// Clear the cart
	currentCustomer->emptyCart();

	// Take the order summary and place the order
	OrderHistory order(bill[0], bill[1]);
	currentCustomer->orderHistory.push_back(order);
	currentCustomer->ORDER_HISTORY_SIZE++;

	old_file.open("db/Customers.txt");
	new_file.open("db/Temp.txt");

	// Update the database
	while (old_file >> customer)
	{
		if (customer.getUsername() != currentCustomer->getUsername())
		{
			new_file << customer;
		}
		else
		{
			// This pointer refers to the current [updated] instance of the class
			new_file << *currentCustomer;
		}
	}

	old_file.close();
	new_file.close();

	remove("db/Customers.txt");
	rename("db/Temp.txt", "db/Customers.txt");
	cout << "\n\t\t\tOrder Placed!\n\t\t\tThank you for using Shopkart!";
}

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
			cout << "\n\n\t\t================================================"
				 << "\n\t\t********\tWELCOME TO SHOPKART\t********"
				 << "\n\t\t================================================\n\n";
			// Show Login Screen
			cout << "\n\t1. Sign Up\t[Customer]"
				 << "\n\t2. Login\t[Customer]"
				 << "\n\t3. Login\t[Shop]"
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

			case 0:
				break;

			default:
				cout << "\n\tPlease enter a valid choice!\n";
				break;
			}
		}
		else if (state == UserState::CUSTOMER)
		{
			// Show home screen
			cout << "\n\t\t1. Show Available items"
				 << "\n\t\t2. Show Cart"
				 << "\n\t\t3. Add an Item to Cart"
				 << "\n\t\t4. Remove an Item from Cart"
				 << "\n\t\t5. Place Order"
				 << "\n\t\t6. View Previous Order History"
				 << "\n\t\t7. Profile"
				 << "\n\t\t8. Logout"
				 << "\n\t\t0. Exit"
				 << "\n\n\t\tEnter your choice : ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				i_obj.displayItem();
				break;

			case 2:
				customer->showCart();
				break;

			case 3:
				c_obj.addItemToCart(customer);
				break;

			case 4:
				c_obj.removeItemFromCart(customer);
				cout << "\n\t\t\tItem removed from the cart!";
				break;

			case 5:
				c_obj.placeOrder(customer);
				break;

			case 6:
				customer->viewPreviousOrderHistory();
				break;

			case 7:
				customer->displayProfile();
				break;

			case 8:
				state = UserState::LOGGED_OUT;
				cout << "\n\tSuccessfully Logged Out!\n";
				break;

			case 0:
				break;

			default:
				cout << "\n\tPlease enter a valid choice!\n";
				break;
			}
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
				cout << "\n\t\tItem added successfully!\n";
				break;

			case 2:
				cout << "\n\t\tEnter the item name to be deleted: ";
				cin >> key;
				i_obj.deleteItem(key);
				cout << "\n\t\tItem deleted successfully!\n";
				break;

			case 3:
				cout << "\n\t\tEnter the name of item to be modified: ";
				cin >> key;
				i_obj.modifyItem(key);
				cout << "\n\t\tItem modified successfully!\n";
				break;

			case 4:
				state = UserState::LOGGED_OUT;
				cout << "\n\tSuccessfully Logged Out!\n";
				break;

			case 0:
				break;

			default:
				cout << "\n\t\tPlease enter a valid choice!\n";
				break;
			}
		}
	}

	return 0;
}
