# cProjects

## Usage
Clone this repository
```bash
git clone https://github.com/anixne/cprojects
cd cprojects
```

<details>
<summary>atgame</summary>
  
### Windows
```
bin\atgame.exe
```
### Linux
to run the executable file you will need wine.
```bash
wine bin/atgame.exe
```


### Gameplay
E - exit <br>
W - up <br>
S - down <br>
A - left <br>
D - right. <br>

Enjoy.


![image](./assets/gameplay.png)
  

### Conclusion
If you have problems or ideas create a new issue.
  </details>
<details>
<summary> arkanoid</summary>
  
### Windows
```
bin\arkanoid.exe
```
### Linux
to run the executable file you will need wine.
```bash
wine bin/arkanoid.exe
```
  
  
 ### Gameplay
Esc - exit <br>
W - start <br>
A - left <br>
D - right. <br>
  

![image](./assets/arkanoidgp.png)

![image](./assets/lvl2.png)  
  
![image](./assets/lvl3.png)    
  
Enjoy.  
  </details>
<details>
  <summary>snowGenerator</summary>
    
### Windows
```
bin\genesnow.exe
```
### Linux
to run the executable file you will need wine.
```bash
wine bin/genesnow.exe
```
![image](./assets/snow.png)
  
</details>  
<details>
<summary>Audio duration calculator</summary>
  
This script calculates all audio files duration in the folder
  
Requirments:
  
```bash
sudo pacman -S ffmpeg
cd src
gcc audio_duration.c -o audio_duration -lavformat -lavcodec -lavutil -lm
```
### Usage

```bash
./audio_duration /path/to/audio/file
```
