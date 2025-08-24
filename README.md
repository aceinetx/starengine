# starengine
A code-only WIP game engine with a raylib rendering backend and cocos2dx-ish feel

<img src="Content/logo.png" width=200 height=200>

## Platform support (top to bottom most supported):
- Linux
- Windows
- Nintendo Switch (Planned)
- Android (Not planned, but i'm thinking of it)

## Limitations of starengine
- Duct-tape solution for input events, raylib having a poll input system makes it harder to implement input events
- Node inheritance is broken for some nodes (i'm talking about nodes inheriting position, scale and rotation of the parent node), while position and scale inherits correctly, rotation is still broken and more likely will be forever

## Features of starengine
- Basic nodes like Label, Sprite, Scene
- Camera control
- Input events
- Actions like MoveTo, ScaleTo and easings for them
- Inspector extension
- Scheduler to run update(), and schedule functions
- Texture and font managers, don't load the same resource twice!

## Get started
First of all, this project is WIP and currently not intended for real use, but if you want to check it out, here are the instructions on how to do so:
- Clone the repo: ```git clone https://github.com/aceinetx/starengine```
- Change the project's name in the CMakeLists.txt to the game name
- Build: ```./star.py build```
- Run: ```./star.py run```
### Build for nintendo switch
Currently starengine only supports building for switch under docker
- Pull the docker image: ```./star.py pull_nx_docker```
- Run the docker image: ```./star.py run_nx_docker```

(In docker)
- Cd to the workspace: ```cd /workspace```
- Build: ```./star.py build -p switch```
