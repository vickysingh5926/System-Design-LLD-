




#include <iostream>
#include <string>
using namespace std;

class Marker {
public:
    string name;
    string color;
    int price;
    int year;

    Marker(string name, string color, int price, int year) {
        this->name = name;
        this->color = color;
        this->price = price;
        this->year = year;
    }
};

// Responsibility 1: Calculate the total (business logic)
class Invoice {
    Marker marker;
    int quantity;
    int total;

public:
    Invoice(Marker marker, int quantity) : marker(marker), quantity(quantity), total(0) {}

    void calculate_total() {
        cout << "Calculating total..." << endl;
        total = marker.price * quantity;
    }

    int get_total() const {
        return total;
    }

    Marker get_marker() const {
        return marker;
    }

    int get_quantity() const {
        return quantity;
    }
};

// Responsibility 2: Managing Database Operations only

class InvoiceDao {
public:
    virtual void save() = 0;   // pure virtual function
    virtual ~InvoiceDao() {}   // virtual destructor for safety
};

// ---------- Concrete implementation: DatabaseInvoiceDao ----------
class DatabaseInvoiceDao : public InvoiceDao {
    Invoice& invoice;

public:
    DatabaseInvoiceDao(Invoice& invoice) : invoice(invoice) {}

    void save() override {
        cout << "Saving to DB..." << endl;
        // Example: could use invoice.getTotal() here if needed
    }
};

// ---------- Concrete implementation: FileInvoiceDao ----------
class FileInvoiceDao : public InvoiceDao {
    Invoice& invoice;

public:
    FileInvoiceDao(Invoice& invoice) : invoice(invoice) {}

    void save() override {
        cout << "Saving to file..." << endl;
    }
};




int main() {
    
    Invoice invoice(Marker("name","color",10,2025),10);
    invoice.calculate_total();

    InvoiceDao* DatabaseInvoiceDao=new DatabaseInvoiceDao(invoice);
    DatabaseInvoiceDao->save();

    InvoiceDao* FileInvoiceDao=new FileInvoiceDao(invoice);
    FileInvoiceDao->save();

    delete DatabaseInvoiceDao;
    delete FileInvoiceDao;

    return 0;
}
