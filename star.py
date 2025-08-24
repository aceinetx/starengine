#!/usr/bin/python
import os, sys, argparse, time

script_path = os.path.dirname(os.path.realpath(__file__))
build_path = script_path+"/build"

parser = argparse.ArgumentParser(prog="star", description="starengine cli")
parser.add_argument('action', help="What to do with the project? build, run", choices=['reconfigure', 'build', 'run', 'pull_nx_docker', 'run_nx_docker'])
parser.add_argument('-p', '--platform', help="Which platform to build the project for?", choices=['host', 'switch'], default='host')
parser.add_argument('-c', '--parallel', help="Specify the value of --parallel for cmake", type=int, default=3)

args = parser.parse_args()

platform = args.platform
action = args.action
parallel = args.parallel

cmake_configure_args = f""
if(platform == 'switch'):
    cmake_configure_args += " -DSWITCH=1"

    def err(msg):
        print(f"\x1b[1;91m[star] {msg}\x1b[0m")

    if not os.path.exists("/.dockerenv"):
        err("It's detected that you are building starengine for nintendo switch without docker.")
        err("I'll let it be known for you that building with devkitpro without docker is unsupported")
        err("and most likely NEVER will be.")
        err("Proceed with caution, any further errors will not be reviewed in github issues.")
        timeout = 8
        for i in range(0, timeout):
            print(f"{timeout-i}..", end="", flush=True)
            time.sleep(1)
        print()

def command(cmd):
    print(f"\x1b[1;93m[star] executing command: \x1b[1;39m{cmd}\x1b[0m")
    os.system(cmd)

def reconfigure():
    print("\x1b[1;93m[star] reconfiguring...\x1b[0m")
    os.makedirs("build", exist_ok=True)
    os.chdir(build_path)
    command(f"cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug {cmake_configure_args}")
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
elif action == "pull_docker":
    command("sudo docker pull devkitpro/devkita64")
elif action == "run_nx_docker":
    command("sudo docker run -it --rm -v \"$(pwd)\":/workspace devkitpro/devkita64")
