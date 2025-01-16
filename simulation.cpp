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
    for(int j=0; j<4; j++) {
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

  double pump[4][4] = {
    {0., 3., 0., 0.},
    {3., 0., 2., 0.},
    {0., 2., 0., 1.},
    {0., 0., 1., 0.},
  };
  double leakage[4] = {1.6, 0.2, 0.38, 0.2};
  double q[4] = {0.52, 0.52, 0.52, 0.52};
  double s[4] = {900., 900., 900., 900.};
  double s_inv[4] = {1/s[0], 1/s[1], 1/s[2], 1/s[3]};

  valarray<double> result(0., 4);
  
  for(int i=0; i<4; i++) {
    result[i] += q[i] * s_inv[i];
    for(int j=0; j<4; j++) {
      double coef = x[i]-x[j] >= 0 ? pump[i][j] : -pump[j][i];
      result[i] -= coef * s_inv[i]  * sqrt(abs(x[i]-x[j]));
    }
    result[i] -= leakage[i] * s_inv[i] * sqrt(abs(x[i]));
  }

  return result;
}

int main() {
  double t = 0;
  valarray<double> x = { 0.74, 0.93, 1.00, 1.23 };
  double h = 0.01;

  vector<tuple<double, valarray<double>>> data;
  data.emplace_back(tuple<double, valarray<double>>(t, x));
  auto begin = clock();
  for(int i=0; i<1000000; i++) {
    x = rk4(f, t, x, h);
    t += h;
    if(i%100 == 0) {
      data.emplace_back(tuple<double, valarray<double>>(t, x));
    }
  }
  auto end = clock();
  cout << (double)(end - begin)/CLOCKS_PER_SEC << "[s]" << endl;

  output(data);
}
