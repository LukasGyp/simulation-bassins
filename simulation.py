import numpy as np
import time


class RK4:
    def __init__(self, f, t0, x0, h):
        self.f = f
        self.t0 = t0
        self.x0 = x0
        self.h = h

        self.t = t0
        self.x = x0

    def step(self):
        f, t, x, h = self.f, self.t, self.x, self.h
        k1 = f(t, x)
        k2 = f(t + h/2, x + h * k1 / 2)
        k3 = f(t + h/2, x + h * k2 / 2)
        k4 = f(t + h, x + h * k3)
        self.x += h * (k1 + 2*k2 + 2*k3 + k4) / 6
        self.t += h
        return self.t, self.x


def f(t, x):
    return np.array([x[1], -x[0]])


rk4 = RK4(f, 0, np.array([0., 1.]), h=0.01)

t_ = [0]
x_ = [0.]

begin = time.perf_counter()
for _ in range(10000000):
    t, x = rk4.step()
    t_.append(t)
    x_.append(x[0])
end = time.perf_counter()
print(end - begin)
