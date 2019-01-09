#ifndef OSTREAM_JOINER_H
#  define OSTREAM_JOINER_H
#define _SCL_SECURE_NO_WARNINGS
// Created by Tomasz Michalik on 5/22/18.
// NOTE: need to use boost/function output iterator and link to exec
#include <boost/function_output_iterator.hpp>
#include <iostream>
#include <string>
using std::basic_ostream;
using std::ostream;
using boost::function_output_iterator;
using std::string;
using std::basic_string;
using std::char_traits;
using std::allocator;

namespace mpcs51044 {
// First, a version just for ostreams (no wide chars, etc.)
struct my_do_output {
    my_do_output(ostream &os, string del)
        : first(true), os(&os), del(del) {
    }
    template<typename T>
    void operator()(T const &t) {
        if(!first) {
            *os << del;
        }
        first = false;
        *os << t;
    }
private:
    bool first;
    ostream *os;
    string del;
};

struct ostream_joiner
  : public function_output_iterator<my_do_output> {
    ostream_joiner(ostream &os, string str)
      : function_output_iterator<my_do_output>({os, str}) {
    }
};


}
#endif