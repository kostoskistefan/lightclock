# Lightclock

Lightclock is a very lightweight floating clock for Linux that only appears on top of fullscreen windows.

It's an alternative to [Hoverclock](https://github.com/kostoskistefan/hoverclock), except that it sacrifices some of the customizability and only shows up on top of fullscreen windows.

## Quick disclaimer
This project is created only by using the XCB library and therefore it only works with the X Window System (X11).

## Installation
### Prebuilt release
You can download the latest executable file from the [releases section](https://github.com/kostoskistefan/lightclock/releases) and run it directly.

### Building from source
#### Dependencies
Make sure you have the following dependencies available on your system:
 * xcb
 * xcb-util
 * xcb-ewmh
 * xcb-icccm

#### Building
First you need to clone the repository, go to the cloned directory and build the executable using the Makefile: 

```
$ git clone https://github.com/kostoskistefan/lightclock.git
$ cd lightclock
$ make
```

After that, you should have an executable file called **lightclock** in the same directory as the Makefile.

## Configuration
To configure the clock, you have to run it at least once for the config file to be created in `$HOME/.config/lightclock/lightclock.conf`. After that you can edit the file to your liking and restart Lightclock.

## Future work
- [ ] Add system tray icon
- [ ] Add freetype/truetype font support

## Getting help
If you have questions, concerns, bug reports, etc, please file an issue in this repository's [Issue Tracker](https://github.com/kostoskistefan/lightclock/issues).

## Getting involved
### Using the issue tracker
Use the [issue tracker](https://github.com/kostoskistefan/lightclock/issues) to request new features, report bugs and ask questions. Any feedback is greatly appreciated.

### Changing the code-base
If you want to directly affect the code, you should fork this repository, make changes on your own fork, then submit a pull request.
