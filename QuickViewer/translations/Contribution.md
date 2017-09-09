# Contribution for multilingual

Unless otherwise noted, QuickViewer Developer Team has created it.

The file whose author name is specified is the copyrighted work of the author, but when they contribute to the project, they are deemed to have agreed to be redistributed under the same conditions as the license of this project.

- quickviewer_el.qm
- quickviewer_el.ts
    - written by "geogeo.gr" <geogeo.gr@gmail.com>

- qt_el.qm
    - It is part of the Qt SDK, but since it is not included in the current SDK, it is included in this source tree.
    - http://code.qt.io/cgit/qt/qttranslations.git/commit/?id=44647ef2cd1908279f4a1142b7cbe43caede544d

## How to translate

### Get translation tool

Get a Qt SDK from there. 

- https://www.qt.io/download-open-source/ (official)
- https://goo.gl/3TZjmW (in Windows)
- *apt install qt4-linguist-tools* (in Ubuntu Linux)

### Procedure of work

1. clone the repository into local. https://github.com/kanryu/quickviewer
1. rename 'QuickViewer/translations/quickviewer_es.ts' to yours (e.g. quickviewer_de.ts as German)
1. Open 'quickviewer_de.ts' with Qt Linguist
   usually "[QtSDK]/msvc2015_64/bin/linguist.exe" (on Windows)
1. Translate terms from English to German :)

[File]->[Release] and the quickviewer_de.qm file and language.ini put on "QuickViewer-XXX-x64/translations/"
You can check translations.

Please add in the language.ini as follows.
```
[German]
code=de
caption=German
qm=quickviewer_de.qm
```



You can send 'quickviewer_de.ts' to us as an email attachment or you can send it with the usual GitHub pull request procedure.



