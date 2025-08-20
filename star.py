#!/usr/bin/python
import os, sys, argparse

script_path = os.path.dirname(os.path.realpath(__file__))
build_path = script_path+"/build"

parser = argparse.ArgumentParser(prog="star", description="starengine cli")
parser.add_argument('action', help="What to do with the project? build, run", choices=['build', 'run'])
parser.add_argument('-p', '--platform', help="Which platform to build the project for?", choices=['host'])

args = parser.parse_args()

platform = args.platform
action = args.action

def reconfigure():
    os.system("cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug")

def build():
    os.makedirs("build", exist_ok=True)
    os.chdir(build_path)
    reconfigure();
    os.system(f"cmake --build {script_path}/build --config Debug --parallel 4")
    os.chdir("..")

def run():
    build()
    os.system(f"cmake --build {script_path}/build --target run --config Debug --parallel 4")

if action == "build":
    build()
elif action == "run":
    run()
