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
        self.x += h * (k1 + k4 + 2*(k2 + k3)) / 6
        self.t += h
        return self.t, self.x


def f(t, x):
    pump = [
            [0., 3., 0., 0.],
            [3., 0., 2., 0.],
            [0., 2., 0., 1.],
            [0., 0., 1., 0.]
            ]
    leakage = np.array([1.6, 0.2, 0.38, 0.2])
    q = np.array([0.52, 0.52, 0.52, 0.52])
    s = np.array([900., 900., 900., 900.])
    s_inv = 1 / s

    result = np.zeros(4)
    for i in range(4):
        result[i] += q[i] * s_inv[i]
        for j in range(4):
            coef = pump[i][j] if x[i]-x[j] >= 0 else -pump[j][i]
            result[i] -= coef * s_inv[i] * np.sqrt(np.abs(x[i]-x[j]))
        result[i] -= leakage[i] * s_inv[i] * np.sqrt(np.abs(x[i]))
    return result


if __name__ == "__main__":
    t = 0
    x = np.array([0.74, 0.93, 1.00, 1.23])

    rk4 = RK4(f, t, x, h=0.01)

    data = np.array([[t, x[0], x[1], x[2], x[3]]])

    begin = time.perf_counter()
    for i in range(100000):
        t, x = rk4.step()
        if i % 100 == 0:
            data = np.concatenate([data, np.array([[t, x[0], x[1], x[2], x[3]]])])

    end = time.perf_counter()
    print(f'{end - begin:.3f}[s]')
    np.savetxt('data.csv', data, delimiter=',')
