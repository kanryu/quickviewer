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
 - Portable (without installers, registries, external libraries)
 - Spread viewing (two images once, for digital books/comics)
 - To read archives directly (zip/7z/rar/cbr/cbz)
 - To show images (bmp/png/jpeg/dds/webp/ico/tga/tiff/gif)
 - Auto rotation (using JPEG EXIF)
 - To show Raw digital camera images
   - Canon (crw, cr2)
   - Nicon (nef)
   - Sony (arw)
   - Ricoh (dng)
   - etc..
 - Can make/view/search catalog from thousands of your digital books
 - Can search books from auto generated tags

## How to use

1. Launch the application and display the window
1. Select a menu on the main menu which choose a folder from the dialog, or Drag Drop a folder contains image files from Windows Explorer to the window
1. A image loaded on the screen is displayed. Browse the images with the "←" or "→" button on the toolbar, the mouse wheel up/down, the forward button of the mouse, or the left and right edge click of the window

## Download

The latest version is **release_version**.

You can download from **[Release Builded Binary](https://github.com/kanryu/quickviewer/releases)** (Windows x86/x64)

You can also clone the latest source code from **[this repository.](https://github.com/kanryu/quickviewer)**

## External Reviews

- **the PORTABLE FREEWARE collection**
    - [https://www.portablefreeware.com/forums/viewtopic.php?f=4&t=23353](https://www.portablefreeware.com/forums/viewtopic.php?f=4&t=23353)
- **MajorGeeks.com**
    - [http://www.majorgeeks.com/files/details/quickviewer.html](http://www.majorgeeks.com/files/details/quickviewer.html)
- **SOFTPEDIA**
    - [http://www.softpedia.com/get/Multimedia/Graphic/Graphic-Viewers/QuickViewer.shtml](http://www.softpedia.com/get/Multimedia/Graphic/Graphic-Viewers/QuickViewer.shtml)
- **FindMySoft**
    - [http://quickviewer.findmysoft.com](http://quickviewer.findmysoft.com)
- **Download82**
    - [http://www.download82.com/download/windows/quickviewer/](http://www.download82.com/download/windows/quickviewer/)
- **Downloadcrew**
    - [https://downloadcrew.com/article/35266-quickviewer](https://downloadcrew.com/article/35266-quickviewer)
- **Free SoftNavi** (in Japanese)
    - [http://www.softnavi.com/review/graphic_viewer/quickviewer_1.html](http://www.softnavi.com/review/graphic_viewer/quickviewer_1.html)
- **indiriliyo** (in Turkish)
    - [http://www.indiriliyo.com/quickviewer-indir-11274/](http://www.indiriliyo.com/quickviewer-indir-11274/)
- **01net.com telecharger.com**(in French)
    - [http://www.01net.com/telecharger/windows/Multimedia/albmums_et_visionneuses/fiches/140048.html](http://www.01net.com/telecharger/windows/Multimedia/albmums_et_visionneuses/fiches/140048.html)
- **快乐无极** (in Simplified Chinese)
    - [http://www.oyksoft.com/soft/46227.html](http://www.oyksoft.com/soft/46227.html)
- **Download HTML.it** (in Italian)
    - [http://download.html.it/software/quickviewer/](http://download.html.it/software/quickviewer/)


Thanks for reviewers! :)

## Functions

- Folders, Archives(e.g. zip) Navigation
    - Drag Drop a folder/archive icon to the window
    - **Open Image Folder** by menu
    - **History** by menu
    - NextVolume, PrevVolume
        - Folders and archives next to the current open position
- Spread Viewing(left/right 2 images at once)
    - Bound on the right side book(toggled)
    - Always open wide images as one view(toggled)
    - Always open first image as one view(toggled)
- Slide Show
- Page Navigation
    - NextPage, PrevPage
    - FastForward, FastBackward(10 pages at once)
    - FirstPage, LastPage
    - Next only one page, Prev only one page(for **Spread Viewing**)
- Bookmarks
    - Save, Load, Clear
- Catalogs
    - Add, Edit, Delete, Show the thumbnails, Search titles by key-word
    - With the database created in advance from folders and archives, it can show the cover at high speed and search.
    - Catalog generate 'Tags'. each tag as a button which can search easier.
- Image Resize
    - Fitting(to the window, normal)
    - ScaleUp, ScaleOut(25%, 33%, 50%, 75%, 100%, 150%, 200%, 300%, 400%, 800%, one of them)
- Operation on images
    - Copy Image to the clipboard
    - Copy File to the clipboard
    - Move the Image to the Recycle Bin
    - Open the file with Exprorer
    - Show the Exif Information(for JPEG)
    - Auto rotation with Exif(for JPEG)
- Window View Setting
    - Fullscreen
    - Stay On Top
    - Restore Window State on next run
- Shaders(quality of resize)
    - Bilinear interpolation(normal)
    - Bicubic interpolation
    - Lanczos interpolation
    - Nearest Neighbor interpolation
- Keyboard Config Setting

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

### Catalogs

via v0.6.0, QuickViewer can make catalogs for your digital books and comics.
click **ShowCatalog** and drop a folder which contains images

![Manage Catalog](https://github.com/kanryu/quickviewer/wiki/images/manage_catalog.png)

Then you can find your books in the Catalog.
(the sample books from https://comicstore.marvel.com/free-comics)


![Show Catalog](https://github.com/kanryu/quickviewer/wiki/images/show_catalog.png)

The Catalog can contain thousands of your books, but in spite of being instantly listed, you can search by text entry or by clicking on a tag.


The Catalog can also be displayed with the main window.

![Embedded Catalog](https://github.com/kanryu/quickviewer/wiki/images/embedded_catalog.jpg)



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
