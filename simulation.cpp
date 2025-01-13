#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <tuple>
#include <valarray>
#include <time.h>
#include <vector>
using namespace std;

int sign(double x) {
  return (x>0) - (x<0);
}

void output(vector<tuple<double, valarray<double>>> data) {
  std::ofstream file("data.csv");

  for(int i=0; i < data.size(); i++) {
    file << get<0>(data[i]);
    const valarray<double> row_x = get<1>(data[i]);
    const int n = row_x.size();
    for(int j=0; j<n; j++) {
      file << "," << row_x[j]; 
    }
    file << endl;
  }
}

valarray<double> rk4(function<valarray<double>(double, valarray<double>)> f, double t, valarray<double> x, double h) {
  valarray<double> k1 = f(t, x);
  valarray<double> k2 = f(t+h/2, x + h * k1 / 2);
  valarray<double> k3 = f(t+h/2, x + h * k2 / 2);
  valarray<double> k4 = f(t + h, x + h * k3);

  return x + h * (k1 + k4 + 2 * (k2 + k3)) / 6;
}

valarray<double> f(double t, valarray<double> x) {
  double k[] = {5., 4., 3., 2.};
  double Q1 = 3;
  double Q2 = 4;
  double s = 7.;

  return {
    Q1/s - k[0]/s * sign(x[0]-x[1]) * sqrt(abs(x[0]-x[1])) - k[2]/s * sqrt(abs(x[0])),
    k[0]/s * sign(x[0] - x[1]) * sqrt(abs(x[0]-x[1])) - k[1]/s * sign(x[1]-x[2]) * sqrt(abs(x[1]-x[2])),
    Q2/s + k[1]/s * sign(x[1]-x[2]) * sqrt(abs(x[1]-x[2])) - k[3]/s * x[2]
  };
}

int main() {
  double t = 0;
  valarray<double> x = { 0., 0., 0. };
  double h = 0.01;

  vector<tuple<double, valarray<double>>> data;
  auto begin = clock();
  for(int i=0; i<100000; i++) {
    x = rk4(f, t, x, h);
    t += h;
    data.emplace_back(tuple<double, valarray<double>>(t, x));
  }
  auto end = clock();
  cout << (double)(end - begin)/CLOCKS_PER_SEC << "[s]" << endl;

  output(data);
}
