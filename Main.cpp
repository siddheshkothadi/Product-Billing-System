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

class Item{
	private:
		string name;
		float price;
		unsigned int quantity;
	
	public:
		
		Item(){
			name="NULL";
			price=0;
			quantity=0;
		}
		
		Item(string n, float p, int q){
			name = n;
			price = p;
			quantity = q;
		}
		
};

class Customer{
	private:
		string username;
		string password;
		string address;
		unsigned long long contactNumber;

	public:
		string getUsername(){
			return username;
		}
	
		void takeInput(){
			cout<<"\n\tEnter Username: ";
			//cin.ignore('\n');
			//getline(cin,username);
			cin>>username;
			cout<<"\n\tEnter password: ";
			//cin.ignore('\n');
			//getline(cin,password);
			cin>>password;
			cout<<"\n\tEnter address: ";
			//cin.ignore('\n');
			//getline(cin,address);
			cin>>address;
			cout<<"\n\tEnter your contact number: ";
			cin>>contactNumber;
			//cin.ignore();
		}
		
		// Current Cart
		//vector<Item> currentCart;
		
		// Order History
		//vector<vector<Item>> orderHistory;
		
		// Default Constructor
		Customer(){
			//currentCart = vector<Item>();
			//orderHistory = vector<vector<Item>>();
			username = "NULL";
			password = "NULL";
			address = "NULL";
			contactNumber = 0;
		}
		
		void show(){
			cout<<username<<" "<<password<<" "<<address<<" "<<contactNumber<<endl;
		}
		
		
};

class Items{
	// File operations here
	
};

class Customers:public Items{
	// File operations here
	
	public:
	
	void showFile(){
		ifstream fin;
		Customer customer;
		
		fin.open("db/Customers.txt",ios::in | ios::binary);

		fin.read((char*)&customer, sizeof(customer));
		
		fin.close();
		
	}
	
	void signUp(){
		ofstream customersFile;
		Customer customer;
		
		// Opening the file in append mode
		customersFile.open("db/Customers.txt", ios::app);
		
		customer.takeInput();
	
		customersFile.write((char*)&customer, sizeof(customer));
		
		customersFile.close();
	}
	
	
};



int main(){
	fstream customersFile;
	Customer customer;
	Customers cs;
	
	cs.signUp();

	cs.showFile();
	
	
    return 0;
}
