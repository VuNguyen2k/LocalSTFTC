import numpy as np

N = 512
F = N // 2 + 1

def gen_inputs(n: int) -> np.ndarray[float]:
    return np.ones((n, ), dtype=np.float32) * 0.5

x = np.fft.fft(gen_inputs(N), n=F)
print(x, x.shape)
