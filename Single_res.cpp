




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
private:
    Invoice &invoice;

public:
    InvoiceDao(Invoice &invoice) : invoice(invoice) {}

    void save_to_DB() {
        cout << "Saving to DB..." << endl;
    }
};

// Responsibility 3: Printing the Invoice only
class InvoicePrinter {
private:
    Invoice &invoice;

public:
    InvoicePrinter(Invoice &invoice) : invoice(invoice) {}

    void print() {
        cout << "Printing invoice..." << endl;
        cout << "Marker: " << invoice.get_marker().name << endl;
        cout << "Quantity: " << invoice.get_quantity() << endl;
        cout << "Total: " << invoice.get_total() << endl;
    }
};

int main() {
    
    Invoice invoice(Marker("name", "color", 10, 2025), 10);
    InvoiceDao invoiceDao(invoice);
    InvoicePrinter invoicePrinter(invoice);

    invoice.calculate_total();
    invoiceDao.save_to_DB();
    invoicePrinter.print();

    return 0;
}
