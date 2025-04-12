#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {

private:

    string category;
    string name;
    double price;
    int quantity;


public:

    // سازنده
    Product(string cat, string n, double p, int q) 
        : category(cat), name(n), price(p), quantity(q) {}


    // متدهای getter
    string getCategory() const 
    {
         return category; 
    }

    string getName() const 
    {
         return name; 
    }

    double getPrice() const 
    {
         return price; 
    }

    int getQuantity() const 
    {
         return quantity; 
    }


    // متدهای setter
    void setQuantity(int q) 
    {
         quantity = q; 
    }

    void setPrice(double p) 
    {
         price = p; 
    }


    // نمایش اطلاعات محصول
    void display() const 
    {
        cout << "category: " << category << endl;
        cout << "name: " << name << endl;
        cout << "price: " << price << endl;
        cout << "quantity: " << quantity << endl;
    }
};

class Wallet {

private:

    double balance;


public:

    Wallet(double initial = 0) : balance(initial) {}


    double getBalance() const 
    {
         return balance; 
    }


    void charge(double amount) 
    {
        balance += amount;
        cout << "sharg anjam shod . mojodi feli: " << balance << endl;
    }


    bool spend(double amount) 
    {

        if (balance >= amount) 
        {
            balance -= amount;
            return true;
        }

        cout << "mojodi kafi nist" << endl;
        return false;

    }


    void display() const 
    {
        cout << "mojodi kife pol: " << balance << endl;
    }

};



class ShoppingCart {

private:

    vector<Product> items;
    double totalPrice;


public:

    ShoppingCart() : totalPrice(0) {}


    void addItem(const Product& product) 
    {

        items.push_back(product);
        totalPrice += product.getPrice();
        cout << "kala be sabad kharid azafe shod" << endl;

    }


    void display() const 
    {

        if (items.empty()) 
        {
            cout << "sabad kharid khali ast" << endl;
            return;
        }

        cout << "--- sabad kharid ---" << endl;

        for (int i = 0; i < items.size(); i++) 
        {
            items[i].display();
            cout << "---------------" << endl;
        }

        cout << "majmoe gheimat: " << totalPrice << endl;

    }


    void clear() 
    {

        items.clear();
        totalPrice = 0;

    }

};


class Store {

    private:
    
        vector<Product> products;
        Wallet adminWallet;
        const string adminPassword = "admin1admin";
    
    
    public:
    
        // مدیریت محصولات
        void addProduct() 
        {
    
            string cat, name;
            double price;
            int quantity;
    
    
            cout << "daste bandi(bazi/manitor/control/hesaet): ";
            cin >> cat;
            cout << "name kala: ";
            cin >> name;
            cout << "gheimat kala: ";
            cin >> price;
            cout << "mojodi kala:";
            cin >> quantity;
    
    
            products.emplace_back(cat, name, price, quantity);
            cout << "kala ba movafaghiat azafe shod" << endl;
    
        }
    
    
        void removeProduct() 
        {
    
            if (products.empty()) 
            {
                cout << "hich kalai barae hazf vojod nadarad" << endl;
                return;
            }
    
    
            string name;
            cout << "name kalae mored nazar barae hazf: ";
            cin >> name;
    
    
            for (size_t i = 0; i < products.size(); i++) 
            {
    
                if (products[i].getName() == name) 
                {
                    products.erase(products.begin() + i);
                    cout << "kala ba movafaghiat hazf shod" << endl;
                    return;
                }
    
            }
    
            cout << "kala yaft nashod" << endl;
    
        }
    
    
        void searchProduct() const 
        {
    
            string name;
            cout << "name kala barae jostojo: ";
            cin >> name;
    
    
            for (int i = 0; i < products.size(); i++)
            {
    
                if (products[i].getName() == name) 
                {
                    cout << "kala yaft shod:\n";
                    products[i].display();
                    return;
                }
            }
    
            cout << "kala yaft nashod" << endl;
    
        }
    
    
        void displayProducts() const 
        {
    
            if (products.empty()) 
            {
                cout << "hich kalai mojod nist" << endl;
                return;
            }
    
    
            cout << "--- list kalaha ---" << endl;
    
            for (const auto& product : products) 
            {
    
                product.display();
                cout << "-------------------" << endl;
    
            }
    
        }
    
    
        void calculateTotalValue() const 
        {
    
            double total = 0;
    
            for (size_t i = 0; i < products.size(); ++i) 
            {
    
                total += products[i].getPrice() * products[i].getQuantity();
    
            }
    
            cout << " arzesh kole mojodi: " << total << endl;
    
        }
    
    
        // مدیریت کیف پول
        void chargeAdminWallet() 
        {
    
            double amount;
            cout << "meghdare sharg: ";
            cin >> amount;
            adminWallet.charge(amount);
    
        }
    
    
        void displayAdminWallet() const 
        {
    
            adminWallet.display();
    
        }
    
    
        // خرید محصول
        bool buyProduct(string name, Wallet& customerWallet, ShoppingCart& cart) 
        {
    
            for (int i = 0; i < products.size(); i++) 
            {
    
                if (products[i].getName() == name && products[i].getQuantity() > 0) 
                {
    
                    if (customerWallet.spend(products[i].getPrice())) 
                    {
    
                        products[i].setQuantity(products[i].getQuantity() - 1);
                        cart.addItem(products[i]);
                        adminWallet.charge(products[i].getPrice());
                        return true;
    
                    }
    
                    return false;
    
                }
            }
            
            cout << "kala yaft nashod ya mojodi nadarad" << endl;
            return false;
        }
    
    
        // احراز هویت مدیر
        bool authenticateAdmin(const string& password) const 
        {
    
            return password == adminPassword;
    
        }
    
    };
    
class CustomerInterface {

    private:
    
        Store& store;
        Wallet customerWallet;
        ShoppingCart cart;
    
    
    public:
    
        CustomerInterface(Store& s) : store(s), customerWallet(1000) {}
    
        void run() 
        {
    
            int choice;
    
            while (true) 
            {
    
                cout << "\n--- menoe moshtari ---" << endl;
                cout << "1. moshahede kalaha " << endl;
                cout << "2. jostojoe kala " << endl;
                cout << "3. sharg kif pol" << endl;
                cout << "4. moshahede mojodi kif pol" << endl;
                cout << "5. afzodan be sabad kharid" << endl;
                cout << "6. moshahede sabad kharid " << endl;
                cout << "0. bazgasht be menoe asli" << endl;
                cout << " entekhab konid: ";
                cin >> choice;
    
    
                switch (choice) 
                {
    
                    case 1:
                        store.displayProducts();
                        break;
    
                    case 2:
                        store.searchProduct();
                        break;
    
                    case 3: 
                    {
                        double amount;
                        cout << " meghdare sharg: ";
                        cin >> amount;
                        customerWallet.charge(amount);
                        break;
                    }
    
                    case 4:
                        customerWallet.display();
                        break;
    
                    case 5: 
                    {
                        string name;
                        cout << " name kalae mored nazar: ";
                        cin >> name;
                        store.buyProduct(name, customerWallet, cart);
                        break;
                    }
    
                    case 6:
                        cart.display();
    
                        break;
    
                    case 0:
                        return;
    
                    default:
                        cout << " gozine na motabar" << endl;
    
                }
            }
        }
    };
    
    
    class AdminInterface {
    
    private:
    
        Store& store;
    
    
    public:
    
        AdminInterface(Store& s) : store(s) {}
    
    
        void run() 
        {
    
            string password;
            cout << " ramze obor: ";
            cin >> password;
    
    
            if (!store.authenticateAdmin(password)) 
            {
    
                cout << " ramz eshtebah ast" << endl;
                return;
    
            }
    
    
            int choice;
    
            while (true) 
            {
    
                cout << "\n--- menoe modiriat ---" << endl;
                cout << "1. afzodan kala" << endl;
                cout << "2. hazfe kala" << endl;
                cout << "3. jostojoe kala" << endl;
                cout << "4. namayesh kalaha" << endl;
                cout << "5. mohasebe arzesh kole mojodi" << endl;
                cout << "6. sharg kife pol modoriat" << endl;
                cout << "7. moshahede mojodi kife pol modiriat" << endl;
                cout << "0. bazgasht be menoe asli" << endl;
                cout << " entekhab konid: ";
    
                cin >> choice;
    
    
                switch (choice) 
                {
    
                    case 1:
                        store.addProduct();
                        break;
    
                    case 2:
                        store.removeProduct();
                        break;
    
                    case 3:
                        store.searchProduct();
                        break;
    
                    case 4:

                    store.displayProducts();
                    break;

                case 5:
                    store.calculateTotalValue();
                    break;

                case 6:
                    store.chargeAdminWallet();
                    break;

                case 7:
                    store.displayAdminWallet();
                    break;

                case 0:
                    return;

                default:
                    cout << " gozine na motabar!" << endl;

            }
        }
    }
};


int main() {


    Store store;
    

    while (true) 
    {
        cout << "\n--- foroshgah bazi ---" << endl;
        cout << "1. vorod be bakhsh modiriat" << endl;
        cout << "2. vorod be bakhsh moshtarian" << endl;
        cout << "0. khorog" << endl;
        cout << " entekhab konid: ";
        

        int choice;
        cin >> choice;


        switch (choice) 
        {

            case 1: 
            {
                AdminInterface admin(store);
                admin.run();
                break;
            }

            case 2: 
            {
                CustomerInterface customer(store);
                customer.run();
                break;
            }

            case 0:
                return 0;

            default:
                cout << " gozine na motabar!" << endl;

        }
    }
}
    