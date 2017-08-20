#include<iostream>

struct NIL{};

template <typename H, typename T = NIL>
struct list{
  typedef H head;
  typedef T tail;
};

template <int n>
struct Int{
  static const int result = n;
};

template <typename list>
struct length{
  const static int result = length<typename list::tail>::result + 1;
};


template <>
struct length<NIL>{
  const static int result = 0;
};


int main(){
  using list123 = list< Int<1>, list< Int<2>, list<Int<3> > > >;
  std::cout << length<list123>::result << std::endl;
  return 0;
}