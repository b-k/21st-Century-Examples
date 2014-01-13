from distutils.core import setup, Extension

py_modules= ['pvnrt']

Emodule = Extension('pvnrt',
       libraries=['pvnrt'],
       library_dirs=['..'],
       sources = ['ideal.py.c'])

setup (name = 'pvnrt',
       #provides='pvnrt',
       version = '1.0',
       description = 'pressure * volume = n * R * Temperature',
       ext_modules = [Emodule])
