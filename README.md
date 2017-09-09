QuickViewer
===========

A image/comic viewer application for Windows and Linux, it can show images very fast

## Project Website(in English / Japanese)

https://kanryu.github.io/quickviewer/

## Summary

 - To show images very fast (using OpenGL)
 - Portable (without installers, registries, external libraries)
 - 2 Page Spread viewing (two images once, for digital books/comics)
 - To read archives directly (zip/7z/rar/cbr/cbz)
 - To show images (bmp/png/jpeg/dds/webp/ico/tga/tiff/gif)
   - Supported for Animated PNG(APNG)/GIF
   - Auto rotation (using JPEG EXIF)
 - To show Raw digital camera images
   - Canon(crw, cr2)
   - Nicon(nef)
   - Sony(arw)
   - Ricoh(dng)
   - etc..
 - Can make/view/search catalog from thousands of your digital books
 - Multilingual support(English/Spanish/Simplified Chinese/Japanese/Greek)

## Download

[binary distributions](https://github.com/kanryu/quickviewer/releases) (Windows x86/x64, Linux AppImage x64)

## Screenshots

### 1 page viewing


![1 page viewing](https://github.com/kanryu/quickviewer/wiki/images/singleview.jpg)

### 2 page spread viewing

![Spread viewing](https://github.com/kanryu/quickviewer/wiki/images/dualview.jpg)

### Stripped viewing

If you want, you can remove all attached bars and display only images.
Hidden bars are displayed automatically when needed.

![Stripped viewing](https://github.com/kanryu/quickviewer/wiki/images/stripped.jpg)



## How to use

- Run the app, and drop image folder/archive to the window.
- Create shortcut, and drop image folder/archive on it.


## Features

- Next Page (Press 'right Arrow Key', 'Mouse wheel down', 'Mouse forward button', or Click left end of window)
- Prev Page (Press 'left Arrow Key', 'Mouse wheel up', 'Mouse back button', or Click right end of window)
- Fullscreen (Press 'F11 Key', click Mouse wheel, or 'Esc Key'(to windowed only))
- Auto loading (auto loading the last book when the app executed)
- Fittng (To fit images up to window size)
- Spread viewing (two image once)
    - Bound on the right side book(e.g. Japanese Style)
- Pre page loading(via v0.2.0)
- Exif Information(via v0.3.0)
- Show Windows Explorer for the current image
- Put the current image into your mailer
- Shader Program Filters(via v0.5.1)
    - Nearest Neighber
    - Bicubic (by GPU)
    - Lanczos
    - Bicubic by CPU
- Catalog(via v0.6.0)
    - Database for your digital books, can manage thansands of volumes, quick view and search
- File Associations(via v0.8.3)

## Screen operations

You can do screen operations with the main menu, tool bar, mouse button, wheel, keyboard and so on.

| Operation   | Device   | Input   | Remarks |
|:------------|:---------|:--------|:--------|
| Next Page   | Keyboard | Right Key(→) | |
|             | Keyboard | Space Key | |
|             | Mouse Wheel | Downward scrolling | |
|             | Mouse    | Forward Button   | |
| Prev Page   | Keyboard | Left Key(←) | |
|             | Keyboard | BackSpace Key | |
|             | Mouse Wheel | Upward scrolling | |
|             | Mouse    | Back Button | |
| First Page  | Keyboard | Home Key | |
| Last Page   | Keyboard | End Key | |
| Next Volume | Keyboard | Page Down Key | open a folder/archive of neighbor |
| Prev Volume | Keyboard | Page Up Key | open a folder/archive of neighbor |
| Fullscreen  | Keyboard | F11 Key | |
|             | Mouse    | Wheel Clicked | as Center Button |
|             | Keyboard | ESC Key | Fullscreen mode only |
| Exit App    | Keyboard | ESC Key | not Fullscreen mode only |
| Scale Up    | Keyboard | Ten keys(+) | do nothing with Fitting |
| Scale Down  | Keyboard | Ten keys(-) | do nothing with Fitting |
| Fitting     | Keyboard | F12 Key |  |
|             | Keyboard | Ten keys(-) | |
|             | Mouse  | Right Button + Wheel Clicked | |
|             | Mouse  | Ctrl + Wheel Clicked | |
| Zoom in     | Mouse Wheel | Right Button + Upward scrolling | |
|             | Mouse Wheel | Ctrl + Upward scrolling | |
| Zoom out    | Mouse Wheel | Right Button + Downward scrolling | |
|             | Mouse Wheel | Ctrl + Downward scrolling | |

## System Requirement

- Operating System
    - Windows Vista,7 or newer
    - Windows Sever 2008 or newer
    - Running on Ubuntu Linux. but currently no supported because we need more contributers.
- CPU
    - minimum Dual Core(more better with internal GPU or external GPU)
- Memory
    - over 1GB free Memory(strongly recommended on x64 architecture)

## Looking for contributers!

- Spanish Speakers
- French Speakers
- Chinese Speakers
- Mac software engeneers


## Report issues

Please report issues as well as configuration details for your working 
QuickViewer installations at <k.kanryu@gmail.com>

Thus, your feedback is welcome at KATO Kanryu<<k.kanryu@gmail.com>>.


## Project Source Code Repository

https://github.com/kanryu/quickviewer

## License

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

