#include<iostream>

struct NIL{};

template <typename H, typename T = NIL>
struct list{
  typedef H head;
  typedef T tail;
};

template <int n>
struct Int{
  static const int val = n;
};

template <typename list>
struct length{
  const static int result = length<typename list::tail>::result + 1;
};

template <>
struct length<NIL>{
  const static int result = 0;
};


template <typename list, int n>
struct Nth {
  static const int result = Nth<typename list::tail,n-1>::result;
};

template <typename list>
struct Nth<list,1>{
  static const int result = list::head::val;
};


template <typename list, int n>
struct checkIfExists{
  static const bool result = (list::head::val == n) or (checkIfExists<typename list::tail, n>::result);
};

template <int n>
struct checkIfExists <NIL,n>{
  static const bool result = false;
};

template <typename list_, int n>
struct prepend{
  typedef list< Int<n> , list_> result;
};


template <typename list_, int n>
struct append{
  typedef list<typename list_::head, typename append<typename list_::tail, n>::result> result;
};

template <int n>
struct append<NIL, n>{
  typedef list< Int<n>, NIL> result;
};


using list123 = list< Int<1>, list< Int<2>, list<Int<3> > > >;
using list0123 = prepend<list123, 0>::result;
using list1234 = append<list123,4>::result;

static_assert(length<list123>::result == 3, "Length does not match");
static_assert(Nth<list123,1>::result == 1, "nth entry not matching");
static_assert(Nth<list123,2>::result == 2, "nth entry not matching");
static_assert(checkIfExists<list123,4>::result == false,"Error");
static_assert(checkIfExists<list123,3>::result == true,"Error");

static_assert(checkIfExists<list123,0>::result == false,"Error");
static_assert(checkIfExists<list0123,0>::result == true,"Error");

static_assert(checkIfExists<list1234,4>::result == true,"Error");
static_assert(checkIfExists<list1234,5>::result == false,"Error");

int main(){
  return 0;
}