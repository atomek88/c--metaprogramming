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

using paremeterized_model_train_factory
  =  parameterized_factory<train_factory, model>;

using parameterized_real_train_factory
  = parameterized_factory<train_factory, real>;

typedef
abstract_factory < locomotive*(Engine), freight_car*(long), caboose >
  flexible_train_factory;
typedef
  concrete_factory
    <flexible_train_factory, real_locomotive, real_freight_car, real_caboose> 
  flexible_real_train_factory;
typedef
  no_t2t_abstract_factory<locomotive, freight_car, caboose>
  no_t2t_train_factory;
typedef
  no_t2t_concrete_factory
    <no_t2t_train_factory, real_locomotive, real_freight_car, real_caboose> 
  no_t2t_real_train_factory;

using mpl_train_factory = mpl_abstract_factory<locomotive, freight_car, caboose>;
using mpl_model_train_factory = mpl_concrete_factory<mpl_train_factory, model_locomotive, model_freight_car, model_caboose>;
int main()
{
  unique_ptr<train_factory> factory(make_unique<model_train_factory>());
  auto l(factory->create<locomotive>());
  l->blow_horn();
  factory = make_unique<parameterized_real_train_factory>();
  l = factory->create<locomotive>();
  l->blow_horn();
  unique_ptr<flexible_train_factory> 
    flexible_factory(make_unique<flexible_real_train_factory>());
  l = flexible_factory->create<locomotive>(Engine(800.0));

  l->blow_horn();
  flexible_factory->create<caboose>()->wave();

  factory = make_unique<parameterized_real_train_factory>();
  l = factory->create<locomotive>();
  l->blow_horn();

  unique_ptr<no_t2t_train_factory> no_t2t_factory = make_unique<no_t2t_real_train_factory>();
  l = factory->create<locomotive>();
  l->blow_horn();

  unique_ptr<mpl_train_factory> mpl_factory = make_unique<mpl_model_train_factory>();
  l = mpl_factory->create<locomotive>();
  l->blow_horn();

  return 0;
}
