#ifndef FACTORY_H
#define FACTORY_H
#include<tuple>
#include<utility>
#include<memory>
#include<type_traits>
#pragma warning(disable:4250)

using std::tuple;
using std::unique_ptr;
using std::add_const_t;

namespace cspp51045 {
	template<typename T>
	struct Type2Type {
		typedef T type;
	};

	template<typename T> struct adapt_signature {
		using type = add_const_t<T> &;
	};

	template<typename T> 
	struct adapt_signature<T &> {
		using type = T;
	};

	template<typename T>
	struct adapt_signature<T &&> {
		using type = T;
	};

	template<typename T>
    struct abstract_creator {
      virtual unique_ptr<T> doCreate(Type2Type<T> &&) = 0;
    };

	template<typename Result, typename ...Args>
	struct abstract_creator<Result*(Args...)>
	{
      virtual unique_ptr <Result> 
		  doCreate(Type2Type<Result>&&, 
			       typename adapt_signature<Args>::type...) = 0;
	};

	template<typename Result, typename ...Ts> struct Signature;
	template<typename Result, typename ...Ts> struct Signature<Result, Result, Ts...> {
		using type = Result;
	};
	template<typename Result, typename ...Args, typename ...Ts> 
	struct Signature<Result, Result*(Args...), Ts...> {
		using type = Result*(Args...);
	};

	template<typename Result, typename T, typename ...Ts> 
    struct Signature<Result, T, Ts...> : public Signature<Result, Ts...> {};

	template<typename... Ts>
	struct abstract_factory : public abstract_creator<Ts>... {
		template<class U, typename ...Args> unique_ptr<U> create(Args&&... args) {
			abstract_creator<typename Signature<U, Ts...>::type> &creator = *this;
			return creator.doCreate(Type2Type<U>(), std::forward<Args>(args)...);
		}
		virtual ~abstract_factory() {}
	};

	template<typename AbstractFactory, typename Abstract, typename Concrete>
	struct concrete_creator : virtual public AbstractFactory {
		unique_ptr<Abstract> doCreate(Type2Type<Abstract>&&) {
			return make_unique<Concrete>();
		}
	};

	template<typename AbstractFactory, typename Result, typename... Args, typename Concrete>
	struct concrete_creator<AbstractFactory, Result*(Args...), Concrete> : virtual public AbstractFactory {
		unique_ptr<Result> doCreate(Type2Type<Result>&&, 
			                        typename adapt_signature<Args>::type... args) {
			return make_unique<Concrete>(std::forward<adapt_signature<Args>::type>(args)...);
		}
	};

	template<typename AbstractFactory, typename... ConcreteTypes>
	struct concrete_factory;

	template<typename... AbstractTypes, typename... ConcreteTypes>
	struct concrete_factory
		<abstract_factory<AbstractTypes...>, ConcreteTypes...>
		: public concrete_creator<abstract_factory<AbstractTypes...>, AbstractTypes, ConcreteTypes>... {
	};

	template<typename AbstractFactory, template<typename> class Concrete>
	struct parameterized_factory;

	template<template<typename> class Concrete, typename... AbstractTypes>
	struct parameterized_factory<abstract_factory<AbstractTypes...>, Concrete>
		: public concrete_factory<abstract_factory<AbstractTypes...>, 
		                          Concrete<AbstractTypes>...> {
	};

	// Alternate implementation that does not use Type2Type
	template<typename T>
	struct no_t2t_abstract_creator {
		virtual T *doCreate() = 0;
	};

	template<typename... Ts>
	struct no_t2t_abstract_factory : virtual public no_t2t_abstract_creator<Ts>... {
		template<class U> U *create() {
			no_t2t_abstract_creator<U> &creator = *this;
			return creator.doCreate();
		}
		virtual ~no_t2t_abstract_factory() {}
	};

	template<typename AbstractFactory, typename Abstract, typename Concrete>
	struct no_t2t_concrete_creator : virtual public no_t2t_abstract_creator<Abstract> {
		Concrete *doCreate() {
			return new Concrete();
		}
	};

	template<typename AbstractFactory, typename... ConcreteTypes>
	struct no_t2t_concrete_factory;

	template<typename... AbstractTypes, typename... ConcreteTypes>
	struct no_t2t_concrete_factory
		<no_t2t_abstract_factory<AbstractTypes...>, ConcreteTypes...>
		: public no_t2t_abstract_factory<AbstractTypes...>,
		  public no_t2t_concrete_creator<no_t2t_abstract_factory<AbstractTypes...>, AbstractTypes, ConcreteTypes>... {
	};

}
#include <boost/mpl/vector.hpp>
#include <boost/mpl/accumulate.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pair.hpp>
namespace cspp51045 {
  namespace mpl = boost::mpl;
  struct empty {
    void doCreate(); // Just so the "using" statement in accumulate_abstract_types makes sense
  };

  template<typename Accumulator, typename AbstractType>
  struct accumulate_abstract_types : public Accumulator {
    using Accumulator::doCreate;
    virtual unique_ptr<AbstractType> doCreate(Type2Type<AbstractType>&&) = 0;
  };

  template<typename ...AbstractTypes>
  struct mpl_abstract_factory 
    : public mpl::accumulate<mpl::vector<AbstractTypes...>, 
	                         empty, 
	                         accumulate_abstract_types<mpl::_1, mpl::_2>>::type {
    template<class U> unique_ptr<U> create() {
      return this->doCreate(Type2Type<U>());
    }
    virtual ~mpl_abstract_factory() {}
  };

  template<typename Accumulator, typename Type>
  struct accumulate_concrete_types : public Accumulator
  {
    unique_ptr<typename Type::first> doCreate(Type2Type<typename Type::first>&&) {
      return make_unique<typename Type::second>();
    }
  };

  template<typename AbstractFactory, typename ...ConcreteTypes>
  struct mpl_concrete_factory;

  template<typename... AbstractTypes, typename ...ConcreteTypes>
  struct mpl_concrete_factory<mpl_abstract_factory<AbstractTypes...>, ConcreteTypes...> 
    : public mpl::accumulate<mpl::vector<mpl::pair<AbstractTypes, ConcreteTypes>...>,
	                         mpl_abstract_factory<AbstractTypes...>, 
	                         accumulate_concrete_types<mpl::_1, mpl::_2>>::type {
    
  };
}
#endif
