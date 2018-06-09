/* foo.cpp */

#include "fft.h"

#include <iostream>
#include <unsupported/Eigen/FFT>
#include <vector>
#include <iterator>


extern "C" {

  void RFFT(double* x, int array_size, double* return_y) {

    printf("In RFFT\n");
    
    Eigen::FFT<double> fft;
    
    std::vector<std::complex<double> > freqvec;
  
    std::vector<double> v; 
    for(int i = 0; i < array_size; ++i) {
      v.push_back(x[i]);
    }

    fft.fwd(freqvec,v);

    int spectrum_size = freqvec.size() / 2;

    for(int i = 0; i < spectrum_size;  i++) {
      return_y[i] = std::real(freqvec[i]) / array_size;
      return_y[spectrum_size + i] = std::imag(freqvec[i]) / array_size;
    }
  }
  
  void RIFFT(double* x, int array_size, double* return_y) {

    printf("In RIFF\n");
    Eigen::FFT<double> fft;
    
    std::vector<double> timevec;
   
    std::vector<std::complex<double>> reconstructed_vector;

    int half = array_size / 2;

    std::vector<double> v(half);
      
    //    v.push_back(0);
    
    //    for(int i = 0; i < half; ++i) {
    //      v.push_back(x[half + i]);
      //v.push_back(x[i]);
    //    }

    //v.push_back(0);
    
    for(int i = 0; i < half; ++i) {
      std::complex<double> complex_value_1 (x[i], x[half+i]);
      reconstructed_vector.push_back(complex_value_1);
    }

    int n = array_size;


    printf("array is %d\n", n);

    for(int k = n/2 + 1; k < n; ++k) {

      double real = std::real(reconstructed_vector[n - k]);
      double imag = -1 * std::imag(reconstructed_vector[n - k]);

      std::complex<double> point (real, imag);

      reconstructed_vector.push_back(point);
    }
  

    //    std::complex<double> complex_value_1 (0, 0);

    //    reconstructed_vector.push_back(complex_value_1);
    
    fft.inv(timevec, reconstructed_vector);
    
    int size = timevec.size();
    
    for(int i = 0; i < size;  i++) {
      return_y[i] = timevec[i] * array_size;
    }

  }
  
} /* extern "C" */