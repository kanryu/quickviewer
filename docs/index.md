---
layout: default
---

# [](#header-1)QuickViewer

**QuickViewer** is a graphic image viewer for comfortable browsing of many images.

This software performs reading of image data in advance.
And drawing the imported image data on the screen with OpenGL.
You can browse images with much smoother response than ever before.

**QuickViewer** is a free software lisenced under GPLv3.

[in English](https://kanryu.github.io/quickviewer/) / [in Japanese](https://kanryu.github.io/quickviewer/index-ja)

## Summary

 - To show images very fast (using OpenGL)
 - Spread viewing(two images once) supported(for digital books)
 - To read archives directly(zip/7z/rar)
 - To show images(bmp/png/jpeg/dds/webp/ico/tga/tiff/gif)
 - Auto rotation(using JPEG EXIF)
 - To show Raw digital camera images
   - Canon(crw, cr2)
   - Nicon(nef)
   - Sony(arw)
   - Ricoh(dng)
   - etc..


## How to use

1. Launch the application and display the window
1. Select a menu on the main menu which choose a folder from the dialog, or Drag Drop a folder contains image files from Windows Explorer to the window
1. A image loaded on the screen is displayed. Browse the images with the "←" or "→" button on the toolbar, the mouse wheel up/down, the forward button of the mouse, or the left and right edge click of the window

## Download

[Release Builded Binary](https://github.com/kanryu/quickviewer/releases) (Windows x86/x64)

Please clone the latest source code from [this repository.](https://github.com/kanryu/quickviewer)

## External Reviews

- the PORTABLE FREEWARE collection
    - https://www.portablefreeware.com/forums/viewtopic.php?f=4&t=23353
- SOFTPEDIA
    - http://www.softpedia.com/get/Multimedia/Graphic/Graphic-Viewers/QuickViewer.shtml
- FindMySoft
    - http://quickviewer.findmysoft.com
- Free SoftNavie(in Japanese)
    - http://www.softnavi.com/review/graphic_viewer/quickviewer_1.html

Thanks for reviewers! :)

## Functions

### Normal Viewing(One Page View)

![Normal Viewing](https://github.com/kanryu/quickviewer/wiki/images/singleview.jpg)

If **Spread Viewing** is off, the window shows one image.


### Spread Viewing(Two Page View)


![Spread Viewing](https://github.com/kanryu/quickviewer/wiki/images/dualview.jpg)

If **Spread Viewing** is on, the window shows two images on side by side.

### JPEG EXIF Information

![EXIF Information](https://github.com/kanryu/quickviewer/wiki/images/exifdialog.jpg)

It draws JPEG images with auto rotation which contained in EXIF Information.
You can see images as long as taken picture with digital camera.

You can checkout EXIF Information of the current JPEG image which you have taken picture by a digital camera.
Click right button on the image view, to be shown a context menu, select 'Exif Information' menu.

### Checkout the location of the image file

You can checkout with Windows Explorer for the current image file.
Click right button on the image view, to be shown a context menu, select 'Open Explorer' menu.


## Screen operations

You can do screen operations with the main menu, tool bar, mouse button, wheel, keyboard and so on.

| Operation   | Device   | Input   | Remarks |
|:------------|:---------|:--------|:--------|
| Next Page   | Keyboard | Right Key(→) | |
|             | Keyboard | Space Key | |
|             | Mouse Wheel | Downword rotation | |
|             | Mouse    | Forward Button   | |
| Prev Page   | Keyboard | Left Key(←) | |
|             | Keyboard | BackSpace Key | |
|             | Mouse Wheel | Upword rotation | |
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
| Image to trash box   | Keyboard | Delete Key | Move the Image of current page to trash box |
| Copy Image   | Keyboard | Ctrl+C Key | Copy Image of current page |




## System Requirement

- Operating System
    - Windows Vista,7 or newer
    - Windows Sever 2008 or newer
    - Linux Desktops(need to build from source code )
- CPU
    - minimum Dual Core(more better with internal GPU or external GPU)
    - strongly recommended on x64 architecture
- Memory
    - over 1GB free Memory

```
The final element.
```
