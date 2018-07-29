# CHANGELOG

## v1.1.1 (Sun Jul 29 19:43:34 2018 +0900) [c9aff29](https://github.com/kanryu/quickviewer/commit/c9aff291ba364c7a8a6e155374342f8fcf6cf5be)

- Show Actions By Group on KeyConfig / MouseConfig
- 'Lanczos 4 interpolation by CPU' became the original performance
- add a menu 'Hide the mouse cursor on fullscreen'
- When each dialog is displayed, the toggle of the closing button is enabled
- use specific action roles instead of text heuristic roles
- pull request by @pazos
- Use standard CFBundleName without version
- pull request by @pazos
- hide menubar icons on mac
- pull request by @pazos
- fix for file chooser filter
- pull request by @pazos

- other commits
    - add a menu 'Hide the mouse cursor on fullscreen' (Sun Jul 29 19:04:08 2018 +0900) [2e07721](https://github.com/kanryu/quickviewer/commit/2e07721207d84b9dcb5b28c5b9f94ec601434726)
    - When each dialog is displayed, the toggle of the closing button is enabled (Sun Jul 29 17:40:52 2018 +0900) [110c88d](https://github.com/kanryu/quickviewer/commit/110c88d94c975662897bdf59c215847ba647474b)
    - Merge pull request #86 from pazos/mac (Thu Jul 26 09:58:43 2018 +0900) [fb24915](https://github.com/kanryu/quickviewer/commit/fb24915ffd0b332662c63e91ae72c3a5a230f5af)
    -  (Thu Jul 26 09:58:43 2018 +0900) [fb24915](https://github.com/kanryu/quickviewer/commit/fb24915ffd0b332662c63e91ae72c3a5a230f5af)
    - use specific action roles instead of text heuristic roles (Thu Jul 26 09:58:43 2018 +0900) [fb24915](https://github.com/kanryu/quickviewer/commit/fb24915ffd0b332662c63e91ae72c3a5a230f5af)
    - use specific action roles instead of text heuristic roles (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    -  (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    - by default Qt on mac tries to populate the 'native' application menu with - at least - (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    - the action for preferences, and the action for quit. It also tries to find the 'about' and 'aboutQt' (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    - actions - if any. (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    -  (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    - Those text heuristics can clash on some circunstances e.g: having 2 or more actions called SettingsSomething, (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    -  or even worst - having 2 or more action named with different names but with the same translation string. (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    -  (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    - This commit replaces the default TextHeuristicMenuRole by specific common actions. (about, quit, preferences, keyboard & mouse preferences..) (Thu Jul 26 01:29:54 2018 +0200) [880a65f](https://github.com/kanryu/quickviewer/commit/880a65f382c96569d28f0c2f2cfb23f8ebf4f7e9)
    - Merge pull request #83 from pazos/mac_cosmetic_fixes (Wed Jul 25 09:14:54 2018 +0900) [29e78b7](https://github.com/kanryu/quickviewer/commit/29e78b70d6f84effc5397b312741cc1a098acb9b)
    -  (Wed Jul 25 09:14:54 2018 +0900) [29e78b7](https://github.com/kanryu/quickviewer/commit/29e78b70d6f84effc5397b312741cc1a098acb9b)
    - Mac cosmetic fixes (Wed Jul 25 09:14:54 2018 +0900) [29e78b7](https://github.com/kanryu/quickviewer/commit/29e78b70d6f84effc5397b312741cc1a098acb9b)
    - Merge pull request #82 from pazos/filechooser_fix_mac (Tue Jul 24 16:37:40 2018 +0900) [ea8e0d3](https://github.com/kanryu/quickviewer/commit/ea8e0d30b835dae1e5312dbc2543af06d2216fb8)
    -  (Tue Jul 24 16:37:40 2018 +0900) [ea8e0d3](https://github.com/kanryu/quickviewer/commit/ea8e0d30b835dae1e5312dbc2543af06d2216fb8)
    - fix for file chooser filter (Tue Jul 24 16:37:40 2018 +0900) [ea8e0d3](https://github.com/kanryu/quickviewer/commit/ea8e0d30b835dae1e5312dbc2543af06d2216fb8)
    - Use standard CFBundleName without version (Tue Jul 24 04:12:45 2018 +0200) [e83f54e](https://github.com/kanryu/quickviewer/commit/e83f54e68f9af8bdedf3e6b7b3f41046797566fb)
    - hide menubar icons on mac (Tue Jul 24 04:12:16 2018 +0200) [d3184bd](https://github.com/kanryu/quickviewer/commit/d3184bd0c41868b2aa43b2ed379042b3cc2c0223)
    - fix for file chooser filter (Tue Jul 24 03:01:43 2018 +0200) [6e7a804](https://github.com/kanryu/quickviewer/commit/6e7a804eda12058275e3adc083a21e75b1ad88d0)
    - Update README.md (Thu Jul 5 15:17:17 2018 +0900) [fcd19a2](https://github.com/kanryu/quickviewer/commit/fcd19a2c2e725f0c4e7da59fd06e936efc02019d)
    - Update index-ja.md (Fri Jun 15 17:16:18 2018 +0900) [748834e](https://github.com/kanryu/quickviewer/commit/748834e8ad63446657dde54630f3942acd682ff0)
    - Update index.md (Fri Jun 15 17:15:37 2018 +0900) [d4cc5de](https://github.com/kanryu/quickviewer/commit/d4cc5de4747b9f23a2edaa8f3e89022a855ca88a)
    - Update README.md (Fri Jun 15 17:14:22 2018 +0900) [1428104](https://github.com/kanryu/quickviewer/commit/1428104adb49f9012f443f636de040c6046509f8)
    - add support for Mac (Fri Jun 15 17:06:27 2018 +0900) [014e858](https://github.com/kanryu/quickviewer/commit/014e858788b8850d088692a665d499240892f77a)
    - Update index.md (Fri May 25 23:17:20 2018 +0900) [0a4fe4e](https://github.com/kanryu/quickviewer/commit/0a4fe4e936436094350509fa0f4e97854ddda9d5)
    - Update index.md (Fri May 25 23:16:55 2018 +0900) [6574256](https://github.com/kanryu/quickviewer/commit/6574256b5bb7e5a6004babeb22896c9ef704cb0c)
    - Update index.md (Fri May 25 23:16:31 2018 +0900) [51af2d1](https://github.com/kanryu/quickviewer/commit/51af2d1bc492ef32ef64433d4c2b51b63eb61b1c)
    - Update index-ja.md (Fri May 25 23:15:36 2018 +0900) [10dc703](https://github.com/kanryu/quickviewer/commit/10dc703b1e72d6a7f4e80bc43f516b01d5cd2bc8)
    - Update index-ja.md (Mon May 14 21:48:07 2018 +0900) [cc6998d](https://github.com/kanryu/quickviewer/commit/cc6998d66c2cfa52a7a5e762b04949a0e4c33539)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sat Apr 7 19:29:04 2018 +0900) [dfd8a13](https://github.com/kanryu/quickviewer/commit/dfd8a13f2a0ebc7bff4573783a8397d501c0a5a8)
    -  start to implement for FileOperators (Sat Apr 7 19:28:48 2018 +0900) [019a8ed](https://github.com/kanryu/quickviewer/commit/019a8ed88be3f4a3ae0778e446229d764c37b3dc)
    -  bugfixed: image dropped when the window is maximized in Windows (Sat Apr 7 19:28:48 2018 +0900) [019a8ed](https://github.com/kanryu/quickviewer/commit/019a8ed88be3f4a3ae0778e446229d764c37b3dc)
    -  bugfixed: crushed when to change dir on FolderWindow (Sat Apr 7 19:28:48 2018 +0900) [019a8ed](https://github.com/kanryu/quickviewer/commit/019a8ed88be3f4a3ae0778e446229d764c37b3dc)
    -  Show Actions By Group on KeyConfig / MouseConfig (Sat Apr 7 19:24:25 2018 +0900) [ba27455](https://github.com/kanryu/quickviewer/commit/ba27455f510faa679ef3eb736c8d3ede7f21264a)
    - Update index-ja.md (Tue Apr 3 19:44:45 2018 +0900) [f9fd541](https://github.com/kanryu/quickviewer/commit/f9fd541f3ce6146a781aa7e22d3a2d296a9e7adb)
    - fixed problem for opening images as relative path(Linux, rev2) (Thu Mar 29 22:20:18 2018 +0900) [6a17f67](https://github.com/kanryu/quickviewer/commit/6a17f678cdf87bc2ad161a6f813ae5314519d017)
    - Update index.md (Sun Mar 18 00:11:12 2018 +0900) [92aace8](https://github.com/kanryu/quickviewer/commit/92aace8c10810cfa21e47429fa7b3d4b9413a4ed)
    - Update index.md (Sun Mar 18 00:05:40 2018 +0900) [913a194](https://github.com/kanryu/quickviewer/commit/913a1942dc2e6874ebd6f2d201a8a7eeae6e24a3)
    - Update README.md (Tue Mar 13 22:48:35 2018 +0900) [173a3b9](https://github.com/kanryu/quickviewer/commit/173a3b91a8794efd6ac28eff3d2c6230b07662ec)
    - Update index-ja.md (Tue Mar 13 22:47:29 2018 +0900) [05129e1](https://github.com/kanryu/quickviewer/commit/05129e1cf5876b4eda650b6b402f7babee66f091)
    - Update index.md (Tue Mar 13 22:46:24 2018 +0900) [1bf3f0e](https://github.com/kanryu/quickviewer/commit/1bf3f0e5653b4d1a970cc2e9c9f8ea838b1efac2)
    - changelog (Tue Mar 13 22:40:42 2018 +0900) [6a0630b](https://github.com/kanryu/quickviewer/commit/6a0630b65b11fdb73f587de5064bad9cc18e6356)

## v1.1.0 (Tue Mar 13 22:40:08 2018 +0900) [2a7ef9a](https://github.com/kanryu/quickviewer/commit/2a7ef9ac2ed79a4b3443f9840819b7a860ebfd0d)

add plguins for JPEG-XR/DDS/JPEG 2000, add options for Folder/Catalog views

- add plguins for JPEG-XR/DDS/JPEG 2000
- add option for saving progress.ini
- add option for save width of Folder/Catalog views
- add option to start app with Folder/Catalog view

- other commits
    - Update index.md (Sat Feb 24 14:30:42 2018 +0900) [87b3b6b](https://github.com/kanryu/quickviewer/commit/87b3b6b2e23c7f8523ae30bf1e88575689f9deb8)
    - Update index.md (Thu Feb 1 11:50:31 2018 +0900) [5557acf](https://github.com/kanryu/quickviewer/commit/5557acfdacdf517c9c401e9b240c99b9bcde6af3)
    - Update README.md (Thu Feb 1 11:49:48 2018 +0900) [bc5bc24](https://github.com/kanryu/quickviewer/commit/bc5bc24943fbe77453c2d2fe55c1f0ccb4f8afc4)
    - support for linux. but currently cannot make AppImage (Sat Jan 27 02:08:44 2018 +0900) [d4cb3c1](https://github.com/kanryu/quickviewer/commit/d4cb3c10a4ef6d470545b85ff3a1a188856947d3)
    - add QVproject.pri (forgotten ...) (Sat Jan 27 00:47:03 2018 +0900) [21f32b5](https://github.com/kanryu/quickviewer/commit/21f32b59cafd35f4d81ace756e3afc7827d8d017)
    - Update index-ja.md (Fri Jan 26 15:08:07 2018 +0900) [dd43d72](https://github.com/kanryu/quickviewer/commit/dd43d72cfc4fcbd00a46baff2921be12f74fb0e4)
    - Update index.md (Fri Jan 26 15:07:25 2018 +0900) [8fa7726](https://github.com/kanryu/quickviewer/commit/8fa7726e572d05d1e8cc7c44fbd463a1effde2dc)
    - Update index.md (Fri Jan 26 15:05:18 2018 +0900) [5f71a51](https://github.com/kanryu/quickviewer/commit/5f71a51a9ca5f48ccb4120c49c3b8aea53611934)
    - Update index-ja.md (Thu Jan 18 20:34:34 2018 +0900) [4b2eeb1](https://github.com/kanryu/quickviewer/commit/4b2eeb10e754c06d95080314a25265eec1f0cb83)
    - Update index.md (Thu Jan 18 20:31:26 2018 +0900) [3f93405](https://github.com/kanryu/quickviewer/commit/3f93405fcb877456908fbff2ae8467bc6f681499)
    - Update README.md (Thu Jan 18 20:29:23 2018 +0900) [6981821](https://github.com/kanryu/quickviewer/commit/69818211953c78ed42dbc1a213cdc15a14eb259b)
    - Update README.md (Thu Jan 18 20:27:16 2018 +0900) [a73b12e](https://github.com/kanryu/quickviewer/commit/a73b12e193816fc7979fdeb896324e0d390f6d9b)
    - bugfixed: Pressing the Rotate button when the image is not loaded will end the Frame (Wed Jan 17 13:39:47 2018 +0900) [c88898d](https://github.com/kanryu/quickviewer/commit/c88898de8beb640372365554a54444b2f7474155)
    - changelog (Mon Jan 15 20:05:26 2018 +0900) [cd11e39](https://github.com/kanryu/quickviewer/commit/cd11e3968f70184e20532c85dff6275c357e8f43)

## v1.0.9 (Mon Jan 15 20:04:38 2018 +0900) [74286a8](https://github.com/kanryu/quickviewer/commit/74286a8452620b9e3750e754e9c469ff88ae0438)

add Next page or volume
add Prev page or volume

- other commits
    - abolished 'CPU Bicubic after GPU Bilinear' (Mon Jan 15 18:40:10 2018 +0900) [d3adbb2](https://github.com/kanryu/quickviewer/commit/d3adbb229fc6431bb94af11e39ab28e6c7f2910a)
    - fixed for luminor() (Mon Jan 15 18:40:10 2018 +0900) [d3adbb2](https://github.com/kanryu/quickviewer/commit/d3adbb229fc6431bb94af11e39ab28e6c7f2910a)
    - add lanczos4 (Sun Jan 14 20:29:41 2018 +0900) [69ad771](https://github.com/kanryu/quickviewer/commit/69ad771a1134ac613759ad48a49776a2fab46342)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sat Jan 13 21:06:32 2018 +0900) [0ec56be](https://github.com/kanryu/quickviewer/commit/0ec56be8f2a93404c79a4485c5e2f36303ac51ff)
    - add Shaders about Spline16/Spline36/Lanczos by CPU (Sat Jan 13 21:06:12 2018 +0900) [e22f9b2](https://github.com/kanryu/quickviewer/commit/e22f9b21178ff6a801d71f18a1be366bb58a517e)
    - Update index-ja.md (Sat Jan 13 15:48:30 2018 +0900) [3737a98](https://github.com/kanryu/quickviewer/commit/3737a984d8fa856d9bd499a1a14536f5777b9f31)
    - Update index.md (Sat Jan 13 15:44:44 2018 +0900) [d356a66](https://github.com/kanryu/quickviewer/commit/d356a660f7b8ceb1c13b830d223727eb593cac41)
    - Update README.md (Sat Jan 13 15:43:35 2018 +0900) [5d6a42d](https://github.com/kanryu/quickviewer/commit/5d6a42d69f41f56517c98f1e60aad53771f609b1)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Thu Jan 11 19:17:08 2018 +0900) [ef0fc34](https://github.com/kanryu/quickviewer/commit/ef0fc34e53c8803a96ee5a9aff3aa1069ce05ea9)
    - luminor_rgba supports interlieved bitmaps(RGBA, RGBA...) (Thu Jan 11 19:16:40 2018 +0900) [c2caf59](https://github.com/kanryu/quickviewer/commit/c2caf598f5f1ddc0cce0740a3a80e32ad60aebb4)
    - Update README.md (Wed Jan 10 13:43:26 2018 +0900) [35ac66b](https://github.com/kanryu/quickviewer/commit/35ac66bdc26b54e2290bb9630ed853215875c740)
    - changelog (Tue Jan 9 01:50:34 2018 +0900) [364ccba](https://github.com/kanryu/quickviewer/commit/364ccbad4f09fb01cade7f03badd822bab8bc696)

## v1.0.8 (Tue Jan 9 01:48:10 2018 +0900) [a5a090a](https://github.com/kanryu/quickviewer/commit/a5a090ab59fdb80226820e0257f2bc1299aa04ee)

add a dialog for change brightness/contrast/gamma

- other commits
    - support for changing the brightness, contrast, or gamma value for the images (Sun Jan 7 15:00:00 2018 +0900) [eafaf10](https://github.com/kanryu/quickviewer/commit/eafaf10c832bc3c380babe3370ca907bfdd3f564)
    - bugfixed: The longer the display sample of Window Title Format becomes, the collapsed design (Sun Dec 17 22:49:36 2017 +0900) [ab75f07](https://github.com/kanryu/quickviewer/commit/ab75f079b99f40f1027dbc1147b0e3f0d16c80e9)
    - changelog (Sun Dec 17 10:07:37 2017 +0900) [859f98b](https://github.com/kanryu/quickviewer/commit/859f98bb4735a97166891c71ffdc4d01dc50b014)
    - changelog (Sun Dec 17 10:05:49 2017 +0900) [d56cbb7](https://github.com/kanryu/quickviewer/commit/d56cbb78da351019b841c5c7958c710f12fbc523)

## v1.0.7 (Sun Dec 17 10:04:40 2017 +0900) [e6e49c7](https://github.com/kanryu/quickviewer/commit/e6e49c7938f768512986ee3f4127a63b7944938a)

(rev2) bugfixed: Fitting was not working properly

## v1.0.7rev0 (Sat Dec 16 21:58:02 2017 +0900) [798d9d7](https://github.com/kanryu/quickviewer/commit/798d9d780c9cd3c7d571e00323e1be420bfe3889)

- the order of volumes should be in order of 1.folder 2.archives
- add flag hide tool bars parmanently
- add flag hide tool bars in full screen
- divided the switching between Fitting and Fitting mode into different flags
- bugfixed: crash on deleting image on a folder
- bugfixed: The position of the window was not saved when exiting the application from the menu

- other commits
    - the order of volumes should be in order of 1.folder 2.archives (Sat Dec 16 21:22:26 2017 +0900) [ef9f113](https://github.com/kanryu/quickviewer/commit/ef9f1138024d46e4bd3442991ba18e7c01bc30fa)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sat Dec 16 21:18:18 2017 +0900) [438f4b7](https://github.com/kanryu/quickviewer/commit/438f4b7ae684460c893c47fd45e9983e75e05413)
    - add flag hide tool bars parmanently (Sat Dec 16 20:57:51 2017 +0900) [b825dff](https://github.com/kanryu/quickviewer/commit/b825dffb67a6df2031b7b8ef114cffb1a013d2eb)
    - add flag hide tool bars in full screen (Sat Dec 16 20:57:51 2017 +0900) [b825dff](https://github.com/kanryu/quickviewer/commit/b825dffb67a6df2031b7b8ef114cffb1a013d2eb)
    - add flag hide tool bars parmanently (Sat Dec 16 20:57:51 2017 +0900) [55f18a1](https://github.com/kanryu/quickviewer/commit/55f18a104d2f2db164f07cde26b85b255a9fdbb9)
    - add flag hide tool bars in full screen (Sat Dec 16 20:57:51 2017 +0900) [55f18a1](https://github.com/kanryu/quickviewer/commit/55f18a104d2f2db164f07cde26b85b255a9fdbb9)
    - divided the switching between Fitting and Fitting mode into different flags (Sat Dec 16 19:57:33 2017 +0900) [7cd19a0](https://github.com/kanryu/quickviewer/commit/7cd19a0eb1ade6c0e8568690c5ede0d3d55bd5c0)
    - bugfixed: crash on deleting image on a folder (Sat Dec 16 18:55:00 2017 +0900) [7d1274b](https://github.com/kanryu/quickviewer/commit/7d1274bf8df8afeff85483312143bdd84f2dadf4)
    - bugfixed: The position of the window was not saved when exiting the application from the menu (Fri Dec 15 00:17:38 2017 +0900) [6103334](https://github.com/kanryu/quickviewer/commit/61033344095c27dd2c6861e32375ebcb291610a6)
    - Update index-ja.md (Wed Dec 13 10:06:23 2017 +0900) [9011b6d](https://github.com/kanryu/quickviewer/commit/9011b6d7eb7208066ceeb90265aa73b5456e91c4)
    - Update index.md (Wed Dec 13 10:05:39 2017 +0900) [66c6141](https://github.com/kanryu/quickviewer/commit/66c6141f073824838bb739916d73076ff92024df)
    - Update README.md (Wed Dec 13 10:05:09 2017 +0900) [2180a1a](https://github.com/kanryu/quickviewer/commit/2180a1a3ca617cdfef1f74cd27bb10aaf874db7c)
    - Update README.md (Sat Dec 2 10:22:12 2017 +0900) [e6223be](https://github.com/kanryu/quickviewer/commit/e6223be9e11d940a09f29053253e69e1e601ccc8)
    - Update README.md (Mon Nov 27 16:24:16 2017 +0900) [ed24c31](https://github.com/kanryu/quickviewer/commit/ed24c312eb741219a66bb13954dd22c6905eb589)
    - Merge pull request #54 from gitter-badger/gitter-badge (Mon Nov 27 16:23:08 2017 +0900) [2f276a5](https://github.com/kanryu/quickviewer/commit/2f276a592d91c6a62229321c836a33ee3430c126)
    -  (Mon Nov 27 16:23:08 2017 +0900) [2f276a5](https://github.com/kanryu/quickviewer/commit/2f276a592d91c6a62229321c836a33ee3430c126)
    - Add a Gitter chat badge to README.md (Mon Nov 27 16:23:08 2017 +0900) [2f276a5](https://github.com/kanryu/quickviewer/commit/2f276a592d91c6a62229321c836a33ee3430c126)
    - Update README.md (Mon Nov 27 16:09:18 2017 +0900) [f3973dd](https://github.com/kanryu/quickviewer/commit/f3973ddaac05ff4a4477e4b99756dee816f237f6)
    - Add Gitter badge (Mon Nov 27 06:55:29 2017 +0000) [8cc6ec6](https://github.com/kanryu/quickviewer/commit/8cc6ec6ccea3b2741e93bc9e9ad387d38d8da525)
    - Update index.md (Fri Nov 24 23:39:46 2017 +0900) [55b9989](https://github.com/kanryu/quickviewer/commit/55b99890eaf4f893e787f7ab91f8655f8f5a5202)
    - Update index.md (Wed Nov 22 19:28:38 2017 +0900) [741b4c4](https://github.com/kanryu/quickviewer/commit/741b4c40664a43e9d632a8f2ab841a2a3a544a76)
    - Update index.md (Thu Nov 16 14:52:18 2017 +0900) [7024420](https://github.com/kanryu/quickviewer/commit/7024420a2352959c5f8a7373258e6febe084131d)
    - changelog (Sun Nov 12 19:32:27 2017 +0900) [358ccc2](https://github.com/kanryu/quickviewer/commit/358ccc2af9aea519766d63639585a8d3e8336a39)

## v1.0.6 (Sun Nov 12 19:31:53 2017 +0900) [2891c9f](https://github.com/kanryu/quickviewer/commit/2891c9fe502b15c6589c45833cb3d98e24d66204)

add 'Fit to width', 1 bugfixed

- add 'Fit to width'
- bugfixed: There may not be able to open as soon as you try to open the image in the root directory of the Windows drive.

- other commits
    - add 'Fit to width' (Sun Nov 12 18:05:28 2017 +0900) [026055a](https://github.com/kanryu/quickviewer/commit/026055aba02bada027e2e9f743088426d8addb22)
    - bugfixed: There may not be able to open as soon as you try to open the image in the root directory of the Windows drive. (Sun Nov 12 14:28:47 2017 +0900) [4f7f670](https://github.com/kanryu/quickviewer/commit/4f7f67048b8b16d1acffeeb32cae335e08ac9cc5)
    - changelog (Fri Nov 3 23:07:45 2017 +0900) [fa05bdf](https://github.com/kanryu/quickviewer/commit/fa05bdf9f3328463b7567d313359da0dc513cdcc)

## v1.0.5 (Fri Nov 3 23:07:17 2017 +0900) [e88fa18](https://github.com/kanryu/quickviewer/commit/e88fa1845e2b377dbdd626507d1501a14b6d59d1)

- update Spanish translations/quickviewer_es.ts
- update cn_zh language resource
- Sometimes display examples of status bar and title bar are incorrect in setting dialog
- The exact file size is not displayed on the status bar etc. when reading the animation image
- Save the path opened with 'Open Image Folder'
- bugfixed: current Volume was not reloaded after deleting the image
- bugfixed: When I tried to open a deleted zip or 7z it was illegally finished
- bugfixed: When changing the display of full screen signage, it did not change until the page was switched

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Fri Nov 3 21:54:53 2017 +0900) [dc7b674](https://github.com/kanryu/quickviewer/commit/dc7b6742dd1da9286f7677d0f38e9fd503879419)
    -  (Fri Nov 3 21:54:53 2017 +0900) [dc7b674](https://github.com/kanryu/quickviewer/commit/dc7b6742dd1da9286f7677d0f38e9fd503879419)
    - # Conflicts: (Fri Nov 3 21:54:53 2017 +0900) [dc7b674](https://github.com/kanryu/quickviewer/commit/dc7b6742dd1da9286f7677d0f38e9fd503879419)
    - #       QuickViewer/src/mainwindow.cpp (Fri Nov 3 21:54:53 2017 +0900) [dc7b674](https://github.com/kanryu/quickviewer/commit/dc7b6742dd1da9286f7677d0f38e9fd503879419)
    - #       QuickViewer/src/models/pagemanager.cpp (Fri Nov 3 21:54:53 2017 +0900) [dc7b674](https://github.com/kanryu/quickviewer/commit/dc7b6742dd1da9286f7677d0f38e9fd503879419)
    - #       QuickViewer/src/models/pagemanager.h (Fri Nov 3 21:54:53 2017 +0900) [dc7b674](https://github.com/kanryu/quickviewer/commit/dc7b6742dd1da9286f7677d0f38e9fd503879419)
    - bugfixed: current Volume was not reloaded after deleting the image (Fri Nov 3 21:29:32 2017 +0900) [041e647](https://github.com/kanryu/quickviewer/commit/041e6474a865560bfdb37dcae6fbddb24c037df7)
    - bugfixed: current Volume was not reloaded after deleting the image (Fri Nov 3 21:29:32 2017 +0900) [a883e8c](https://github.com/kanryu/quickviewer/commit/a883e8ca192b0c0c9508eeb76d68280e6ff740ff)
    - bugfixed: When I tried to open a deleted zip or 7z it was illegally finished (Fri Nov 3 20:35:09 2017 +0900) [90b7810](https://github.com/kanryu/quickviewer/commit/90b7810d28d27f217c8532fd6834518cb3f1c916)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Fri Nov 3 20:33:08 2017 +0900) [d175fe5](https://github.com/kanryu/quickviewer/commit/d175fe515ab2ad3f4af678e00b29af9eac935226)
    - bugfixed: When changing the display of full screen signage, it did not change until the page was switched (Fri Nov 3 20:32:53 2017 +0900) [793292a](https://github.com/kanryu/quickviewer/commit/793292a71bf0f98f6dda4202da8fec3bd2ad6948)
    - Update README.md (Wed Nov 1 09:51:41 2017 +0900) [aa2b05b](https://github.com/kanryu/quickviewer/commit/aa2b05be8c87563f04673c205cfc6e70ece0a58c)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon Oct 30 21:15:07 2017 +0900) [c34cda4](https://github.com/kanryu/quickviewer/commit/c34cda47efd0fe434a4d398b86d86a711f1347d4)
    - update Spanish translations/quickviewer_es.ts (Mon Oct 30 21:14:54 2017 +0900) [7bd6cf6](https://github.com/kanryu/quickviewer/commit/7bd6cf61c12de0be5fbb6093e18d05ab45de75dd)
    -  (Mon Oct 30 21:14:54 2017 +0900) [7bd6cf6](https://github.com/kanryu/quickviewer/commit/7bd6cf61c12de0be5fbb6093e18d05ab45de75dd)
    -  contributed by @dragons4life (Mon Oct 30 21:14:54 2017 +0900) [7bd6cf6](https://github.com/kanryu/quickviewer/commit/7bd6cf61c12de0be5fbb6093e18d05ab45de75dd)
    - Update Contribution.md (Mon Oct 30 19:20:03 2017 +0900) [216462c](https://github.com/kanryu/quickviewer/commit/216462c2c1e841066bd72db2694e6e065c8c2e7b)
    - update cn_zh language resource (Mon Oct 30 18:27:56 2017 +0900) [b7bc3a4](https://github.com/kanryu/quickviewer/commit/b7bc3a4ef2931abd08c33e8a7182db4b1bc80591)
    -  (Mon Oct 30 18:27:56 2017 +0900) [b7bc3a4](https://github.com/kanryu/quickviewer/commit/b7bc3a4ef2931abd08c33e8a7182db4b1bc80591)
    -  contriuted by 河海江超群<mcoder2014@sina.com>, Thanks! (Mon Oct 30 18:27:56 2017 +0900) [b7bc3a4](https://github.com/kanryu/quickviewer/commit/b7bc3a4ef2931abd08c33e8a7182db4b1bc80591)
    - Sometimes display examples of status bar and title bar are incorrect in setting dialog (Sun Oct 29 22:43:49 2017 +0900) [e4026b2](https://github.com/kanryu/quickviewer/commit/e4026b2abbbb5c80b0379681fd5c6c0bd4fd2e0a)
    - The exact file size is not displayed on the status bar etc. when reading the animation image (Sun Oct 29 22:28:01 2017 +0900) [f627eb5](https://github.com/kanryu/quickviewer/commit/f627eb586b4e8dada163475ef379baa1fb219b5d)
    - changelog (Sat Oct 28 18:16:38 2017 +0900) [779158c](https://github.com/kanryu/quickviewer/commit/779158c0de10ea356bb4f44301c811af3a1833da)

## v1.0.4 (Sat Oct 28 18:15:59 2017 +0900) [1ded411](https://github.com/kanryu/quickviewer/commit/1ded41152975b1b17ebc7ecb5f75261e9e154f4d)

scrolling with mouse, start of zoom position of Loupe Tool, bugfixed

- Reflect on the status bar when the display magnification is changed
- add Flag to scroll the image with moving the mouse pointer instead of displaying the scroll bar
- The image will be magnified exactly at the position of the lens of Loupe Tool
- bugfixed: In the case where assignment of input is set to another Action, the assignment may disappear at the time of initialization of the whole

- other commits
    - Temporarily switch to GPU Bilinear when using loupe when CPU Resizing (Sat Oct 28 15:20:41 2017 +0900) [1a94117](https://github.com/kanryu/quickviewer/commit/1a94117056217db41816a918bbbaa5958aa02767)
    - Update index-ja.md (Sat Oct 28 14:46:15 2017 +0900) [3a0e1b4](https://github.com/kanryu/quickviewer/commit/3a0e1b4b85a568ecfa2cf70b0a5533079fd9bf4f)
    - Update index.md (Sat Oct 28 14:43:13 2017 +0900) [9c84c80](https://github.com/kanryu/quickviewer/commit/9c84c80bea6e9af97e2af2b82c98c91c296fd36a)
    - Loupe tool under zooming (Sat Oct 28 14:26:25 2017 +0900) [29faca3](https://github.com/kanryu/quickviewer/commit/29faca31e6b38d8ed0a36a3bce11a374c871d947)
    - add Flag to scroll the image with moving the mouse pointer instead of displaying the scroll bar (Sat Oct 28 02:37:11 2017 +0900) [45972cc](https://github.com/kanryu/quickviewer/commit/45972cc6caa919558b3e28c4d3e0eddebfa679f0)
    - The image will be magnified exactly at the position of the lens of the magnifying glass (Sat Oct 28 01:49:10 2017 +0900) [2342077](https://github.com/kanryu/quickviewer/commit/234207735be687113ba0a3d135e72a30bc82784a)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Fri Oct 27 09:13:40 2017 +0900) [74fed44](https://github.com/kanryu/quickviewer/commit/74fed442c6dd2eecad2d12ecb361a18cf49ec6d8)
    - bugfixed: When registering an existing shortcut to another action, the new shortcut sometimes disappears depending on the order of rewriting from the shortcut information in Defaults (Fri Oct 27 09:13:15 2017 +0900) [1f454f2](https://github.com/kanryu/quickviewer/commit/1f454f2ad222e719222a74e2e90795353739a9f5)
    - Update index-ja.md (Thu Oct 26 19:27:39 2017 +0900) [19bc30a](https://github.com/kanryu/quickviewer/commit/19bc30a3e60a55edb6fca17a633a3db74fac2328)
    - Update index.md (Thu Oct 26 19:19:38 2017 +0900) [818c05f](https://github.com/kanryu/quickviewer/commit/818c05fd421600bb3bb47547b865dcabec67db7e)
    - changelog (Thu Oct 26 17:04:53 2017 +0900) [ce73a34](https://github.com/kanryu/quickviewer/commit/ce73a34b604e2cbb1963a877e580e63037b6f364)

## v1.0.3 (Thu Oct 26 17:03:42 2017 +0900) [1a318b6](https://github.com/kanryu/quickviewer/commit/1a318b6cb5ccd213783f04d37da2fe95330b4431)

add loupe, animation image with scaling, 2 bugfixed

- add Simple loupe function
- Change animation image to scale by bilinear interpolation regardless of Shader setting
- bugfixed: A window may not be activated when it is activated by image file association
- bugfixed: In the case where assignment of input is set to another Action, the assignment may disappear at the time of initialization of the whole

- other commits
    - Simple loupe function (Thu Oct 26 14:22:25 2017 +0900) [b293542](https://github.com/kanryu/quickviewer/commit/b293542696187c540d61ab881fe48ccda008648b)
    - Change animation image to scale by bilinear interpolation regardless of Shader setting (Thu Oct 26 10:19:52 2017 +0900) [77491fb](https://github.com/kanryu/quickviewer/commit/77491fbbc50fc26472ebd946fe9e8ef244808cf4)
    - Update index.md (Wed Oct 25 21:03:25 2017 +0900) [103a116](https://github.com/kanryu/quickviewer/commit/103a116399ed72cea3dce18785a50e79dc1ee988)
    - Update index.md (Wed Oct 25 21:01:15 2017 +0900) [39b3d6c](https://github.com/kanryu/quickviewer/commit/39b3d6c80b4c0f29468cf9f98a26c57f06e8ecf8)
    - Update index.md (Wed Oct 25 18:06:57 2017 +0900) [d5af8e6](https://github.com/kanryu/quickviewer/commit/d5af8e6a18c95e56c409cf5c0d25b79139d7ceb5)
    - Update index.md (Wed Oct 25 18:03:56 2017 +0900) [732a545](https://github.com/kanryu/quickviewer/commit/732a54509cf693e9ff7e1f802b9e59cfbdb05d98)
    - Merge pull request #49 from geogeo-gr/patch-2 (Sat Oct 21 05:15:47 2017 +0900) [7a84ddf](https://github.com/kanryu/quickviewer/commit/7a84ddfbbbd8609e3dec0dd211fdbf3cf4bb528d)
    -  (Sat Oct 21 05:15:47 2017 +0900) [7a84ddf](https://github.com/kanryu/quickviewer/commit/7a84ddfbbbd8609e3dec0dd211fdbf3cf4bb528d)
    - Update quickviewer_el.ts to v1.0.2 (Sat Oct 21 05:15:47 2017 +0900) [7a84ddf](https://github.com/kanryu/quickviewer/commit/7a84ddfbbbd8609e3dec0dd211fdbf3cf4bb528d)
    - Update quickviewer_el.ts (Fri Oct 20 11:06:52 2017 +0300) [5a1b990](https://github.com/kanryu/quickviewer/commit/5a1b990655ce4fa5e7ba04a7036a01321ed8a6b8)
    -  (Fri Oct 20 11:06:52 2017 +0300) [5a1b990](https://github.com/kanryu/quickviewer/commit/5a1b990655ce4fa5e7ba04a7036a01321ed8a6b8)
    -  add 'Divide wide image into 2 pages (Fri Oct 20 11:06:52 2017 +0300) [5a1b990](https://github.com/kanryu/quickviewer/commit/5a1b990655ce4fa5e7ba04a7036a01321ed8a6b8)
    - Update index.md (Tue Oct 17 18:46:03 2017 +0900) [3d8bb5b](https://github.com/kanryu/quickviewer/commit/3d8bb5b48f5faf735d6cbb66369bee2f94558973)
    - Update index.md (Mon Oct 16 02:44:36 2017 +0900) [0404e57](https://github.com/kanryu/quickviewer/commit/0404e5741d666a0ee9cda14eed6939ee941250ba)
    - In the case where assignment of input is set to another Action, the assignment may disappear at the time of initialization of the whole (Mon Oct 16 01:32:56 2017 +0900) [790fcca](https://github.com/kanryu/quickviewer/commit/790fcca4859f593b1df160dd68ab5116c6470b14)
    - changelog (Sun Oct 15 15:57:41 2017 +0900) [afad4f4](https://github.com/kanryu/quickviewer/commit/afad4f421f05937ada4029ddce28b738336cf1b6)

## v1.0.2 (Sun Oct 15 15:56:32 2017 +0900) [dff804a](https://github.com/kanryu/quickviewer/commit/dff804a467733ad9f1f538076f701f52c35f896b)

- add 'Divide wide image into 2 pages'
- Known bug:
- Since the rotation of the tablet can not be detected, correct display can not be performed immediately after rotation.
- You can solve by moving to the next page and returning to the original page

- other commits
    -  support to activate the window when run with file association (Sun Oct 15 14:10:49 2017 +0900) [edabc9c](https://github.com/kanryu/quickviewer/commit/edabc9c5a447def9de46e57b444de2663ee73054)
    -  support to activate the window when image file dropped (Sun Oct 15 14:10:49 2017 +0900) [edabc9c](https://github.com/kanryu/quickviewer/commit/edabc9c5a447def9de46e57b444de2663ee73054)
    - bugfixed: When switching '2 page spread', the page has changed (Sun Oct 15 13:14:10 2017 +0900) [403bf8d](https://github.com/kanryu/quickviewer/commit/403bf8d0b29b9bf4c4176ca332839b2d8ea6b19a)
    - qvtest depends (Sun Oct 15 06:34:28 2017 +0900) [981667b](https://github.com/kanryu/quickviewer/commit/981667bc1e5bbf923d20eb549fd4c0f6892bfce7)
    - Update index-ja.md (Sat Oct 14 18:22:56 2017 +0900) [5a9256e](https://github.com/kanryu/quickviewer/commit/5a9256e3604474da96ddb065f73b88d152d865f2)
    - Update index-ja.md (Sat Oct 14 18:21:47 2017 +0900) [9e21985](https://github.com/kanryu/quickviewer/commit/9e21985a15352f19866609994cee6317872bb823)
    - Update index.md (Sat Oct 14 18:11:52 2017 +0900) [5cbd239](https://github.com/kanryu/quickviewer/commit/5cbd239a20b13f87b01e909eacc9c4c29140d98f)
    - changelog (Sat Oct 14 06:36:16 2017 +0900) [6238808](https://github.com/kanryu/quickviewer/commit/6238808bbf241e658c03c8bcd6d4b38abc58622b)

## v1.0.1 (Sat Oct 14 06:35:39 2017 +0900) [06bc84f](https://github.com/kanryu/quickviewer/commit/06bc84fc64cb169adee770111ac12e54e6c89cea)

pinch with touch panel, support for solid 7z, bugfixed

- Addition of screen rescaling and rotation function with touch panel
- Add to expand solid 7z archive to temporary directory
- bugfixed: Closing the setting dialog with no image displayed aborted

- other commits
    - Addition of screen rescaling and rotation function with touch panel (Sat Oct 14 06:34:43 2017 +0900) [2fcf76d](https://github.com/kanryu/quickviewer/commit/2fcf76d4da46a39097ed0cab040ccf0be82f6c85)
    - bugfixed: Closing the setting dialog with no image displayed aborted (Thu Oct 12 04:19:48 2017 +0900) [79a84cd](https://github.com/kanryu/quickviewer/commit/79a84cdb77165a84585f8c740be3f43c02789b59)
    -  code checking for g++ (Sat Oct 7 06:26:59 2017 +0900) [4a773fb](https://github.com/kanryu/quickviewer/commit/4a773fbf7ec444b3f59476bb27d3e35a0b946137)
    -  bugfixed: It cannot be opened when AppImage is passed a file containing spaces (Sat Oct 7 06:26:59 2017 +0900) [4a773fb](https://github.com/kanryu/quickviewer/commit/4a773fbf7ec444b3f59476bb27d3e35a0b946137)
    - changelog (Sun Oct 1 16:38:14 2017 +0900) [cd0baf2](https://github.com/kanryu/quickviewer/commit/cd0baf290add60c84955b2aefa592dce07d37441)

## v1.0.0 (Sun Oct 1 16:37:28 2017 +0900) [d4b06fd](https://github.com/kanryu/quickviewer/commit/d4b06fd8329137c3469b243f6d209ebcf81a2de3)

support for changing text format, abolish a menu, 2 bugfixed

- support for changing text format  of title bar and status bar
- abolish 'Show full path of volume'
- bugfixed: There were cases where redrawing was not performed normally when the image was reduced or rotated
- bugfixed: Rotating the image by resizing by the CPU caused the wrong aspect ratio

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Fri Sep 29 08:38:45 2017 +0900) [1ab257f](https://github.com/kanryu/quickviewer/commit/1ab257f0dde52437b475c03c1fa09a9575c7d23c)
    -  bugfixed: There were cases where redrawing was not performed normally when the image was reduced or rotated (Fri Sep 29 08:38:34 2017 +0900) [c42b9ba](https://github.com/kanryu/quickviewer/commit/c42b9ba84a2a5e7867a6bdd46e77f236483937e5)
    -  bugfixed: Rotating the image by resizing by the CPU caused the wrong aspect ratio (Fri Sep 29 08:38:34 2017 +0900) [c42b9ba](https://github.com/kanryu/quickviewer/commit/c42b9ba84a2a5e7867a6bdd46e77f236483937e5)
    - Update index.md (Fri Sep 29 02:14:06 2017 +0900) [a6f4ba5](https://github.com/kanryu/quickviewer/commit/a6f4ba5559a5ec2f5e09a02e7ca66a9701084c7c)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Thu Sep 28 21:30:07 2017 +0900) [878d6d6](https://github.com/kanryu/quickviewer/commit/878d6d6072f48f11163bb0fbd62ae0136894683c)
    - add ImageString (Thu Sep 28 21:29:52 2017 +0900) [ac63b3f](https://github.com/kanryu/quickviewer/commit/ac63b3fb31e7ad28c77bfc67b0c2cba775af2a74)
    - Update index.md (Tue Sep 26 08:29:59 2017 +0900) [920723c](https://github.com/kanryu/quickviewer/commit/920723c6528d89b1e7ae0b1c3c10c3f76107a252)
    - update quickviewer_el (Mon Sep 25 18:04:18 2017 +0900) [daf13cc](https://github.com/kanryu/quickviewer/commit/daf13cc30249eec7e0f8398dc8bf421b9ba41b9e)
    - Merge pull request #44 from geogeo-gr/patch-1 (Mon Sep 25 18:03:11 2017 +0900) [1eaa1cf](https://github.com/kanryu/quickviewer/commit/1eaa1cf89de7ae09d52632b6a21addf08c3daeab)
    -  (Mon Sep 25 18:03:11 2017 +0900) [1eaa1cf](https://github.com/kanryu/quickviewer/commit/1eaa1cf89de7ae09d52632b6a21addf08c3daeab)
    - Update quickviewer_el (Mon Sep 25 18:03:11 2017 +0900) [1eaa1cf](https://github.com/kanryu/quickviewer/commit/1eaa1cf89de7ae09d52632b6a21addf08c3daeab)
    - Update quickviewer_el (Mon Sep 25 11:19:33 2017 +0300) [18930d3](https://github.com/kanryu/quickviewer/commit/18930d363cbda078f325d2f79e6a33c78fcc164f)
    -  (Mon Sep 25 11:19:33 2017 +0300) [18930d3](https://github.com/kanryu/quickviewer/commit/18930d363cbda078f325d2f79e6a33c78fcc164f)
    - Supports touch panel input, enlarge menubar/toolbar, hide bars (Mon Sep 25 11:19:33 2017 +0300) [18930d3](https://github.com/kanryu/quickviewer/commit/18930d363cbda078f325d2f79e6a33c78fcc164f)
    - Update index-ja.md (Mon Sep 25 07:11:49 2017 +0900) [1f686d2](https://github.com/kanryu/quickviewer/commit/1f686d22c07278c12608b8d4b892804645efe511)
    - Update index-ja.md (Mon Sep 25 07:00:09 2017 +0900) [1063288](https://github.com/kanryu/quickviewer/commit/1063288a835fc583d6a5e3b27f8b6c7352765454)
    - Update README.md (Mon Sep 25 06:55:59 2017 +0900) [7a76d47](https://github.com/kanryu/quickviewer/commit/7a76d47652af30cd387a941cc4dd93eb833cb4b6)
    - Update index.md (Mon Sep 25 06:55:16 2017 +0900) [0ac4d02](https://github.com/kanryu/quickviewer/commit/0ac4d0281ca9641d8e8645caaab34bc9d6942a2a)
    - changelog (Mon Sep 25 06:36:43 2017 +0900) [2f0db41](https://github.com/kanryu/quickviewer/commit/2f0db412ab46ff1e515b97a85a5ba5dfd85684f3)
    - changelog (Mon Sep 25 06:35:25 2017 +0900) [b8c263f](https://github.com/kanryu/quickviewer/commit/b8c263f16c0f9bc8047cb86d50254bba753bcac9)

## v0.9.9 (Mon Sep 25 06:34:49 2017 +0900) [e4cfe93](https://github.com/kanryu/quickviewer/commit/e4cfe93d42ce83794f48fdcfa702deb0d02c0bb7)

Supports touch panel input, enlarge menubar/toolbar, hide bars, bugfixed

- Supports touch panel input
- add function to enlarge display of main menu and tool bar
- Hide scroll bars in full screen mode
- Hide page bar permanently
- bugfixed: The left end was not displayed when the image is larger than the screen

- other commits
    - behavior of touch paging (Mon Sep 25 05:36:11 2017 +0900) [526c6ce](https://github.com/kanryu/quickviewer/commit/526c6cee77a8d2aac3180a683206cd47f383b181)
    -  Hide scroll bars in full screen mode (Mon Sep 25 05:14:16 2017 +0900) [16faa44](https://github.com/kanryu/quickviewer/commit/16faa44d330ff80b410038255729249ed9328007)
    -  bugfixed: The left end was not displayed when the image is larger than the screen (Mon Sep 25 05:14:16 2017 +0900) [16faa44](https://github.com/kanryu/quickviewer/commit/16faa44d330ff80b410038255729249ed9328007)
    - Hide page bar permanently (Mon Sep 25 04:52:30 2017 +0900) [8c7af04](https://github.com/kanryu/quickviewer/commit/8c7af04b8902f45116ec4a6f34fbbc74889d240c)
    - Supports touch panel input (Mon Sep 25 04:26:18 2017 +0900) [d342039](https://github.com/kanryu/quickviewer/commit/d34203944946a3543b195fa962faf589b45860fa)
    - support to change range of show innerframes (Sun Sep 24 03:16:51 2017 +0900) [fab699e](https://github.com/kanryu/quickviewer/commit/fab699e8ee86140d0363809f035010b9ebf7206d)
    - merged (Sun Sep 24 02:16:36 2017 +0900) [c01ad6e](https://github.com/kanryu/quickviewer/commit/c01ad6ef2e06a8f278fb242875532768935eb2ee)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sun Sep 24 00:01:03 2017 +0900) [d170b06](https://github.com/kanryu/quickviewer/commit/d170b06bf27c59beb6772329ebca82e446710e3d)
    -  (Sun Sep 24 00:01:03 2017 +0900) [d170b06](https://github.com/kanryu/quickviewer/commit/d170b06bf27c59beb6772329ebca82e446710e3d)
    - # Conflicts: (Sun Sep 24 00:01:03 2017 +0900) [d170b06](https://github.com/kanryu/quickviewer/commit/d170b06bf27c59beb6772329ebca82e446710e3d)
    - #       QuickViewer/src/mainwindow.cpp (Sun Sep 24 00:01:03 2017 +0900) [d170b06](https://github.com/kanryu/quickviewer/commit/d170b06bf27c59beb6772329ebca82e446710e3d)
    - add function to enlarge display of main menu and tool bar (Sat Sep 23 23:58:06 2017 +0900) [c2b1471](https://github.com/kanryu/quickviewer/commit/c2b1471698d2c290ef4b2752738d098b753b6cfe)
    - checked on Ubuntu Linux-14.04.5 (Wed Sep 20 23:41:38 2017 +0900) [fd9dbf2](https://github.com/kanryu/quickviewer/commit/fd9dbf2bdf1c0529f9c8e5e6a578d020b6003b4f)
    - changelog (Wed Sep 20 22:51:45 2017 +0900) [a40f68f](https://github.com/kanryu/quickviewer/commit/a40f68fb7991ffb8aff8ee61429be3ba41a8352f)

## v0.9.8 (Wed Sep 20 22:51:00 2017 +0900) [57605f8](https://github.com/kanryu/quickviewer/commit/57605f8e43dcf871be6e66134469fa51a1aa5733)

improve behavior for tool windows and scroll bars, add 2 menus, 2 bugfixed

- improve behavior
- tool windows such as Catalog/Folder Window
- If scroll bars are required only for width or height of an image, only the scroll bars that are required are displayed.
- can Scroll images with cursor keys when to show scrollbars
- add 'Don't update history'
- add 'Show full path of the volume'
- bugfixed: The left end was not displayed when the image is larger than the screen
- bugfixed: prevent to crash on incorrect file

- other commits
    - remove shortcutbutton (Wed Sep 20 10:22:43 2017 +0900) [8b6ff79](https://github.com/kanryu/quickviewer/commit/8b6ff79e125f9aa9df47ced57723fa3ad4672648)
    -  can Scroll images with cursor keys when to show scrollbars (Wed Sep 20 09:32:52 2017 +0900) [447c089](https://github.com/kanryu/quickviewer/commit/447c089dd8b3774fcb29fd76f53f65bc3e642ab1)
    -  bugfixed: The left end was not displayed when the image is larger than the screen (Wed Sep 20 09:32:52 2017 +0900) [447c089](https://github.com/kanryu/quickviewer/commit/447c089dd8b3774fcb29fd76f53f65bc3e642ab1)
    -  add 'Don't update history' (Wed Sep 20 05:25:42 2017 +0900) [b55d474](https://github.com/kanryu/quickviewer/commit/b55d474995f33d8194880a9d260527aaf019d1b5)
    -  add 'Show full path of the volume' (Wed Sep 20 05:25:42 2017 +0900) [b55d474](https://github.com/kanryu/quickviewer/commit/b55d474995f33d8194880a9d260527aaf019d1b5)
    - If scroll bars are required only for width or height of an image, only the scroll bars that are required are displayed. (Wed Sep 20 03:38:41 2017 +0900) [1bb1ee5](https://github.com/kanryu/quickviewer/commit/1bb1ee5ec094ad748fddfecc0bc78ea880e1c20f)
    - prevent to crash on incorrect file (Sat Sep 16 02:20:56 2017 +0900) [3782ad7](https://github.com/kanryu/quickviewer/commit/3782ad7e31fa9e5755e9fbb5b8e9c097436f27b6)
    - changelog (Fri Sep 15 17:44:32 2017 +0900) [316f33e](https://github.com/kanryu/quickviewer/commit/316f33ec921d4210514b0e787ebd21cf1ac500c3)

## v0.9.7 (Fri Sep 15 17:44:02 2017 +0900) [8dffaf4](https://github.com/kanryu/quickviewer/commit/8dffaf434d03f3b288e1723721b09cea997d2891)

improved loading JPEG, Exif display, bugfixed

- improved loading JPEG
- Added option to change precision (iDCT) at JPEG loading
- The JPEG in CYMK format can be correctly read using ICC Profile.
- Improvement of Exif information display
- bugfixed: When multiple shortcut keys were registered, it did not work properly

- other commits
    - Update index.md (Thu Sep 14 01:29:14 2017 +0900) [0a37ae1](https://github.com/kanryu/quickviewer/commit/0a37ae1d9f2757440c0734d8d013fe9a08cabfef)
    - Update index.md (Thu Sep 14 01:07:54 2017 +0900) [bf2444d](https://github.com/kanryu/quickviewer/commit/bf2444d8b532ce9a945b80179eaf9e7be0702727)
    - Update index-ja.md (Thu Sep 14 01:07:26 2017 +0900) [43204f2](https://github.com/kanryu/quickviewer/commit/43204f206247b46471ee2eeb3d6942ca8559fedc)
    - Update index-ja.md (Thu Sep 14 01:00:34 2017 +0900) [1750db0](https://github.com/kanryu/quickviewer/commit/1750db051f28cd06ecdea5e5829101abcf6d041a)
    - Update index.md (Thu Sep 14 01:00:08 2017 +0900) [d84fe1d](https://github.com/kanryu/quickviewer/commit/d84fe1d6d0b4869071b79b5763be0cae0aeaa070)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Wed Sep 13 13:38:34 2017 +0900) [2c869e4](https://github.com/kanryu/quickviewer/commit/2c869e419d840ca2bb7d4df470395474637c4379)
    - Delete once 'exiv2 submodule' points to a commit that does not exist (Wed Sep 13 13:38:18 2017 +0900) [e91fe38](https://github.com/kanryu/quickviewer/commit/e91fe38864dc105cf36804cf9c8af266a4a713ae)
    - Update index.md (Wed Sep 13 13:29:19 2017 +0900) [1c48b97](https://github.com/kanryu/quickviewer/commit/1c48b97f17f0b28c3e9d0558c5eba83d70288164)
    - Update index.md (Wed Sep 13 13:27:49 2017 +0900) [d4a0945](https://github.com/kanryu/quickviewer/commit/d4a0945940e01d9f5c530e9d701361f4357cfcf4)
    - bugfixed: When multiple shortcut keys are registered for an Action, the first shortcut does not work. (Wed Sep 13 04:11:07 2017 +0900) [259ce69](https://github.com/kanryu/quickviewer/commit/259ce69d79c81884ab72610f0bcee5702109ab2d)
    - add qactionmanager (Mon Sep 11 22:39:42 2017 +0900) [eac9cdd](https://github.com/kanryu/quickviewer/commit/eac9cddfaab56e3652e8bc55a92db5d3f9fc9c8e)
    - refactoring (Mon Sep 11 22:08:07 2017 +0900) [6836106](https://github.com/kanryu/quickviewer/commit/6836106131bcc63486c75f9241e4b4c50132d77f)
    -  (Mon Sep 11 22:08:07 2017 +0900) [6836106](https://github.com/kanryu/quickviewer/commit/6836106131bcc63486c75f9241e4b4c50132d77f)
    -  add QActionManager (Mon Sep 11 22:08:07 2017 +0900) [6836106](https://github.com/kanryu/quickviewer/commit/6836106131bcc63486c75f9241e4b4c50132d77f)
    - update easyexif (Mon Sep 11 16:38:53 2017 +0900) [c3403b4](https://github.com/kanryu/quickviewer/commit/c3403b497059f000052187611a0c713c8cfe0c0f)
    - replace easyexif (Mon Sep 11 09:46:55 2017 +0900) [2c42743](https://github.com/kanryu/quickviewer/commit/2c42743bb0d7034c1b7c642f1945a1499cc7cb76)
    - add qvtest (Mon Sep 11 09:44:43 2017 +0900) [22eb8af](https://github.com/kanryu/quickviewer/commit/22eb8af61d0e2874d0228e96e3987f28961abdcc)
    - Update and rename contributed.md to Contribution.md (Sat Sep 9 16:19:10 2017 +0900) [573e891](https://github.com/kanryu/quickviewer/commit/573e891cea8b2352572f84b6bcc0e2edeca7877b)
    - Update README.md (Sat Sep 9 13:49:56 2017 +0900) [1bf45bf](https://github.com/kanryu/quickviewer/commit/1bf45bf513351c1fbe3a29ebdbfe8325bb4a7c1f)
    - Update contributed.md (Sat Sep 9 13:13:18 2017 +0900) [bd9156f](https://github.com/kanryu/quickviewer/commit/bd9156f56a1df8db99892fc7807774f2778e9ee0)
    - Update contributed.md (Sat Sep 9 13:00:21 2017 +0900) [c3cac95](https://github.com/kanryu/quickviewer/commit/c3cac9532ed3e6a8c15b3d022d1ab92329ead7c4)
    - add German language resource (Sat Sep 9 12:47:32 2017 +0900) [e44ba61](https://github.com/kanryu/quickviewer/commit/e44ba61092e24e2fa4df681026e3ddbf00a2ace1)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Thu Sep 7 17:50:51 2017 +0900) [b14828c](https://github.com/kanryu/quickviewer/commit/b14828c51545a9b89fcb437c0221e9aaa0bd23b4)
    - add libstdc++.so (for linux) (Thu Sep 7 17:50:26 2017 +0900) [18b9204](https://github.com/kanryu/quickviewer/commit/18b9204d1c6fe07c4ea164d512c734209ededf64)
    -  Add Greek translation(written by geogeo.gr) (Thu Sep 7 17:34:42 2017 +0900) [893d83e](https://github.com/kanryu/quickviewer/commit/893d83e0ba3eec2f9b513c738b8e274cf0b53713)
    - bugfixed: thubnail images of the catalog could not be made (Tue Sep 5 13:35:07 2017 +0900) [aeeb1fd](https://github.com/kanryu/quickviewer/commit/aeeb1fd2b4c942fcc120a030361d4c3fd2d78cbe)

## v0.9.6 (Tue Sep 5 12:27:38 2017 +0900) [56a0466](https://github.com/kanryu/quickviewer/commit/56a0466320857ea8e33f005faf9049d42d4de66d)

changelog

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Tue Sep 5 12:27:03 2017 +0900) [f33e902](https://github.com/kanryu/quickviewer/commit/f33e902338e59519fef6c96259c91e0432ab010c)
    -  bugfixed: When restarting with the image in the directory opened, only one page was displayed regardless of 2 page spread settings (Tue Sep 5 12:26:52 2017 +0900) [cc817b7](https://github.com/kanryu/quickviewer/commit/cc817b7520184b3154b0fa23258a121d6d7a6e40)
    -  bugfixed: Bookmarks were improperly increased when restarting the application (Tue Sep 5 12:26:52 2017 +0900) [cc817b7](https://github.com/kanryu/quickviewer/commit/cc817b7520184b3154b0fa23258a121d6d7a6e40)
    -  bugfixed: failed to restore the images contained in 7z and zip archives at startup (Tue Sep 5 12:26:52 2017 +0900) [cc817b7](https://github.com/kanryu/quickviewer/commit/cc817b7520184b3154b0fa23258a121d6d7a6e40)
    - Update HowToBuild.md (Tue Sep 5 03:08:53 2017 +0900) [0b32552](https://github.com/kanryu/quickviewer/commit/0b325527de79a39510ee872f4bbeb2f7ccb8076f)
    - Update HowToBuild.md (Tue Sep 5 03:07:43 2017 +0900) [f60814a](https://github.com/kanryu/quickviewer/commit/f60814a7ea5fc94c0d5ba0ef83f00b2debe23ccd)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Tue Sep 5 02:57:23 2017 +0900) [4ebe201](https://github.com/kanryu/quickviewer/commit/4ebe201b9f78da0ab455554dc4e53d097df4d7a2)
    - support for thumbnail database (Tue Sep 5 02:54:58 2017 +0900) [8fb82f5](https://github.com/kanryu/quickviewer/commit/8fb82f502714543a173c1805b8739da2bf0ef876)
    - make application dir into '~/.quickviewer' (Tue Sep 5 02:54:58 2017 +0900) [8fb82f5](https://github.com/kanryu/quickviewer/commit/8fb82f502714543a173c1805b8739da2bf0ef876)
    - Update HowToBuild.md (Mon Sep 4 22:39:34 2017 +0900) [686ffab](https://github.com/kanryu/quickviewer/commit/686ffaba4ae99a50fc7e567a8ee2b3a954b6aef7)
    - Correction for warning when building with gcc (Mon Sep 4 19:35:22 2017 +0900) [2857300](https://github.com/kanryu/quickviewer/commit/2857300bdaf6eec73c859120771a464edc24d5cf)
    - Update index.md (Mon Sep 4 04:51:08 2017 +0900) [887f6dd](https://github.com/kanryu/quickviewer/commit/887f6dd90c6b2950461f6be87b84bd8769a31ba2)
    - Update README.md (Mon Sep 4 04:43:17 2017 +0900) [46bfbaa](https://github.com/kanryu/quickviewer/commit/46bfbaa767a83870431d2fb5d4abb8f85539b8f8)
    - Update index.md (Mon Sep 4 04:12:05 2017 +0900) [a3dd439](https://github.com/kanryu/quickviewer/commit/a3dd43990ad655c7895738ffd492b7e4cb5f2ced)
    - Enable deletion when archive is open (Mon Sep 4 03:59:25 2017 +0900) [d75cda0](https://github.com/kanryu/quickviewer/commit/d75cda02f1d4544578038545f1b6aad9c2180ac0)
    -  qnamedpipe as submodule (Mon Sep 4 02:24:27 2017 +0900) [42b4dd8](https://github.com/kanryu/quickviewer/commit/42b4dd87b70d2f6ab462e6a3f324bfb8a3a7513b)
    -  checked on windows (Mon Sep 4 02:24:27 2017 +0900) [42b4dd8](https://github.com/kanryu/quickviewer/commit/42b4dd87b70d2f6ab462e6a3f324bfb8a3a7513b)
    - support Prohibit multiple running on Linux (Mon Sep 4 01:46:25 2017 +0900) [398ed00](https://github.com/kanryu/quickviewer/commit/398ed00121c613fff856bdea7d5eb6df7be37fd2)

## v0.9.5 (Sun Sep 3 03:10:54 2017 +0900) [2bc8ef6](https://github.com/kanryu/quickviewer/commit/2bc8ef6cd66cab6eef2a01b2c99cf9f62ff5a79d)

changelog

- other commits
    - improve behavior of run by file association, bugfixed (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  Enable QtSDK standard text language resource (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  Turn on checking if associations are defined in the registry (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  support for file association for current user only (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  bugfixed: Opening an image file in association when multiple activation is prohibited causes the z-order of the window to be inappropriate (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  bugfixed: When multiple image activation is prohibited, even when image file is opened more than once by association, it does not show  only 1-page display (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  Change zip extraction to use 7zip (for linux) (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  validate desktop configulation(on linux) (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    -  issue on #31 (Sun Sep 3 03:10:25 2017 +0900) [7f89ffc](https://github.com/kanryu/quickviewer/commit/7f89ffc76a94e39cc6af1646e412e832edd54822)
    - Update HowToBuild.md (Sun Sep 3 00:34:31 2017 +0900) [640336e](https://github.com/kanryu/quickviewer/commit/640336e8b219020b2feeb76fb9020a1994fd941e)
    - Update HowToBuild.md (Sat Sep 2 23:32:35 2017 +0900) [17f022d](https://github.com/kanryu/quickviewer/commit/17f022de84efb2bb3be0f1de915c61235adce711)
    - Update HowToBuild.md (Sat Sep 2 23:24:56 2017 +0900) [b73cef2](https://github.com/kanryu/quickviewer/commit/b73cef223b3da416bcc79739d654ad36017007eb)
    - Update README.md (Sat Sep 2 22:39:47 2017 +0900) [7fbf18d](https://github.com/kanryu/quickviewer/commit/7fbf18d031372324480b9078b562fe364c193201)
    - validate desktop file (Sat Sep 2 21:09:15 2017 +0900) [6ae1281](https://github.com/kanryu/quickviewer/commit/6ae1281e53f4064886b2fe388608ee3ec48e396d)
    -  (Sat Sep 2 21:09:15 2017 +0900) [6ae1281](https://github.com/kanryu/quickviewer/commit/6ae1281e53f4064886b2fe388608ee3ec48e396d)
    -  issue on #31 (Sat Sep 2 21:09:15 2017 +0900) [6ae1281](https://github.com/kanryu/quickviewer/commit/6ae1281e53f4064886b2fe388608ee3ec48e396d)
    -  Opening an image file in association when multiple activation is prohibited causes the z-order of the window to be inappropriate (Sat Sep 2 16:05:20 2017 +0900) [f737a61](https://github.com/kanryu/quickviewer/commit/f737a61b0dafe4c54af954a522ff60538bb8f570)
    -  When multiple image activation is prohibited, even when image file is opened more than once by association, it does not show  only 1-page display (Sat Sep 2 16:05:20 2017 +0900) [f737a61](https://github.com/kanryu/quickviewer/commit/f737a61b0dafe4c54af954a522ff60538bb8f570)
    - Change zip extraction to use 7zip (for linux) (Sat Sep 2 05:55:17 2017 +0900) [befd5f8](https://github.com/kanryu/quickviewer/commit/befd5f8c9d41dcabf1c08bb97a4a8c2efb3c9af9)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sat Sep 2 01:47:27 2017 +0900) [48d4e22](https://github.com/kanryu/quickviewer/commit/48d4e22518e3f3d3db5de419d2078d95ed1f437c)
    -  Turn on checking if associations are defined in the registry (Sat Sep 2 01:47:09 2017 +0900) [064f01b](https://github.com/kanryu/quickviewer/commit/064f01b309ca2c900cea87d8eb390d3f93c2e76c)
    -  Supports current user only registry settings (Sat Sep 2 01:47:09 2017 +0900) [064f01b](https://github.com/kanryu/quickviewer/commit/064f01b309ca2c900cea87d8eb390d3f93c2e76c)
    - Update index-ja.md (Fri Sep 1 17:27:44 2017 +0900) [c27423b](https://github.com/kanryu/quickviewer/commit/c27423b9e3c59dbc8aa447d4c33c8eff6a614ac4)
    - Update index.md (Fri Sep 1 17:27:13 2017 +0900) [9013291](https://github.com/kanryu/quickviewer/commit/9013291563e508fc2fc0301e9c2268890f647ef9)
    - Update index.md (Fri Sep 1 17:23:02 2017 +0900) [b5e0e23](https://github.com/kanryu/quickviewer/commit/b5e0e232e4d16756aff6279829e54debb40dfa5f)
    - Update index.md (Fri Sep 1 17:22:22 2017 +0900) [643468e](https://github.com/kanryu/quickviewer/commit/643468ed19ace780ce159fc47f19d2e79c715fd9)
    - Update index.md (Fri Sep 1 13:23:14 2017 +0900) [3c9f6c3](https://github.com/kanryu/quickviewer/commit/3c9f6c3850bc0d5bffd3e45d949702bb56ee59ec)
    - support building as portable AppImage in Linux (Thu Aug 31 17:04:36 2017 +0900) [7e7726f](https://github.com/kanryu/quickviewer/commit/7e7726f83502ea98ab4efbe32ead1226c1b900c8)
    - Revert "remove old submodules" (Thu Aug 31 14:49:57 2017 +0900) [29c5f30](https://github.com/kanryu/quickviewer/commit/29c5f30272fb17480ffcdfce590d15482eebe685)
    -  (Thu Aug 31 14:49:57 2017 +0900) [29c5f30](https://github.com/kanryu/quickviewer/commit/29c5f30272fb17480ffcdfce590d15482eebe685)
    - This reverts commit 43512071b21a55f5fd93a1837f89eb6f51a0280e. (Thu Aug 31 14:49:57 2017 +0900) [29c5f30](https://github.com/kanryu/quickviewer/commit/29c5f30272fb17480ffcdfce590d15482eebe685)
    - The file path of each resource is controlled by qt.conf. Switch specifications because it is different for Windows and Linux. When qt.conf is applied, it must be deployed and it is not suitable for debugging, so set it for release only. (Thu Aug 31 01:19:49 2017 +0900) [531df13](https://github.com/kanryu/quickviewer/commit/531df134c1eb7bcbb2a6d2003ea6566e25e3be29)
    - Enable QtSDK standard text language resource (Wed Aug 30 15:10:27 2017 +0900) [ec03065](https://github.com/kanryu/quickviewer/commit/ec030658491278d2bfb8d5d20a1ccf2519abbbd8)
    - Update HowToBuild.md (Wed Aug 30 00:41:42 2017 +0900) [76d712b](https://github.com/kanryu/quickviewer/commit/76d712bc86491c01fc134b0122895e2aa4205612)
    - remove old submodules (Tue Aug 29 23:03:36 2017 +0900) [4351207](https://github.com/kanryu/quickviewer/commit/43512071b21a55f5fd93a1837f89eb6f51a0280e)
    - build check again in windows (Tue Aug 29 23:03:00 2017 +0900) [75e8a1f](https://github.com/kanryu/quickviewer/commit/75e8a1f89bcc693c86fe4946b273894b4aef6654)
    - use qinnerframe in unix OSs (Tue Aug 29 22:09:18 2017 +0900) [def7f4f](https://github.com/kanryu/quickviewer/commit/def7f4f0057f91698d874da19d340b30991f9613)
    - support for building new Qt7z in unix OSs (Tue Aug 29 21:31:21 2017 +0900) [3d5af22](https://github.com/kanryu/quickviewer/commit/3d5af2207841edb7e4ba47e3ec8e3867058d00cd)
    -  checked in kubuntu-17.04 (Tue Aug 29 21:31:21 2017 +0900) [3d5af22](https://github.com/kanryu/quickviewer/commit/3d5af2207841edb7e4ba47e3ec8e3867058d00cd)
    - p7zip (Tue Aug 29 18:10:52 2017 +0900) [b348557](https://github.com/kanryu/quickviewer/commit/b348557232d9388b071dc6088337ec4cf3604195)
    - Update index.md (Mon Aug 28 22:16:33 2017 +0900) [c8aa307](https://github.com/kanryu/quickviewer/commit/c8aa30781643586b20fad26b7b8ac674bab66101)
    - changelog (Mon Aug 28 21:54:35 2017 +0900) [fdd1708](https://github.com/kanryu/quickviewer/commit/fdd1708455687090fd9878f504c4d8e23220e78d)
    - Add Greek translation, abolished a menu, support for zip with Deflate64 (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)
    -  (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)
    -  Add Greek translation(written by geogeo.gr) (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)
    -  thanks a lot! :) (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)
    -  abolished 'Show titlebar on fullscreen' (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)
    -  Because I concluded that there was an illegal behavior caused by a bug in Qt when I manipulated the menu and I can not fix it. (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)
    -  support for zip with Deflate64 (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)
    -  Discontinued support by zlib / minizip and switched to zip support with 7zip (Mon Aug 28 21:40:31 2017 +0900) [fab2c8e](https://github.com/kanryu/quickviewer/commit/fab2c8ee10c6a4819351d188deff18e130a68831)

## v0.9.4 (Mon Aug 28 19:08:24 2017 +0900) [de74b9c](https://github.com/kanryu/quickviewer/commit/de74b9c73e1b430db0d1b8e0c0d8a97fbf5bf4c1)

add new Qt7z

- other commits
    - remove old qt7z (Mon Aug 28 19:06:40 2017 +0900) [801c967](https://github.com/kanryu/quickviewer/commit/801c9679bbfb67ef0dd8f3b399b15f839f0c187c)
    -  Add Greek translation(written by geogeo.gr) (Thu Aug 24 13:00:22 2017 +0900) [a4e75e1](https://github.com/kanryu/quickviewer/commit/a4e75e1c6b3df3b5694dc7ae3a1969381da6d7a7)
    - Update HowToBuild.md (Sun Aug 20 23:19:28 2017 +0900) [8dfe025](https://github.com/kanryu/quickviewer/commit/8dfe02569118108b8239f4641ee9b94b67c1d118)
    - Update HowToBuild.md (Sun Aug 20 23:02:45 2017 +0900) [7089211](https://github.com/kanryu/quickviewer/commit/70892115061341eda9231c32f3c3cb9f54ed69d1)

## v0.9.3 (Sun Aug 20 17:46:24 2017 +0900) [2c5505f](https://github.com/kanryu/quickviewer/commit/2c5505f3f44d53b63f144dc1b004c677c2bae315)

changelog

- other commits
    - changing rendering method, support Direct2D, bugfixed (Sun Aug 20 17:45:39 2017 +0900) [693d005](https://github.com/kanryu/quickviewer/commit/693d00564d079806879b9265fe2c7a7b8dacf2f0)
    -  (Sun Aug 20 17:45:39 2017 +0900) [693d005](https://github.com/kanryu/quickviewer/commit/693d00564d079806879b9265fe2c7a7b8dacf2f0)
    -  Rendering with Windows GDI is standard on Windows, from this version (Sun Aug 20 17:45:39 2017 +0900) [693d005](https://github.com/kanryu/quickviewer/commit/693d00564d079806879b9265fe2c7a7b8dacf2f0)
    -  significant speed up (Sun Aug 20 17:45:39 2017 +0900) [693d005](https://github.com/kanryu/quickviewer/commit/693d00564d079806879b9265fe2c7a7b8dacf2f0)
    -  support Direct2D rendering (Sun Aug 20 17:45:39 2017 +0900) [693d005](https://github.com/kanryu/quickviewer/commit/693d00564d079806879b9265fe2c7a7b8dacf2f0)
    -  bugfixed: Reading of PNG was very slow (Sun Aug 20 17:45:39 2017 +0900) [693d005](https://github.com/kanryu/quickviewer/commit/693d00564d079806879b9265fe2c7a7b8dacf2f0)
    - Update shader.md (Sun Aug 20 06:06:58 2017 +0900) [549dd2a](https://github.com/kanryu/quickviewer/commit/549dd2aa02a721b6713ecc8b3cad9d5c13a6a577)
    - Update index-ja.md (Sun Aug 20 06:06:02 2017 +0900) [83c877c](https://github.com/kanryu/quickviewer/commit/83c877c1466061ee4ad18e76c2afec1698758cea)
    - Update _config.yml (Sun Aug 20 05:45:35 2017 +0900) [ee0fe1e](https://github.com/kanryu/quickviewer/commit/ee0fe1e57ee43fc3ef379897472a49ebce96d771)
    - Update index.html (Sun Aug 20 05:44:30 2017 +0900) [1e12cb0](https://github.com/kanryu/quickviewer/commit/1e12cb05864dff2ee3e7fe0459b8ab16ba73d1d7)
    - Update shader-ja.md (Sun Aug 20 05:42:54 2017 +0900) [db169ea](https://github.com/kanryu/quickviewer/commit/db169ea402538c42af279147b2b0b50af6fd1773)
    - Update shader.md (Sun Aug 20 05:42:28 2017 +0900) [597a4cf](https://github.com/kanryu/quickviewer/commit/597a4cfd61e16fad629913e01d99a24b6fe58891)
    - Update index-ja.md (Sun Aug 20 05:41:59 2017 +0900) [659fac0](https://github.com/kanryu/quickviewer/commit/659fac0343ecc7b037ed71f1a5f82f220778bafc)
    - Update default.html (Sun Aug 20 05:40:34 2017 +0900) [95d8ee3](https://github.com/kanryu/quickviewer/commit/95d8ee37642ce39bece91c713dea2a1042480a93)
    - Update index.md (Sun Aug 20 05:35:44 2017 +0900) [19662ec](https://github.com/kanryu/quickviewer/commit/19662ecac13a60b32428b128aa954c88041c7b78)
    - Update _config.yml (Sun Aug 20 05:34:12 2017 +0900) [2e2cff2](https://github.com/kanryu/quickviewer/commit/2e2cff2a7933de64bdb221a76f4912df9c31ec4e)
    - Update HowToBuild.md (Fri Aug 18 09:01:00 2017 +0900) [3e9e294](https://github.com/kanryu/quickviewer/commit/3e9e294d6ed8c33c326a3ef9237b34b30528fa6a)
    - support for build by MinGW(windows) (Fri Aug 18 08:54:26 2017 +0900) [c4fad18](https://github.com/kanryu/quickviewer/commit/c4fad184e837d0e7be98445d3f808351fcbdbb8d)
    - Update index.md (Fri Aug 18 05:45:06 2017 +0900) [881e23c](https://github.com/kanryu/quickviewer/commit/881e23ce1c27dcfd9ff152f707a321892e74887e)
    - Update index.md (Fri Aug 18 05:39:19 2017 +0900) [3043156](https://github.com/kanryu/quickviewer/commit/3043156fb9a59e0df1ff0c2a78cef933b1d4477b)
    - Update HowToBuild.md (Thu Aug 17 21:53:36 2017 +0900) [a33eb6f](https://github.com/kanryu/quickviewer/commit/a33eb6f25fc1db3fe2e0db10269175ab2bc9acfd)
    - Update HowToBuild.md (Thu Aug 17 21:52:42 2017 +0900) [a917b8b](https://github.com/kanryu/quickviewer/commit/a917b8b6dbfce7244800fd431e0d6591893b6c4a)
    - Update HowToBuild.md (Thu Aug 17 21:39:23 2017 +0900) [fca6aa2](https://github.com/kanryu/quickviewer/commit/fca6aa27fd303fa7fad576cc3408ec2ed2b48e92)

## v0.9.2 (Thu Aug 17 11:35:53 2017 +0900) [763f7dd](https://github.com/kanryu/quickviewer/commit/763f7ddddd3acb9b579ae664a53b7437cec212bd)

changelog

- other commits
    - 3 bugfixed (Thu Aug 17 11:35:15 2017 +0900) [90c1f31](https://github.com/kanryu/quickviewer/commit/90c1f31e2f5b442cb38f62b9430acec448376fe8)
    -  (Thu Aug 17 11:35:15 2017 +0900) [90c1f31](https://github.com/kanryu/quickviewer/commit/90c1f31e2f5b442cb38f62b9430acec448376fe8)
    -  bugfixed: Rebooting the application with the archive open failed to load correctly (Thu Aug 17 11:35:15 2017 +0900) [90c1f31](https://github.com/kanryu/quickviewer/commit/90c1f31e2f5b442cb38f62b9430acec448376fe8)
    -  bugfixed: There was a Tiff file that can not be read correctly (Thu Aug 17 11:35:15 2017 +0900) [90c1f31](https://github.com/kanryu/quickviewer/commit/90c1f31e2f5b442cb38f62b9430acec448376fe8)
    -  bugfixed: can read special JPEG data such as CMYK and YCCK. However, the color is incorrect (Thu Aug 17 11:35:15 2017 +0900) [90c1f31](https://github.com/kanryu/quickviewer/commit/90c1f31e2f5b442cb38f62b9430acec448376fe8)
    - Update HowToBuild.md (Wed Aug 16 20:38:18 2017 +0900) [d9c4d7a](https://github.com/kanryu/quickviewer/commit/d9c4d7af1275cd52d98e996182831c8ae1a6555d)
    - Update HowToBuild.md (Wed Aug 16 07:53:33 2017 +0900) [a952b5c](https://github.com/kanryu/quickviewer/commit/a952b5caaa2d187eac807e0bf20e4e9ae9ea0354)
    - Update HowToBuild.md (Wed Aug 16 07:52:44 2017 +0900) [82d4ffc](https://github.com/kanryu/quickviewer/commit/82d4ffc9b42f3e5eaed6e49b97d5528d1be34a60)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Wed Aug 16 07:44:06 2017 +0900) [d153bbe](https://github.com/kanryu/quickviewer/commit/d153bbef3e445477b9d93bf4c9836361f859a0e4)
    -  (Wed Aug 16 07:44:06 2017 +0900) [d153bbe](https://github.com/kanryu/quickviewer/commit/d153bbef3e445477b9d93bf4c9836361f859a0e4)
    - # Conflicts: (Wed Aug 16 07:44:06 2017 +0900) [d153bbe](https://github.com/kanryu/quickviewer/commit/d153bbef3e445477b9d93bf4c9836361f859a0e4)
    - #       QuickViewer/QuickViewer.pro (Wed Aug 16 07:44:06 2017 +0900) [d153bbe](https://github.com/kanryu/quickviewer/commit/d153bbef3e445477b9d93bf4c9836361f859a0e4)
    - build checking for command builders (Wed Aug 16 07:16:45 2017 +0900) [fa640d0](https://github.com/kanryu/quickviewer/commit/fa640d067be3ae8f3e34d3cbce0ce8faf5da56c2)
    - Update HowToBuild.md (Wed Aug 16 07:19:13 2017 +0900) [1c8defb](https://github.com/kanryu/quickviewer/commit/1c8defb9be54d9b8c56ff8cad3ec3b0759774e09)
    - build checking for command builders (Wed Aug 16 07:16:45 2017 +0900) [7087bdb](https://github.com/kanryu/quickviewer/commit/7087bdb4eab5b3f5b36ae9f76631689e63aaab92)
    - Update HowToBuild.md (Wed Aug 16 07:15:31 2017 +0900) [35351b7](https://github.com/kanryu/quickviewer/commit/35351b7485d1765dc990a8d5e1882241c4ad19ac)
    - Update HowToBuild.md (Wed Aug 16 06:56:33 2017 +0900) [a981e07](https://github.com/kanryu/quickviewer/commit/a981e0784cd38cd3538408d20b9e5c81565ea571)
    - Update HowToBuild.md (Wed Aug 16 06:51:03 2017 +0900) [f84bf81](https://github.com/kanryu/quickviewer/commit/f84bf81c668609ee8854f35c7abac61b9d3a044a)
    - Update index.md (Tue Aug 15 20:36:51 2017 +0900) [09d69c6](https://github.com/kanryu/quickviewer/commit/09d69c69adedeba58fc603dcc4ff33fa94cfead4)
    - Update HowToBuild.md (Tue Aug 15 05:41:24 2017 +0900) [1f30228](https://github.com/kanryu/quickviewer/commit/1f3022868a6aba3427bfd41ac08bb69085d99191)
    - Update HowToBuild.md (Tue Aug 15 02:20:30 2017 +0900) [535f728](https://github.com/kanryu/quickviewer/commit/535f72864316da45cd4d28d7d252a5ee846ac441)
    - Update index.md (Mon Aug 14 17:54:24 2017 +0900) [2483973](https://github.com/kanryu/quickviewer/commit/2483973b5eeb8319f27ef8a8c8888f7d0db9c8dd)
    - Delete google64744654cbb28b4c.html (Wed Aug 9 12:48:39 2017 +0900) [3cbc81f](https://github.com/kanryu/quickviewer/commit/3cbc81f3f34d825384931e368e8dcd4cb1dcd4c3)
    - Add files via upload (Wed Aug 9 12:31:59 2017 +0900) [4e5f909](https://github.com/kanryu/quickviewer/commit/4e5f90977353d76c841b895c99a37017fac1e63c)
    - Update index.md (Wed Aug 9 09:59:51 2017 +0900) [ad58657](https://github.com/kanryu/quickviewer/commit/ad586576eb45f36a484fda7168ebacec25ab6f81)
    - Update index.md (Wed Aug 9 08:24:43 2017 +0900) [26a9e53](https://github.com/kanryu/quickviewer/commit/26a9e53006e3a2dc63129245b59b71c7ceba387b)

## v0.9.1 (Wed Aug 9 06:16:22 2017 +0900) [db68a38](https://github.com/kanryu/quickviewer/commit/db68a38d0ff1e41e209df7edc2c0ce937336a349)

changelog

- other commits
    - Removal of unnecessary warning output (Wed Aug 9 06:13:34 2017 +0900) [a12fc2d](https://github.com/kanryu/quickviewer/commit/a12fc2dd7f0232ba0edcb38d6bc68a2ce30df8d3)
    - Improvement of behavior, bugfixed (Wed Aug 9 02:36:47 2017 +0900) [2ae13f2](https://github.com/kanryu/quickviewer/commit/2ae13f2518ed3786ea14e0230888cb418c3081da)
    -  (Wed Aug 9 02:36:47 2017 +0900) [2ae13f2](https://github.com/kanryu/quickviewer/commit/2ae13f2518ed3786ea14e0230888cb418c3081da)
    -  Improvement of behavior when an image file is specified and opened (Wed Aug 9 02:36:47 2017 +0900) [2ae13f2](https://github.com/kanryu/quickviewer/commit/2ae13f2518ed3786ea14e0230888cb418c3081da)
    -  bugfixed: When the folder path was long in FolderWindow, the width of the window was widened (Wed Aug 9 02:36:47 2017 +0900) [2ae13f2](https://github.com/kanryu/quickviewer/commit/2ae13f2518ed3786ea14e0230888cb418c3081da)
    -  bugfixed: When the full screen signage was 2 page spread view, the left and right were opposite (Wed Aug 9 02:36:47 2017 +0900) [2ae13f2](https://github.com/kanryu/quickviewer/commit/2ae13f2518ed3786ea14e0230888cb418c3081da)

## v0.9.0_rev2 (Mon Aug 7 03:55:48 2017 +0900) [46a9f8b](https://github.com/kanryu/quickviewer/commit/46a9f8bf7a3ac400ef8425bc4d6901ed52f72acd)

changelog

- other commits
    - bugfixed: memory leak occurred if you made an image in the same folder more than once (Mon Aug 7 03:55:13 2017 +0900) [82c7c6e](https://github.com/kanryu/quickviewer/commit/82c7c6edecd478cb7cbec8c3d08ce6c53659d3e2)

## v0.9.0 (Mon Aug 7 02:16:58 2017 +0900) [b33d4bd](https://github.com/kanryu/quickviewer/commit/b33d4bd54d3741ad0fbcc0f1cc9fd4207e096af0)

changelog

- other commits
    - Improvement of file prefetching, zooming, bugfixed (Mon Aug 7 02:16:24 2017 +0900) [7c6a3f5](https://github.com/kanryu/quickviewer/commit/7c6a3f53d461f1d7c4dd0c93e07edf95e5ec6a00)
    -  (Mon Aug 7 02:16:24 2017 +0900) [7c6a3f5](https://github.com/kanryu/quickviewer/commit/7c6a3f53d461f1d7c4dd0c93e07edf95e5ec6a00)
    -  Improvement of file prefetching (Mon Aug 7 02:16:24 2017 +0900) [7c6a3f5](https://github.com/kanryu/quickviewer/commit/7c6a3f53d461f1d7c4dd0c93e07edf95e5ec6a00)
    -  Speedup when Volume Switching (Mon Aug 7 02:16:24 2017 +0900) [7c6a3f5](https://github.com/kanryu/quickviewer/commit/7c6a3f53d461f1d7c4dd0c93e07edf95e5ec6a00)
    -  Speedup when QuickViewer is opened with images specified (Mon Aug 7 02:16:24 2017 +0900) [7c6a3f5](https://github.com/kanryu/quickviewer/commit/7c6a3f53d461f1d7c4dd0c93e07edf95e5ec6a00)
    -  Switching the image while zooming will return to the upper left (Mon Aug 7 02:16:24 2017 +0900) [7c6a3f5](https://github.com/kanryu/quickviewer/commit/7c6a3f53d461f1d7c4dd0c93e07edf95e5ec6a00)
    -  bugfixed: images which mislabelled the extension, could not be opened (Mon Aug 7 02:16:24 2017 +0900) [7c6a3f5](https://github.com/kanryu/quickviewer/commit/7c6a3f53d461f1d7c4dd0c93e07edf95e5ec6a00)
    - build with MinGW (Sun Aug 6 02:14:58 2017 +0900) [c95d8bd](https://github.com/kanryu/quickviewer/commit/c95d8bdbd3518d60043104f8d616628e8d80971e)

## v0.8.9 (Sat Aug 5 04:33:47 2017 +0900) [bd2a8a0](https://github.com/kanryu/quickviewer/commit/bd2a8a0739c091ec68c4023960e87b1a40b3e579)

changelog

- other commits
    - Improved stability of x86 release, Speed up the Volume switching, 3 bugfixed (Sat Aug 5 04:33:11 2017 +0900) [9faebb7](https://github.com/kanryu/quickviewer/commit/9faebb765be55f498c6cecc2cf6fe9a57754c67f)
    -  (Sat Aug 5 04:33:11 2017 +0900) [9faebb7](https://github.com/kanryu/quickviewer/commit/9faebb765be55f498c6cecc2cf6fe9a57754c67f)
    -  Improved stability of x86 release (Sat Aug 5 04:33:11 2017 +0900) [9faebb7](https://github.com/kanryu/quickviewer/commit/9faebb765be55f498c6cecc2cf6fe9a57754c67f)
    -  bugfixed: Often, when an image exceeding 4096 pixels is read, it is illegitimate (Sat Aug 5 04:33:11 2017 +0900) [9faebb7](https://github.com/kanryu/quickviewer/commit/9faebb765be55f498c6cecc2cf6fe9a57754c67f)
    -  bugfixed: Irregular end when image loading high load (Sat Aug 5 04:33:11 2017 +0900) [9faebb7](https://github.com/kanryu/quickviewer/commit/9faebb765be55f498c6cecc2cf6fe9a57754c67f)
    -  Speed up the Volume switching (Sat Aug 5 04:33:11 2017 +0900) [9faebb7](https://github.com/kanryu/quickviewer/commit/9faebb765be55f498c6cecc2cf6fe9a57754c67f)
    -  bugfixed: Illegal termination when reading images from archives (Sat Aug 5 04:33:11 2017 +0900) [9faebb7](https://github.com/kanryu/quickviewer/commit/9faebb765be55f498c6cecc2cf6fe9a57754c67f)
    - Update index-ja.md (Thu Aug 3 19:14:37 2017 +0900) [bf8318b](https://github.com/kanryu/quickviewer/commit/bf8318ba309f3df5831d059d82f0aa7b4b113570)
    - Update index.md (Thu Aug 3 19:11:51 2017 +0900) [20a4ff1](https://github.com/kanryu/quickviewer/commit/20a4ff107b0781face7628ee365945f561845a3f)
    - Update README.md (Thu Aug 3 19:09:36 2017 +0900) [5df72b5](https://github.com/kanryu/quickviewer/commit/5df72b51e681652035171c90e37a4583e32bee5b)

## v0.8.8 (Thu Aug 3 12:45:26 2017 +0900) [923c221](https://github.com/kanryu/quickviewer/commit/923c221440543cb3fd11d81fad62a58c567dd28b)

changelog

- other commits
    - Improvement of English notation and toolbar display, Mouse input customization, bugfixed (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    -  (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    -  Improvement of English notation (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    -  Improvement of toolbar display (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    -  Each hidden bar is automatically displayed when hovering with the mouse (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    -  Mouse input customization (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    -  Customizable mouse input as well as shortcut key (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    -  bugfixed: When image or volume switching was performed in the state that the image leading was not completed, it was illegally terminated (Thu Aug 3 12:44:53 2017 +0900) [ddb84a3](https://github.com/kanryu/quickviewer/commit/ddb84a3e5eac6c00c9b9d61946f6e8f35f952d09)
    - Update HowToBuild.md (Mon Jul 31 17:39:37 2017 +0900) [e023382](https://github.com/kanryu/quickviewer/commit/e023382fbbb86ef110b97d2e66c087161ad5d022)
    - Update HowToBuild.md (Mon Jul 31 17:38:31 2017 +0900) [98bd792](https://github.com/kanryu/quickviewer/commit/98bd7921e5bc410ab387bb8179501162a675bcaa)
    - translations (Mon Jul 31 08:48:56 2017 +0900) [d7ee522](https://github.com/kanryu/quickviewer/commit/d7ee52244a239515b717ab0eb9b9ec495addd969)
    - Merge pull request #18 from Gitoffthelawn/patch-1 (Mon Jul 31 08:34:04 2017 +0900) [f99f61e](https://github.com/kanryu/quickviewer/commit/f99f61e18a9cd595967e80e15fc5f9ac1660e958)
    -  (Mon Jul 31 08:34:04 2017 +0900) [f99f61e](https://github.com/kanryu/quickviewer/commit/f99f61e18a9cd595967e80e15fc5f9ac1660e958)
    - Multiple improvements (Mon Jul 31 08:34:04 2017 +0900) [f99f61e](https://github.com/kanryu/quickviewer/commit/f99f61e18a9cd595967e80e15fc5f9ac1660e958)
    - don't create shared folders into bin (Mon Jul 31 08:24:54 2017 +0900) [21477f9](https://github.com/kanryu/quickviewer/commit/21477f98cdce72d418efea4aeaad8471cb4ab785)
    - Update HowToBuild.md (Mon Jul 31 08:17:41 2017 +0900) [d042920](https://github.com/kanryu/quickviewer/commit/d04292058d6ff9efbd300cb9a13b19eccc3a6f3b)
    - Update HowToBuild.md (Mon Jul 31 08:14:08 2017 +0900) [79d607a](https://github.com/kanryu/quickviewer/commit/79d607a9baa4ccc6ff66a8ebe12e4e7bcd366e1d)
    - Update HowToBuild.md (Mon Jul 31 08:03:03 2017 +0900) [0a20f2b](https://github.com/kanryu/quickviewer/commit/0a20f2bac69fadb95d6ee9b142d50538989214ee)
    - Update HowToBuild.md (Mon Jul 31 07:57:46 2017 +0900) [643b668](https://github.com/kanryu/quickviewer/commit/643b668d903cfdab9b1c8a09529627cd516a65a3)
    - Multiple improvements (Sun Jul 30 11:38:10 2017 -0700) [5006c25](https://github.com/kanryu/quickviewer/commit/5006c25b8cc9125ffd9aa4d6ace998ce718ffc63)
    -  (Sun Jul 30 11:38:10 2017 -0700) [5006c25](https://github.com/kanryu/quickviewer/commit/5006c25b8cc9125ffd9aa4d6ace998ce718ffc63)
    - I hope this helps you :) (Sun Jul 30 11:38:10 2017 -0700) [5006c25](https://github.com/kanryu/quickviewer/commit/5006c25b8cc9125ffd9aa4d6ace998ce718ffc63)

## v0.8.7 (Sun Jul 30 20:36:38 2017 +0900) [30967dc](https://github.com/kanryu/quickviewer/commit/30967dc30c09fd20efe0395f19442ea0e407c18b)

changelog

- other commits
    - Speed up of prefetching, 2 bugfixed (Sun Jul 30 20:35:42 2017 +0900) [7387d35](https://github.com/kanryu/quickviewer/commit/7387d35cd89c850ff500ec20f12b419c3ef7f23c)
    -  (Sun Jul 30 20:35:42 2017 +0900) [7387d35](https://github.com/kanryu/quickviewer/commit/7387d35cd89c850ff500ec20f12b419c3ef7f23c)
    -  Speed up by improvement of prefetching (Sun Jul 30 20:35:42 2017 +0900) [7387d35](https://github.com/kanryu/quickviewer/commit/7387d35cd89c850ff500ec20f12b419c3ef7f23c)
    -  Significant speedup of bicubic interpolation by CPU (Sun Jul 30 20:35:42 2017 +0900) [7387d35](https://github.com/kanryu/quickviewer/commit/7387d35cd89c850ff500ec20f12b419c3ef7f23c)
    -  bugfixed: occasionally ended illegally when PrevPage was executed (Sun Jul 30 20:35:42 2017 +0900) [7387d35](https://github.com/kanryu/quickviewer/commit/7387d35cd89c850ff500ec20f12b419c3ef7f23c)
    -  bugfixed: does not disappear when displaying the tool bar at full screen (Sun Jul 30 20:35:42 2017 +0900) [7387d35](https://github.com/kanryu/quickviewer/commit/7387d35cd89c850ff500ec20f12b419c3ef7f23c)
    - build check for gcc 5.4.0 on Ubuntu 16.04.4 (Sun Jul 30 03:26:58 2017 +0900) [cbf265e](https://github.com/kanryu/quickviewer/commit/cbf265e60b9ca4858753e1a7591a52e689dfe507)
    - removed duplicated source file specification (Sun Jul 30 02:41:18 2017 +0900) [c7d4171](https://github.com/kanryu/quickviewer/commit/c7d41711d72d9449a03a8fc439ba71c6701bea4e)

## v0.8.6 (Sun Jul 30 00:27:14 2017 +0900) [f7b5c41](https://github.com/kanryu/quickviewer/commit/f7b5c411e2f54ab1cbc991cac43c26fa0f8c185a)

changelog

- other commits
    - Support for ProhibitMultipleRunning, improved Toolbar/Menubar/PageBar behaviors (Sun Jul 30 00:26:32 2017 +0900) [a080bb1](https://github.com/kanryu/quickviewer/commit/a080bb1ca8c185f873b6bf5a3f6036cf26cd973c)
    -  (Sun Jul 30 00:26:32 2017 +0900) [a080bb1](https://github.com/kanryu/quickviewer/commit/a080bb1ca8c185f873b6bf5a3f6036cf26cd973c)
    -  Support for ProhibitMultipleRunning (Sun Jul 30 00:26:32 2017 +0900) [a080bb1](https://github.com/kanryu/quickviewer/commit/a080bb1ca8c185f873b6bf5a3f6036cf26cd973c)
    -  set as top window when run QuickViewr again (Sun Jul 30 00:26:32 2017 +0900) [a080bb1](https://github.com/kanryu/quickviewer/commit/a080bb1ca8c185f873b6bf5a3f6036cf26cd973c)
    -  Images will be loaded by first QuickViewr if you drop images onto the Executable file (Sun Jul 30 00:26:32 2017 +0900) [a080bb1](https://github.com/kanryu/quickviewer/commit/a080bb1ca8c185f873b6bf5a3f6036cf26cd973c)
    -  improved Toolbar/Menubar/PageBar behaviors (Sun Jul 30 00:26:32 2017 +0900) [a080bb1](https://github.com/kanryu/quickviewer/commit/a080bb1ca8c185f873b6bf5a3f6036cf26cd973c)
    -  Each hidden bar is automatically displayed when hovering with the mouse (Sun Jul 30 00:26:32 2017 +0900) [a080bb1](https://github.com/kanryu/quickviewer/commit/a080bb1ca8c185f873b6bf5a3f6036cf26cd973c)
    - Update shader-ja.md (Sat Jul 29 03:53:33 2017 +0900) [bf31d1b](https://github.com/kanryu/quickviewer/commit/bf31d1ba39812c32c20121975dc616b4d0a15bce)
    - Update shader.md (Sat Jul 29 03:50:47 2017 +0900) [9c109ce](https://github.com/kanryu/quickviewer/commit/9c109cee26481b1fdd8fc9186d06d29b13776072)
    - Update shader.md (Sat Jul 29 03:49:53 2017 +0900) [783ed72](https://github.com/kanryu/quickviewer/commit/783ed72ecab27c9ec9c573b10d41fbc8ed6fc8f6)
    - Update shader.md (Sat Jul 29 03:47:04 2017 +0900) [78221f8](https://github.com/kanryu/quickviewer/commit/78221f8809afc12fb49ef7d91b83a6b09c108530)
    - Update index-ja.md (Sat Jul 29 03:42:30 2017 +0900) [27cb10a](https://github.com/kanryu/quickviewer/commit/27cb10acdbd87a9d92890eda8ed8647ee83a6e34)
    - Update index.md (Sat Jul 29 03:40:41 2017 +0900) [baf24be](https://github.com/kanryu/quickviewer/commit/baf24be959cea61716877935594834dc6e2b3bc7)
    - Create shader-ja.md (Sat Jul 29 03:34:18 2017 +0900) [bc67998](https://github.com/kanryu/quickviewer/commit/bc67998fa0c7f6dc2dba31d8bfd334f08a5b07ef)
    - Add files via upload (Sat Jul 29 03:21:39 2017 +0900) [cc8f206](https://github.com/kanryu/quickviewer/commit/cc8f206a04990b5236153533cffb19986561d2bd)
    - Update shader.md (Sat Jul 29 03:20:32 2017 +0900) [dd595b9](https://github.com/kanryu/quickviewer/commit/dd595b909158b0e888e2d1b9d33c3e446c25f039)
    - Add files via upload (Sat Jul 29 03:19:11 2017 +0900) [f75396f](https://github.com/kanryu/quickviewer/commit/f75396fd66dea3b41666655a7877b5d4e2bfb3c4)
    - Add files via upload (Sat Jul 29 03:12:07 2017 +0900) [f7b46fe](https://github.com/kanryu/quickviewer/commit/f7b46fed2c4cb93d4acf2b2f4ff132ccd9c62c3f)
    - Update shader.md (Sat Jul 29 03:10:21 2017 +0900) [dc7d752](https://github.com/kanryu/quickviewer/commit/dc7d7524c7772984df25d10da40afaac2cde0381)
    - Update shader.md (Sat Jul 29 03:08:13 2017 +0900) [360e121](https://github.com/kanryu/quickviewer/commit/360e1216a86bb0fd5a89a5c1e8f6f6a12175504e)
    - Add files via upload (Sat Jul 29 03:05:47 2017 +0900) [81d9e89](https://github.com/kanryu/quickviewer/commit/81d9e8917df501ff9a0eab4f6b54bf2c958c7a95)
    - Update shader.md (Sat Jul 29 03:04:50 2017 +0900) [068ef9b](https://github.com/kanryu/quickviewer/commit/068ef9bd5fda9aa414a690d045c3433b3c14fe2a)
    - Update shader.md (Sat Jul 29 03:04:04 2017 +0900) [b1623ab](https://github.com/kanryu/quickviewer/commit/b1623abbd39348460eac4e8aa46c568fc8877781)
    - Create shader.md (Sat Jul 29 02:49:11 2017 +0900) [e1ccc27](https://github.com/kanryu/quickviewer/commit/e1ccc27418b02d2a1be3e1431a23b12c47d99936)
    - Update index.md (Sat Jul 29 01:52:05 2017 +0900) [6c47fdf](https://github.com/kanryu/quickviewer/commit/6c47fdf4fabd588af39ad53f6a7b9e282219e249)
    - Update index.md (Fri Jul 28 12:00:41 2017 +0900) [c83e69b](https://github.com/kanryu/quickviewer/commit/c83e69bccb9cbaa2168cb6495a267634f1744960)
    - Update README.md (Fri Jul 28 11:54:28 2017 +0900) [2e7b6ce](https://github.com/kanryu/quickviewer/commit/2e7b6ceac13f6ebe9aecef04c0d122b6bd867fdd)
    - Update README.md (Fri Jul 28 11:52:11 2017 +0900) [d63345d](https://github.com/kanryu/quickviewer/commit/d63345d74614dbf4f01b4ea6499225cb65af3607)

## v0.8.5_rev2 (Fri Jul 28 02:19:27 2017 +0900) [3da4349](https://github.com/kanryu/quickviewer/commit/3da43497c1b5a66e23e641557f10e5ed57819949)

changelog

- other commits
    - merged (Fri Jul 28 02:16:55 2017 +0900) [27d1cf0](https://github.com/kanryu/quickviewer/commit/27d1cf0bec05889c66f4ae5152d42cd469338853)
    - changelog (Fri Jul 28 02:03:02 2017 +0900) [02e7ee0](https://github.com/kanryu/quickviewer/commit/02e7ee0323a7fbe0a7466dde4bdb8d16c236c130)
    - Improve the behavior at fullscreen (Fri Jul 28 02:02:25 2017 +0900) [d335d27](https://github.com/kanryu/quickviewer/commit/d335d2736117ecbc27a2513bfa83c074eca0e14c)
    -  (Fri Jul 28 02:02:25 2017 +0900) [d335d27](https://github.com/kanryu/quickviewer/commit/d335d2736117ecbc27a2513bfa83c074eca0e14c)
    -  add Frame-less fullscreen toolbar (Fri Jul 28 02:02:25 2017 +0900) [d335d27](https://github.com/kanryu/quickviewer/commit/d335d2736117ecbc27a2513bfa83c074eca0e14c)
    -  Improve the behavior of pagebar at fullscreen (Fri Jul 28 02:02:25 2017 +0900) [d335d27](https://github.com/kanryu/quickviewer/commit/d335d2736117ecbc27a2513bfa83c074eca0e14c)
    - qlanguageselector (Fri Jul 28 01:51:03 2017 +0900) [96c46a3](https://github.com/kanryu/quickviewer/commit/96c46a393296b824aec7a7378c2b872762520ca0)
    - qlanguageselector (Fri Jul 28 01:43:40 2017 +0900) [302a993](https://github.com/kanryu/quickviewer/commit/302a99316168569729e49f9bc593e2bc9c1e6384)
    - Update index.md (Thu Jul 27 21:23:42 2017 +0900) [7fd1b8f](https://github.com/kanryu/quickviewer/commit/7fd1b8f411b364d5e3c20d9baa672f8cf96dca2a)
    - Update HowToBuild.md (Thu Jul 27 15:50:04 2017 +0900) [80bf0d6](https://github.com/kanryu/quickviewer/commit/80bf0d65c20e6f82801e37ab7b6d2096d1d01090)

## v0.8.4 (Wed Jul 26 23:03:40 2017 +0900) [46df730](https://github.com/kanryu/quickviewer/commit/46df730c25c80baac3120f5fc59df49dc108e01c)

changelog

- other commits
    - Improvement on fullscreen, calibrated English notation (Wed Jul 26 23:03:10 2017 +0900) [a55339f](https://github.com/kanryu/quickviewer/commit/a55339f150e1273685d7e7004c3a0aa927c1bca9)
    -  (Wed Jul 26 23:03:10 2017 +0900) [a55339f](https://github.com/kanryu/quickviewer/commit/a55339f150e1273685d7e7004c3a0aa927c1bca9)
    -  Improvement on how to display the toolbar at fullscreen (Wed Jul 26 23:03:10 2017 +0900) [a55339f](https://github.com/kanryu/quickviewer/commit/a55339f150e1273685d7e7004c3a0aa927c1bca9)
    -  calibrated English notation of QuickViewer (Wed Jul 26 23:03:10 2017 +0900) [a55339f](https://github.com/kanryu/quickviewer/commit/a55339f150e1273685d7e7004c3a0aa927c1bca9)
    -  Since Spanish or Chinese notation was manually fixed, it may be wrong (Wed Jul 26 23:03:10 2017 +0900) [a55339f](https://github.com/kanryu/quickviewer/commit/a55339f150e1273685d7e7004c3a0aa927c1bca9)
    - English Notation (Wed Jul 26 02:59:21 2017 +0900) [415425f](https://github.com/kanryu/quickviewer/commit/415425fe02edb3e5d11a9a60aa58fbfaf690d584)
    - Improvement on how to display the toolbar at full screen (Wed Jul 26 02:10:29 2017 +0900) [6173437](https://github.com/kanryu/quickviewer/commit/6173437db9b9934068715b9874731877fd9ee891)
    - add comments for translators (Sat Jul 22 23:38:05 2017 +0900) [3f75cb0](https://github.com/kanryu/quickviewer/commit/3f75cb00de8dedeb26a4b116911b3cdfc257ce72)

## v0.8.3 (Fri Jul 21 20:25:14 2017 +0900) [00d942d](https://github.com/kanryu/quickviewer/commit/00d942d3148037c77756783e73b1eb31d05d34c9)

changelog

- other commits
    - Support for Simplified Chinese, file associations, not confirm to delete file (Fri Jul 21 20:24:49 2017 +0900) [e3057fd](https://github.com/kanryu/quickviewer/commit/e3057fdaaee047a77462f6715dcfaaa076474818)
    -  (Fri Jul 21 20:24:49 2017 +0900) [e3057fd](https://github.com/kanryu/quickviewer/commit/e3057fdaaee047a77462f6715dcfaaa076474818)
    -  Support for Simplified Chinese (Fri Jul 21 20:24:49 2017 +0900) [e3057fd](https://github.com/kanryu/quickviewer/commit/e3057fdaaee047a77462f6715dcfaaa076474818)
    -  now you can add other language support without editing programs (Fri Jul 21 20:24:49 2017 +0900) [e3057fd](https://github.com/kanryu/quickviewer/commit/e3057fdaaee047a77462f6715dcfaaa076474818)
    -  Support for file assciations (Fri Jul 21 20:24:49 2017 +0900) [e3057fd](https://github.com/kanryu/quickviewer/commit/e3057fdaaee047a77462f6715dcfaaa076474818)
    -  not portable, but If you do not run it will not change to the system (Fri Jul 21 20:24:49 2017 +0900) [e3057fd](https://github.com/kanryu/quickviewer/commit/e3057fdaaee047a77462f6715dcfaaa076474818)
    -  not confirm to delete file (Fri Jul 21 20:24:49 2017 +0900) [e3057fd](https://github.com/kanryu/quickviewer/commit/e3057fdaaee047a77462f6715dcfaaa076474818)
    - Update index.md (Thu Jul 20 04:21:59 2017 +0900) [e3e3735](https://github.com/kanryu/quickviewer/commit/e3e37353263782175db60403fd83c7eabb548b5f)
    - Update HowToBuild.md (Sun Jul 16 16:17:37 2017 +0900) [d5e4c23](https://github.com/kanryu/quickviewer/commit/d5e4c238d3a763550e555495f0e3a0e567498496)
    - Update index.md (Sun Jul 16 15:29:46 2017 +0900) [5140d2d](https://github.com/kanryu/quickviewer/commit/5140d2deb674cb9f817b78caffc2a0dce6b2d932)
    - Update index.md (Sun Jul 16 15:28:48 2017 +0900) [e7f895b](https://github.com/kanryu/quickviewer/commit/e7f895bdac20a28c6268a5769a8e7dd17c0ef4d9)
    - Update HowToBuild.md (Sun Jul 16 11:04:04 2017 +0900) [d8429f8](https://github.com/kanryu/quickviewer/commit/d8429f81444a696c184581938191506cd15a4f83)
    - Update HowToBuild.md (Sat Jul 15 23:43:00 2017 +0900) [ee4c5a2](https://github.com/kanryu/quickviewer/commit/ee4c5a2b3bf594dd3778bdb6019b45d7782e63bc)
    - Update HowToBuild.md (Sat Jul 15 23:12:15 2017 +0900) [b3ee717](https://github.com/kanryu/quickviewer/commit/b3ee7173b84305311e63d03ca67cbbcd097881fe)
    - Update HowToBuild.md (Sat Jul 15 03:51:55 2017 +0900) [e8e71ed](https://github.com/kanryu/quickviewer/commit/e8e71eda92648ffaf54b481b8c682ec2df04419b)
    - Update HowToBuild.md (Sat Jul 15 03:50:48 2017 +0900) [97afceb](https://github.com/kanryu/quickviewer/commit/97afceb2743668aef22320e7fe81cf9d1729073a)
    - Update HowToBuild.md (Sat Jul 15 03:34:46 2017 +0900) [ec348a9](https://github.com/kanryu/quickviewer/commit/ec348a906adc9da47268728ba89928b7770f28b1)
    - Update HowToBuild.md (Sat Jul 15 03:32:06 2017 +0900) [d6b443a](https://github.com/kanryu/quickviewer/commit/d6b443af3bf28ceee19efc0761cc8aff8a001e13)
    - Update HowToBuild.md (Sat Jul 15 03:28:33 2017 +0900) [f563965](https://github.com/kanryu/quickviewer/commit/f56396563164723c5c5616dcbeebd8bfb4d589d2)
    - Update HowToBuild.md (Sat Jul 15 03:28:09 2017 +0900) [1c296c4](https://github.com/kanryu/quickviewer/commit/1c296c4b969681ba20869d0fd6e1b9531711f4b3)
    - Update HowToBuild.md (Sat Jul 15 03:25:19 2017 +0900) [cc71203](https://github.com/kanryu/quickviewer/commit/cc7120367317e70fae26b78e7fca44adff59e3ff)
    - Update HowToBuild.md (Sat Jul 15 03:23:45 2017 +0900) [65aa56b](https://github.com/kanryu/quickviewer/commit/65aa56bc87f2000527dcc471dfea46bdbd8ec3af)
    - Create HowToBuild.md (Sat Jul 15 03:20:36 2017 +0900) [1001134](https://github.com/kanryu/quickviewer/commit/1001134da20548a969284bfaa1cf5ba1c63b034f)
    - add chinise resource, remove doubled source files (Sat Jul 15 01:22:45 2017 +0900) [3f9b2b9](https://github.com/kanryu/quickviewer/commit/3f9b2b9311b770565b2c321730ccc9d8f0519edc)
    -  (Sat Jul 15 01:22:45 2017 +0900) [3f9b2b9](https://github.com/kanryu/quickviewer/commit/3f9b2b9311b770565b2c321730ccc9d8f0519edc)
    -  add chinise resource (Sat Jul 15 01:22:45 2017 +0900) [3f9b2b9](https://github.com/kanryu/quickviewer/commit/3f9b2b9311b770565b2c321730ccc9d8f0519edc)
    -  remove doubled source files (Sat Jul 15 01:22:45 2017 +0900) [3f9b2b9](https://github.com/kanryu/quickviewer/commit/3f9b2b9311b770565b2c321730ccc9d8f0519edc)

## v0.8.2 (Thu Jul 13 20:31:50 2017 +0900) [c1d97ab](https://github.com/kanryu/quickviewer/commit/c1d97abf74b873e044d1dba2705d58028a4a82b6)

changelog

- other commits
    - Support display in Spanish, change language, start on fullscreen, fullscreen signage, bugfixed (Thu Jul 13 20:31:16 2017 +0900) [a8a2982](https://github.com/kanryu/quickviewer/commit/a8a298257d7666ff7bb91ab55b7f177d02399351)
    -  (Thu Jul 13 20:31:16 2017 +0900) [a8a2982](https://github.com/kanryu/quickviewer/commit/a8a298257d7666ff7bb91ab55b7f177d02399351)
    -  change language on the app, you select (Thu Jul 13 20:31:16 2017 +0900) [a8a2982](https://github.com/kanryu/quickviewer/commit/a8a298257d7666ff7bb91ab55b7f177d02399351)
    -  start the app on fullscreen (Thu Jul 13 20:31:16 2017 +0900) [a8a2982](https://github.com/kanryu/quickviewer/commit/a8a298257d7666ff7bb91ab55b7f177d02399351)
    -  a signage of fullpath of the image on fullscreen (Thu Jul 13 20:31:16 2017 +0900) [a8a2982](https://github.com/kanryu/quickviewer/commit/a8a298257d7666ff7bb91ab55b7f177d02399351)
    -  bugfixed: While using CPU zooming, displaying an animation image was incorrectly terminated (Thu Jul 13 20:31:16 2017 +0900) [a8a2982](https://github.com/kanryu/quickviewer/commit/a8a298257d7666ff7bb91ab55b7f177d02399351)
    - Update index-ja.md (Wed Jul 12 01:28:43 2017 +0900) [ec61c4a](https://github.com/kanryu/quickviewer/commit/ec61c4a1d7d5e0ddd5ba249a480c0b4908987e66)
    - Update index.md (Wed Jul 12 01:28:14 2017 +0900) [fcc287f](https://github.com/kanryu/quickviewer/commit/fcc287f5ffa2f274ed2ae5aa2414002715fbf6b1)
    - Update README.md (Wed Jul 12 01:27:47 2017 +0900) [bbe8d04](https://github.com/kanryu/quickviewer/commit/bbe8d0469469044aa7a6934104a01e18bd5d20db)
    - Update README.md (Wed Jul 12 00:03:28 2017 +0900) [87321d9](https://github.com/kanryu/quickviewer/commit/87321d97c198e6744324749c5651b6e647f78a38)
    - Update index.md (Tue Jul 11 23:55:23 2017 +0900) [004177d](https://github.com/kanryu/quickviewer/commit/004177d84edfc556038ff80ffba3c1f926228634)
    - Update index-ja.md (Tue Jul 11 23:54:54 2017 +0900) [f68faef](https://github.com/kanryu/quickviewer/commit/f68faef636b065c69747e9ade6a787998b7dc1b6)
    - Update index-ja.md (Tue Jul 11 23:54:01 2017 +0900) [795f49d](https://github.com/kanryu/quickviewer/commit/795f49dd6e32212fecbb4cc5deee6b451f4d6959)
    - Update index.md (Tue Jul 11 23:53:08 2017 +0900) [1a28122](https://github.com/kanryu/quickviewer/commit/1a281220dae99740390e290257be59101cd00c4f)
    - Update README.md (Tue Jul 11 23:52:28 2017 +0900) [6d0851d](https://github.com/kanryu/quickviewer/commit/6d0851db3f0ccd357a3597b7dd870c2a8eca9d2d)

## v0.8.1 (Tue Jul 11 23:45:41 2017 +0900) [6ff7371](https://github.com/kanryu/quickviewer/commit/6ff73717a6de41d96a4f590dfcc8b30527e762dc)

Merge branch 'master' of https://github.com/kanryu/quickviewer

- other commits
    - changelog (Tue Jul 11 23:45:15 2017 +0900) [15a1645](https://github.com/kanryu/quickviewer/commit/15a164502aef9e7f1c2ebc51e4e686de94f81055)
    - Support for Animated PNG(APNG), read completed check, improve ExifDialog (Tue Jul 11 23:44:39 2017 +0900) [aef78a1](https://github.com/kanryu/quickviewer/commit/aef78a1b5d7f308a4a41ca7a914e1597bbb189f6)
    -  (Tue Jul 11 23:44:39 2017 +0900) [aef78a1](https://github.com/kanryu/quickviewer/commit/aef78a1b5d7f308a4a41ca7a914e1597bbb189f6)
    -  read completed check, if you read complate, FolderWindow shows a green bar (Tue Jul 11 23:44:39 2017 +0900) [aef78a1](https://github.com/kanryu/quickviewer/commit/aef78a1b5d7f308a4a41ca7a914e1597bbb189f6)
    -  improve ExifDialog (Tue Jul 11 23:44:39 2017 +0900) [aef78a1](https://github.com/kanryu/quickviewer/commit/aef78a1b5d7f308a4a41ca7a914e1597bbb189f6)
    -  will be embedded (Tue Jul 11 23:44:39 2017 +0900) [aef78a1](https://github.com/kanryu/quickviewer/commit/aef78a1b5d7f308a4a41ca7a914e1597bbb189f6)
    -  can next/prev changing (Tue Jul 11 23:44:39 2017 +0900) [aef78a1](https://github.com/kanryu/quickviewer/commit/aef78a1b5d7f308a4a41ca7a914e1597bbb189f6)
    - Update index.md (Tue Jul 11 14:43:55 2017 +0900) [a6b72f5](https://github.com/kanryu/quickviewer/commit/a6b72f5513e5e2c172baab765c53b4367ba747f9)
    - Update default.html (Tue Jul 11 12:09:03 2017 +0900) [0eb9b32](https://github.com/kanryu/quickviewer/commit/0eb9b327d563f8414a9e57b0b572de798c71dbd3)
    - Update disqus.html (Tue Jul 11 12:07:07 2017 +0900) [e6d5951](https://github.com/kanryu/quickviewer/commit/e6d59513f83e886de02c1ec2d2f59c2f329ac5c1)
    - Update disqus.html (Tue Jul 11 12:03:38 2017 +0900) [9a3a91e](https://github.com/kanryu/quickviewer/commit/9a3a91e03cce9c611e57cb9cfc527555e57987c8)
    - Update index-ja.md (Tue Jul 11 12:00:01 2017 +0900) [6736171](https://github.com/kanryu/quickviewer/commit/6736171de1ce263ccbc9e148be54e5b5e676f8d6)
    - Update disqus.html (Tue Jul 11 11:57:57 2017 +0900) [a37b17a](https://github.com/kanryu/quickviewer/commit/a37b17a6d9a9f4e004da93ab21cf957600a637bd)
    - Update default.html (Tue Jul 11 11:57:31 2017 +0900) [5dba1b4](https://github.com/kanryu/quickviewer/commit/5dba1b4f7b60d875d3cc02e5138c697e40798d65)
    - Update default.html (Tue Jul 11 11:55:50 2017 +0900) [2611490](https://github.com/kanryu/quickviewer/commit/26114908c1415cb61b8545995f2964af76a3da0a)
    - Update default.html (Tue Jul 11 11:45:44 2017 +0900) [d9dabb9](https://github.com/kanryu/quickviewer/commit/d9dabb9a31c75843c67bd9512de98c1dec21e655)
    - Update default.html (Tue Jul 11 11:43:28 2017 +0900) [e03319a](https://github.com/kanryu/quickviewer/commit/e03319aaf02d3632b3de2750ee45a8efd8df33c5)
    - Update default.html (Tue Jul 11 11:42:04 2017 +0900) [d3250c2](https://github.com/kanryu/quickviewer/commit/d3250c22a5d8fa415bbeabddd205b2d94672d89c)
    - Update default.html (Tue Jul 11 11:38:59 2017 +0900) [83491b0](https://github.com/kanryu/quickviewer/commit/83491b0f6105fec854b9ab3b9dc3e782d9d4b1d3)
    - Update default.html (Tue Jul 11 11:37:38 2017 +0900) [9b1c22e](https://github.com/kanryu/quickviewer/commit/9b1c22e3f5203ed2d8a91c99cf213316ebf9a170)
    - Update index.md (Tue Jul 11 11:34:35 2017 +0900) [f1b0104](https://github.com/kanryu/quickviewer/commit/f1b0104f12554bb0cf3c28d0ce72f46f7925e743)
    - disqus (Tue Jul 11 11:34:14 2017 +0900) [39fc33e](https://github.com/kanryu/quickviewer/commit/39fc33e755458624d845f7ea1bb845af555546df)
    - Update index.md (Tue Jul 11 11:20:33 2017 +0900) [4e86e0e](https://github.com/kanryu/quickviewer/commit/4e86e0e64f4152d61c4994efb89741739efffc69)
    - Update index.md (Sun Jul 9 12:07:55 2017 +0900) [a6bcc20](https://github.com/kanryu/quickviewer/commit/a6bcc202e335e8d8aeea687c2e5aa0c2f3a14110)
    - Update index.md (Sat Jul 8 10:33:13 2017 +0900) [4e9c154](https://github.com/kanryu/quickviewer/commit/4e9c1549f59b809ae670d1d9f70298eded5f42b2)
    - Update index.md (Sat Jul 8 10:22:49 2017 +0900) [c3c9cc2](https://github.com/kanryu/quickviewer/commit/c3c9cc2980d8afde0617904921513a4db80e82d2)
    - Update index.md (Sat Jul 8 10:17:29 2017 +0900) [708a71c](https://github.com/kanryu/quickviewer/commit/708a71c630cd10d0b2a8bb87d602f714ce2071a4)
    - Update index.md (Sat Jul 8 10:15:54 2017 +0900) [7825b98](https://github.com/kanryu/quickviewer/commit/7825b98918dd41b788d75da6c7a2668e9c60f89a)
    - Update index.md (Fri Jul 7 23:32:47 2017 +0900) [f80a381](https://github.com/kanryu/quickviewer/commit/f80a38152be4bab214d0a8aff234417a2e57d550)
    - Update index-ja.md (Fri Jul 7 19:08:31 2017 +0900) [f100b44](https://github.com/kanryu/quickviewer/commit/f100b44671102342ee54f283de026a1ed69de4c3)
    - Update README.md (Fri Jul 7 19:05:58 2017 +0900) [f439a28](https://github.com/kanryu/quickviewer/commit/f439a289647731f2f878860d1653cf5bd1659ee2)
    - Update index.md (Fri Jul 7 19:05:55 2017 +0900) [264cf0c](https://github.com/kanryu/quickviewer/commit/264cf0ca918047a9133b27d7d9fd8ddb4751190b)
    - Update README.md (Fri Jul 7 19:01:20 2017 +0900) [127874e](https://github.com/kanryu/quickviewer/commit/127874edf57ff4b73f0775c05563a7da91527b3d)

## v0.8.0 (Fri Jul 7 18:22:43 2017 +0900) [bc588dd](https://github.com/kanryu/quickviewer/commit/bc588dd2bb99c862df070c85211aa105218a18b2)

changelog

- other commits
    - support animation GIFs, mouse wheel resizing, bugfixed (Fri Jul 7 18:22:05 2017 +0900) [67ff497](https://github.com/kanryu/quickviewer/commit/67ff49720fd40bbec1e232692d30d530516aa652)
    -  (Fri Jul 7 18:22:05 2017 +0900) [67ff497](https://github.com/kanryu/quickviewer/commit/67ff49720fd40bbec1e232692d30d530516aa652)
    -  support animation GIFs(Not enough when CPU resizing) (Fri Jul 7 18:22:05 2017 +0900) [67ff497](https://github.com/kanryu/quickviewer/commit/67ff49720fd40bbec1e232692d30d530516aa652)
    -  mouse wheel resizing (Fri Jul 7 18:22:05 2017 +0900) [67ff497](https://github.com/kanryu/quickviewer/commit/67ff49720fd40bbec1e232692d30d530516aa652)
    -  Ctrl+Wheel Clicked/Right Button+Wheel Clicked: toggle Fitting (Fri Jul 7 18:22:05 2017 +0900) [67ff497](https://github.com/kanryu/quickviewer/commit/67ff49720fd40bbec1e232692d30d530516aa652)
    -  Ctrl+Wheel Scrolled/Right Button+Wheel Scrolled: manual resizing (Fri Jul 7 18:22:05 2017 +0900) [67ff497](https://github.com/kanryu/quickviewer/commit/67ff49720fd40bbec1e232692d30d530516aa652)
    -  bugfixed: left trimmed when images bigger than the window (Fri Jul 7 18:22:05 2017 +0900) [67ff497](https://github.com/kanryu/quickviewer/commit/67ff49720fd40bbec1e232692d30d530516aa652)
    - Update index.md (Wed Jul 5 23:42:19 2017 +0900) [85e6a54](https://github.com/kanryu/quickviewer/commit/85e6a543700b5585c370e6a3c9c24cac15a464e5)

## v0.7.8 (Wed Jul 5 19:02:03 2017 +0900) [e565436](https://github.com/kanryu/quickviewer/commit/e5654367e0c8c52325eacad674332a9c34e576dc)

changelog

- other commits
    - support for drag scrolling, show original size, fixed wheel paging (Wed Jul 5 19:01:13 2017 +0900) [e6a2ef9](https://github.com/kanryu/quickviewer/commit/e6a2ef958d392840147b6a649488c6c1df1695d8)
    -  (Wed Jul 5 19:01:13 2017 +0900) [e6a2ef9](https://github.com/kanryu/quickviewer/commit/e6a2ef958d392840147b6a649488c6c1df1695d8)
    -  support for drag scrolling when images bigger than window (Wed Jul 5 19:01:13 2017 +0900) [e6a2ef9](https://github.com/kanryu/quickviewer/commit/e6a2ef958d392840147b6a649488c6c1df1695d8)
    -  show original size when images smaller than window on fitting (Wed Jul 5 19:01:13 2017 +0900) [e6a2ef9](https://github.com/kanryu/quickviewer/commit/e6a2ef958d392840147b6a649488c6c1df1695d8)
    -  fixed: wheel paging when images bigger than window (Wed Jul 5 19:01:13 2017 +0900) [e6a2ef9](https://github.com/kanryu/quickviewer/commit/e6a2ef958d392840147b6a649488c6c1df1695d8)
    - Update index-ja.md (Wed Jul 5 11:57:45 2017 +0900) [6c5af91](https://github.com/kanryu/quickviewer/commit/6c5af919f70ee12e8ffcb222c31d827ea799b26d)
    - Update index.md (Tue Jul 4 19:15:47 2017 +0900) [32e4396](https://github.com/kanryu/quickviewer/commit/32e4396f1ed0096017255045b6c0f058db036f7c)
    - Update index.md (Tue Jul 4 18:36:07 2017 +0900) [25d60c4](https://github.com/kanryu/quickviewer/commit/25d60c4e835df8e327d5b8bca2c3c03970256348)
    - Update index.md (Tue Jul 4 18:26:28 2017 +0900) [2ba6907](https://github.com/kanryu/quickviewer/commit/2ba6907dc01a49018767a4e2c8a910ed2f0ace4c)
    - Update index.md (Tue Jul 4 18:18:51 2017 +0900) [a6ac7da](https://github.com/kanryu/quickviewer/commit/a6ac7da1b950a84985d261ac1b7a1cf600e41347)

## v0.7.7 (Tue Jul 4 13:22:29 2017 +0900) [e9682d0](https://github.com/kanryu/quickviewer/commit/e9682d0a3bfa39a92b03dbef5a78e3e7f11bb141)

changelog

- other commits
    - add support to Rename, change background color, bugfixed (Tue Jul 4 13:21:25 2017 +0900) [9ac7966](https://github.com/kanryu/quickviewer/commit/9ac79669ef8162e4ea8ce54e10d196899e2fe7a8)
    -  (Tue Jul 4 13:21:25 2017 +0900) [9ac7966](https://github.com/kanryu/quickviewer/commit/9ac79669ef8162e4ea8ce54e10d196899e2fe7a8)
    -  support to Rename current image file, only for folders (Tue Jul 4 13:21:25 2017 +0900) [9ac7966](https://github.com/kanryu/quickviewer/commit/9ac79669ef8162e4ea8ce54e10d196899e2fe7a8)
    -  support to change background color, can be checkered pattern (Tue Jul 4 13:21:25 2017 +0900) [9ac7966](https://github.com/kanryu/quickviewer/commit/9ac79669ef8162e4ea8ce54e10d196899e2fe7a8)
    -  bugfixed: if set max volume cache < 4, changing the volume resulted in an unauthorized termination (Tue Jul 4 13:21:25 2017 +0900) [9ac7966](https://github.com/kanryu/quickviewer/commit/9ac79669ef8162e4ea8ce54e10d196899e2fe7a8)
    -  buffixed: If the volume is already read, even if you specify the file of the folder and open the volume, the read file was opened (Tue Jul 4 13:21:25 2017 +0900) [9ac7966](https://github.com/kanryu/quickviewer/commit/9ac79669ef8162e4ea8ce54e10d196899e2fe7a8)
    - Update index.md (Sat Jul 1 08:48:06 2017 +0900) [391deec](https://github.com/kanryu/quickviewer/commit/391deec64cf9627bbbdc4e092f42c8ded72390fc)
    - Update index.md (Sat Jul 1 08:28:57 2017 +0900) [c9e7929](https://github.com/kanryu/quickviewer/commit/c9e7929c87cfd46722672233a3aeb68bdee1c7ab)
    - Update index.md (Sat Jul 1 08:26:45 2017 +0900) [380b5f5](https://github.com/kanryu/quickviewer/commit/380b5f5a133d57164e334f25e9c2c8e0570ec2fc)
    - changelog (Thu Jun 29 17:10:20 2017 +0900) [9694db2](https://github.com/kanryu/quickviewer/commit/9694db2c9a4c60bc7fed624dce8802f8eacbf697)
    - Support for resizing Alpha Images by CPU, add Option Dialog, save memory (Thu Jun 29 17:01:28 2017 +0900) [e472373](https://github.com/kanryu/quickviewer/commit/e47237378ac3b2d84d29d0a895c572eac32829a3)
    -  (Thu Jun 29 17:01:28 2017 +0900) [e472373](https://github.com/kanryu/quickviewer/commit/e47237378ac3b2d84d29d0a895c572eac32829a3)
    -  Support for resizing Alpha Images by CPU(zimg) (Thu Jun 29 17:01:28 2017 +0900) [e472373](https://github.com/kanryu/quickviewer/commit/e47237378ac3b2d84d29d0a895c572eac32829a3)
    -  add Option Dialog(2 options) (Thu Jun 29 17:01:28 2017 +0900) [e472373](https://github.com/kanryu/quickviewer/commit/e47237378ac3b2d84d29d0a895c572eac32829a3)
    -  save memory hack(x86) (Thu Jun 29 17:01:28 2017 +0900) [e472373](https://github.com/kanryu/quickviewer/commit/e47237378ac3b2d84d29d0a895c572eac32829a3)

## v0.7.6 (Wed Jun 28 11:21:59 2017 +0900) [84cce6c](https://github.com/kanryu/quickviewer/commit/84cce6c22267be8c438c596dbad8d050d79b210f)

add language resource for Spanish

- other commits
    - Update index.md (Wed Jun 28 04:11:33 2017 +0900) [8d82be9](https://github.com/kanryu/quickviewer/commit/8d82be9237c26555329d1e4b8b5891cbaf785d93)
    - Update index.md (Wed Jun 28 03:52:28 2017 +0900) [f065230](https://github.com/kanryu/quickviewer/commit/f065230b4035d58098c01caa7bbcd5806572726e)
    - Update index.md (Wed Jun 28 03:38:19 2017 +0900) [18c7d40](https://github.com/kanryu/quickviewer/commit/18c7d407c9dd5f207fa3bb1dd845be08a3794490)

## v0.7.5 (Fri Jun 16 04:42:31 2017 +0900) [d6e7cc2](https://github.com/kanryu/quickviewer/commit/d6e7cc2b5e78ab6df2bad5563a643302ab9d863d)

changelog

- other commits
    - 4 bugfixed (Fri Jun 16 04:41:20 2017 +0900) [c477d7f](https://github.com/kanryu/quickviewer/commit/c477d7f3a79e66aec97f44133542e793d43f9207)
    -  (Fri Jun 16 04:41:20 2017 +0900) [c477d7f](https://github.com/kanryu/quickviewer/commit/c477d7f3a79e66aec97f44133542e793d43f9207)
    -  bugfixed: Opening the volume again after reading over 10 pages resulted in an unauthorized termination (Fri Jun 16 04:41:20 2017 +0900) [c477d7f](https://github.com/kanryu/quickviewer/commit/c477d7f3a79e66aec97f44133542e793d43f9207)
    -  bugfixed: Keyboard input did not work if FolderWindow is displayed in the main window (Fri Jun 16 04:41:20 2017 +0900) [c477d7f](https://github.com/kanryu/quickviewer/commit/c477d7f3a79e66aec97f44133542e793d43f9207)
    -  bugfixed: The image was not loaded even if switching the volume with the keyboard in FolderWindow (Fri Jun 16 04:41:20 2017 +0900) [c477d7f](https://github.com/kanryu/quickviewer/commit/c477d7f3a79e66aec97f44133542e793d43f9207)
    -  bugfixed: After switching to another Volume with SpreadViewing, and go back to original Volume, it goes one page (Fri Jun 16 04:41:20 2017 +0900) [c477d7f](https://github.com/kanryu/quickviewer/commit/c477d7f3a79e66aec97f44133542e793d43f9207)
    -  changed: for including some Qt common headers (Fri Jun 16 04:41:20 2017 +0900) [c477d7f](https://github.com/kanryu/quickviewer/commit/c477d7f3a79e66aec97f44133542e793d43f9207)

## v0.7.4 (Thu Jun 15 05:04:28 2017 +0900) [8e1b3ea](https://github.com/kanryu/quickviewer/commit/8e1b3eaa6ba115896355ee730a21708c435107bf)

changelog

- other commits
    - Record/Show/Load read progress of volumes (Thu Jun 15 05:03:53 2017 +0900) [9043573](https://github.com/kanryu/quickviewer/commit/90435737146b3a12d77660fcb9e73a648a5efbd3)
    -  to show read progress in FolderWindow (Thu Jun 15 05:03:53 2017 +0900) [9043573](https://github.com/kanryu/quickviewer/commit/90435737146b3a12d77660fcb9e73a648a5efbd3)
    -  to load with read progress for volumes (Thu Jun 15 05:03:53 2017 +0900) [9043573](https://github.com/kanryu/quickviewer/commit/90435737146b3a12d77660fcb9e73a648a5efbd3)
    - changelog (Mon Jun 12 17:20:43 2017 +0900) [2a2960b](https://github.com/kanryu/quickviewer/commit/2a2960b391f11f2f82d3269cd69f74dd28f5efb7)
    - Problems arise when building fileloader with g ++, so make it a shared library and avoid it (Mon Jun 12 17:19:51 2017 +0900) [4dd9f68](https://github.com/kanryu/quickviewer/commit/4dd9f682df21da2060cbc3ea844402f086c34cb4)

## v0.7.3 (Fri Jun 9 01:29:10 2017 +0900) [b000f92](https://github.com/kanryu/quickviewer/commit/b000f9293a0b71beaf2a485b511e6cd3c64ebdad)

changelog

- other commits
    - add support to list-up image in subfolders, 2 bugfixed (Fri Jun 9 01:28:47 2017 +0900) [f37f10a](https://github.com/kanryu/quickviewer/commit/f37f10a816822e301a32ef9eaa6cf460023d088f)
    -  add support to list-up image in subfolders, ignored archives (Fri Jun 9 01:28:47 2017 +0900) [f37f10a](https://github.com/kanryu/quickviewer/commit/f37f10a816822e301a32ef9eaa6cf460023d088f)
    -  bugfixed: Garbled characters occurred in the display of file names containing multi-byte characters in the zip archive (Fri Jun 9 01:28:47 2017 +0900) [f37f10a](https://github.com/kanryu/quickviewer/commit/f37f10a816822e301a32ef9eaa6cf460023d088f)
    -  bugfixed: When resizing with CPU, some images with α were not displayed (Fri Jun 9 01:28:47 2017 +0900) [f37f10a](https://github.com/kanryu/quickviewer/commit/f37f10a816822e301a32ef9eaa6cf460023d088f)
    - Update index-ja.md (Tue Jun 6 23:21:33 2017 +0900) [c224fbf](https://github.com/kanryu/quickviewer/commit/c224fbf38645e8c71969aa1523f1da525e37c357)

## v0.7.2 (Mon Jun 5 18:35:03 2017 +0900) [e9cf927](https://github.com/kanryu/quickviewer/commit/e9cf9276b9cda67c8141baf9f7feab917a3cc6d1)

changelog

- other commits
    - improve zip loader, 1 bug fixed (Mon Jun 5 18:34:34 2017 +0900) [d05e849](https://github.com/kanryu/quickviewer/commit/d05e8492e613dbe73ccb3fe9b3b7bc69310abbb4)
    -  (Mon Jun 5 18:34:34 2017 +0900) [d05e849](https://github.com/kanryu/quickviewer/commit/d05e8492e613dbe73ccb3fe9b3b7bc69310abbb4)
    -  improve zip loader, couldn't load multibyte inner filenames of files (Mon Jun 5 18:34:34 2017 +0900) [d05e849](https://github.com/kanryu/quickviewer/commit/d05e8492e613dbe73ccb3fe9b3b7bc69310abbb4)
    -  bugfixed: wrong view size for auto rounded by JPEG EXIF with CPU interplations (Mon Jun 5 18:34:34 2017 +0900) [d05e849](https://github.com/kanryu/quickviewer/commit/d05e8492e613dbe73ccb3fe9b3b7bc69310abbb4)
    -  don't use OpenGL until use Shaders (Mon Jun 5 18:34:34 2017 +0900) [d05e849](https://github.com/kanryu/quickviewer/commit/d05e8492e613dbe73ccb3fe9b3b7bc69310abbb4)

## v0.7.1 (Fri Jun 2 14:23:28 2017 +0900) [0f5be54](https://github.com/kanryu/quickviewer/commit/0f5be54cc8e627817e4e55446ee5b3b68a33288c)

changelog

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Fri Jun 2 14:23:16 2017 +0900) [ab2b044](https://github.com/kanryu/quickviewer/commit/ab2b044b091853a0d5cbbefcddcda85bafee8931)
    - add CPU Bicubic interpolation (Fri Jun 2 14:22:47 2017 +0900) [fd1cce7](https://github.com/kanryu/quickviewer/commit/fd1cce767108eb179fdb936b36906f06c528f044)
    -  build tested on ubuntu linux (Fri Jun 2 14:22:47 2017 +0900) [fd1cce7](https://github.com/kanryu/quickviewer/commit/fd1cce767108eb179fdb936b36906f06c528f044)
    -  build support about zimg by g++ (Fri Jun 2 14:22:47 2017 +0900) [fd1cce7](https://github.com/kanryu/quickviewer/commit/fd1cce767108eb179fdb936b36906f06c528f044)
    -  list drives on FolderWindow (Fri Jun 2 14:22:47 2017 +0900) [fd1cce7](https://github.com/kanryu/quickviewer/commit/fd1cce767108eb179fdb936b36906f06c528f044)
    - Update index.md (Thu Jun 1 18:56:18 2017 +0900) [e7b9524](https://github.com/kanryu/quickviewer/commit/e7b952470f0148581a18df4a83474cea72d7e982)
    - Update index.md (Tue May 30 09:42:33 2017 +0900) [91f5ac2](https://github.com/kanryu/quickviewer/commit/91f5ac2de3a7f6608a2b835667439abd5e3e284a)
    - changelog (Tue May 30 06:25:07 2017 +0900) [723ed9c](https://github.com/kanryu/quickviewer/commit/723ed9c939a1c3a40676dba33039f72eee496348)
    - build/run checked on ubuntu-16.04.2 x64 (Tue May 30 06:24:07 2017 +0900) [8bb5c62](https://github.com/kanryu/quickviewer/commit/8bb5c62eebf5e9a3a6af7ea035cd4c0097d57857)
    -  zimg don't run correctly(so can't run with shader/CPU Bicubic) (Tue May 30 06:24:07 2017 +0900) [8bb5c62](https://github.com/kanryu/quickviewer/commit/8bb5c62eebf5e9a3a6af7ea035cd4c0097d57857)
    -  Catalog don't run correctly (Tue May 30 06:24:07 2017 +0900) [8bb5c62](https://github.com/kanryu/quickviewer/commit/8bb5c62eebf5e9a3a6af7ea035cd4c0097d57857)

## v0.7.0 (Sat May 27 18:10:44 2017 +0900) [8101cef](https://github.com/kanryu/quickviewer/commit/8101cefdf01abe8e56de36751d2beb995e1394d2)

changelog

- other commits
    - Add FolderWindow, CPU Interpolation (Sat May 27 18:10:11 2017 +0900) [26f0b31](https://github.com/kanryu/quickviewer/commit/26f0b31a94542a2121b4a307bb921a4cacc759d5)
    -  FolderWindow provides a simple view for folders/archives on current folder (Sat May 27 18:10:11 2017 +0900) [26f0b31](https://github.com/kanryu/quickviewer/commit/26f0b31a94542a2121b4a307bb921a4cacc759d5)
    -  support CPU Interpolation, very high quality but shortly slow (Sat May 27 18:10:11 2017 +0900) [26f0b31](https://github.com/kanryu/quickviewer/commit/26f0b31a94542a2121b4a307bb921a4cacc759d5)
    - Add FolderWindow (Sat May 27 08:39:49 2017 +0900) [41328f3](https://github.com/kanryu/quickviewer/commit/41328f3cd1b18af937dd6cf1b374768a7b5c9fa4)
    -  (Sat May 27 08:39:49 2017 +0900) [41328f3](https://github.com/kanryu/quickviewer/commit/41328f3cd1b18af937dd6cf1b374768a7b5c9fa4)
    -  when to load volume from folder, search into only one subfolder (Sat May 27 08:39:49 2017 +0900) [41328f3](https://github.com/kanryu/quickviewer/commit/41328f3cd1b18af937dd6cf1b374768a7b5c9fa4)
    -  bug fixed: can't load inner path of zip which contains multibyte words (Fri May 26 09:45:28 2017 +0900) [f07e541](https://github.com/kanryu/quickviewer/commit/f07e541317f4ba4424e3f72eeb6b459c34492dfc)
    -  refactoring: relocated the source tree (Fri May 26 09:45:28 2017 +0900) [f07e541](https://github.com/kanryu/quickviewer/commit/f07e541317f4ba4424e3f72eeb6b459c34492dfc)
    -  begin to implement folderwindow (Fri May 26 09:45:28 2017 +0900) [f07e541](https://github.com/kanryu/quickviewer/commit/f07e541317f4ba4424e3f72eeb6b459c34492dfc)

## v0.6.6 (Tue May 16 21:57:40 2017 +0900) [0f64a5d](https://github.com/kanryu/quickviewer/commit/0f64a5d5bfd286d73ad48b0192a2438669269c96)

changelog

- other commits
    - Support archives of Catalog, smaller Catalog grid, improve folder loading, refactoring (Tue May 16 21:56:47 2017 +0900) [b8acaf0](https://github.com/kanryu/quickviewer/commit/b8acaf06b90e2f1d81529b69f480af431c25d0cc)
    -  (Tue May 16 21:56:47 2017 +0900) [b8acaf0](https://github.com/kanryu/quickviewer/commit/b8acaf06b90e2f1d81529b69f480af431c25d0cc)
    -  now support archives of Catalog, including zip,rar,cbr,cbz (Tue May 16 21:56:47 2017 +0900) [b8acaf0](https://github.com/kanryu/quickviewer/commit/b8acaf06b90e2f1d81529b69f480af431c25d0cc)
    -  smaller Catalog grid for not long titles(folder or archive name) (Tue May 16 21:56:47 2017 +0900) [b8acaf0](https://github.com/kanryu/quickviewer/commit/b8acaf06b90e2f1d81529b69f480af431c25d0cc)
    -  if folder not have files and have subfolders, QuickViewer attempt open a subfolder (Tue May 16 21:56:47 2017 +0900) [b8acaf0](https://github.com/kanryu/quickviewer/commit/b8acaf06b90e2f1d81529b69f480af431c25d0cc)
    -  refactoring(remove Japanese comments, remove Unnecessary source codes) (Tue May 16 21:56:47 2017 +0900) [b8acaf0](https://github.com/kanryu/quickviewer/commit/b8acaf06b90e2f1d81529b69f480af431c25d0cc)
    -  change some menu texts (Tue May 16 21:56:47 2017 +0900) [b8acaf0](https://github.com/kanryu/quickviewer/commit/b8acaf06b90e2f1d81529b69f480af431c25d0cc)

## v0.6.5 (Sun May 14 17:18:41 2017 +0900) [69fda94](https://github.com/kanryu/quickviewer/commit/69fda94ca6769e223037959636392e8e878fee6d)

changelog

- other commits
    - 2 bugfixed (Sun May 14 17:17:43 2017 +0900) [1bd4baf](https://github.com/kanryu/quickviewer/commit/1bd4bafe9b0c1e656017997713eda4260373986f)
    -  (Sun May 14 17:17:43 2017 +0900) [1bd4baf](https://github.com/kanryu/quickviewer/commit/1bd4bafe9b0c1e656017997713eda4260373986f)
    -  application ends abnormally after catalog deletion (Sun May 14 17:17:43 2017 +0900) [1bd4baf](https://github.com/kanryu/quickviewer/commit/1bd4bafe9b0c1e656017997713eda4260373986f)
    -  if filename of image is too long, the width of the main window was forcibly changed (Sun May 14 17:17:43 2017 +0900) [1bd4baf](https://github.com/kanryu/quickviewer/commit/1bd4bafe9b0c1e656017997713eda4260373986f)
    - Update index-ja.md (Sun May 14 16:06:44 2017 +0900) [6bd491d](https://github.com/kanryu/quickviewer/commit/6bd491d5e30d89bba44b18dbf7acfda61e3c32de)
    - Update index-ja.md (Sun May 14 16:04:19 2017 +0900) [09459c2](https://github.com/kanryu/quickviewer/commit/09459c2aaa814ffab583630aa2ae9522f5a182c8)
    - Update index.md (Sun May 14 15:56:40 2017 +0900) [a0ad58c](https://github.com/kanryu/quickviewer/commit/a0ad58c28afb65d4c6e9b8e1e541831acd789a17)
    - Update index.md (Sun May 14 02:07:09 2017 +0900) [593429b](https://github.com/kanryu/quickviewer/commit/593429b2477f3eb09ce135dcbda42539f56a2347)

## v0.6.4 (Sun May 14 01:56:44 2017 +0900) [7fb809a](https://github.com/kanryu/quickviewer/commit/7fb809a21528385199d23d81347271fdda088e95)

changelog

- other commits
    - add new feature, TagBar (Sun May 14 01:56:06 2017 +0900) [5753dc4](https://github.com/kanryu/quickviewer/commit/5753dc46e7bf2eb987c23af05609524b6e1c6c76)
    -  (Sun May 14 01:56:06 2017 +0900) [5753dc4](https://github.com/kanryu/quickviewer/commit/5753dc46e7bf2eb987c23af05609524b6e1c6c76)
    -  'Tag' is a auto generated words from Book Titles, include Publishers, Authors, and other properties (Sun May 14 01:56:06 2017 +0900) [5753dc4](https://github.com/kanryu/quickviewer/commit/5753dc46e7bf2eb987c23af05609524b6e1c6c76)
    -  each 'Tag' as a small buttons on CatalogWindow (Sun May 14 01:56:06 2017 +0900) [5753dc4](https://github.com/kanryu/quickviewer/commit/5753dc46e7bf2eb987c23af05609524b6e1c6c76)
    -  if you click Tag buttons, Catalog only shows the books have the tag (Sun May 14 01:56:06 2017 +0900) [5753dc4](https://github.com/kanryu/quickviewer/commit/5753dc46e7bf2eb987c23af05609524b6e1c6c76)

## v0.6.3 (Sat May 13 06:59:07 2017 +0900) [332f255](https://github.com/kanryu/quickviewer/commit/332f2559a612b2ca607dad66d29865d8a68d367a)

changelog

- other commits
    - much faster CatalogWindow (Sat May 13 06:56:22 2017 +0900) [bc1787e](https://github.com/kanryu/quickviewer/commit/bc1787e36ff87f64b91a7dcb91e47ef737f40bd3)
    -  remove limitation volume counts (Sat May 13 06:56:22 2017 +0900) [bc1787e](https://github.com/kanryu/quickviewer/commit/bc1787e36ff87f64b91a7dcb91e47ef737f40bd3)
    -  background volumes initialization (Sat May 13 06:56:22 2017 +0900) [bc1787e](https://github.com/kanryu/quickviewer/commit/bc1787e36ff87f64b91a7dcb91e47ef737f40bd3)
    -  scroll vertical for ListMode on CatalogWindow (Sat May 13 06:56:22 2017 +0900) [bc1787e](https://github.com/kanryu/quickviewer/commit/bc1787e36ff87f64b91a7dcb91e47ef737f40bd3)
    -  bugfixed: CatalogWindow as modeless, can't accept drop files (Sat May 13 06:56:22 2017 +0900) [bc1787e](https://github.com/kanryu/quickviewer/commit/bc1787e36ff87f64b91a7dcb91e47ef737f40bd3)
    -  known problem: mouse wheel scroll is slow on CatalogWindow when ListMode -> Icon/IconNoText changed (Sat May 13 06:56:22 2017 +0900) [bc1787e](https://github.com/kanryu/quickviewer/commit/bc1787e36ff87f64b91a7dcb91e47ef737f40bd3)
    - Update README.md (Fri May 12 01:46:20 2017 +0900) [02b037b](https://github.com/kanryu/quickviewer/commit/02b037bbc018ca748d9a8822f48adee9ba22c809)

## v0.6.2 (Thu May 11 22:48:28 2017 +0900) [b338740](https://github.com/kanryu/quickviewer/commit/b3387406eafee3bdce9c1eaffe1d2b14297ca833)

changelog

- other commits
    - Add notation of shortcut, speedup for catalog, more simple title (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    -  (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    -  Add notation of shortcut key to each item of main menu (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    -  Add a function to remove (Options) under certain conditions from the (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    - title of the book registered in the catalog (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    -  Speed up thumbnail loading process saved in database (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    -  Accelerated Incremental Search and Display Switching in Catalog Window (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    -  Fix some display phrases (Thu May 11 22:45:52 2017 +0900) [2413c69](https://github.com/kanryu/quickviewer/commit/2413c69b3735f59ed14c8db24fed3558c12a53d1)
    - refactoring (Wed May 10 03:32:57 2017 +0900) [9830d72](https://github.com/kanryu/quickviewer/commit/9830d720a6da2aba1bbe72cad43550c9f668834f)
    -  (Wed May 10 03:32:57 2017 +0900) [9830d72](https://github.com/kanryu/quickviewer/commit/9830d720a6da2aba1bbe72cad43550c9f668834f)
    -  add precompiled header(stdafx.h) (Wed May 10 03:32:57 2017 +0900) [9830d72](https://github.com/kanryu/quickviewer/commit/9830d720a6da2aba1bbe72cad43550c9f668834f)
    -  remove wornings(Remove unnecessary local variables) (Wed May 10 03:32:57 2017 +0900) [9830d72](https://github.com/kanryu/quickviewer/commit/9830d720a6da2aba1bbe72cad43550c9f668834f)

## v0.6.1 (Tue May 9 02:48:11 2017 +0900) [e618790](https://github.com/kanryu/quickviewer/commit/e6187908bb5a96ad4814719c6453bd6f6df03ba5)

changelog

- other commits
    - add inner CatalogWindow, 3 bugfixed (Tue May 9 02:47:33 2017 +0900) [0d8eeb1](https://github.com/kanryu/quickviewer/commit/0d8eeb13ff7d3b2fd01c4ecf6c11a09620771c55)
    -  bug fixed: when to run from other directries, wrong ini files created. (Tue May 9 02:47:33 2017 +0900) [0d8eeb1](https://github.com/kanryu/quickviewer/commit/0d8eeb13ff7d3b2fd01c4ecf6c11a09620771c55)
    -  bug fixed: onle newer catalogs, don't activeted about edit/delete buttons. (Tue May 9 02:47:33 2017 +0900) [0d8eeb1](https://github.com/kanryu/quickviewer/commit/0d8eeb13ff7d3b2fd01c4ecf6c11a09620771c55)
    -  bug fixed: when manual resizing and image is smaller than the window, image was wrong position (Tue May 9 02:47:33 2017 +0900) [0d8eeb1](https://github.com/kanryu/quickviewer/commit/0d8eeb13ff7d3b2fd01c4ecf6c11a09620771c55)
    -  when a catalog executed, make MainWindow activate (Tue May 9 02:47:33 2017 +0900) [0d8eeb1](https://github.com/kanryu/quickviewer/commit/0d8eeb13ff7d3b2fd01c4ecf6c11a09620771c55)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon May 8 17:03:11 2017 +0900) [66e4257](https://github.com/kanryu/quickviewer/commit/66e4257ec77f327a0d75c27c2b16f57197fba28e)
    - merge QuickCatalog.pro into QuickViewer.pro (Mon May 8 17:01:58 2017 +0900) [0f1d753](https://github.com/kanryu/quickviewer/commit/0f1d75314e78eb1154387cae6b40f8f9243f6fad)
    - Update index.md (Mon May 8 16:27:07 2017 +0900) [8338cf8](https://github.com/kanryu/quickviewer/commit/8338cf8ac48562d5b24a77db58b0339a2f2ef4f9)
    - Update index.md (Mon May 8 16:24:13 2017 +0900) [e05340f](https://github.com/kanryu/quickviewer/commit/e05340f24cdb9873586fd3c937d74a64334ac64d)

## v0.6.0 (Sun May 7 01:58:16 2017 +0900) [388ed47](https://github.com/kanryu/quickviewer/commit/388ed4707b43110ddb32d9c0857c35c727c0bdb9)

changelog

- other commits
    - Support Book Catalogs, easy to view thumbnails of frontpage of books and search fast (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  to create/view/search 'Catalogs' (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  whihc contains the thumbnails of frontpage of Books as icon (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  search by title(folder name of volumes) (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  change words 'Database' -> 'Catalog' (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  change QuickCatalog app to static lib (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  hide updateButton/updateAllButton (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  MainWindow can open CatalogWindow (Sun May 7 01:57:35 2017 +0900) [59a25a8](https://github.com/kanryu/quickviewer/commit/59a25a8ee47e2035084c07e00f5c84599453173a)
    -  add icons/catalog.ico (Sat May 6 22:18:57 2017 +0900) [b68ab0b](https://github.com/kanryu/quickviewer/commit/b68ab0bdf2e2651af17a9adc7b23f733cff3b974)
    -  add mainmenu(CatalogWindow) (Sat May 6 22:18:57 2017 +0900) [b68ab0b](https://github.com/kanryu/quickviewer/commit/b68ab0bdf2e2651af17a9adc7b23f733cff3b974)
    -  reserved create catalogs on ManageDatabaseDialog (Sat May 6 22:18:57 2017 +0900) [b68ab0b](https://github.com/kanryu/quickviewer/commit/b68ab0bdf2e2651af17a9adc7b23f733cff3b974)
    -  can drop CatalogWIndow (Sat May 6 22:18:57 2017 +0900) [b68ab0b](https://github.com/kanryu/quickviewer/commit/b68ab0bdf2e2651af17a9adc7b23f733cff3b974)
    -  can multi drop ManageDatabaseDialog (Sat May 6 22:18:57 2017 +0900) [b68ab0b](https://github.com/kanryu/quickviewer/commit/b68ab0bdf2e2651af17a9adc7b23f733cff3b974)
    -  bugfixed deleteAllCatalogs (Sat May 6 22:18:57 2017 +0900) [b68ab0b](https://github.com/kanryu/quickviewer/commit/b68ab0bdf2e2651af17a9adc7b23f733cff3b974)
    -  implement searchCombo (Sat May 6 18:13:32 2017 +0900) [944097e](https://github.com/kanryu/quickviewer/commit/944097e3a1c94538e0e18e3a45a071f79074b605)
    -  fast to create Frontpage Thumbnails of Books (Sat May 6 18:13:32 2017 +0900) [944097e](https://github.com/kanryu/quickviewer/commit/944097e3a1c94538e0e18e3a45a071f79074b605)
    - making catalogwindow, managedatabasedialog, databasesettingdialog (Wed May 3 22:33:06 2017 +0900) [59666fa](https://github.com/kanryu/quickviewer/commit/59666fa8fe2ff967f8a5e035e85f5a7017a4c6fa)
    -  making catalogwindow(volumeList) (Wed May 3 22:33:06 2017 +0900) [59666fa](https://github.com/kanryu/quickviewer/commit/59666fa8fe2ff967f8a5e035e85f5a7017a4c6fa)
    -  to create t_files uses workers (Mon May 1 19:46:51 2017 +0900) [67f883a](https://github.com/kanryu/quickviewer/commit/67f883acc8e704b03853165985e4598716917a1a)
    -  initialize of ManageDatabaseDialog (Mon May 1 19:46:51 2017 +0900) [67f883a](https://github.com/kanryu/quickviewer/commit/67f883acc8e704b03853165985e4598716917a1a)
    - Create/Delete Catalog which can cancel (Mon May 1 18:25:50 2017 +0900) [2d4c75d](https://github.com/kanryu/quickviewer/commit/2d4c75dfa9cd9e7fc84dbdce2ca916e14b3ee51d)
    - changelog (Mon May 1 13:42:34 2017 +0900) [896b2c0](https://github.com/kanryu/quickviewer/commit/896b2c0155ab22e8832892321c42f3345cd8de79)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon May 1 13:40:57 2017 +0900) [994cfb9](https://github.com/kanryu/quickviewer/commit/994cfb9423911c6003be59c72db85a8ea889b13c)
    - parted to new project 'fileloader.pro', new project QuickCatalog (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)
    -  (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)
    -  parted to new project 'fileloader.pro' (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)
    -  which contains commonly modules to load archives (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)
    -  new project QuickCatalog (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)
    -  it provides functions to create/manage Thumbnail Catalogs, and (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)
    - Catalog Filer (Mon May 1 13:38:06 2017 +0900) [c2d620c](https://github.com/kanryu/quickviewer/commit/c2d620ca3fc59801e0470547764fc9a483f56523)
    - Update index.md (Tue Apr 25 21:40:12 2017 +0900) [d8829f3](https://github.com/kanryu/quickviewer/commit/d8829f329f146f6996cb2399b50802f08c8170bc)
    - Update index.md (Tue Apr 25 19:48:47 2017 +0900) [082efbd](https://github.com/kanryu/quickviewer/commit/082efbdb9aaae44afdf7005f9fde2d93c8aeba69)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Tue Apr 25 19:43:46 2017 +0900) [2c4daef](https://github.com/kanryu/quickviewer/commit/2c4daef85cfb6a1b6e90d49a33df4568942def1c)
    - max width 1080px (Tue Apr 25 19:43:20 2017 +0900) [53a41cd](https://github.com/kanryu/quickviewer/commit/53a41cdcc82b8fce61206bf8dce86dcbf2f49980)
    - Update index.md (Tue Apr 25 08:13:05 2017 +0900) [43349c9](https://github.com/kanryu/quickviewer/commit/43349c98300d26f1c71ba6e3743ecd5a95c5acd3)

## v0.5.6 (Mon Apr 24 23:40:38 2017 +0900) [3fe835b](https://github.com/kanryu/quickviewer/commit/3fe835b3a77fbb4bc26b362fe6ffeb0616224a65)

changelog

- other commits
    - improve AutoLoaded, ScaleUp behavior, add a menu (Mon Apr 24 23:38:19 2017 +0900) [29dea25](https://github.com/kanryu/quickviewer/commit/29dea252da40d0e7c3760a708dcb540818ed9d71)
    -  (Mon Apr 24 23:38:19 2017 +0900) [29dea25](https://github.com/kanryu/quickviewer/commit/29dea252da40d0e7c3760a708dcb540818ed9d71)
    -  AutoLoad from Bookmarks (Mon Apr 24 23:38:19 2017 +0900) [29dea25](https://github.com/kanryu/quickviewer/commit/29dea252da40d0e7c3760a708dcb540818ed9d71)
    -  after this version auto saved to latest bookmarks when to exit the app (Mon Apr 24 23:38:19 2017 +0900) [29dea25](https://github.com/kanryu/quickviewer/commit/29dea252da40d0e7c3760a708dcb540818ed9d71)
    -  Show ScrollBars when manual ScaleUp on normal/maximize windowFlags (Mon Apr 24 23:38:19 2017 +0900) [29dea25](https://github.com/kanryu/quickviewer/commit/29dea252da40d0e7c3760a708dcb540818ed9d71)
    -  add menu(OpenProjectWeb) (Mon Apr 24 23:38:19 2017 +0900) [29dea25](https://github.com/kanryu/quickviewer/commit/29dea252da40d0e7c3760a708dcb540818ed9d71)
    - Update index.md (Mon Apr 24 18:39:58 2017 +0900) [52b4384](https://github.com/kanryu/quickviewer/commit/52b43840cbd2e5dc7d015db915fa18a5b7223901)
    - Update index.md (Mon Apr 24 18:36:48 2017 +0900) [1311785](https://github.com/kanryu/quickviewer/commit/1311785d6d67f43d9994870c2701c483c0f399a7)
    - Update index.md (Mon Apr 24 16:33:57 2017 +0900) [4a3ce17](https://github.com/kanryu/quickviewer/commit/4a3ce17d4fb4fa9e67fb31bca92d177eddb24065)
    - Update index-ja.md (Mon Apr 24 16:33:19 2017 +0900) [e900072](https://github.com/kanryu/quickviewer/commit/e90007270b93dcdfa22e7b01391d5be2802b5553)
    - Update screen.scss (Mon Apr 24 16:31:35 2017 +0900) [424bc37](https://github.com/kanryu/quickviewer/commit/424bc37a7ae0c08886ec3b171eb96dbdb083bdfa)
    - Update index.md (Mon Apr 24 00:31:33 2017 +0900) [89471b2](https://github.com/kanryu/quickviewer/commit/89471b2872fc667d844e47f990c738cd60dd7266)
    - changelog (Sun Apr 23 17:45:39 2017 +0900) [ba3bf93](https://github.com/kanryu/quickviewer/commit/ba3bf93dd1713838cebc27e94d2f6f0cb4b012fd)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sun Apr 23 17:44:30 2017 +0900) [c1abe1f](https://github.com/kanryu/quickviewer/commit/c1abe1f412cff4a8173a9f7ede08cc6eb481932a)
    - removed QtRAR, add latest unrar (Sun Apr 23 17:42:29 2017 +0900) [7e37d4c](https://github.com/kanryu/quickviewer/commit/7e37d4c802554ac4e88b171cdefe8cd8ee6839eb)
    -  (Sun Apr 23 17:42:29 2017 +0900) [7e37d4c](https://github.com/kanryu/quickviewer/commit/7e37d4c802554ac4e88b171cdefe8cd8ee6839eb)
    -  removed QtRAR, because it needs some changes and bundled unrar is old (Sun Apr 23 17:42:29 2017 +0900) [7e37d4c](https://github.com/kanryu/quickviewer/commit/7e37d4c802554ac4e88b171cdefe8cd8ee6839eb)
    -  add latest unrar and a simple wrapper(RarExtractor) (Sun Apr 23 17:42:29 2017 +0900) [7e37d4c](https://github.com/kanryu/quickviewer/commit/7e37d4c802554ac4e88b171cdefe8cd8ee6839eb)
    - Update index.md (Sun Apr 23 10:24:53 2017 +0900) [20ef220](https://github.com/kanryu/quickviewer/commit/20ef220232222b3702687704c09edd94b81ddf3a)
    - Update index.md (Sun Apr 23 00:29:19 2017 +0900) [8aea2cf](https://github.com/kanryu/quickviewer/commit/8aea2cf625bef02c62e4c222bbfbf96ff0f840ce)
    - Update README.md (Sat Apr 22 11:23:46 2017 +0900) [de8faef](https://github.com/kanryu/quickviewer/commit/de8faef38237dfa8abf0f18e8c51fa3d5dcf2b03)

## v0.5.5 (Sat Apr 22 00:27:37 2017 +0900) [2f13827](https://github.com/kanryu/quickviewer/commit/2f1382746a71b83b7fbd489e8266319a27a6a1df)

changelog

- other commits
    - speed up for large JPEG, support cbr/cbz, improve ScaleUp/ScaleOut, 2 bug fix (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)
    -  (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)
    -  twice times speed up for loading JPEGs over 4096px (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)
    -  now can load cbr/cbz format(without support for book database) (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)
    -  improve behavior ScaleUp/ScaleOut (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)
    -  bug fix, An error occurred when closing the application after changing Volume (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)
    -  bug fix, File sharing archive can not be opened (Sat Apr 22 00:26:15 2017 +0900) [6d61dba](https://github.com/kanryu/quickviewer/commit/6d61dba5131b0bef932f350223e755b679014ee0)
    - Update index-ja.md (Fri Apr 21 10:36:51 2017 +0900) [4d143b5](https://github.com/kanryu/quickviewer/commit/4d143b5de771a2e5278595e43dd913d9818c1222)
    - Update index.md (Fri Apr 21 10:35:26 2017 +0900) [221383e](https://github.com/kanryu/quickviewer/commit/221383e3e1478d4451555325afb9369212c545d2)
    - Update README.md (Fri Apr 21 10:32:46 2017 +0900) [2240a28](https://github.com/kanryu/quickviewer/commit/2240a2883fde0cd6e4f326410308cedf922ca624)
    - Update README.md (Fri Apr 21 10:32:27 2017 +0900) [db7e365](https://github.com/kanryu/quickviewer/commit/db7e365b2f5bb90f5050a485ccf1024f6cc8bd1b)
    - Update index.md (Fri Apr 21 04:40:42 2017 +0900) [4faa2bc](https://github.com/kanryu/quickviewer/commit/4faa2bc2c05974c32cdbff9a2a7dbef96f1eda95)
    - Update index.md (Fri Apr 21 03:34:26 2017 +0900) [dd2431a](https://github.com/kanryu/quickviewer/commit/dd2431a2bb41963d8ffce6462bbcd9ceda9b3eba)
    - Update index-ja.md (Fri Apr 21 03:33:38 2017 +0900) [bcbb2a7](https://github.com/kanryu/quickviewer/commit/bcbb2a7b6aeb9e52ccc77f3246248e07905e8c9e)
    - Update index.md (Fri Apr 21 03:31:53 2017 +0900) [19d6f42](https://github.com/kanryu/quickviewer/commit/19d6f4236776da9562a4920dd12b936fd8b72f12)

## v0.5.4 (Thu Apr 20 18:03:54 2017 +0900) [53f4108](https://github.com/kanryu/quickviewer/commit/53f41086b81c0f55f4372658f46b62087565a383)

changelog

- other commits
    - add Bookmarks, improve behavior about loading JPEGs (Thu Apr 20 18:02:38 2017 +0900) [a967ffc](https://github.com/kanryu/quickviewer/commit/a967ffc1c0e3e00cbc330d419d602337acbac093)
    -  (Thu Apr 20 18:02:38 2017 +0900) [a967ffc](https://github.com/kanryu/quickviewer/commit/a967ffc1c0e3e00cbc330d419d602337acbac093)
    -  add Bookmarks(Save/Load/Clear) (Thu Apr 20 18:02:38 2017 +0900) [a967ffc](https://github.com/kanryu/quickviewer/commit/a967ffc1c0e3e00cbc330d419d602337acbac093)
    -  improve behavior about loading JPEGs (Thu Apr 20 18:02:38 2017 +0900) [a967ffc](https://github.com/kanryu/quickviewer/commit/a967ffc1c0e3e00cbc330d419d602337acbac093)
    -  turbojpeg returns -1 when to load some JPEGs(e.g. Photoshop CS5!) (Thu Apr 20 18:02:38 2017 +0900) [a967ffc](https://github.com/kanryu/quickviewer/commit/a967ffc1c0e3e00cbc330d419d602337acbac093)
    -  because it is not real error, so loaded correctly (Thu Apr 20 18:02:38 2017 +0900) [a967ffc](https://github.com/kanryu/quickviewer/commit/a967ffc1c0e3e00cbc330d419d602337acbac093)

## v0.5.3 (Mon Apr 17 20:22:21 2017 +0900) [697b723](https://github.com/kanryu/quickviewer/commit/697b723ea6717a097cf3875b7106679ef2a932c5)

changelog

- other commits
    - improve file sorting/fixed bug (Mon Apr 17 20:21:35 2017 +0900) [b693e96](https://github.com/kanryu/quickviewer/commit/b693e962c6a3835fff00e8392867a4e416895a51)
    -  (Mon Apr 17 20:21:35 2017 +0900) [b693e96](https://github.com/kanryu/quickviewer/commit/b693e962c6a3835fff00e8392867a4e416895a51)
    -  improve file sorting(Windows caseInsensitive using StrCmpLogicalW()) (Mon Apr 17 20:21:35 2017 +0900) [b693e96](https://github.com/kanryu/quickviewer/commit/b693e962c6a3835fff00e8392867a4e416895a51)
    -  fixed bug about StayOnTop(using WinAPI) (Mon Apr 17 20:21:35 2017 +0900) [b693e96](https://github.com/kanryu/quickviewer/commit/b693e962c6a3835fff00e8392867a4e416895a51)
    -  add some Japanese translations (Mon Apr 17 20:21:35 2017 +0900) [b693e96](https://github.com/kanryu/quickviewer/commit/b693e962c6a3835fff00e8392867a4e416895a51)
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

## v0.5.2_rev2 (Sun Apr 16 18:24:32 2017 +0900) [2d8db4d](https://github.com/kanryu/quickviewer/commit/2d8db4d77f6cef7684a598277a9b8edab8279f41)

changelog

- other commits
    - add Key Config(Rotate/CopyFile/SlideShow) (Sun Apr 16 18:23:21 2017 +0900) [9cc3dc5](https://github.com/kanryu/quickviewer/commit/9cc3dc5ef03cbdd1be3720d18d32068f5d0ccc9c)

## v0.5.2 (Sun Apr 16 18:01:44 2017 +0900) [4f0d11d](https://github.com/kanryu/quickviewer/commit/4f0d11d59a79aaab0ec438812ce282fde7094938)

changelog

- other commits
    - changelog (Sun Apr 16 17:59:32 2017 +0900) [cde4f30](https://github.com/kanryu/quickviewer/commit/cde4f300d86673dfd487cb7d1ea660b621a1d903)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sun Apr 16 17:58:55 2017 +0900) [11b60dc](https://github.com/kanryu/quickviewer/commit/11b60dc274ec37054ee132ed2440b0ae5f6a7eb9)
    - add SlideShow/CopyFile/RotateImage, 2 bug fixed (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)
    -  (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)
    -  add SlideShow/CopyFile/RotateImage (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)
    -  refactoring(ImageShaderEffect -> ShaderManager) (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)
    -  bug fixed(last 2 paging) (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)
    -  bug fixed(open explorer) (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)
    -  improve(more collect page bar on dualview) (Sun Apr 16 17:58:41 2017 +0900) [59d12fe](https://github.com/kanryu/quickviewer/commit/59d12fe9e92038cb41de49b9897b778df073d19f)
    - Update README.md (Fri Apr 14 16:35:43 2017 +0900) [fd8da52](https://github.com/kanryu/quickviewer/commit/fd8da52e1505043f5066b3b5bcd5d70abbab72e4)

## v0.5.1 (Thu Apr 13 21:14:25 2017 +0900) [78d1ecf](https://github.com/kanryu/quickviewer/commit/78d1ecfb4d1b222c7f560fd64f65a556cd5609f3)

changelog

- other commits
    - Support Shaders, Save Window States, Add FastFoward/Backward (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)
    -  (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)
    -  Support GPU Shaders(NearestNeighbor/Bicubic/Lanczos) (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)
    -  Save/Restore Window States(Position/Size/WindowStates) (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)
    -  add FastForward/Backward buttons(fixed by 10 pages) (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)
    -  Key Config Rules Changed (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)
    -  Please remove old ini files (Thu Apr 13 21:13:04 2017 +0900) [dad17cf](https://github.com/kanryu/quickviewer/commit/dad17cf3f87fce576126960cdef1940184ecfb55)

## v0.5.0 (Wed Apr 12 10:25:42 2017 +0900) [0095c41](https://github.com/kanryu/quickviewer/commit/0095c416faaff71b420e73c608c125563313a73c)

changelog

- other commits
    - more faster volume changing, refactoring (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)
    -  (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)
    -  add pre loading for volume changing(NextVolume/PrevVolume) (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)
    -  QuickViewer.pro now can provide distribution package(Windows) (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)
    -  refactoring (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)
    -  add PageManager, TimeOrderedCache (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)
    -  comment outed qDebug() (Wed Apr 12 10:24:23 2017 +0900) [1c561d1](https://github.com/kanryu/quickviewer/commit/1c561d1050fd90789bd852c43eadbc9ea9699319)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Tue Apr 11 09:38:00 2017 +0900) [ed3e260](https://github.com/kanryu/quickviewer/commit/ed3e2607158499ee40bc144628cccad7e97fea83)
    - support deploying, refactoring (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    -  (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    -  support deploying by pro(nolonger deploy.bat needed, run 'jom install') (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    -  refactoring(add PageGraphicsItem) (Tue Apr 11 09:36:13 2017 +0900) [7ed282c](https://github.com/kanryu/quickviewer/commit/7ed282c5051872e4b5e3c1671b317eb5a900fc8a)
    - Update index.md (Tue Apr 11 05:44:01 2017 +0900) [fc91c0b](https://github.com/kanryu/quickviewer/commit/fc91c0b1c8d34d0e093a17b4dd056c231791fe6e)

## v0.4.3 (Mon Apr 10 05:15:19 2017 +0900) [34de18f](https://github.com/kanryu/quickviewer/commit/34de18f33237f6f33c8ca3e2cde9757c2cca13cd)

changelog

- other commits
    - fixed bug, add shortcut newmenus (Mon Apr 10 05:13:47 2017 +0900) [a2ccbe6](https://github.com/kanryu/quickviewer/commit/a2ccbe68558021b1105810cfb2d1f2d1ec158838)
    -  (Mon Apr 10 05:13:47 2017 +0900) [a2ccbe6](https://github.com/kanryu/quickviewer/commit/a2ccbe68558021b1105810cfb2d1f2d1ec158838)
    -  fixed bug NextVolume/PageVolume, default key configs were in the opposite direction by mistake (Mon Apr 10 05:13:47 2017 +0900) [a2ccbe6](https://github.com/kanryu/quickviewer/commit/a2ccbe68558021b1105810cfb2d1f2d1ec158838)
    -  add shortcut DeletePage/CopyPage (Mon Apr 10 05:13:47 2017 +0900) [a2ccbe6](https://github.com/kanryu/quickviewer/commit/a2ccbe68558021b1105810cfb2d1f2d1ec158838)
    -  change words, delete image -> move the image to trash box (Mon Apr 10 05:13:47 2017 +0900) [a2ccbe6](https://github.com/kanryu/quickviewer/commit/a2ccbe68558021b1105810cfb2d1f2d1ec158838)
    - changelog (Mon Apr 10 04:59:05 2017 +0900) [d8477d1](https://github.com/kanryu/quickviewer/commit/d8477d100a36fe1f11cb92b4ac398861ca3a6a47)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon Apr 10 04:57:52 2017 +0900) [ad5e04b](https://github.com/kanryu/quickviewer/commit/ad5e04b3e5865074e065b1f1fa49b03ebba74369)
    - improve PageBar, add CopyImage/DeleteImage (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  improve PageBar(using QStyle::SH_Slider_AbsoluteSetButtons) (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  add CopyImage to clipboard (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    -  add DeleteImage to trashbox(referred to https://github.com/siliconscholar/sherman/blob/6397a274c704519f8e0b7f628ad0beadde0e1d53/src/win/deleter.cpp) (Mon Apr 10 04:55:58 2017 +0900) [2c582d8](https://github.com/kanryu/quickviewer/commit/2c582d86aac988e1feb2a474a1ca836168ebb643)
    - Create .gitattributes (Sat Apr 8 00:01:41 2017 +0900) [ee555e3](https://github.com/kanryu/quickviewer/commit/ee555e3850fdb99b33f559cf92a8b2d274950dd3)

## v0.4.2 (Fri Apr 7 03:10:57 2017 +0900) [fd3f2f6](https://github.com/kanryu/quickviewer/commit/fd3f2f605f4a977584cf571a57c998b464da5f16)

changelog

- other commits
    - Build Support on linux, can hide menubar, add 3 menus (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  Build Support for linux(tested on Ubuntu 16.02.2) (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  fixed a bug, Next only one page (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  can hide menubar on windows (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  add 3 menus (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  ShowMainMenu (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  ClearHistory (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    -  StayOnTop (Fri Apr 7 03:03:25 2017 +0900) [3c7cb8c](https://github.com/kanryu/quickviewer/commit/3c7cb8cb83eccbffb548fc86c40f70d85c26d599)
    - Linux Builde checked (Thu Apr 6 03:54:05 2017 +0900) [3858a36](https://github.com/kanryu/quickviewer/commit/3858a3655e68c2fd0d96aa5432159914cb37749a)

## v0.4.1 (Wed Apr 5 07:31:42 2017 +0900) [151203d](https://github.com/kanryu/quickviewer/commit/151203ddee158ec03bad4e81ec76b606d15520f5)

changelog

- other commits
    - JPEG/Raw loader plugin updated. 2 menus added (Wed Apr 5 07:29:41 2017 +0900) [36d4b39](https://github.com/kanryu/quickviewer/commit/36d4b39c927c3b6ac758885e6bed432213b42cd7)
    -  (Wed Apr 5 07:29:41 2017 +0900) [36d4b39](https://github.com/kanryu/quickviewer/commit/36d4b39c927c3b6ac758885e6bed432213b42cd7)
    -  JPEG/Raw image loader plugin updated. much faster than before(especially on x64) (Wed Apr 5 07:29:41 2017 +0900) [36d4b39](https://github.com/kanryu/quickviewer/commit/36d4b39c927c3b6ac758885e6bed432213b42cd7)
    -  add flag to show toolbar (Wed Apr 5 07:29:41 2017 +0900) [36d4b39](https://github.com/kanryu/quickviewer/commit/36d4b39c927c3b6ac758885e6bed432213b42cd7)
    -  add flag that always first image is one view (Wed Apr 5 07:29:41 2017 +0900) [36d4b39](https://github.com/kanryu/quickviewer/commit/36d4b39c927c3b6ac758885e6bed432213b42cd7)

## v0.4.0 (Mon Apr 3 22:00:11 2017 +0900) [9777572](https://github.com/kanryu/quickviewer/commit/977757234e442c58676aa57d2f8c119d3147ba6b)

changelog

- other commits
    - support Key Configs (Mon Apr 3 21:57:02 2017 +0900) [20da721](https://github.com/kanryu/quickviewer/commit/20da721fca323590c9aa480fca24249dafa5e3e0)
    -  support all actions save/load ini, customized run actions (Mon Apr 3 21:57:02 2017 +0900) [20da721](https://github.com/kanryu/quickviewer/commit/20da721fca323590c9aa480fca24249dafa5e3e0)
    -  add Key Config Dialog (Mon Apr 3 21:57:02 2017 +0900) [20da721](https://github.com/kanryu/quickviewer/commit/20da721fca323590c9aa480fca24249dafa5e3e0)

## v0.3.5 (Mon Apr 3 03:10:41 2017 +0900) [af12a95](https://github.com/kanryu/quickviewer/commit/af12a95b70ef0e2b0c852859349ec1b1060c64e9)

changelog

- other commits
    - add NextOnePage/PrevOnePage, fixed Open Explorer (Mon Apr 3 03:07:26 2017 +0900) [f9ef10e](https://github.com/kanryu/quickviewer/commit/f9ef10ea8854810cf721e1b3b90760c7a4ec18cc)
    -  (Mon Apr 3 03:07:26 2017 +0900) [f9ef10e](https://github.com/kanryu/quickviewer/commit/f9ef10ea8854810cf721e1b3b90760c7a4ec18cc)
    -  add NextOnePage/PrevOnePage (to next/prev 1 Page whether if DualView is on) (Mon Apr 3 03:07:26 2017 +0900) [f9ef10e](https://github.com/kanryu/quickviewer/commit/f9ef10ea8854810cf721e1b3b90760c7a4ec18cc)
    -  fixed Open Explorer(for spaces included file path), use as reference https://github.com/owncloud/client/blob/master/src/gui/openfilemanager.cpp (Mon Apr 3 03:07:26 2017 +0900) [f9ef10e](https://github.com/kanryu/quickviewer/commit/f9ef10ea8854810cf721e1b3b90760c7a4ec18cc)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Mon Apr 3 02:07:43 2017 +0900) [e8794ca](https://github.com/kanryu/quickviewer/commit/e8794caafed8e143e664d69ef58e9044ca7e2aee)
    - Update index-ja.md (Sun Apr 2 19:00:47 2017 +0900) [1318e14](https://github.com/kanryu/quickviewer/commit/1318e1402799f7965c59ff38941f175e3ac287dd)
    - Update index.md (Sun Apr 2 18:52:32 2017 +0900) [247b297](https://github.com/kanryu/quickviewer/commit/247b297358589cee7d87eb2fd24d80b912804dae)
    - Update README.md (Sun Apr 2 18:52:09 2017 +0900) [3f2ec39](https://github.com/kanryu/quickviewer/commit/3f2ec39d17bffdfdf10b57df5440ea4a1123defa)
    - changelog (Sun Apr 2 17:53:20 2017 +0900) [77bfc81](https://github.com/kanryu/quickviewer/commit/77bfc81868e9b9e34a2e63b4a8e26df206fec02b)
    - Update index.html (Sat Apr 1 22:17:46 2017 +0900) [668a936](https://github.com/kanryu/quickviewer/commit/668a936f227b0808851532c7fec60b6ed16c305b)
    - Update index.html (Sat Apr 1 22:15:59 2017 +0900) [61ded06](https://github.com/kanryu/quickviewer/commit/61ded06c1381e23e1acccb9404fe145b773b9380)

## v0.3.4 (Sun Apr 2 17:53:26 2017 +0900) [8f4876e](https://github.com/kanryu/quickviewer/commit/8f4876ee85163c80e0725a055069ba190dc9f763)

Merge branch 'master' of https://github.com/kanryu/quickviewer

- other commits
    - changelog (Sun Apr 2 17:53:20 2017 +0900) [a87b92f](https://github.com/kanryu/quickviewer/commit/a87b92f52be3c2252f9104489fbc68f3b444de6c)
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sun Apr 2 17:52:00 2017 +0900) [38bc291](https://github.com/kanryu/quickviewer/commit/38bc2919e7432ab667d065ae5fa095e1ab5cf79f)
    -  (Sun Apr 2 17:52:00 2017 +0900) [38bc291](https://github.com/kanryu/quickviewer/commit/38bc2919e7432ab667d065ae5fa095e1ab5cf79f)
    - support NextVolume/PrevVolume (Sun Apr 2 17:52:00 2017 +0900) [38bc291](https://github.com/kanryu/quickviewer/commit/38bc2919e7432ab667d065ae5fa095e1ab5cf79f)
    -  (Sun Apr 2 17:52:00 2017 +0900) [38bc291](https://github.com/kanryu/quickviewer/commit/38bc2919e7432ab667d065ae5fa095e1ab5cf79f)
    -  PrevPage by BackSpase Key pressed (Sun Apr 2 17:52:00 2017 +0900) [38bc291](https://github.com/kanryu/quickviewer/commit/38bc2919e7432ab667d065ae5fa095e1ab5cf79f)
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

## v0.3.3 (Sat Apr 1 01:59:25 2017 +0900) [0139667](https://github.com/kanryu/quickviewer/commit/0139667ad5090dff73329f4a386e03cc69462119)

changelog

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Sat Apr 1 01:58:59 2017 +0900) [6a6d0b5](https://github.com/kanryu/quickviewer/commit/6a6d0b5229aaf51b967f65af9702b8574a49df07)
    - support Raw Images, check version (Sat Apr 1 01:57:37 2017 +0900) [8aa44a2](https://github.com/kanryu/quickviewer/commit/8aa44a210cf40c1a1aa4ab5125c3959c4716b352)
    -  (Sat Apr 1 01:57:37 2017 +0900) [8aa44a2](https://github.com/kanryu/quickviewer/commit/8aa44a210cf40c1a1aa4ab5125c3959c4716b352)
    -  support Raw Images (Canon/Nicon/Sony/Ricoh/etc..) (Sat Apr 1 01:57:37 2017 +0900) [8aa44a2](https://github.com/kanryu/quickviewer/commit/8aa44a210cf40c1a1aa4ab5125c3959c4716b352)
    -  test support for EXIF of Raw images (very rude behavior) (Sat Apr 1 01:57:37 2017 +0900) [8aa44a2](https://github.com/kanryu/quickviewer/commit/8aa44a210cf40c1a1aa4ab5125c3959c4716b352)
    -  check version with browser (Sat Apr 1 01:57:37 2017 +0900) [8aa44a2](https://github.com/kanryu/quickviewer/commit/8aa44a210cf40c1a1aa4ab5125c3959c4716b352)
    - Update index.md (Sat Apr 1 01:38:12 2017 +0900) [c260615](https://github.com/kanryu/quickviewer/commit/c260615697f40a60286159732d379b7733eda6c5)
    - Update index.md (Sat Apr 1 01:30:04 2017 +0900) [f0a180f](https://github.com/kanryu/quickviewer/commit/f0a180fc6c0b01efdd4f3187e2c5faa9e5c4e890)
    - Update index.md (Sat Apr 1 01:27:19 2017 +0900) [c2c1966](https://github.com/kanryu/quickviewer/commit/c2c1966a3e12339f29d716186c35e0ea6716d86c)
    - Update index.md (Sat Apr 1 01:25:58 2017 +0900) [0c7cbe7](https://github.com/kanryu/quickviewer/commit/0c7cbe783e65074ecba033b6f408fc2fe8f96603)
    - checkversion script (Sat Apr 1 01:21:50 2017 +0900) [ef673aa](https://github.com/kanryu/quickviewer/commit/ef673aa2f3150b8f8342e2c11b127b072a671cdc)

## v0.3.2 (Fri Mar 31 06:28:50 2017 +0900) [5ef95b5](https://github.com/kanryu/quickviewer/commit/5ef95b5e047ad7680ba8fa838e4d1df016e276b7)

CHANGELOG

- other commits
    - Merge branch 'master' of https://github.com/kanryu/quickviewer (Fri Mar 31 06:28:17 2017 +0900) [cb7b450](https://github.com/kanryu/quickviewer/commit/cb7b4501030df65048821b669ab071dce7b37aa1)
    - fixed when png file dropped (Fri Mar 31 06:27:49 2017 +0900) [c6ff3be](https://github.com/kanryu/quickviewer/commit/c6ff3be94044612100b06d54fe4bb7f3f0a93406)
    - Update README.md (Fri Mar 31 05:28:30 2017 +0900) [f00c36d](https://github.com/kanryu/quickviewer/commit/f00c36de540508aec55d0797c43e5690dba12854)
    - Update README.md (Fri Mar 31 05:27:16 2017 +0900) [8bd3ccd](https://github.com/kanryu/quickviewer/commit/8bd3ccd9e07a09c73099c56fcae3646da8c1fdc8)
    - Update index-ja.md (Fri Mar 31 05:23:53 2017 +0900) [6f0cc66](https://github.com/kanryu/quickviewer/commit/6f0cc660ff91e15a67d0469b8b63314d1eebbe15)
    - Update index.md (Fri Mar 31 05:20:07 2017 +0900) [9c09be0](https://github.com/kanryu/quickviewer/commit/9c09be0591b8292d4eeb68e69e11e623d6f52432)
    - Update README.md (Fri Mar 31 05:19:21 2017 +0900) [fda1e21](https://github.com/kanryu/quickviewer/commit/fda1e21fd60367747356fb19a325b9153f032b40)
    - Update index.md (Fri Mar 31 05:06:35 2017 +0900) [9f484f3](https://github.com/kanryu/quickviewer/commit/9f484f3c8529c06e9375a830521abe40fd43c857)
    - Update index.md (Fri Mar 31 05:06:15 2017 +0900) [f763498](https://github.com/kanryu/quickviewer/commit/f76349814736a8e6e8ed4cfb7785c80f17f1b393)

## v0.3.1 (Fri Mar 31 04:37:29 2017 +0900) [283d783](https://github.com/kanryu/quickviewer/commit/283d783a4221deae190328808ebe63f296ff5c42)

CHANGELOG

- other commits
    -  refactoring (Fri Mar 31 03:42:55 2017 +0900) [f1cd515](https://github.com/kanryu/quickviewer/commit/f1cd515820748a241a6036bfe4e9ff60dc37eb8e)
    -  support RAR archive (Fri Mar 31 03:42:55 2017 +0900) [f1cd515](https://github.com/kanryu/quickviewer/commit/f1cd515820748a241a6036bfe4e9ff60dc37eb8e)
    -  add Key Config Dialog (Fri Mar 31 03:42:55 2017 +0900) [f1cd515](https://github.com/kanryu/quickviewer/commit/f1cd515820748a241a6036bfe4e9ff60dc37eb8e)
    -  improve behavior of changing between normal and fullscreen (Fri Mar 31 03:42:55 2017 +0900) [f1cd515](https://github.com/kanryu/quickviewer/commit/f1cd515820748a241a6036bfe4e9ff60dc37eb8e)
    - CHANGELOG (Thu Mar 30 14:25:48 2017 +0900) [e9f8189](https://github.com/kanryu/quickviewer/commit/e9f81892e517f505d38951b5405b079fdcd61708)
    - CHANGELOG (Thu Mar 30 14:22:50 2017 +0900) [661a7b1](https://github.com/kanryu/quickviewer/commit/661a7b17fdac7fb78275bfcc6ebd381f1f7054ac)
    - refactoring (Thu Mar 30 14:19:25 2017 +0900) [961b44a](https://github.com/kanryu/quickviewer/commit/961b44adf69a69408732498b0b8dde59831a2343)
    -  (Thu Mar 30 14:19:25 2017 +0900) [961b44a](https://github.com/kanryu/quickviewer/commit/961b44adf69a69408732498b0b8dde59831a2343)
    -  remove comments outdated (Thu Mar 30 14:19:25 2017 +0900) [961b44a](https://github.com/kanryu/quickviewer/commit/961b44adf69a69408732498b0b8dde59831a2343)
    -  followed for version up of ResizeHalf (Thu Mar 30 14:19:25 2017 +0900) [961b44a](https://github.com/kanryu/quickviewer/commit/961b44adf69a69408732498b0b8dde59831a2343)
    - Update CHANGELOG.md (Thu Mar 30 05:30:03 2017 +0900) [d348354](https://github.com/kanryu/quickviewer/commit/d348354dd8b1d79cdd9bf5ad02bd94e78d42db27)
    - Update CHANGELOG.md (Thu Mar 30 05:23:40 2017 +0900) [4381c43](https://github.com/kanryu/quickviewer/commit/4381c437506434746dedb8df31d02fa83584539f)
    -  add keyconfig dialog (Thu Mar 30 05:20:11 2017 +0900) [26b4536](https://github.com/kanryu/quickviewer/commit/26b45365790e108d8313cb52919cb5766945e3fc)
    -  refactoring (Thu Mar 30 05:20:11 2017 +0900) [26b4536](https://github.com/kanryu/quickviewer/commit/26b45365790e108d8313cb52919cb5766945e3fc)
    -  add FileLoader object(supports external plugin) (Thu Mar 30 05:20:11 2017 +0900) [26b4536](https://github.com/kanryu/quickviewer/commit/26b45365790e108d8313cb52919cb5766945e3fc)
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

## v0.2.6 (Mon Mar 27 17:28:50 2017 +0900) [2b514bf](https://github.com/kanryu/quickviewer/commit/2b514bfcf96795512aa355c9009c3fb2ed9c1229)

Merge branch 'master' of https://github.com/kanryu/quickviewer

- other commits
    -  followed for version up of ResizeHalf (Mon Mar 27 17:25:52 2017 +0900) [c5217cc](https://github.com/kanryu/quickviewer/commit/c5217cc7e5febbae460a585438ff15381812ce7f)
    -  fixed behavior of knob on page slider (Mon Mar 27 17:25:52 2017 +0900) [c5217cc](https://github.com/kanryu/quickviewer/commit/c5217cc7e5febbae460a585438ff15381812ce7f)
    -  fixed paging as Spread Viewing (Mon Mar 27 17:25:52 2017 +0900) [c5217cc](https://github.com/kanryu/quickviewer/commit/c5217cc7e5febbae460a585438ff15381812ce7f)
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
    - fixed bug about archive pre loading (Thu Mar 23 17:41:34 2017 +0900) [946e367](https://github.com/kanryu/quickviewer/commit/946e367cc058051479d4ff15ac255a2b2a7ee069)

## v0.1.10 (Thu Mar 23 17:15:32 2017 +0900) [8e3cdd6](https://github.com/kanryu/quickviewer/commit/8e3cdd667958c2c1977d98ebb4264313ecfd6d63)

README

- other commits
    - implements a feature about page pre loading (Thu Mar 23 17:13:52 2017 +0900) [d8fe6cd](https://github.com/kanryu/quickviewer/commit/d8fe6cd5534d2ea87d720bb42f3b67ec9a02db19)
    -  add a menu which open a image folder (Thu Mar 23 17:02:37 2017 +0900) [78692c6](https://github.com/kanryu/quickviewer/commit/78692c681c36856033d26a8b438f606b2e40cac9)
    -  to show "NOT IMAGE" which the page is not a valid image file (Thu Mar 23 17:02:37 2017 +0900) [78692c6](https://github.com/kanryu/quickviewer/commit/78692c681c36856033d26a8b438f606b2e40cac9)
    -  add a menu "always open wide image as one view" (Thu Mar 23 17:02:37 2017 +0900) [78692c6](https://github.com/kanryu/quickviewer/commit/78692c681c36856033d26a8b438f606b2e40cac9)
    -  fixed a bug which there is page number wrong when one page viewing (Thu Mar 23 17:02:37 2017 +0900) [78692c6](https://github.com/kanryu/quickviewer/commit/78692c681c36856033d26a8b438f606b2e40cac9)

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
    - Initial commit (Mon Mar 20 20:20:42 2017 +0900) [cf7a533](https://github.com/kanryu/quickviewer/commit/cf7a533b634deb04eeff4036958bc934215920c9)
