import os, sys
from subprocess import call, check_call, CalledProcessError

"""
  Convenience script
"""

print 'python version: ', sys.version

SOURCE                 = os.path.abspath('src')
BUILD                  = os.path.abspath('build')
BUILD_TYPE             = 'Debug'

"""
do this:
cmake -G "Visual Studio 14 2015 Win64" BUILD
"""

def ensure_dir(dir):
	if not os.path.exists(dir):
		os.makedirs(dir)

def try_remove_file(file):
	try:
		os.remove(file)
	except:
		pass

cmake_args = [
	'cmake',
	'-G',
	'Visual Studio 14 2015 Win64',
#    '-DCMAKE_BUILD_TYPE:STRING=' +  BUILD_TYPE,
	SOURCE
]

print ''
print BUILD,'> ',cmake_args[0],'^'
for arg in cmake_args[1:-1]:
        print '\t',arg,'^'
print '\t',cmake_args[-1]
print ''

curdir = os.getcwd()
try:
	ensure_dir(BUILD)
	os.chdir(BUILD)
	try_remove_file('CMakeCache.txt')
	check_call(cmake_args)
	print 'done!'

finally:
	os.chdir(curdir)
