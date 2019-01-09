#include "factory.h"
#include "trains.h"
#include <string>
#include <iostream>
#include <memory>
using namespace std;
using namespace cspp51045;

// using statements replace typedefs (and more)
using train_factory = abstract_factory<locomotive, freight_car, caboose>;
using model_train_factory
  = concrete_factory<train_factory, 
	                 model_locomotive, model_freight_car, model_caboose>;

// Compare how the using statement for model_train_factory is clearer
// than the equivalent typedef for real_train_factory
typedef
  concrete_factory
    <train_factory, real_locomotive, real_freight_car, real_caboose> 
  real_train_factory;

int main()
{
  unique_ptr<train_factory> factory(make_unique<model_train_factory>());
  auto l(factory->create<locomotive>());
  l->blow_horn();
 
  return 0;
}
