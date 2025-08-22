#!/usr/bin/python
import os, sys, argparse

script_path = os.path.dirname(os.path.realpath(__file__))
build_path = script_path+"/build"

parser = argparse.ArgumentParser(prog="star", description="starengine cli")
parser.add_argument('action', help="What to do with the project? build, run", choices=['reconfigure', 'build', 'run'])
parser.add_argument('-p', '--platform', help="Which platform to build the project for?", choices=['host'])
parser.add_argument('-c', '--parallel', help="Specify the value of --parallel for cmake", type=int, default=3)

args = parser.parse_args()

platform = args.platform
action = args.action
parallel = args.parallel

def command(cmd):
    print(f"\x1b[1;93m[star] executing command: \x1b[1;39m{cmd}\x1b[0m")
    os.system(cmd)

def reconfigure():
    print("\x1b[1;93m[star] reconfiguring...\x1b[0m")
    os.makedirs("build", exist_ok=True)
    os.chdir(build_path)
    command("cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug")
    os.chdir("..")

def build():
    reconfigure();
    print("\x1b[1;93m[star] building...\x1b[0m")
    command(f"cmake --build {script_path}/build --config Debug --parallel {parallel}")

def run():
    build()
    print("\x1b[1;93m[star] running...\x1b[0m")
    command(f"cmake --build {script_path}/build --target run --config Debug --parallel {parallel}")

if action == "reconfigure":
    reconfigure()
elif action == "build":
    build()
elif action == "run":
    run()
