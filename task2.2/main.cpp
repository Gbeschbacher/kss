#include <iostream>
#include <cmath>

constexpr unsigned NPAD = 0;
constexpr unsigned _expStart = 10;
constexpr unsigned _expEnd = 28;

constexpr unsigned repsPerExp = 20;

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

  std::cout << "Exponent\tCycles / List Element"<<std::endl;

  for (unsigned _exp = _expStart; _exp <= _expEnd; ++_exp){

    unsigned workingSetSize = pow(2, _exp) / sizeof(l);
    for(unsigned sampleRun = 0; sampleRun < repsPerExp; ++sampleRun){
      //std::cout << "NPAD\t" << NPAD;
      for (unsigned i = currentElementIndex; i < workingSetSize; ++i){
        current->n  = new l();
        current = current->n;
      }
      currentElementIndex = workingSetSize;

      uint64_t time = measure::cycles([&start, &current](){
        current = &start;
        while (current->n != nullptr){
          current = current->n;
        }
      });

      samples[sampleRun] = time;

    }
    std::cout << _exp << "\t" <<arithmetic_mean(samples, repsPerExp)/workingSetSize << std::endl;
    //std::cout << "\t Working Set Size\t" << "2^" << _exp << "\t Cycles/List Element\t" << (time/workingSetSize) << std::endl;
    //std::cout << "\tMean\t" << measure::arithmetic_mean(samples, repsPerExp) << "\tSSD\t" << measure::sample_standard_deviation(samples, repsPerExp) << std::endl;
  }


  return EXIT_SUCCESS;
}