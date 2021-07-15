# fireman
A C game I made to practice the C language. It is about a fireman in a fiery city. Written and tested on Ubuntu 20.04.2.

## Installation
You need to install the ncurses library.
```bash
sudo apt install libncurses5* libncursesw5*
```

Then compile the source code.
```bash
make
```

## Usage
To run the game.
```bash
./fireman
```

To clean the project.
```bash
make clean
```


## Docker
Alternatively, you can run fireman using Docker.

### Build Image
```bash
docker build -t fireman .
```

### Run Image as a Container
```bash
docker run -it --rm fireman
```

### Pull from Docker Hub
```bash
docker pull sergiormh/fireman
```

### Run Pulled Image
```bash
docker pull sergiormh/fireman
```

### Bug
If you run it using Docker, you might notice that, in the first menu of the game, an option gets chosen before you
have the time to choose it yourself. Right now I am lazy to investigate more about this.


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.


## License
[MIT](https://choosealicense.com/licenses/mit/)