#include <iostream>
#include <cmath>

constexpr unsigned NPAD = 24;
constexpr unsigned _expStart = 10;
constexpr unsigned _expEnd = 25;

struct measure {

  private:
    static uint64_t rdtsc(){
      unsigned int lo, hi;
      __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
      return ((uint64_t)hi << 32) | lo;
    }

  public:
    template<typename _function, typename ..._args>
    static uint64_t cycles(_function func, _args&&... args){
      uint64_t x = measure::rdtsc();
      func(std::forward<_args>(args)...);
      uint64_t y = measure::rdtsc();
      return (y - x);
    }
};

struct l{
  l * n;
  long pad[NPAD];
};

int main(){

  l start;
  l * current = &start;

  unsigned next_element_index = 0;

  for (unsigned _exp = _expStart; _exp <= _expEnd; ++_exp){
    std::cout << "NPAD\t" << NPAD;
    unsigned end_working_set_size = pow(2, _exp);
    for (unsigned i = next_element_index; i < end_working_set_size; ++i){
      current->n  = new l();
      current = current->n;
    }
    next_element_index = end_working_set_size;

    uint64_t time = measure::cycles([&start, &current](){
      current = &start;
      while (current->n != nullptr){
        current = current->n;
      }
    });

    std::cout << "\t Working Set Size\t" << "2^" << _exp << "\t Cycles/List Element\t" << (time/end_working_set_size) << std::endl;
  }


  return EXIT_SUCCESS;
}