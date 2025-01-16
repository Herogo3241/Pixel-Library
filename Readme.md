# Computer Graphics Algorithms Implementation Library

This is the library for implementing computer graphics algorithms and generating output images or videos. You can install the library and compile and run the code on both Linux and Windows (WSL2) environments. 

## Tools Required

- **Operating System**: Linux / Windows (WSL2)
- **Software**: [ImageMagick](https://imagemagick.org/index.php)

## Installation

1. **Clone the Repository**  
   First, clone the repository to your local machine:

   ```bash
   git clone https://github.com/Herogo3241/Pixel-Library.git
   cd Pixel-Library
   ```

2. **Install ImageMagick**  
   To install ImageMagick, follow the steps for your operating system:

   ```bash
   sudo apt update
   sudo apt install imagemagick
   ```
3. **Install ffmpeg**  
   ffmpeg is needed to generate video of the animation, to install:

   ```bash
   sudo apt install ffmpeg
   ```
   
4. **Installing library**
   To install pixel library, follow the steps for your operating system:

   ```bash
   sudo apt install make
   sudo make install
   ``` 

## Compilation

Once the repository is cloned and dependencies are installed, you can compile the code using the following command:

```bash
gcc main.c -L. -lpixel [-o <executable name>]
```

After compiling the code, you can run the resulting executable to test the implemented algorithms.


The program will run and execute the computer graphics algorithms.




## Set Up for Windows

Once the repository is cloned, follow these steps:
   - Open WSL terminal in the Pixel-Library folder

   1) Run the following commands in WSL
      ```bash
         sudo apt update
         
         sudo apt install imagemagick

         sudo apt install ffmpeg

         sudo apt install make

         sudo make install
      ```
   2) Install the latest version of Xming X server. This is required for viewing the result in windows.
      [link](https://sourceforge.net/projects/xming/)

      Once installed, run the app from the start menu. The app icon will be displayed in your appbar.

   3) Restart the WSL terminal.
   4) Run the program using the following commands:
      ```bash
         gcc <ProgramName>.c -L. -lpixel [-o <executable name>]
      ```

After compiling the code, you can run the resulting executable to test the implemented algorithms.


The program will run and execute the computer graphics algorithms.

