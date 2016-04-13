import numpy as np
import matplotlib.pyplot as plt

def main():
    t1 = np.linspace(3, 8, 9)
    t2 = np.linspace(0, 32, 9)

    plt.title('test')
    plt.ylabel('Y')
    plt.xlabel('X')
    #  plt.grid(True)
    plt.axis([0, 40, 0, 40])
    lines = plt.plot(t1, t2, color='g', linestyle='-', linewidth=2.0)
    #  plt.setp(lines, color='r', linewidth=1.0, linestyle='-')

    plt.savefig('line.png')

if __name__ == '__main__':
    main()
