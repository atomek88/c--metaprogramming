#ifndef TRAIN_H
#  define TRAIN_H

#include <iostream>
#include <string>
using std::cout;
using std::endl;


namespace cspp51045 {
	struct Engine {
		Engine(double horsepower = 0) : horsepower(horsepower) {}
		Engine(Engine const &e) : horsepower(e.horsepower) {
			cout << "Copying engine" << endl;
		}
		double horsepower;
	};
	
struct locomotive {
  locomotive(Engine engine = Engine()) : engine(engine) {}
  virtual void blow_horn() = 0;
protected:
  Engine engine;
};

struct freight_car {
  freight_car(long capacity = 0) : cap(capacity) {}
  virtual void load_coal() = 0;
protected:
  long cap;
};

struct caboose {
  virtual void wave() = 0;
};

// The optional override keyword is new to C++11 and tells
// the compiler to warn you if this method does not override
// a base class method (in which case you probably got a signature wrong)
struct model_locomotive : public locomotive {
  using locomotive::locomotive;
  void blow_horn() override { 
    cout << "honk" << std::string(static_cast<int>(engine.horsepower/100), '.') << endl; 
  }
};

struct model_freight_car : public freight_car {
  model_freight_car(long cap = 0) : freight_car(cap) {}
  virtual void load_coal() override {
    cout << "Filling with coal dust. Pretending it's coal" << endl;
  }
};

struct model_caboose : public caboose {
  virtual void wave() override {
    cout << "Model conductor has hand in waving position" << endl;
  }
};

struct real_locomotive : public locomotive {
  using locomotive::locomotive;
  void blow_horn() override {
    cout << "HOOOOONNNNNNKKKKK" 
         << std::string(static_cast<int>(engine.horsepower/100), '!') << endl;
  }
};

struct real_freight_car : public freight_car {
  real_freight_car(long cap = 0) : freight_car(cap) {}
  void load_coal() override {
    cout << "Powering our nation (and heating our planet)" << endl;
  }
};

struct real_caboose : public caboose {
  virtual void wave() override {
    cout << "Bye, kids" << endl;
  }
};


}

#endif
