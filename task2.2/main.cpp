#include <iostream>
#include <cmath>

#ifndef NPAD
#define NPAD 0
#endif

constexpr unsigned _expStart = 10;
constexpr unsigned _expEnd = 28;
constexpr unsigned repsPerExp = 100;

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

template<typename T>
double arithmetic_mean(T* data, uint32_t nelem) {
  double sum = 0.0;
  for (uint32_t i = 0; i <nelem; ++i) {
    sum += data[i];
  }
  return sum / static_cast<double>(nelem);
}

template<typename T>
double sample_standard_deviation(T* data, uint32_t nelem) {
  double sum = 0.0;
  double mean = arithmetic_mean(data, nelem);

  for (uint32_t i = 0; i <nelem; ++i) {
    double diff = data[i]-mean;
    sum += diff * diff;
  }

  return sqrt((1.0/static_cast<double>(nelem-1)) * sum);
}

struct l{
  l * n;
  long pad[NPAD];
};

int main(){

  l start;
  l * current = &start;

  uint64_t samples[repsPerExp];

  unsigned currentElementIndex = 0;


  for (unsigned _exp = _expStart; _exp <= _expEnd; ++_exp){

    std::cout << "npad\t" << NPAD;
    std::cout <<"\texponent\t" << _exp;

    unsigned workingSetSize = pow(2, _exp) / sizeof(l);

    for (unsigned i = currentElementIndex; i < workingSetSize; ++i){
      current->n  = new l();
      current = current->n;
    }

    currentElementIndex = workingSetSize;

    for(unsigned sampleRun = 0; sampleRun < repsPerExp; ++sampleRun){

      uint64_t time = measure::cycles([&start, &current](){
        current = &start;
        while (current->n != nullptr){
          current = current->n;
        }
      });

      samples[sampleRun] = time;
    }

    std::cout << "\ttime\t" << arithmetic_mean(samples, repsPerExp)/workingSetSize;
    std::cout << "\tdeviation\t" << sample_standard_deviation(samples, repsPerExp) << std::endl;
  }


  current = start.next;
  l * next = nullptr;
  while(current != nullptr){
    n = current->n;
    delete current;
    current = n;
  }

  return EXIT_SUCCESS;
}