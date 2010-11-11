#!/usr/bin/env python

"""
Used to compile python code in the src directory

Author: Remo Cocco
"""

import compileall
import getopt
import os
import os.path
import re
import shutil
import sys


global CWD
global BUILD_DIR
global SOURCE_DIR
CWD = sys.path[0] + "/" # always the directory containing the script
BUILD_DIR = CWD + "build/"
SOURCE_DIR = CWD + "src/"

"""
DEPRECATED
No longer needed.
This is not how python does things
"""
def checkBuildDirConsitency():
    if not os.path.exists(BUILD_DIR):
        os.mkdir(BUILD_DIR)
    
"""
DEPRECATED
No longer needed.
This is not how python does things
"""
def moveCompilerScriptsToBuildDirectory():
    for compilerScript in os.listdir(SOURCE_DIR):
        if not re.search('.*\.pyc$', compilerScript) == None:
            shutil.move(SOURCE_DIR + compilerScript, BUILD_DIR + compilerScript)

def compileAllPythonSource():
    #checkBuildDirConsitency()
    compileall.compile_dir(dir=SOURCE_DIR, rx=re.compile('/[.]svn'))
    #moveCompilerScriptsToBuildDirectory()
    
def clean():
    #if os.path.exists(BUILD_DIR):
        #shutil.rmtree(BUILD_DIR)
    for compilerScript in os.listdir(SOURCE_DIR):
        if not re.search('.*\.pyc$', compilerScript) == None:
            os.remove( SOURCE_DIR + compilerScript)
    

def usage():
    print "compile [--clean]"

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h", ["help", "clean"])
    except getopt.GetoptError, err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)

    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("--clean"):
            clean()
            sys.exit()
        else:
            usage()
            sys.exit(1)

    # if not options have been meet compile
    compileAllPythonSource()

if __name__ == "__main__":
    main()
