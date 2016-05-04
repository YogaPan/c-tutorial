def logger(func):
    def wrapper():
        print('start')
        func()
        print('stop')
    return wrapper

@logger
def say():
    print('fuck')

def main():
    say()

if __name__ == '__main__':
    main()
