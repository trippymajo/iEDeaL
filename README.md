# 🎞️🎼 iEDeaL - Simple timestamps from EDL (Adobe Premier Pro) 🎼🎥

**iEDeaL** is an EDL parser designed to extract music track names and their timestamps from Adobe Premiere Pro projects.
It analyzes an EDL file and produces a clean list of all music cues used in the timeline. 

## ⚠️ Requirements ⚠️

* C++ compiler (C++11 or later)
* CMake (for generating build files)
* (Optional) Qt or other libraries

## 🚀 Build 🚀
Clone the repository and build using CMake:  
```bash
git clone https://github.com/trippymajo/iEDeaL.git
cd iEDeaL
mkdir build
cd build
cmake ..
cmake --build .     # or: cmake --build . --config Release
```
This will produce an executable (iEDeaL or iEDeaL.exe) inside the build directory.  

## 👩‍💻 Usage 🔌
### 🎞️ In Adobe Premier Pro:
1. Open -> Export
2. Pick EDL extension
3. Checkbox only audio, uncheck all other
4. Pick tracks where audio included
5. Click Ok!

### 🌟 In iEDeaL:
1. File -> Export
2. Pick EDL file

The parser will:
1. Read the EDL
2. Extract music tracks
3. Output timestamps, durations, and clip source data in Text box

**This is useful for editors who need to quickly generate a soundtrack list from their Premiere timeline.**
