#ifndef FACTORY_H
#define FACTORY_H
#include<tuple>
#include<memory>
using std::tuple;
using std::unique_ptr;

namespace cspp51045 {
template<typename T>
struct Type2Type {
  typedef T type;
};

template<typename T>
struct abstract_creator {
    virtual unique_ptr<T> doCreate(Type2Type<T>) = 0;
};

template<typename... T> struct abstract_factory_helper;

template<>
struct abstract_factory_helper<> {
};

template<typename Head, typename... Tail>
struct abstract_factory_helper<Head, Tail...>
  : public abstract_creator<Head>, abstract_factory_helper<Tail...> {
};

template<typename... T>
struct abstract_factory 
  : public abstract_factory_helper<T...> {
    template<class U> unique_ptr<U> create() {
        // Since template methods can't be virtual, use the template
        // argument to uniquely identify a virtual non-template method
        // We will need to cast up because the different doCreate<>
        // methods hide each other ("method hiding")
        abstract_creator<U> &creator = *this;
        return creator.doCreate(Type2Type<U>());
    }
};

template
  <typename AbstractFactory,
   typename UnimplementedAbstractTypes, 
   typename... UnimplementedConcreteTypes>
struct concrete_factory_helper;

template<typename AbstractFactory>
struct concrete_factory_helper<AbstractFactory, tuple<>>
  : public AbstractFactory {
};

template
  <typename AbstractFactory, 
   typename AbstractType, typename ... RemainingAbstractTypes,
   typename ConcreteType, typename... RemainingConcreteTypes>
struct concrete_factory_helper
  <AbstractFactory, 
   tuple<AbstractType, RemainingAbstractTypes...>,
   ConcreteType, RemainingConcreteTypes...>
  : public concrete_factory_helper
             <AbstractFactory,
              tuple<RemainingAbstractTypes...>,
	      RemainingConcreteTypes...> {
  unique_ptr<AbstractType> doCreate(Type2Type<AbstractType>) override {
    return make_unique<ConcreteType>();
  }
};

template<typename AbstractFactory, typename... ConcreteTypes>
struct concrete_factory;

template<typename... AbstractTypes, typename... ConcreteTypes>
struct concrete_factory
  <abstract_factory<AbstractTypes...>, ConcreteTypes...> 
  : public concrete_factory_helper
             <abstract_factory<AbstractTypes...>,
              tuple<AbstractTypes...>,
              ConcreteTypes...> {
};

}
#endif
