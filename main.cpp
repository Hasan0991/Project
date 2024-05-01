//Suppose we are to add a shipping option to our application.
// Create a class Product.
// The Product has a int weight in kgs, double volume in [Math Processing Error] and a boolean fragile fields.
// Create an abstract base class Shipping with a possible method which accepts a Product,
// a cost and time methods -- each of which has to be a pure virtual method
// Create at least three shipping options, each of which rejects different products based on their features.
// For instance, Plane can only carry small items which weigh small amount, offer high cost based on the total weight,
// but the time is short. As an another example,
// Ship ignores weight, its shipping cost is calculated based on volume alone, but may not carry fragile products.
// And a Truck may not carry items larger than 1000kg, a volume greater than 20 [Math Processing Error],
// and the cost is calculated based on a mixture of weight and volume.
// Add a options function which take a vector of Shipping * and a Product,
// and will print out various shipping options: for each Shipping which accepts the Product (for which the possible returns true),
// print out the cost and time of the shipping.
#include <iostream>
#include <vector>
#include<cassert>

using namespace std;

class Shipping; // Forward declaration

class Products {
    int kg;
    double volume;
    bool fragile;

public:
    Products(int _kg, double _volume, bool _fragile)
            : kg(_kg), volume(_volume), fragile(_fragile) {}

    int get_kg() const { return kg; }
    double get_volume() const { return volume; }
    bool is_fragile() const { return fragile; }
};

class Shipping {
    string name;

public:
    explicit Shipping(string _name) : name(_name) {}
    std::string  get_name(){
        return name;
    }


    virtual int cost(const Products& product) const = 0;
    virtual int time(const Products& product) const = 0;
    virtual bool possible(const Products& product) const = 0;
    virtual ~Shipping(){}

};


class Plane : public Shipping {
public:
    Plane() : Shipping("Plane") {}

    bool possible(const Products& p) const override {
        return (p.get_kg() < 10 && p.get_volume() <= 0.5 && !p.is_fragile());
    }

    int cost(const Products& product) const override {
        return product.get_kg() * 10;
    }

    int time(const Products& product) const override {
        return 2;
    }
};


class Ship : public Shipping {
public:
    Ship() : Shipping("Ship") {}
    bool possible(const Products& product) const override {
        return (product.get_volume() <= 10 && !product.is_fragile());
    }

    int cost(const Products& product) const override {
        return static_cast<int>(product.get_volume() * 20);
    }

    int time(const Products& product) const override {
        return 7;
    }
};

class Truck : public Shipping {
public:
    Truck() : Shipping("Truck") {}
    bool possible(const Products& product) const override {
        return (product.get_kg() <= 1000 && product.get_volume() <= 20);
    }

    int cost(const Products& product) const override {
        return product.get_kg() * 5 + static_cast<int>(product.get_volume()) * 10;
    }

    int time(const Products& product) const override {
        return 3;
    }
};

class Possibility {
    Products* products;
    vector<Shipping*> shipping_options;

public:
    Possibility(Products* _products, const vector<Shipping*>& _shipping_options)
            : products(_products), shipping_options(_shipping_options) {}

    void accept() {
        bool accepted = false;
        for (Shipping* shipping : shipping_options) {
            if (shipping->possible(*products)) {
                cout << "Shipping by " << shipping->get_name() << ":\n";
                cout << "Cost: $" << shipping->cost(*products) << ", Time : " << shipping->time(*products) << " days\n";
            }
            else{
                cout<<"Shipping by "<<shipping->get_name() <<" is not accepted "<<"\n";
            }
        }
    }

};
void clean_method(vector<Shipping*>& shipping) {
    for (Shipping* s : shipping) {
        delete s;
    }
    shipping.clear();
}
void test_products() {
    Products product1(5, 0.4, false);


    // Test Products getters
    assert(product1.get_kg() == 5);
    assert(product1.get_volume() == 0.4);
    assert(!product1.is_fragile());

}
void test_shipping(){
    Plane plane;
    Products product1(5, 0.4, false);
    assert(!plane.possible(product1));
}
int main() {

    vector<Products*> products;
    products.push_back(new Products(5, 0, false));
    products.push_back(new Products(600, 12.0, true));
    products.push_back(new Products(1200, 25.0, false));


    vector<Shipping*> shippingOptions;
    shippingOptions.push_back(new Plane());
    shippingOptions.push_back(new Ship());
    shippingOptions.push_back(new Truck());

    for (Products* product : products) {
        Possibility p(product, shippingOptions);
        cout<<"for product with parametrs "<< product->get_kg()<<"kg"<<endl;
        p.accept();
    }

    // Clean up dynamically allocated memory
    for (Products* product : products) {
        delete product;
    }
    clean_method(shippingOptions);


}
