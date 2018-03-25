// Use new CRAN package BH for Boost headers

// [[Rcpp::depends(BH)]]
// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <cmath>
#include <boost/circular_buffer.hpp>
#include <random>
#include <exception>
#include <stdexcept>

using boost::circular_buffer;
using std::mt19937_64;
using std::normal_distribution;
using std::invalid_argument;

class Egarch
{
public:
  Egarch(double alphazero, double alphaone, double gamma, double beta):
  alphaZero_(alphazero), alphaOne_(alphaone), gamma_(gamma), beta_(beta){};
  
  double operator()(double prevSigma, double norm) const
  {
    return (std::sqrt(std::exp( alphaZero_ + alphaOne_*(std::abs(norm) + gamma_*(norm)) 
            + beta_ * std::log(prevSigma * prevSigma))));
  };
  
private:
  double alphaZero_;
  double alphaOne_;
  double gamma_;
  double beta_;
  
};

// [[Rcpp::export]]
boost::circular_buffer<double> simVolatilties(double alphaZero, double alphaOne, double gamma, double beta, double initSigma, int bufferSize, int seed)
{
  if (bufferSize < 0 )
  {
    throw invalid_argument("Buffer size must be positive \n");
    
  }
  boost::circular_buffer<double> cb(bufferSize);
  mt19937_64 mtre(seed);
  normal_distribution<> nd;
  
  

  Egarch eg(alphaZero, alphaOne, gamma, beta);

  cb.push_back(initSigma);
  unsigned iterations = bufferSize;
  for(unsigned i = 1; i < iterations; ++i)
  {
    
    cb.push_back(eg(cb[i-1],nd(mtre)));
  }

  return cb;
}

