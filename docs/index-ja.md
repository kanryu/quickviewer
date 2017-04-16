---
layout: default
---

# [](#header-1)QuickViewer

**QuickViewer** は、たくさんの画像を快適に閲覧するための画像ビューアです。

画像データの読み込みを先回りして行い、読み込んだ画像データをOpenGLで画面に描画することで、これまでにない軽快さで画像を閲覧できるようになります。

**QuickViewer** は GPLv3 のフリーソフトウェアです。

[英語表記](https://kanryu.github.io/quickviewer/) / [日本語表記](https://kanryu.github.io/quickviewer/index-ja)


## こういうソフトです

- 画像切り替えメチャ早(OpenGL使用)
- 本を読むのに便利な見開き表示
- アーカイブファイルの直接読み込み(zip/7z/rar)
- これらの画像形式に対応(bmp/png/jpeg/dds/webp/ico/tga/tiff/gif)
- JPEG EXIFに対応し、撮影したそのままの向きで画像を表示
- 主要カメラメーカーのRaw画像形式に対応
    - Canon(crw, cr2)
    - Nicon(nef)
    - Sony(arw)
    - Ricoh(dng)
    - などなど

## 使い方


1. アプリを起動し、ウィンドウを表示します
1. メインメニューの選択してダイアログからフォルダを選ぶ、もしくはエクスプローラーから画像ファイルの入ったフォルダをアプリのウィンドウにDrag Dropします
1. 画面に読み込んだ画像が表示されます。ツールバーの「←」「→」ボタン、マウスホイール、マウスの進む戻るボタン、ウィンドウの左右端クリックなどで画像を切り替えます

## ダウンロード

[ビルド済みリリース版](https://github.com/kanryu/quickviewer/releases) (Windows x86/x64)

ソースコードについては [リポジトリ](https://github.com/kanryu/quickviewer) から最新のソースコードをcloneして入手してください。

## 外部レビュー

- Free SoftNavie様
    - http://www.softnavi.com/review/graphic_viewer/quickviewer_1.html
- the PORTABLE FREEWARE collection様(英語)
    - https://www.portablefreeware.com/forums/viewtopic.php?f=4&t=23353
- SOFTPEDIA様(英語)
    - http://www.softpedia.com/get/Multimedia/Graphic/Graphic-Viewers/QuickViewer.shtml
- FindMySoft様(英語)
    - http://quickviewer.findmysoft.com

レビューしてくれてどうもありがとう！


## 機能紹介

### 通常表示(1ページ表示)

![通常表示](https://github.com/kanryu/quickviewer/wiki/images/singleview.jpg)

『見開き表示』をオフにしている場合、画面に画像を1枚表示します。

### 見開き表示


![見開き表示](https://github.com/kanryu/quickviewer/wiki/images/dualview.jpg)


『見開き表示』をオンにしている場合、画像を2枚横に並べて表示します。

### JPEG EXIF情報の表示

![EXIF情報](https://github.com/kanryu/quickviewer/wiki/images/exifdialog.jpg)

デジタルカメラなどで撮影したJPEG画像について、画像ファイルの中のEXIF情報を確認することができます。
画面を右クリックしてコンテキストメニューを表示し、『Exif情報を表示する』を選択してください。

### 画像の場所をExplorerで確認

現在表示中の画像がどこにあるのかをExplorerで確認できます。
画面を右クリックしてコンテキストメニューを表示し、『エクスプローラーで開く』を選択してください。


## 画面の操作

画面の操作はメインメニュー、ツールバー、マウスボタン、ホイール、キーボードなどで行うことができます。

| 操作        | デバイス   | 入力内容 | 備考 |
|:------------|:----------|:--------|:--------|
| 次のページ   | キーボード | 右キー(→) | |
|             | キーボード | スペースキー | |
|             | マウスホイール | 下回転 | |
|             | マウス     | 進むボタン   | |
| 前のページ   | キーボード | 左キー(←) | |
|             | キーボード | バックスペースキー | |
|             | マウスホイール | 上回転 | |
|             | マウス     | 戻るボタン | |
| 最初のページ | キーボード | Homeキー | |
| 最後のページ | キーボード | Endキー | |
| 次のボリューム | キーボード | Page Down | 隣りあったフォルダやアーカイブに移動します |
| 前のボリューム | キーボード | Page Up | 隣りあったフォルダやアーカイブに移動します |
| 全画面表示   | キーボード | F11キー | |
|             | キーボード | ESCキー | 全画面解除のみ |
|             | マウス     | ホイールクリック | 中央ボタンクリック扱い |
| フィット表示 | キーボード | F12キー | |
|             | キーボード | テンキー(\*) | |
| 画像拡大     | キーボード | テンキー(+) | フィット表示時使用不可 |
| 画像縮小     | キーボード | テンキー(-) | フィット表示時使用不可 |

```
The final element.
```
