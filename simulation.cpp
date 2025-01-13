#include <fstream>
#include <functional>
#include <iostream>
#include <tuple>
#include <valarray>
#include <time.h>
#include <vector>
using namespace std;

void output(vector<tuple<float, valarray<float>>> data) {
  std::ofstream file("data.csv");

  for(int i=0; i < data.size(); i++) {
    file << get<0>(data[i]);
    const valarray<float> row_x = get<1>(data[i]);
    const int n = row_x.size();
    for(int j=0; j<n; j++) {
      file << "," << row_x[j]; 
    }
    file << endl;
  }
}

valarray<float> rk4(function<valarray<float>(float, valarray<float>)> f, float t, valarray<float> x, float h) {
  valarray<float> k1 = f(t, x);
  valarray<float> k2 = f(t+h/2, x + h * k1 / 2);
  valarray<float> k3 = f(t+h/2, x + h * k2 / 2);
  valarray<float> k4 = f(t + h, x + h * k3);

  return x + h * (k1 + k4 + 2 * (k2 + k3)) / 6;
}

valarray<float> f(float t, valarray<float> x) {
  return {x[1], -x[0]};
}

int main() {
  int n = 2;
  float t = 0;
  valarray<float> x = { 0, 1 };
  float h = 0.01;

  vector<tuple<float, valarray<float>>> data;
  auto begin = clock();
  for(int i=0; i<100; i++) {
    x = rk4(f, t, x, h);
    t += h;
    data.emplace_back(tuple<float, valarray<float>>(t, x));
  }
  auto end = clock();
  cout << (double)(end - begin)/CLOCKS_PER_SEC << "[s]" << endl;
}
