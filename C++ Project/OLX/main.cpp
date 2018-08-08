#include<iostream>
#include<cstring>
#include<fstream>
#include<stdlib.h>
using namespace std;

const char userfile[15] ="Users.txt";
const char productfile[15] ="Products.txt";
const char categoryfile[15] ="Categories.txt";


class user
{
	long userID;
	char userName[40];
	char email[40];
	char password[40];
	char role[20];
public:
	bool login(user &u);
	void Register(user &u);
	void save(user u1);
	void update();
	void welcomeUser();
	void manageUsers();
	void showAllUsers();
	void displayUser();
	long getLastUserID();
	user getUserById(long id);
	char* getUserName();
	char* getUserMail();
	void createAdmin();
};

class categories
{
	char categoryName[25];
	long categoryId;
public:
	void displayCategories();
	categories getCategory(int categoryId);
	char* getCategoryName();
	long getLastCategoryId();
	void addCategories();
	void manageCategories();
	void save(categories c);
	void update();

};

class product
{
	public:
	long prodId;
	long sellerId;
	char prodName[50];
	char modelNo[50];
	int price;
	int categoryId;
	void displayProduct();
	void displayProductByCat(long catId);
	void saveProduct(product p1);
	void sell(long sellerid);
	void buy();
};


bool user::login(user &u)
{
		user u1;
		system("cls");
		bool valid = false;
	    cout<< "Enter User Name :  ";
		cin>>u1.userName;
		cout<< "Enter password :  ";
		cin>>u1.password;

		//validate user
		fstream file;
		file.open(userfile,ios::in|ios::binary);
		if(!file)
			cout<<"Users files could not be opened";
		else
		{
			while(file)
			{
				file.read((char*)&u, sizeof(u));
				if(strcmp(u1.userName ,u.userName) == 0 && strcmp(u1.password,u.password) == 0)
				{
					valid =true;
					break;
				}
			}
		}
		file.close();
		return valid;
}

void user::Register(user &u1)
{
		system("cls");
		u1.userID = u1.getLastUserID() + 1;
	    cout<< "Enter User Name :  ";
		cin>>u1.userName;
	    cout<< "Enter Email Id :  ";
		cin>>u1.email;
		cout<< "Enter password :  ";
		cin>>u1.password;
		strcpy(u1.role,"user");
		u1.save(u1);
}

long user::getLastUserID()
{
		fstream file;
		user u1;
		long userid;
		file.open(userfile, ios::in|ios::binary);
		if(file)
		{
			while(!file.eof())
			{
				file.read((char*)&u1, sizeof(u1));
				userid=u1.userID;
			}
		}
		file.close();
		return userid;
}

void user::save(user u1)
{
		fstream file;
		file.open(userfile,ios::app|ios::binary);
		if(file)
		file.write((char*)&u1, sizeof(u1));
		else
			cout<<"Problem reading the product file";
		file.close();
}

void user::createAdmin()
{
		fstream file;
		user u1;
		u1.userID = u1.getLastUserID() + 1;
		strcpy(u1.userName,"admin");
		strcpy(u1.password,"admin");
		strcpy(u1.email,"admin@olx.in");
		strcpy(u1.role,"admin");
		file.open(userfile,ios::app|ios::out|ios::binary);
		if(file)
		file.write((char*)&u1, sizeof(u1));
		else
			cout<<"Problem reading the file";
		file.close();
}

void user::welcomeUser()
{
	int option;
	system("cls");
	if(strcmp(this->role , "user") == 0)
	{
		cout<<" Select one of the following options (1/2) : "<<endl;
		cout<<" 1. Sell : "<<endl;
		cout<<" 2. Buy : "<<endl;
		cin>>option;
		product p1;
		switch (option)
		{
		case 1:  p1.sell(this->userID);
			break;
		case 2: p1.buy();
			break;
		}
	}
	else if(strcmp(role , "admin") == 0)
	{
		cout<<" Select one of the following options (1-3) : "<<endl;
		cout<<" 1. Add Users : "<<endl;
		cout<<" 2. Manage Users : "<<endl;
		cout<<" 3. Add categories : "<<endl;
		cout<<" 4. Manage categories : "<<endl;
		cin>>option;
		user u;
		categories c;
		switch (option)
		{
		case 1: u.Register(u);
			break;
		case 2: u.manageUsers();
			break;
		case 3 : c.addCategories();
			break;
		case 4 : c.manageCategories();
			break;
		}
	}
	else
		cout<< "Invalid role";
}

void user:: manageUsers()
{
	int option;
	long userid;
	user u1;
	u1.showAllUsers();
	cout << "select the user to be edited";
	cin >> userid;
	u1 = u1.getUserById(userid);
    cout << "currect user details : ";
	u1.displayUser();
	cout << "Now enter the updated user details : "<< endl;
	cout<< "Enter User Name :  " << endl;
	cin>>u1.userName;
	cout<< "Enter Email Id :  " << endl;
	cin>>u1.email;
	cout<< "Choose Role = 1. Admin  2. User  " <<endl;
	cin>>option;
    switch(option)
	{
	case 1 : strcpy(u1.role,"admin");
		break;
	case 2 : strcpy(u1.role,"user");
		break;
	}
	u1.update();
}

void user:: update()
{
	//TODO : update file
}

void user:: displayUser()
{
	cout<< "User Name = " << this->userName;
	cout<< "User Email = " << this->email;
	cout<< "User Role = " << this->role;
}

char* user::getUserName()
{
	return this->userName;
}

char* user::getUserMail()
{
	return this->email;
}

user user:: getUserById(long id)

{
		fstream file;
		user u1;
		file.open(userfile, ios::in|ios::binary);
		while(file.read((char*)&u1, sizeof(u1)))
		{
			if(u1.userID == id)
			break;
		}
		file.close();
		return u1;
}

void user:: showAllUsers()
{
		fstream file;
		user u1;
		file.open(userfile, ios::in|ios::binary);
		while(!file.eof())
		{
			file.read((char*)&u1, sizeof(u1));
			cout << u1.userID << ". " << u1.userName << endl;
		}
		file.close();
}

void product::sell(long sellerid)
	{
		int catId;
		product p1;
		categories c1;
		system("cls");
		c1.displayCategories();
		cout<< "Choose any one category number for your product : ";
		cin>>p1.categoryId;
		system("cls");
		cout<< "Enter Product Name :  ";
		cin.getline(p1.prodName,50);
		cout<< "Enter Product Model Number :  ";
		cin.getline(p1.modelNo,50);
		cout<< "Enter Product Price :  ";
		cin>>p1.price;
		p1.sellerId = sellerid;
		p1.saveProduct(p1);
		system("cls");
		cout<<"Your product is posted for selling with the following details : "<<endl;
		p1.displayProduct();
	}

long categories::getLastCategoryId()
{
		fstream file;
		categories c;
		long catId=0;
		file.open(categoryfile, ios::in|ios::binary);
		if(file)
		{
			while(!file.eof())
			{
				file.read((char*)&c, sizeof(c));
				catId = c.categoryId;
			}
		}
		file.close();
		return catId;
}

categories categories::getCategory(int categoryId)
{
		fstream file;
		categories c1;
		file.open(categoryfile, ios::in|ios::binary);
		while(!file.eof())
		{
			file.read((char*)&c1, sizeof(c1));
			if(c1.categoryId == categoryId)
				break;
		}
		file.close();
		return c1;
}

char* categories::getCategoryName()
{
	return this->categoryName;
}

void categories::manageCategories()
{
	int option;
	long catid;
	categories c1;
	c1.displayCategories();
	cout << "select the category to be edited";
	cin >> catid;
	c1 = c1.getCategory(catid);
    cout << "currect category details : ";
	cout << c1.categoryId << " . "<<c1.categoryName<<endl;
	cout << "Now enter the updated category : "<< endl;
	cout<< "Enter category Name :  " << endl;
	cin>>c1.categoryName;
	c1.update();
}

void categories:: update()
{
}

void categories::save(categories c)
{
		fstream file;
		file.open(categoryfile,ios::app);
		if(file)
		file.write((char*)&c, sizeof(c));
		else
			cout<<"Problem reading the category file";
		file.close();
}

void categories::addCategories()
{
	char flag = 'y';
	categories c;
	system("cls");
	while(flag == 'y')
	{
		cout<< "Enter category name : "<<endl;
		cin >> c.categoryName;
		c.categoryId = c.getLastCategoryId() + 1;
		c.save(c);
		cout << c.categoryName << " category is saved." <<endl;
		cout << "want to enter more categries ? (y|n) ";
		cin >> flag;
	}
}

void categories::displayCategories()
	{
		fstream file;
		categories c1;
		file.open(categoryfile);
		while(file.read((char*)&c1, sizeof(c1)))
		{
			cout << c1.categoryId << ". " << c1.categoryName << endl;
		}
		file.close();
	}

	void product::displayProduct()
	{
		categories c;
		user u;
		c = c.getCategory(this->categoryId);
		u = u.getUserById(sellerId);
		cout << "Product Name : " << prodName<<endl;
		cout << "Product Model : " << modelNo << endl;
		cout << "Product Price : " << price << endl;
		cout << "Product category : " << c.getCategoryName() << endl;
		cout << "Seller Name : " << u.getUserName() << endl;
		cout << "Seller Email : " << u.getUserMail() << endl;
	}

	void product::displayProductByCat(long catId)
	{
		fstream file;
		product p1;
		int counter =0;
		file.open(productfile, ios::in|ios::binary);
		while(file.read((char*)&p1, sizeof(p1)))
		{
			if(p1.categoryId == catId)
			{
				p1.displayProduct();
				counter++;
			}
		}
		if(counter == 0)
			cout << "sorry no products found";
	}

	void product::saveProduct(product p1)
	{
		fstream file;
		file.open(productfile,ios::app);
		if(file)
		file.write((char*)&p1, sizeof(p1));
		else
			cout<<"Problem reading the product file";
		file.close();
	}

	void product::buy()
	{
		long catid;
		categories c;
		system("cls");
		c.displayCategories();
		cout << "choose one category for the product you want to buy";
		cin >> catid;
		this->displayProductByCat(catid);
	}

int main ()
{
	user u;
	//u.createAdmin();

	int option;
	cout<<" .... Welcome To OLX ......." <<endl;

	cout<<" Select one of the following options (1/2) : "<<endl;
	cout<<" 1. Login : "<<endl;
	cout<<" 2. Register : "<<endl;
	cin>>option;

	switch (option)
	{
	case 1: if (u.login(u))
				u.welcomeUser();
			else
				cout << "Invalid user";
		break;
	case 2: u.Register(u);
		u.welcomeUser();
		break;
	}
	return 0;
}

