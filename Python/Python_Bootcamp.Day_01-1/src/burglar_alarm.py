# import splitwise
import functional_purse

def squeak_decorator(func):
    def wrapper(*args, **kwargs):
        print("SQUEAK")
        return func(*args, **kwargs)
    return wrapper

add_ingot = squeak_decorator(functional_purse.add_ingot)

get_ingot = squeak_decorator(functional_purse.get_ingot)

empty = squeak_decorator(functional_purse.empty)
