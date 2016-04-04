import matplotlib.pyplot as plt
import numpy as np

def main():
    a = np.array([1, 2, 3, 4])
    b = np.array([1, 4, 9, 16])
    plt.title('test.png')
    plt.plot(a, b)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.savefig('test.png')


if __name__ == '__main__':
    main()
