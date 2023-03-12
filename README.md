# rainbow
A lolcat alternative made in C

## Config
Config can be found in `config.h`
`BOLD`: If the output is bold
`BG`: If the background should be rainbowed
`FG`: If the foreground (text) should be rainbowed
`SKIPSPACES`: Skip spaces (looks weird with BG enabled)
`XITER`: The step used for each character (radians)
`YITER`: The step used for each line (radians)
`BUFLEN`: Length of the buffer used for reading input


## Compiling
Run `make`

## Installing
Run `make install` to install  
Run `make uninstall` to uninstall

## Usage
Run `inputoverlay`

## Problems
Window managers with background blur, and/or borders are not told to disable these features  
The display char can only be a char so multichar's (such as emojis or CJK) cannot be used
