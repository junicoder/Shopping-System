#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib> 

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

map<string, map<string, double>> items;
map<pair<int, int>, string> names;

void fillItems() {
    items["Mobile"]["Samsung"] = 15000;
    items["Mobile"]["Redmi"] = 12000;
    items["Mobile"]["Apple"] = 100000;
    items["Laptop"]["HP"] = 40000;
    items["Laptop"]["Lenovo"] = 35000;
    items["Laptop"]["Macbook"] = 250000;
    items["Course"]["C"] = 1000;
    items["Course"]["C++"] = 3000;
    items["Course"]["Java"] = 4000;
    items["Course"]["Python"] = 3500;

    names[{1, 1}] = "Apple";
    names[{1, 2}] = "Redmi";
    names[{1, 3}] = "Samsung";

    names[{2, 1}] = "HP";
    names[{2, 2}] = "Lenovo";
    names[{2, 3}] = "Macbook";

    names[{3, 1}] = "C";
    names[{3, 2}] = "C++";
    names[{3, 3}] = "Java";
    names[{3, 4}] = "Python";
}

class customer {
    string name;
    string username;
    string password;
    map<string, map<string, int>> selected_items;
    string review;

public:
    customer() {
        cout << "Enter your name: ";
        getline(cin, name);
        username = "user";
        password = "pass";
    }

    bool signIn() {
        string entered_username, entered_password;
        cout << "Enter your username: ";
        cin >> entered_username;
        cout << "Enter your password: ";
        cin >> entered_password;
        if (entered_username == username && entered_password == password) {
            return true;
        } else {
            cout << "Incorrect username or password. Please try again." << endl;
            return false;
        }
    }

    void addToCart(string a, string b) {
        selected_items[a][b]++;
    }

    void removeFromCart(string a, string b) {
        if (selected_items.find(a) != selected_items.end() &&
            selected_items[a].find(b) != selected_items[a].end() &&
            selected_items[a][b] > 0) {
            selected_items[a][b]--;
            cout << "Item removed from cart: " << b << " from category " << a << endl;
        } else {
            cout << "Item not found in cart: " << b << " from category " << a << endl;
        }
    }

    void writeReview() {
        cout << "Please write your review: ";
        cin.ignore();
        getline(cin, review);
    }

    void showCart() {
        cout << "Your Cart:\n";
        cout << "Category #\tItem #\t \tItem\tQuantity\n";
        int catNum = 1;
        for (auto& category : selected_items) {
            int itemNum = 1;
            for (auto& item : category.second) {
                string model = item.first;
                int quantity = item.second;
                cout << getCategoryNumber(category.first) <<"\t \t "<< getItemNumber(category.first, model) << "\t"  << "\t" << model << "\t"
                     << quantity << endl;
                itemNum++;
            }
            catNum++;
        }
    }

    int getCategoryNumber(const string& category) {
        if (category == "Mobile") {
            return 1;
        } else if (category == "Laptop") {
            return 2;
        } else if (category == "Course") {
            return 3;
        }
        return -1; // Invalid category
    }

    int getItemNumber(const string& category, const string& item) {
        if (category == "Mobile") {
            return getMobileItemNumber(item);
        } else if (category == "Laptop") {
            return getLaptopItemNumber(item);
        } else if (category == "Course") {
            return getCourseItemNumber(item);
        }
        return -1; // Invalid category
    }

    int getMobileItemNumber(const string& item) {
    if (item == "Samsung") {
        return 3;
    } else if (item == "Redmi") {
        return 2;
    } else if (item == "Apple") {
        return 1;
    }
    return -1; // Invalid item
}


    int getLaptopItemNumber(const string& item) {
        if (item == "HP") {
            return 1;
        } else if (item == "Lenovo") {
            return 2;
        } else if (item == "Macbook") {
            return 3;
        }
        return -1; // Invalid item
    }

    int getCourseItemNumber(const string& item) {
        if (item == "C") {
            return 1;
        } else if (item == "C++") {
            return 2;
        } else if (item == "Java") {
            return 3;
        } else if (item == "Python") {
            return 4;
        }
        return -1; // Invalid item
    }

    void printBill() {
        int total_amount = 0;
        cout << "Category\t"
             << "Item\t"
             << "Quantity\t"
             << "Cost\n";

        for (auto& category : selected_items) {
            for (auto& item : category.second) {
                string model = item.first;
                int quantity = item.second;
                int temp = quantity * items[category.first][model];
                cout << category.first << "\t\t" << model << "\t"
                     << quantity << "\t\t" << temp << endl;
                total_amount += temp;
            }
        }

        cout << "-------------------------------"
             << "-------------\n";
        cout << "Total amount: \t\t\t" << total_amount << endl;
        cout << "-------------------------------"
             << "-------------\n";
        cout << "Review: " << review << endl;
        cout << "*****THANK YOU FOR SHOPPING*****\n";
        cout << "*********SHOPPING system*********\n\n";
    }
};

class shop {
public:
    shop() {}

    virtual void show() {}

    virtual void select(customer &obj) {}

    void showMenu() {
        cout<<"\n \n    ============================\n";
    cout<<"    |     SHOPPING SYSTEM      |\n";
    cout<<"    ============================\n";
        cout<<"\n         ================\n";
        cout <<"         |     MENU     |\n";
        cout <<"         ================\n";
        cout << "---------------------------------\n";
        cout << "| 1. Mobile                     |\n";
        cout << "| 2. Laptop                     |\n";
        cout << "| 3. Programming Courses        |\n";
        cout << "| 4. Checkout                   |\n";
        cout << "| 5. Add Item to Cart           |\n";
        cout << "| 6. Remove Item from Cart      |\n";
        cout << "---------------------------------\n";
    }
};

class mobile : public shop {
public:
    void show() {
        cout << "- - - - - - - - - - -"
                " - -\nItem, Cost\n";
        int cnt = 1;
        for (auto &it : items["Mobile"]) {
            cout << cnt++ << ". " << it.first << ", Rs."
                 << it.second << "/-\n";
        }

        cout << "- - - - - - - - - - - - -\n\n";
    }

    void select(customer &obj) {
        cout << "These are the smartphone categories we have....\n";
        int num;
        cout << "Enter your selection\n";
        cin >> num;
        if (num < 1 || num > 3) {
            cout << "Wrong Input\n";
            return;
        }
        cout << "\n\nPURCHASE SUCCESSFULL!! ";
        cout << names[{1, num}]
             << " IS ADDED TO THE CART\n\n";
        obj.addToCart("Mobile", names[{1, num}]);
    }
};

class laptop : public shop {
public:
    void show() {
        cout << "- - - - - - - - - - -"
                " - -\nItem, Cost\n";
        int cnt = 1;
        for (auto &it : items["Laptop"]) {
            cout << cnt++ << ". " << it.first << ", Rs."
                 << it.second << "/-\n";
        }
        cout << "- - - - - - - - - - - - -\n";
    }
    void select(customer &obj) {
        cout << "These are the laptop categories we have....\n";
        int num;
        cout << "Enter your selection\n";
        cin >> num;
        if (num < 1 || num > 3) {
            cout << "Wrong Input\n";
            return;
        }
        cout << "\n\nPURCHASE SUCCESSFULL!! ";
        cout << names[{2, num}]
             << " IS ADDED TO THE CART\n\n";
        obj.addToCart("Laptop", names[{2, num}]);
    }
};

class courses : public shop {
public:
    void show() {
        cout << "- - - - - - - - - - "
                " - -\nItem, Cost\n";
        int cnt = 1;
        for (auto &it : items["Course"]) {
            cout << cnt++ << ". " << it.first << ", Rs."
                 << it.second << "/-\n";
        }
        cout << "- - - - - - - - - - - - -\n";
    }
    void select(customer &obj) {
        cout << "These are the courses categories we have....\n";
        int num;
        cout << "Enter your selection\n";
        cin >> num;
        if (num < 1 || num > 4) {
            cout << "Wrong Input\n";
            return;
        }
        cout << "\n\nPURCHASE SUCCESSFULL!! ";
        cout << names[{3, num}]
             << " IS ADDED TO THE CART\n\n";
        obj.addToCart("Course", names[{3, num}]);
    }
};

int main() {
    fillItems();
    cout<<"\n \n \n         ============================\n";
    cout<<"         |     SHOPPING SYSTEM      |\n";
    cout<<"         ============================\n";
    cout<<"  ==============================================\n";
    cout<<"  |  WELCOME TO ONLINE SHOPPING WE DEAL IN.    |\n";
    cout<<"  |        ELECTRONIC GADGETS AND COURSES.     |\n";
    cout<<"  |  Presented by:                             |\n";           
    cout<<"  |        Muhammad Junaid F2023266884         |\n";        
    cout<<"  |           Ahmad Shabir F2023266888         |\n";
    cout<<"  |            Arqum Ghani F2023266507         |\n";
    cout<<"  ==============================================\n \n \n";
    
    
    customer c;
    bool loggedIn = false;

    while (!loggedIn) {
        loggedIn = c.signIn();
    }

    shop *s;

    while (true) {
        s = new shop();
        s->showMenu();
        int val;
        cout << "Please select an option to proceed "<<endl;
        cout << "further. If you choose to checkout, "<<endl;
        cout << "shopping will end and bill will be "<<endl;
        cout << "generated for the items bought so far...\n";
        cin >> val;

        if (val == 1) {
            s = new mobile();
            s->show();
            c.showCart();
            s->select(c);
        } else if (val == 2) {
            s = new laptop();
            s->show();
            c.showCart();
            s->select(c);
        } else if (val == 3) {
            s = new courses();
            s->show();
            c.showCart();
            s->select(c);
        } else if (val == 4) {
            c.writeReview();
            c.printBill();
            break;
        } else if (val == 5) {
            c.showCart();
            cout << "Enter category number to add to cart: ";
            int catNum;
            cin >> catNum;
            cout << "Enter item number to add to cart: ";
            int itemNum;
            cin >> itemNum;
            string category, item;
            if (catNum == 1) {
                category = "Mobile";
            } else if (catNum == 2) {
                category = "Laptop";
            } else if (catNum == 3) {
                category = "Course";
            } else {
                cout << "Invalid category number\n";
                continue;
            }
            if (itemNum < 1 || itemNum > 3) {
                cout << "Invalid item number\n";
                continue;
            }
            if (category == "Mobile") {
                item = names[{1, itemNum}];
            } else if (category == "Laptop") {
                item = names[{2, itemNum}];
            } else if (category == "Course") {
                item = names[{3, itemNum}];
            }
            c.addToCart(category, item);
            c.showCart(); // Show updated cart after adding
        } else if (val == 6) {
            c.showCart();
            cout << "Enter category number to remove from cart: ";
            int catNum;
            cin >> catNum;
            cout << "Enter item number to remove from cart: ";
            int itemNum;
            cin >> itemNum;
            string category, item;
            if (catNum == 1) {
                category = "Mobile";
            } else if (catNum == 2) {
                category = "Laptop";
            } else if (catNum == 3) {
                category = "Course";
            } else {
                cout << "Invalid category number\n";
                continue;
            }
            if (category == "Mobile") {
                item = names[{1, itemNum}];
            } else if (category == "Laptop") {
                item = names[{2, itemNum}];
            } else if (category == "Course") {
                item = names[{3, itemNum}];
            }
            c.removeFromCart(category, item);
            c.showCart(); // Show updated cart after removing
        } else {
            cout << "Wrong Input. Please select a valid option.\n\n";
        }
        cout << "REDIRECTING TO THE MAIN MENU.....\n\n";
        sleep_until(system_clock::now() + seconds(3));
        system("clear"); // Use "clear" command to clear screen on Unix-based systems
        delete s; // Free memory
    }

    return 0;
}
