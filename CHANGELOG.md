# CHANGELOG

## v0.6.2 (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)

Add notation of shortcut, speedup for catalog, more simple title

- Add notation of shortcut key to each item of main menu
- Add a function to remove (Options) under certain conditions from the
title of the book registered in the catalog
- Speed up thumbnail loading process saved in database
- Accelerated Incremental Search and Display Switching in Catalog Window
- Fix some display phrases

## v0.6.2_pre (Wed May 10 03:32:57 2017 +0900) [9830d72](https://github.com/kanryu/quickviewer/commit/9830d720a6da2aba1bbe72cad43550c9f668834f)

refactoring

- add precompiled header(stdafx.h)
- remove wornings(Remove unnecessary local variables)

- other commits
    - changelog (Tue May 9 02:48:11 2017 +0900) [e618790](https://github.com/kanryu/quickviewer/commit/e6187908bb5a96ad4814719c6453bd6f6df03ba5)

## v0.6.1 (Tue May 9 02:47:33 2017 +0900) [0d8eeb1](https://github.com/kanryu/quickviewer/commit/0d8eeb13ff7d3b2fd01c4ecf6c11a09620771c55)

add inner CatalogWindow, 3 bugfixed
- bug fixed: when to run from other directries, wrong ini files created.
- bug fixed: onle newer catalogs, don't activeted about edit/delete buttons.
- bug fixed: when manual resizing and image is smaller than the window, image was wrong position
- when a catalog executed, make MainWindow activate

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon May 8 17:03:11 2017 +0900) [66e4257](https://github.com/kanryu/quickviewer/commit/66e4257ec77f327a0d75c27c2b16f57197fba28e)

## v0.6.1_pre (Mon May 8 17:01:58 2017 +0900) [0f1d753](https://github.com/kanryu/quickviewer/commit/0f1d75314e78eb1154387cae6b40f8f9243f6fad)

merge QuickCatalog.pro into QuickViewer.pro

- other commits
    - Update index.md (Mon May 8 16:27:07 2017 +0900) [8338cf8](https://github.com/kanryu/quickviewer/commit/8338cf8ac48562d5b24a77db58b0339a2f2ef4f9)
    - Update index.md (Mon May 8 16:24:13 2017 +0900) [e05340f](https://github.com/kanryu/quickviewer/commit/e05340f24cdb9873586fd3c937d74a64334ac64d)
    - changelog (Sun May 7 01:58:16 2017 +0900) [388ed47](https://github.com/kanryu/quickviewer/commit/388ed4707b43110ddb32d9c0857c35c727c0bdb9)

## v0.6.0 (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)

Support Book Catalogs, easy to view thumbnails of frontpage of books and search fast

- to create/view/search 'Catalogs'
- whihc contains the thumbnails of frontpage of Books as icon
- search by title(folder name of volumes)
- change words 'Database' -> 'Catalog'
- change QuickCatalog app to static lib
- hide updateButton/updateAllButton
- MainWindow can open CatalogWindow

## v0.6.0_pre5 (Sat May 6 22:18:57 2017 +0900) [b68ab0b](https://github.com/kanryu/quickviewer/commit/b68ab0bdf2e2651af17a9adc7b23f733cff3b974)

- add icons/catalog.ico
- add mainmenu(CatalogWindow)
- reserved create catalogs on ManageDatabaseDialog
- can drop CatalogWIndow
- can multi drop ManageDatabaseDialog
- bugfixed deleteAllCatalogs

## v0.6.0_pre4 (Sat May 6 18:13:32 2017 +0900) [944097e](https://github.com/kanryu/quickviewer/commit/944097e3a1c94538e0e18e3a45a071f79074b605)

- implement searchCombo
- fast to create Frontpage Thumbnails of Books

## v0.6.0_pre3 (Wed May 3 22:33:06 2017 +0900) [59666fa](https://github.com/kanryu/quickviewer/commit/59666fa8fe2ff967f8a5e035e85f5a7017a4c6fa)

making catalogwindow, managedatabasedialog, databasesettingdialog
- making catalogwindow(volumeList)

- other commits
    -  to create t_files uses workers (Mon May 1 19:46:51 2017 +0900) [67f883a](https://github.com/kanryu/quickviewer/commit/67f883acc8e704b03853165985e4598716917a1a)
    -  initialize of ManageDatabaseDialog (Mon May 1 19:46:51 2017 +0900) [67f883a](https://github.com/kanryu/quickviewer/commit/67f883acc8e704b03853165985e4598716917a1a)

## v0.6.0_pre2 (Mon May 1 18:25:50 2017 +0900) [2d4c75d](https://github.com/kanryu/quickviewer/commit/2d4c75dfa9cd9e7fc84dbdce2ca916e14b3ee51d)

Create/Delete Catalog which can cancel

- other commits
    - changelog (Mon May 1 13:42:34 2017 +0900) [896b2c0](https://github.com/kanryu/quickviewer/commit/896b2c0155ab22e8832892321c42f3345cd8de79)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon May 1 13:40:57 2017 +0900) [994cfb9](https://github.com/kanryu/quickviewer/commit/994cfb9423911c6003be59c72db85a8ea889b13c)

## v0.6.0_pre (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)

parted to new project 'fileloader.pro', new project QuickCatalog

- parted to new project 'fileloader.pro'
- which contains commonly modules to load archives
- new project QuickCatalog
- it provides functions to create/manage Thumbnail Catalogs, and
Catalog Filer

- other commits
    - Update index.md (Tue Apr 25 21:40:12 2017 +0900) [d8829f3](https://github.com/kanryu/quickviewer/commit/d8829f329f146f6996cb2399b50802f08c8170bc)
    - Update index.md (Tue Apr 25 19:48:47 2017 +0900) [082efbd](https://github.com/kanryu/quickviewer/commit/082efbdb9aaae44afdf7005f9fde2d93c8aeba69)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Tue Apr 25 19:43:46 2017 +0900) [2c4daef](https://github.com/kanryu/quickviewer/commit/2c4daef85cfb6a1b6e90d49a33df4568942def1c)
    - max width 1080px (Tue Apr 25 19:43:20 2017 +0900) [53a41cd](https://github.com/kanryu/quickviewer/commit/53a41cdcc82b8fce61206bf8dce86dcbf2f49980)
    - Update index.md (Tue Apr 25 08:13:05 2017 +0900) [43349c9](https://github.com/kanryu/quickviewer/commit/43349c98300d26f1c71ba6e3743ecd5a95c5acd3)
    - changelog (Mon Apr 24 23:40:38 2017 +0900) [3fe835b](https://github.com/kanryu/quickviewer/commit/3fe835b3a77fbb4bc26b362fe6ffeb0616224a65)

## v0.5.6 (Mon Apr 24 23:38:19 2017 +0900) [29dea25](https://github.com/kanryu/quickviewer/commit/29dea252da40d0e7c3760a708dcb540818ed9d71)

improve AutoLoaded, ScaleUp behavior, add a menu

- AutoLoad from Bookmarks
- after this version auto saved to latest bookmarks when to exit the app
- Show ScrollBars when manual ScaleUp on normal/maximize windowFlags
- add menu(OpenProjectWeb)

- other commits
    - Update index.md (Mon Apr 24 18:39:58 2017 +0900) [52b4384](https://github.com/kanryu/quickviewer/commit/52b43840cbd2e5dc7d015db915fa18a5b7223901)
    - Update index.md (Mon Apr 24 18:36:48 2017 +0900) [1311785](https://github.com/kanryu/quickviewer/commit/1311785d6d67f43d9994870c2701c483c0f399a7)
    - Update index.md (Mon Apr 24 16:33:57 2017 +0900) [4a3ce17](https://github.com/kanryu/quickviewer/commit/4a3ce17d4fb4fa9e67fb31bca92d177eddb24065)
    - Update index-ja.md (Mon Apr 24 16:33:19 2017 +0900) [e900072](https://github.com/kanryu/quickviewer/commit/e90007270b93dcdfa22e7b01391d5be2802b5553)
    - Update screen.scss (Mon Apr 24 16:31:35 2017 +0900) [424bc37](https://github.com/kanryu/quickviewer/commit/424bc37a7ae0c08886ec3b171eb96dbdb083bdfa)
    - Update index.md (Mon Apr 24 00:31:33 2017 +0900) [89471b2](https://github.com/kanryu/quickviewer/commit/89471b2872fc667d844e47f990c738cd60dd7266)
    - changelog (Sun Apr 23 17:45:39 2017 +0900) [ba3bf93](https://github.com/kanryu/quickviewer/commit/ba3bf93dd1713838cebc27e94d2f6f0cb4b012fd)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sun Apr 23 17:44:30 2017 +0900) [c1abe1f](https://github.com/kanryu/quickviewer/commit/c1abe1f412cff4a8173a9f7ede08cc6eb481932a)

## v0.5.6_pre (Sun Apr 23 17:42:29 2017 +0900) [7e37d4c](https://github.com/kanryu/quickviewer/commit/7e37d4c802554ac4e88b171cdefe8cd8ee6839eb)

removed QtRAR, add latest unrar

- removed QtRAR, because it needs some changes and bundled unrar is old
- add latest unrar and a simple wrapper(RarExtractor)

- other commits
    - Update index.md (Sun Apr 23 10:24:53 2017 +0900) [20ef220](https://github.com/kanryu/quickviewer/commit/20ef220232222b3702687704c09edd94b81ddf3a)
    - Update index.md (Sun Apr 23 00:29:19 2017 +0900) [8aea2cf](https://github.com/kanryu/quickviewer/commit/8aea2cf625bef02c62e4c222bbfbf96ff0f840ce)
    - Update README.md (Sat Apr 22 11:23:46 2017 +0900) [de8faef](https://github.com/kanryu/quickviewer/commit/de8faef38237dfa8abf0f18e8c51fa3d5dcf2b03)
    - changelog (Sat Apr 22 00:27:37 2017 +0900) [2f13827](https://github.com/kanryu/quickviewer/commit/2f1382746a71b83b7fbd489e8266319a27a6a1df)

## v0.5.5 (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)

speed up for large JPEG, support cbr/cbz, improve ScaleUp/ScaleOut, 2 bug fix

- twice times speed up for loading JPEGs over 4096px
- now can load cbr/cbz format(without support for book database)
- improve behavior ScaleUp/ScaleOut
- bug fix, An error occurred when closing the application after changing Volume
- bug fix, File sharing archive can not be opened

- other commits
    - Update index-ja.md (Fri Apr 21 10:36:51 2017 +0900) [4d143b5](https://github.com/kanryu/quickviewer/commit/4d143b5de771a2e5278595e43dd913d9818c1222)
    - Update index.md (Fri Apr 21 10:35:26 2017 +0900) [221383e](https://github.com/kanryu/quickviewer/commit/221383e3e1478d4451555325afb9369212c545d2)
    - Update README.md (Fri Apr 21 10:32:46 2017 +0900) [2240a28](https://github.com/kanryu/quickviewer/commit/2240a2883fde0cd6e4f326410308cedf922ca624)
    - Update README.md (Fri Apr 21 10:32:27 2017 +0900) [db7e365](https://github.com/kanryu/quickviewer/commit/db7e365b2f5bb90f5050a485ccf1024f6cc8bd1b)
    - Update index.md (Fri Apr 21 04:40:42 2017 +0900) [4faa2bc](https://github.com/kanryu/quickviewer/commit/4faa2bc2c05974c32cdbff9a2a7dbef96f1eda95)
    - Update index.md (Fri Apr 21 03:34:26 2017 +0900) [dd2431a](https://github.com/kanryu/quickviewer/commit/dd2431a2bb41963d8ffce6462bbcd9ceda9b3eba)
    - Update index-ja.md (Fri Apr 21 03:33:38 2017 +0900) [bcbb2a7](https://github.com/kanryu/quickviewer/commit/bcbb2a7b6aeb9e52ccc77f3246248e07905e8c9e)
    - Update index.md (Fri Apr 21 03:31:53 2017 +0900) [19d6f42](https://github.com/kanryu/quickviewer/commit/19d6f4236776da9562a4920dd12b936fd8b72f12)
    - changelog (Thu Apr 20 18:03:54 2017 +0900) [53f4108](https://github.com/kanryu/quickviewer/commit/53f41086b81c0f55f4372658f46b62087565a383)

## v0.5.4 (Thu Apr 20 18:02:38 2017 +0900) [a967ffc](https://github.com/kanryu/quickviewer/commit/a967ffc1c0e3e00cbc330d419d602337acbac093)

add Bookmarks, improve behavior about loading JPEGs

- add Bookmarks(Save/Load/Clear)
- improve behavior about loading JPEGs
- turbojpeg returns -1 when to load some JPEGs(e.g. Photoshop CS5!)
- because it is not real error, so loaded correctly

- other commits
    - changelog (Mon Apr 17 20:22:21 2017 +0900) [697b723](https://github.com/kanryu/quickviewer/commit/697b723ea6717a097cf3875b7106679ef2a932c5)

## v0.5.3 (Mon Apr 17 20:21:35 2017 +0900) [b693e96](https://github.com/kanryu/quickviewer/commit/b693e962c6a3835fff00e8392867a4e416895a51)

improve file sorting/fixed bug

- improve file sorting(Windows caseInsensitive using StrCmpLogicalW())
- fixed bug about StayOnTop(using WinAPI)
- add some Japanese translations

- other commits
    - Update index-ja.md (Mon Apr 17 15:42:50 2017 +0900) [87d0fe0](https://github.com/kanryu/quickviewer/commit/87d0fe010485a38525099200a3e7caced5243b84)
    - Update index.md (Mon Apr 17 15:39:01 2017 +0900) [93743f7](https://github.com/kanryu/quickviewer/commit/93743f7927ced40ccbf5cedffaad68004823f2ae)
    - Update default.html (Mon Apr 17 15:37:55 2017 +0900) [fe0dee9](https://github.com/kanryu/quickviewer/commit/fe0dee9b798c68f1a695434f986c6a64c9f77080)
    - Update index.html (Mon Apr 17 15:20:11 2017 +0900) [7ce4ab0](https://github.com/kanryu/quickviewer/commit/7ce4ab075adea89fdec00cbb030c7fab298803f1)
    - Update index.md (Sun Apr 16 22:43:35 2017 +0900) [b3c7544](https://github.com/kanryu/quickviewer/commit/b3c7544d2b1dcdfb2ed239a413d61814d2ad867b)
    - Update index-ja.md (Sun Apr 16 21:03:51 2017 +0900) [21fc95b](https://github.com/kanryu/quickviewer/commit/21fc95bf12a97f062458c40d0f990d54b9258959)
    - Update index-ja.md (Sun Apr 16 20:54:48 2017 +0900) [63cbae7](https://github.com/kanryu/quickviewer/commit/63cbae7e1da4fccb671ba36a27366a857a3ea562)
    - Update index.md (Sun Apr 16 20:51:37 2017 +0900) [261eab7](https://github.com/kanryu/quickviewer/commit/261eab76f63003e9e820b59c33a741f9224b0a42)
    - Update index.md (Sun Apr 16 20:23:59 2017 +0900) [10a1d46](https://github.com/kanryu/quickviewer/commit/10a1d4605dafc6fecbdf09528a2f7d7924184a8f)
    - Update index-ja.md (Sun Apr 16 20:22:19 2017 +0900) [dc9db22](https://github.com/kanryu/quickviewer/commit/dc9db22116825dbd4f834ca614603faa79adc0d5)
    - Update index.md (Sun Apr 16 20:18:57 2017 +0900) [87e7302](https://github.com/kanryu/quickviewer/commit/87e730221d480af40fdfcb9bc5075a3256ede2dc)
    - Update index-ja.md (Sun Apr 16 20:18:09 2017 +0900) [2adbc5d](https://github.com/kanryu/quickviewer/commit/2adbc5dc96dcb9cdfa41bd55694275c7fb4e3eeb)
    - Update index.md (Sun Apr 16 20:10:56 2017 +0900) [3ee3e03](https://github.com/kanryu/quickviewer/commit/3ee3e03f8f141b6f428b7eb55d7a80980fc45a3d)
    - Update index-ja.md (Sun Apr 16 20:10:37 2017 +0900) [3553363](https://github.com/kanryu/quickviewer/commit/35533630e03f3b39872972589e32f7993c239c85)
    - Update index-ja.md (Sun Apr 16 20:09:19 2017 +0900) [0cc9791](https://github.com/kanryu/quickviewer/commit/0cc9791b429e46a3363cdfa2a70623f6ad3b89bf)
    - Update index-ja.md (Sun Apr 16 20:07:28 2017 +0900) [69a4a46](https://github.com/kanryu/quickviewer/commit/69a4a465027d5e3106ea14aec8e776edc39c922f)
    - Update index-ja.md (Sun Apr 16 19:54:36 2017 +0900) [43ff583](https://github.com/kanryu/quickviewer/commit/43ff5832f8b46568536264382040731a01a96e1b)
    - Update index-ja.md (Sun Apr 16 19:53:49 2017 +0900) [02854bc](https://github.com/kanryu/quickviewer/commit/02854bcd80ffbdecca3e7d3292774034dc5b86f9)
    - Update index.md (Sun Apr 16 19:51:51 2017 +0900) [cb9af00](https://github.com/kanryu/quickviewer/commit/cb9af004d4811c057277f537bd10b98831992c91)
    - changelog (Sun Apr 16 18:24:32 2017 +0900) [2d8db4d](https://github.com/kanryu/quickviewer/commit/2d8db4d77f6cef7684a598277a9b8edab8279f41)

## v0.5.2_rev2 (Sun Apr 16 18:23:21 2017 +0900) [9cc3dc5](https://github.com/kanryu/quickviewer/commit/9cc3dc5ef03cbdd1be3720d18d32068f5d0ccc9c)

add Key Config(Rotate/CopyFile/SlideShow)

- other commits
    - changelog (Sun Apr 16 18:01:44 2017 +0900) [4f0d11d](https://github.com/kanryu/quickviewer/commit/4f0d11d59a79aaab0ec438812ce282fde7094938)
    - changelog (Sun Apr 16 17:59:32 2017 +0900) [cde4f30](https://github.com/kanryu/quickviewer/commit/cde4f300d86673dfd487cb7d1ea660b621a1d903)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sun Apr 16 17:58:55 2017 +0900) [11b60dc](https://github.com/kanryu/quickviewer/commit/11b60dc274ec37054ee132ed2440b0ae5f6a7eb9)

## v0.5.2 (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)

add SlideShow/CopyFile/RotateImage, 2 bug fixed

- add SlideShow/CopyFile/RotateImage
- refactoring(ImageShaderEffect -> ShaderManager)
- bug fixed(last 2 paging)
- bug fixed(open explorer)
- improve(more collect page bar on dualview)

- other commits
    - Update README.md (Fri Apr 14 16:35:43 2017 +0900) [fd8da52](https://github.com/kanryu/quickviewer/commit/fd8da52e1505043f5066b3b5bcd5d70abbab72e4)
    - changelog (Thu Apr 13 21:14:25 2017 +0900) [78d1ecf](https://github.com/kanryu/quickviewer/commit/78d1ecfb4d1b222c7f560fd64f65a556cd5609f3)

## v0.5.1 (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)

Support Shaders, Save Window States, Add FastFoward/Backward

- Support GPU Shaders(NearestNeighbor/Bicubic/Lanczos)
- Save/Restore Window States(Position/Size/WindowStates)
- add FastForward/Backward buttons(fixed by 10 pages)
- Key Config Rules Changed
- Please remove old ini files

- other commits
    - changelog (Wed Apr 12 10:25:42 2017 +0900) [0095c41](https://github.com/kanryu/quickviewer/commit/0095c416faaff71b420e73c608c125563313a73c)

## v0.5.0 (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)

more faster volume changing, refactoring

- add pre loading for volume changing(NextVolume/PrevVolume)
- QuickViewer.pro now can provide distribution package(Windows)
- refactoring
- add PageManager, TimeOrderedCache
- comment outed qDebug()

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Tue Apr 11 09:38:00 2017 +0900) [ed3e260](https://github.com/kanryu/quickviewer/commit/ed3e2607158499ee40bc144628cccad7e97fea83)
    - support deploying, refactoring (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    -  (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    -  support deploying by pro(nolonger deploy.bat needed, run 'jom install') (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    -  refactoring(add PageGraphicsItem) (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    - Update index.md (Tue Apr 11 05:44:01 2017 +0900) [fc91c0b](https://github.com/kanryu/quickviewer/commit/fc91c0b1c8d34d0e093a17b4dd056c231791fe6e)
    - changelog (Mon Apr 10 05:15:19 2017 +0900) [34de18f](https://github.com/kanryu/quickviewer/commit/34de18f33237f6f33c8ca3e2cde9757c2cca13cd)

## v0.4.3 (Mon Apr 10 05:13:47 2017 +0900) [a2ccbe6](https://github.com/kanryu/quickviewer/commit/a2ccbe68558021b1105810cfb2d1f2d1ec158838)

fixed bug, add shortcut newmenus

- fixed bug NextVolume/PageVolume, default key configs were in the opposite direction by mistake
- add shortcut DeletePage/CopyPage
- change words, delete image -> move the image to trash box

- other commits
    - changelog (Mon Apr 10 04:59:05 2017 +0900) [d8477d1](https://github.com/kanryu/quickviewer/commit/d8477d100a36fe1f11cb92b4ac398861ca3a6a47)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon Apr 10 04:57:52 2017 +0900) [ad5e04b](https://github.com/kanryu/quickviewer/commit/ad5e04b3e5865074e065b1f1fa49b03ebba74369)
    - improve PageBar, add CopyImage/DeleteImage (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  improve PageBar(using QStyle::SH_Slider_AbsoluteSetButtons) (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  add CopyImage to clipboard (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  add DeleteImage to trashbox(referred to https://github.com/siliconscholar/sherman/blob/6397a274c704519f8e0b7f628ad0beadde0e1d53/src/win/deleter.cpp) (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    - Create .gitattributes (Sat Apr 8 00:01:41 2017 +0900) [ee555e3](https://github.com/kanryu/quickviewer/commit/ee555e3850fdb99b33f559cf92a8b2d274950dd3)
    - changelog (Fri Apr 7 03:10:57 2017 +0900) [fd3f2f6](https://github.com/kanryu/quickviewer/commit/fd3f2f605f4a977584cf571a57c998b464da5f16)

## v0.4.2 (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)

Build Support on linux, can hide menubar, add 3 menus

- Build Support for linux(tested on Ubuntu 16.02.2)
- fixed a bug, Next only one page
- can hide menubar on windows
- add 3 menus
- ShowMainMenu
- ClearHistory
- StayOnTop

- other commits
    - Linux Builde checked (Thu Apr 6 03:54:05 2017 +0900) [3858a36](https://github.com/kanryu/quickviewer/commit/3858a3655e68c2fd0d96aa5432159914cb37749a)
    - changelog (Wed Apr 5 07:31:42 2017 +0900) [151203d](https://github.com/kanryu/quickviewer/commit/151203ddee158ec03bad4e81ec76b606d15520f5)

## v0.4.1 (Wed Apr 5 07:29:41 2017 +0900) [36d4b39](https://github.com/kanryu/quickviewer/commit/36d4b39c927c3b6ac758885e6bed432213b42cd7)

JPEG/Raw loader plugin updated. 2 menus added

- JPEG/Raw image loader plugin updated. much faster than before(especially on x64)
- add flag to show toolbar
- add flag that always first image is one view

- other commits
    - changelog (Mon Apr 3 22:00:11 2017 +0900) [9777572](https://github.com/kanryu/quickviewer/commit/977757234e442c58676aa57d2f8c119d3147ba6b)

## v0.4.0 (Mon Apr 3 21:57:02 2017 +0900) [20da721](https://github.com/kanryu/quickviewer/commit/20da721fca323590c9aa480fca24249dafa5e3e0)

support Key Configs
- support all actions save/load ini, customized run actions
- add Key Config Dialog

- other commits
    - changelog (Mon Apr 3 03:10:41 2017 +0900) [af12a95](https://github.com/kanryu/quickviewer/commit/af12a95b70ef0e2b0c852859349ec1b1060c64e9)

## v0.3.5 (Mon Apr 3 03:07:26 2017 +0900) [f9ef10e](https://github.com/kanryu/quickviewer/commit/f9ef10ea8854810cf721e1b3b90760c7a4ec18cc)

add NextOnePage/PrevOnePage, fixed Open Explorer

- add NextOnePage/PrevOnePage (to next/prev 1 Page whether if DualView is on)
- fixed Open Explorer(for spaces included file path), use as reference https://github.com/owncloud/client/blob/master/src/gui/openfilemanager.cpp

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon Apr 3 02:07:43 2017 +0900) [e8794ca](https://github.com/kanryu/quickviewer/commit/e8794caafed8e143e664d69ef58e9044ca7e2aee)
    - Update index-ja.md (Sun Apr 2 19:00:47 2017 +0900) [1318e14](https://github.com/kanryu/quickviewer/commit/1318e1402799f7965c59ff38941f175e3ac287dd)
    - Update index.md (Sun Apr 2 18:52:32 2017 +0900) [247b297](https://github.com/kanryu/quickviewer/commit/247b297358589cee7d87eb2fd24d80b912804dae)
    - Update README.md (Sun Apr 2 18:52:09 2017 +0900) [3f2ec39](https://github.com/kanryu/quickviewer/commit/3f2ec39d17bffdfdf10b57df5440ea4a1123defa)
    - changelog (Sun Apr 2 17:53:20 2017 +0900) [77bfc81](https://github.com/kanryu/quickviewer/commit/77bfc81868e9b9e34a2e63b4a8e26df206fec02b)
    - Update index.html (Sat Apr 1 22:17:46 2017 +0900) [668a936](https://github.com/kanryu/quickviewer/commit/668a936f227b0808851532c7fec60b6ed16c305b)
    - Update index.html (Sat Apr 1 22:15:59 2017 +0900) [61ded06](https://github.com/kanryu/quickviewer/commit/61ded06c1381e23e1acccb9404fe145b773b9380)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sun Apr 2 17:53:26 2017 +0900) [8f4876e](https://github.com/kanryu/quickviewer/commit/8f4876ee85163c80e0725a055069ba190dc9f763)
    - changelog (Sun Apr 2 17:53:20 2017 +0900) [a87b92f](https://github.com/kanryu/quickviewer/commit/a87b92f52be3c2252f9104489fbc68f3b444de6c)

## v0.3.4 (Sun Apr 2 17:52:00 2017 +0900) [38bc291](https://github.com/kanryu/quickviewer/commit/38bc2919e7432ab667d065ae5fa095e1ab5cf79f)

Merge branch 'master' of https://github.com/kanryu/quickviewer

support NextVolume/PrevVolume

- PrevPage by BackSpase Key pressed

- other commits
    - Update index.html (Sat Apr 1 22:17:46 2017 +0900) [81a3303](https://github.com/kanryu/quickviewer/commit/81a330386ad2821f4cd3d6bfe27c9a406faf1ea9)
    - Update index.html (Sat Apr 1 22:15:59 2017 +0900) [5724289](https://github.com/kanryu/quickviewer/commit/5724289024e24a17b876658d85ed97de0f0c99e7)
    - Update index.html (Sat Apr 1 22:12:46 2017 +0900) [0d0ea78](https://github.com/kanryu/quickviewer/commit/0d0ea78ef1a97319ec59b48627e304745faf2dd5)
    - check version with JavaScript (Sat Apr 1 22:04:34 2017 +0900) [5e855f7](https://github.com/kanryu/quickviewer/commit/5e855f745df50aa79265335db075284437be1ea3)
    - check version with JavaScript (Sat Apr 1 22:04:34 2017 +0900) [827dce5](https://github.com/kanryu/quickviewer/commit/827dce5e6c1a75805f7a16f58743c4899d4e068e)
    - google analystics config (Sat Apr 1 21:09:32 2017 +0900) [e2f57f2](https://github.com/kanryu/quickviewer/commit/e2f57f27b972d35c80d9e990a6f5d8580619d053)
    - Update index-ja.md (Sat Apr 1 02:10:47 2017 +0900) [7b39fe7](https://github.com/kanryu/quickviewer/commit/7b39fe7e72a7449781555c9257a7043026e9a3df)
    - Update index-ja.md (Sat Apr 1 02:09:23 2017 +0900) [4960a19](https://github.com/kanryu/quickviewer/commit/4960a194c5bd52495432975050aee96196f35f7d)
    - Update index.md (Sat Apr 1 02:07:22 2017 +0900) [86b35d7](https://github.com/kanryu/quickviewer/commit/86b35d7295601de507445c5259e4bc671564163e)
    - Update README.md (Sat Apr 1 02:06:58 2017 +0900) [1f8554a](https://github.com/kanryu/quickviewer/commit/1f8554aba80e2915272ca3335e07ef0dcd987b53)
    - changelog (Sat Apr 1 01:59:25 2017 +0900) [0139667](https://github.com/kanryu/quickviewer/commit/0139667ad5090dff73329f4a386e03cc69462119)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sat Apr 1 01:58:59 2017 +0900) [6a6d0b5](https://github.com/kanryu/quickviewer/commit/6a6d0b5229aaf51b967f65af9702b8574a49df07)

## v0.3.3 (Sat Apr 1 01:57:37 2017 +0900) [8aa44a2](https://github.com/kanryu/quickviewer/commit/8aa44a210cf40c1a1aa4ab5125c3959c4716b352)

support Raw Images, check version

- support Raw Images (Canon/Nicon/Sony/Ricoh/etc..)
- test support for EXIF of Raw images (very rude behavior)
- check version with browser

- other commits
    - Update index.md (Sat Apr 1 01:38:12 2017 +0900) [c260615](https://github.com/kanryu/quickviewer/commit/c260615697f40a60286159732d379b7733eda6c5)
    - Update index.md (Sat Apr 1 01:30:04 2017 +0900) [f0a180f](https://github.com/kanryu/quickviewer/commit/f0a180fc6c0b01efdd4f3187e2c5faa9e5c4e890)
    - Update index.md (Sat Apr 1 01:27:19 2017 +0900) [c2c1966](https://github.com/kanryu/quickviewer/commit/c2c1966a3e12339f29d716186c35e0ea6716d86c)
    - Update index.md (Sat Apr 1 01:25:58 2017 +0900) [0c7cbe7](https://github.com/kanryu/quickviewer/commit/0c7cbe783e65074ecba033b6f408fc2fe8f96603)
    - checkversion script (Sat Apr 1 01:21:50 2017 +0900) [ef673aa](https://github.com/kanryu/quickviewer/commit/ef673aa2f3150b8f8342e2c11b127b072a671cdc)
    - CHANGELOG (Fri Mar 31 06:28:50 2017 +0900) [5ef95b5](https://github.com/kanryu/quickviewer/commit/5ef95b5e047ad7680ba8fa838e4d1df016e276b7)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Fri Mar 31 06:28:17 2017 +0900) [cb7b450](https://github.com/kanryu/quickviewer/commit/cb7b4501030df65048821b669ab071dce7b37aa1)

## v0.3.2 (Fri Mar 31 06:27:49 2017 +0900) [c6ff3be](https://github.com/kanryu/quickviewer/commit/c6ff3be94044612100b06d54fe4bb7f3f0a93406)

fixed when png file dropped

- other commits
    - Update README.md (Fri Mar 31 05:28:30 2017 +0900) [f00c36d](https://github.com/kanryu/quickviewer/commit/f00c36de540508aec55d0797c43e5690dba12854)
    - Update README.md (Fri Mar 31 05:27:16 2017 +0900) [8bd3ccd](https://github.com/kanryu/quickviewer/commit/8bd3ccd9e07a09c73099c56fcae3646da8c1fdc8)
    - Update index-ja.md (Fri Mar 31 05:23:53 2017 +0900) [6f0cc66](https://github.com/kanryu/quickviewer/commit/6f0cc660ff91e15a67d0469b8b63314d1eebbe15)
    - Update index.md (Fri Mar 31 05:20:07 2017 +0900) [9c09be0](https://github.com/kanryu/quickviewer/commit/9c09be0591b8292d4eeb68e69e11e623d6f52432)
    - Update README.md (Fri Mar 31 05:19:21 2017 +0900) [fda1e21](https://github.com/kanryu/quickviewer/commit/fda1e21fd60367747356fb19a325b9153f032b40)
    - Update index.md (Fri Mar 31 05:06:35 2017 +0900) [9f484f3](https://github.com/kanryu/quickviewer/commit/9f484f3c8529c06e9375a830521abe40fd43c857)
    - Update index.md (Fri Mar 31 05:06:15 2017 +0900) [f763498](https://github.com/kanryu/quickviewer/commit/f76349814736a8e6e8ed4cfb7785c80f17f1b393)
    - CHANGELOG (Fri Mar 31 04:37:29 2017 +0900) [283d783](https://github.com/kanryu/quickviewer/commit/283d783a4221deae190328808ebe63f296ff5c42)

## v0.3.1 (Fri Mar 31 03:42:55 2017 +0900) [f1cd515](https://github.com/kanryu/quickviewer/commit/f1cd515820748a241a6036bfe4e9ff60dc37eb8e)

- refactoring
- support RAR archive
- add Key Config Dialog
- improve behavior of changing between normal and fullscreen

- other commits
    - CHANGELOG (Thu Mar 30 14:25:48 2017 +0900) [e9f8189](https://github.com/kanryu/quickviewer/commit/e9f81892e517f505d38951b5405b079fdcd61708)
    - CHANGELOG (Thu Mar 30 14:22:50 2017 +0900) [661a7b1](https://github.com/kanryu/quickviewer/commit/661a7b17fdac7fb78275bfcc6ebd381f1f7054ac)

## v0.3.1_pre2 (Thu Mar 30 14:19:25 2017 +0900) [961b44a](https://github.com/kanryu/quickviewer/commit/961b44adf69a69408732498b0b8dde59831a2343)

refactoring

- remove comments outdated
- followed for version up of ResizeHalf

- other commits
    - Update CHANGELOG.md (Thu Mar 30 05:30:03 2017 +0900) [d348354](https://github.com/kanryu/quickviewer/commit/d348354dd8b1d79cdd9bf5ad02bd94e78d42db27)
    - Update CHANGELOG.md (Thu Mar 30 05:23:40 2017 +0900) [4381c43](https://github.com/kanryu/quickviewer/commit/4381c437506434746dedb8df31d02fa83584539f)

## v0.3.1_pre (Thu Mar 30 05:20:11 2017 +0900) [26b4536](https://github.com/kanryu/quickviewer/commit/26b45365790e108d8313cb52919cb5766945e3fc)

- add keyconfig dialog
- refactoring
- add FileLoader object(supports external plugin)

- other commits
    - Update index.md (Thu Mar 30 03:16:49 2017 +0900) [96a4008](https://github.com/kanryu/quickviewer/commit/96a4008d34fee6203f9457e015ff23d23756fddb)
    - Update index.md (Thu Mar 30 03:16:04 2017 +0900) [cedc13b](https://github.com/kanryu/quickviewer/commit/cedc13bc70e8cf821feb963662946361bb73a509)
    - Update index.md (Thu Mar 30 03:05:39 2017 +0900) [12d8c97](https://github.com/kanryu/quickviewer/commit/12d8c976552e594a897030f5146adc139d40d3c1)
    - Update index.md (Thu Mar 30 03:02:32 2017 +0900) [1b2b76e](https://github.com/kanryu/quickviewer/commit/1b2b76eed4f2d257a2c0fafd6c6466998dfd6d8f)
    - Update index.md (Thu Mar 30 02:57:34 2017 +0900) [3614ab8](https://github.com/kanryu/quickviewer/commit/3614ab8d4e3895fa55e95393cf0a0752788a4e3e)
    - Update README.md (Thu Mar 30 02:57:17 2017 +0900) [f0e5a94](https://github.com/kanryu/quickviewer/commit/f0e5a947c01bdec31069d8301771d4f4d888d37f)
    - Update index.md (Thu Mar 30 02:50:25 2017 +0900) [d782f7b](https://github.com/kanryu/quickviewer/commit/d782f7b1b0dada061efb0b5f1ab8467ceca20f3c)
    - Update index.md (Thu Mar 30 02:46:24 2017 +0900) [1954621](https://github.com/kanryu/quickviewer/commit/195462191a8badc09fe7d464532ed09e6b9de649)
    - Create CHANGELOG.md (Thu Mar 30 00:46:26 2017 +0900) [ff5caa2](https://github.com/kanryu/quickviewer/commit/ff5caa2a4faea8726f82d0481ed52b20099d35f4)
    - Update README.md (Wed Mar 29 00:19:45 2017 +0900) [9f131e7](https://github.com/kanryu/quickviewer/commit/9f131e72cf28b177cc7965768f46297a1b0464ec)
    - Update index.md (Tue Mar 28 23:17:13 2017 +0900) [2b5fb49](https://github.com/kanryu/quickviewer/commit/2b5fb494bf4aa122803d3374b11d334e4ea5863a)
    - Update README.md (Tue Mar 28 23:16:42 2017 +0900) [33a76c5](https://github.com/kanryu/quickviewer/commit/33a76c5666e4f3d315134e4f45bed96d3f8a9473)
    - Update README.md (Tue Mar 28 23:15:00 2017 +0900) [68edbe4](https://github.com/kanryu/quickviewer/commit/68edbe4691e9a62dc19db073e4b85dc15e8cbe4c)
    - Update README.md (Tue Mar 28 23:13:16 2017 +0900) [432c68f](https://github.com/kanryu/quickviewer/commit/432c68fde1e47f02d2a09b98955f703885be1ba8)
    - Update README.md (Tue Mar 28 23:11:05 2017 +0900) [6d86b24](https://github.com/kanryu/quickviewer/commit/6d86b2491d18679e9493af294c073c6332f2e862)
    - google analystic (Tue Mar 28 23:05:50 2017 +0900) [73ecf70](https://github.com/kanryu/quickviewer/commit/73ecf70f3e7ea8ae54b06b26690076ddad996bfb)
    - Update index.md (Tue Mar 28 03:50:40 2017 +0900) [ba14ff8](https://github.com/kanryu/quickviewer/commit/ba14ff8a31bddedc8e1d12b07bb09853a0588e25)
    - Update index.md (Tue Mar 28 03:25:50 2017 +0900) [5734c35](https://github.com/kanryu/quickviewer/commit/5734c35c35ff4e30d3777eff0206e70fab1b64db)
    - Update index-ja.md (Tue Mar 28 03:16:33 2017 +0900) [6b743a9](https://github.com/kanryu/quickviewer/commit/6b743a9be639874ad1b423eddb39a3b412a1e12d)
    - avoid error submodle problem (Tue Mar 28 01:16:32 2017 +0900) [b691ef1](https://github.com/kanryu/quickviewer/commit/b691ef15b38f2ec486adc11bd3d66f7d30c01c77)

## v0.3.0 (Tue Mar 28 00:27:51 2017 +0900) [deea997](https://github.com/kanryu/quickviewer/commit/deea9979e39777bfeaba9e5130b2da809e24b6ca)

- support JPEG EXIF
- support opening explorer(filer) for current image file or archive
- those function are on context menus
- fixed for images which RGBA8888 and not 4 multpiles of width

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon Mar 27 17:28:50 2017 +0900) [2b514bf](https://github.com/kanryu/quickviewer/commit/2b514bfcf96795512aa355c9009c3fb2ed9c1229)

## v0.2.6 (Mon Mar 27 17:25:52 2017 +0900) [c5217cc](https://github.com/kanryu/quickviewer/commit/c5217cc7e5febbae460a585438ff15381812ce7f)

- followed for version up of ResizeHalf
- fixed behavior of knob on page slider
- fixed paging as Spread Viewing

- other commits
    - Update README.md (Mon Mar 27 06:55:32 2017 +0900) [4c27474](https://github.com/kanryu/quickviewer/commit/4c27474ce32a8f117e64a82b572190160bf649a9)
    - Update README.md (Mon Mar 27 06:52:42 2017 +0900) [ec1151d](https://github.com/kanryu/quickviewer/commit/ec1151df295dfed8aaae748e1b22a0f934b635a6)

## v0.2.5 (Mon Mar 27 06:38:26 2017 +0900) [f54ba2a](https://github.com/kanryu/quickviewer/commit/f54ba2a2f0c77b92e53f46c1436247f9bce4dae1)

- supported about big images over 4096px, which are auto half-resized with using ResizeHalf
- improved pre-load mechanism
- fixed page counter with Spread Viewing

## v0.2.4 (Sun Mar 26 16:15:53 2017 +0900) [2ca08a2](https://github.com/kanryu/quickviewer/commit/2ca08a230000aef01144fc5c4788ed0475bb690b)

- fixed heap freeing error with directory paging
- add statusbar
- to show filename, image size to WindowTitle or statusbar

## v0.2.3 (Sat Mar 25 21:50:07 2017 +0900) [8f01a93](https://github.com/kanryu/quickviewer/commit/8f01a9343f3bd01a6199817ca7915d35968d11cd)

fixed pre load cache algorithm

## v0.2.2 (Sat Mar 25 20:03:47 2017 +0900) [a37f5b0](https://github.com/kanryu/quickviewer/commit/a37f5b0d4fba528646a0abc5c9adbb90e27cd4e4)

0.2.2

- other commits
    -  add FirstPage/LastPage on toolbar, and keyboard shortcuts (Sat Mar 25 17:51:55 2017 +0900) [be87ef9](https://github.com/kanryu/quickviewer/commit/be87ef956ccf8374c86816dff7c2847ac643254f)
    -  fixed some menu phrases (Sat Mar 25 17:51:55 2017 +0900) [be87ef9](https://github.com/kanryu/quickviewer/commit/be87ef956ccf8374c86816dff7c2847ac643254f)
    -  Fullscreen toggled when Enter Key Pressed (Sat Mar 25 17:51:55 2017 +0900) [be87ef9](https://github.com/kanryu/quickviewer/commit/be87ef956ccf8374c86816dff7c2847ac643254f)

## v0.2.1 (Sat Mar 25 16:20:14 2017 +0900) [51cfb6e](https://github.com/kanryu/quickviewer/commit/51cfb6ef9fddfe742c141b42d91abfe4a69a8314)

- fixed pre loading
- fixed open file dialog
- fixed for empty image folder

- other commits
    - Update index.md (Fri Mar 24 20:47:32 2017 +0900) [1739d99](https://github.com/kanryu/quickviewer/commit/1739d9913c1915c723e6d1efa02b5c9e5e89608a)
    - Update index.md (Fri Mar 24 20:46:06 2017 +0900) [3667fca](https://github.com/kanryu/quickviewer/commit/3667fca88661a534dab21a0fdf6a16e6251d25ac)
    - Update index-ja.md (Fri Mar 24 20:44:40 2017 +0900) [d5e53b1](https://github.com/kanryu/quickviewer/commit/d5e53b1bb5fdcdd55dc339245ec7d5b02563035d)
    - Update index.md (Fri Mar 24 20:43:43 2017 +0900) [83f3868](https://github.com/kanryu/quickviewer/commit/83f3868096714c84cbdb7748813eaafe35823ba9)
    - project page(japanese) (Fri Mar 24 20:33:13 2017 +0900) [9ea8612](https://github.com/kanryu/quickviewer/commit/9ea8612c7278ffc034fe14dddb57dee9e3760ff5)
    - README (Fri Mar 24 15:50:18 2017 +0900) [3716ce4](https://github.com/kanryu/quickviewer/commit/3716ce4d9382fbf682012203dc78c1ef40cb936e)
    - Update default.html (Thu Mar 23 23:13:05 2017 +0900) [8241556](https://github.com/kanryu/quickviewer/commit/824155673c41945c905ef66bece52bb3b8be4056)
    - Update _config.yml (Thu Mar 23 23:09:16 2017 +0900) [d1bb67d](https://github.com/kanryu/quickviewer/commit/d1bb67df106dd99cbe0a5ffabddeeeceb54957b8)
    - Update index.md (Thu Mar 23 23:08:02 2017 +0900) [9ed379d](https://github.com/kanryu/quickviewer/commit/9ed379dd13e0647af1db54b6a1e481b9ff425f7f)
    - Update index.md (Thu Mar 23 22:51:12 2017 +0900) [bb2dd06](https://github.com/kanryu/quickviewer/commit/bb2dd06f26a72232f8f706d34f4ddbe425e7fd91)
    - Update index.md (Thu Mar 23 22:49:38 2017 +0900) [8ed9207](https://github.com/kanryu/quickviewer/commit/8ed920760baf64cf43f5ca7ccb31c8e8d3e6ff09)
    - index (Thu Mar 23 22:47:16 2017 +0900) [3315ba4](https://github.com/kanryu/quickviewer/commit/3315ba48c9418da19f0f2272df25a81dfecbb6c3)
    - index (Thu Mar 23 22:42:34 2017 +0900) [1830ae3](https://github.com/kanryu/quickviewer/commit/1830ae3f76a9b914eba36d56c76981aa028134bd)
    - index (Thu Mar 23 22:28:15 2017 +0900) [bc41b31](https://github.com/kanryu/quickviewer/commit/bc41b31235f14a8ec9fe3ed72821e172d3343e67)
    - index (Thu Mar 23 22:19:28 2017 +0900) [b80b5b0](https://github.com/kanryu/quickviewer/commit/b80b5b054a687a6855a006254dd0723f65555391)
    - project web page (Thu Mar 23 21:58:57 2017 +0900) [3c29e76](https://github.com/kanryu/quickviewer/commit/3c29e769aef6489e14be72f289301c61887de444)

## v0.2.0 (Thu Mar 23 17:41:34 2017 +0900) [946e367](https://github.com/kanryu/quickviewer/commit/946e367cc058051479d4ff15ac255a2b2a7ee069)

fixed bug about archive pre loading

- other commits
    - README (Thu Mar 23 17:15:32 2017 +0900) [8e3cdd6](https://github.com/kanryu/quickviewer/commit/8e3cdd667958c2c1977d98ebb4264313ecfd6d63)
    - implements a feature about page pre loading (Thu Mar 23 17:13:52 2017 +0900) [d8fe6cd](https://github.com/kanryu/quickviewer/commit/d8fe6cd5534d2ea87d720bb42f3b67ec9a02db19)

## v0.1.10 (Thu Mar 23 17:02:37 2017 +0900) [78692c6](https://github.com/kanryu/quickviewer/commit/78692c681c36856033d26a8b438f606b2e40cac9)

- add a menu which open a image folder
- to show "NOT IMAGE" which the page is not a valid image file
- add a menu "always open wide image as one view"
- fixed a bug which there is page number wrong when one page viewing

## v_0.1.9 (Wed Mar 22 15:11:22 2017 +0900) [45f44d8](https://github.com/kanryu/quickviewer/commit/45f44d8f9e055c5cae556037cbc2b402f9c9d975)

can open image with dropping directly && can open image when dropped to app-icon on explorer

## v_0.1.8 (Tue Mar 21 19:23:33 2017 +0900) [0c4b311](https://github.com/kanryu/quickviewer/commit/0c4b3119478dd5f51f360fdfde51ef423d184d54)

refactoring, event handler fix, dual view pageing fix

- other commits
    - release url (Mon Mar 20 22:42:34 2017 +0900) [4a95280](https://github.com/kanryu/quickviewer/commit/4a952800d45a566b6dcb476c77c8ba4283e34fc9)

## v_0.1.7 (Mon Mar 20 22:35:48 2017 +0900) [227f3b0](https://github.com/kanryu/quickviewer/commit/227f3b01c1588f9d5be1883c3b465e525394740c)

i18n between English and Japanese

- other commits
    - url (Mon Mar 20 21:07:54 2017 +0900) [7447649](https://github.com/kanryu/quickviewer/commit/74476497f954c09c059c2bed5c0a33a59811dbe3)
    - add images (Mon Mar 20 21:06:43 2017 +0900) [7eb7d08](https://github.com/kanryu/quickviewer/commit/7eb7d08c5182228323362ade9d0942a499e7062a)
    - README (Mon Mar 20 20:52:37 2017 +0900) [77bff1a](https://github.com/kanryu/quickviewer/commit/77bff1a08544f6db5825d0fa948a7aa85291ff61)
    - initial version (Mon Mar 20 20:31:18 2017 +0900) [a5e2d86](https://github.com/kanryu/quickviewer/commit/a5e2d860b48060c1088e32241f691aa89d68291c)

## v_0.1.0 (Mon Mar 20 20:20:42 2017 +0900) [cf7a533](https://github.com/kanryu/quickviewer/commit/cf7a533b634deb04eeff4036958bc934215920c9)

Initial commit
