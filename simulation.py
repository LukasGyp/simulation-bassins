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
    k = [5, 4, 3, 2]
    q1 = 5
    q2 = 0
    s = 7

    return np.array([
        q1/s - k[0]/s * np.sign(x[0]-x[1]) * np.sqrt(np.abs(x[0]-x[1])) - k[2]/s * np.sqrt(np.abs(x[0])),
        k[0]/s * np.sign(x[0]-x[1]) * np.sqrt(abs(x[0]-x[1])) - k[1]/s * np.sign(x[1]-x[2]) * np.sqrt(np.abs(x[1]-x[2])),
        q2/s + k[1]/s * np.sign(x[1]-x[2]) * np.sqrt(np.abs(x[1]-x[2])) - k[3]/s * np.sqrt(x[2])
        ])


rk4 = RK4(f, 0, np.array([0., 0., 0.]), h=0.01)

data = np.array([[0., 0., 0., 0.]])

begin = time.perf_counter()
for _ in range(100000):
    t, x = rk4.step()
    data = np.concatenate([data, np.array([[t, x[0], x[1], x[2]]])])

end = time.perf_counter()
print(f'{end - begin:.3f}[s]')
np.savetxt('data_py.csv', data, delimiter=',')
