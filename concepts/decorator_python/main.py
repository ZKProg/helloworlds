import os
import sys

"""
Decorators proof of concetp.
Will demonstrate decorators with, and without arguments.
Will also demonstrate 2 different syntaxes:
  - @decorator calling syntax
  - ()() calling syntax
"""

# Simple decorator (no argument passed)
def decorator(function):
    def modified_function(message):
        print("From modified function:", message)
    return modified_function


# Decorator with arguments passed
def decowithargs(arguments):
    def wrapper(function):
        def modified_function(message):
            for i in range(arguments):
                print(message)
            print("The message has been printed {} times".format(arguments))
        return modified_function
    return wrapper

# Decorated functions
@decorator
def say(message):
    print(message)

@decowithargs(10)
def repeat(message):
    print(message)

def hello(name):
    print(name)

"""
Call conventions
"""

say("Hello Decorators")

repeat("This is a repeated message")
closure = decowithargs(5)(hello)
closure("Repeated with closure")
