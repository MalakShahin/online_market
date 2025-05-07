#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Product {
public:
	Product(int id, std::string name, double price, std::string category, int seller_id, int quantity)
		: id(id), name(name), price(price), category(category), seller_id(seller_id), quantity(quantity) {}

	int getId() const { return id; }
	std::string getName() const { return name; }
	double getPrice() const { return price; }
	std::string getCategory() const { return category; }
	int getSellerId() const { return seller_id; }
	int getQuantity() const { return quantity; }

	void setQuantity(int quantity) { this->quantity = quantity; }
	void setSellerId(int seller_id) { this->seller_id = seller_id; }

private:
	int id;
	std::string name;
	double price;
	std::string category;
	int seller_id;
	int quantity;
};

class Seller {
public:
	Seller(int id, std::string name, std::string email)
		: id(id), name(name), email(email) {}

	int getId() const { return id; }
	std::string getName() const { return name; }
	std::string getEmail() const { return email; }

private:
	int id;
	std::string name;
	std::string email;
};

class Customer {
public:
	Customer(int id, std::string name, std::string address, std::string phone, std::string email)
		: id(id), name(name), address(address), phone(phone), email(email) {}

	int getId() const { return id; }
	std::string getName() const { return name; }
	std::string getAddress() const { return address; }
	std::string getPhone() const { return phone; }
	std::string getEmail() const { return email; }

	void addProductToCart(Product product) {
		cart.push_back(product);
	}

	std::vector<Product> getCart() const { return cart; }

private:
	int id;
	std::string name;
	std::string address;
	std::string phone;
	std::string email;
	std::vector<Product> cart;
};


    class Receipt {
public:
    // Other member variables and functions...
	Receipt(int id, std::vector<Product> products, int customer_id, double total_price, double shipment_price)
		: id(id), products(products), customer_id(customer_id), total_price(total_price), shipment_price(shipment_price) {}

    // Function to create a new receipt for a customer's order
    static Receipt createReceipt(int id, const Customer& customer, double total_price) {
        std::vector<Product> products = customer.getCart();
        double shipment_price = 30.0;
        return Receipt(id, products, customer, total_price, shipment_price);
    }

private:

    // Constructor for the Receipt class
    Receipt(int id, std::vector<Product> products, const Customer& customer, double total_price, double shipment_price)
        : id(id), products(products), customer(customer), total_price(total_price), shipment_price(shipment_price) {}

        int getId() const { return id; }
	std::vector<Product> getProducts() const { return products; }
	int getCustomerId() const { return customer_id; }
	double getTotalPrice() const { return total_price; }
	double getShipmentPrice() const { return shipment_price; }

    int id;
	std::vector<Product> products;
	int customer_id;
	double total_price;
	double shipment_price;

};



// Function to display all products in a given category
void displayProductsByCategory(const std::vector<Product>& products, const std::string& category) {
	std::vector<Product> filtered_products;
	std::copy_if(products.begin(), products.end(), std::back_inserter(filtered_products),
		[&category](const Product& product) { return product.getCategory() == category; });

	for (const Product& product : filtered_products) {
		std::cout << "ID: " << product.getId() << ", Name: " << product.getName()
			<< ", Price: " << product.getPrice() << ", Category: " << product.getCategory()
			<< ", Seller ID: " << product.getSellerId() << ", Quantity: " << product.getQuantity() << std::endl;
	}
}

// Function to add a product to a given customer's cart
void addProductToCart(Customer& customer, const Product& product) {
	customer.addProductToCart(product);
}

// Function to calculate the total price of a customer's cart
double calculateCartTotal(const Customer& customer) {
	double total = 0.0;
	for (const Product& product : customer.getCart()) {
		total += product.getPrice() * product.getQuantity();
	}
	return total;
}

// Function to create a new receipt for a customer's order
Receipt createReceipt(int id, const Customer& customer, double total_price) {
	std::vector<Product> products = customer.getCart();
	double shipment_price = 30.0;
	return Receipt(id, products, customer.getId(), total_price, shipment_price);
}

int main() {
	// Create some sample products, sellers, and customers
	Product product1(1, "Laptop", 1000.0, "Electronics", 1, 10);
	Product product2(2, "Book", 50.0, "Books", 2, 50);
	Product product3(3, "Shirt", 20.0, "Clothing", 3, 100);

	Seller seller1(1, "John Doe", "john.doe@example.com");
	Seller seller2(2, "Jane Doe", "jane.doe@example.com");
	Seller seller3(3, "Bob Smith", "bob.smith@example.com");

	Customer customer1(1, "Alice Johnson", "123 Main St", "555-1234", "alice.johnson@example.com");

	// Add products to sellers
	product1.setSellerId(seller1.getId());
	product2.setSellerId(seller2.getId());
	product3.setSellerId(seller3.getId());

	// Create a vector to hold all products
	std::vector<Product> products = { product1, product2, product3 };

	// Display all products in the Electronics category
	std::cout << "Electronics category:" << std::endl;
	displayProductsByCategory(products, "Electronics");

	// Add a product to the customer's cart
	addProductToCart(customer1, product2);

	// Calculate the total price of the customer's cart
	double cart_total = calculateCartTotal(customer1);
	std::cout << "Cart total: $" << cart_total << std::endl;

	// Create a new receipt for the customer's order
	Receipt receipt(1, customer1, cart_total);

	// Display the receipt information
	std::cout << "Receipt:" << std::endl;
	std::cout << "ID: " << receipt.getId() << std::endl;
	for (const Product& product : receipt.getProducts()) {
		std::cout << "Product: " << product.getName() << ", Quantity: " << product.getQuantity() << std::endl;
	}
	std::cout << "Customer ID: " << receipt.getCustomerId()<< std::endl;
	std::cout << "Total price: $" << receipt.getTotalPrice() << std::endl;
	std::cout << "Shipment price: $" << receipt.getShipmentPrice() << std::endl;

	return 0;
}
