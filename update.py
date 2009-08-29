#!/usr/bin/env python 
# ------------------------------------------------------------------------------
# update.py
# ------------------------------------------------------------------------------
# 
# (C) Copyright Ulf Ejlertsson 2009
# 

import subprocess
import sys
import os
import time

def draw_spinner(cmd, delay=0.2):
    for char in '/-\|':
        sys.stdout.write(cmd + char)
        sys.stdout.flush()
        time.sleep(delay)
        sys.stdout.write('\r')

   

class SVNError(Exception):
    pass

class MakeError(Exception):
    pass

# svn update
def svn_update(path):
    os.chdir(path)

    #execute the 'svn update'
    update = "svn update"
    process = subprocess.Popen(update, shell=True, stdout=subprocess.PIPE)
    (sout, serr) = process.communicate()
    #print 'SVN update ' + path + '...'
    for line in sout.split('\n'):
        draw_spinner('SVN update ' + path + ' ')

    print '\t\t\tOK! '
    process.wait()

    if process.returncode != 0:
        raise SVNError('Failed to update: ' + path)

    return repr(process.communicate())

    
def make_llvm(path, do_clean=False):
    os.chdir(path)

    if do_clean:
        clean = "make clean"
        process = subprocess.Popen(clean, shell=True, stdout=subprocess.PIPE)
        (sout, serr) = process.communicate()
        print clean + '...'
        for line in sout.split('\n'):
            draw_spinner('make clean ')
        print '\t\t\tOK!'    
        process.wait()
        if process.returncode != 0:
            raise MakeError('Failed to ' + clean)

    make = 'make -j2'
    process = subprocess.Popen(make, shell=True, stdout=subprocess.PIPE)
    (sout, serr) = process.communicate()
    #print 'compiling [' + make + ']...'
    for line in sout.split('\n'):
        draw_spinner('compiling [' + make + '] ')
    print '\t\t\tOK! '
    process.wait()
    if process.returncode != 0:
        raise MakeError('Failed to ' + make)

    return repr(process.communicate())

def update_llvm():
    try:
        TRUNK = 'llvm/trunk'
        svn_update(TRUNK)
        svn_update('tools/clang/')
        make_llvm('../../')
    except Exception, e:
        print e

if __name__ == '__main__':
    update_llvm()

    
    

# End of Script
