### 日本語 / [English](https://github.com/kanryu/quickviewer#readme)

QuickViewer
===========


**QuickViewer** は、たくさんの画像を快適に閲覧するための画像ビューアです。

画像データの読み込みを先回りして行い、読み込んだ画像データをOpenGLで画面に描画することで、これまでにない軽快さで画像を閲覧できるようになります。

**QuickViewer** は GPLv3 のフリーソフトウェアです。

![github tag](https://badgen.net/github/tag/kanryu/quickviewer)
![github downloads](https://badgen.net/github/assets-dl/kanryu/quickviewer)
![github last commit](https://badgen.net/github/last-commit/kanryu/quickviewer)
![opencollective backers](https://badgen.net/opencollective/backers/quickviewer)
![opencollective contributors](https://badgen.net/opencollective/contributors/quickviewer)
![opencollective balance](https://badgen.net/opencollective/balance/quickviewer)
![opencollective yearly](https://badgen.net/opencollective/yearly/quickviewer)
[![Join the chat at https://gitter.im/kanryu/quickviewer](https://badges.gitter.im/kanryu/quickviewer.svg)](https://gitter.im/kanryu/quickviewer?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)


## こういうソフトです

- 画像切り替えメチャ早(OpenGL使用)
- インストール作業なしでどこでも動いてレジストリの書き込みなし
- タブレットPC対応
- 本を読むのに便利な見開き表示
- アーカイブファイルの直接読み込み(zip/7z/rar/cbz/cb7/cbr/cab/tar.gz/tar.bz2/tar.xz/他)
- これらの画像形式に対応(bmp/png/jpeg/ico/dds/tga/tiff/gif)
    - 現代的な画像形式に対応(JPEG 2000/JPEG XR/WebP)
    - アニメーションPNG(APNG)/GIFに対応
    - JPEG EXIFに対応し、撮影したそのままの向きで画像を表示
    - CMYK形式のJPEGに対応し、sRGBに自動変換されて表示
- 主要カメラメーカーのRaw画像形式に対応
    - Canon (crw/cr2)
    - Nikon (nef)
    - Sony (arw)
    - Ricoh, Pentax (dng)
    - などなど
 - あなたの何千冊ものデジタルブック、マンガを『カタログ』として登録でき、軽快に一覧表示、検索できます
 - カタログの本は自動生成されたタグでも検索できます
 - タッチパネル入力(ページ切り替え/フルスクリーン切り替え/画像拡大・縮小・回転)
 - 複数言語対応(日本語/英語/簡体字中国語/スペイン語/フランス語/アラビア語/ロシア語/ギリシャ語)


## 使い方

1. アプリを起動し、ウィンドウを表示します
1. メインメニューの選択してダイアログからフォルダを選ぶ、もしくはエクスプローラーから画像ファイルの入ったフォルダをアプリのウィンドウにDrag Dropします
1. 画面に読み込んだ画像が表示されます。ツールバーの「←」「→」ボタン、マウスホイール、マウスの進む戻るボタン、ウィンドウの左右端クリックなどで画像を切り替えます


## ダウンロード

- 最新版は **release_version** です。
- [ビルド済みリリース版](https://github.com/kanryu/quickviewer/releases) からダウンロードしてください。(Windows x86/x64, Mac dmg x64, Linux AppImage x64)
    - **Lhaplus** などのdeflate64に対応していない古いアーカイバは使用しないでください。[**7z**](https://sevenzip.osdn.jp/)などをご利用ください。
- ソースコードについては [リポジトリ](https://github.com/kanryu/quickviewer) から最新のソースコードをcloneして入手してください。


## 機能紹介

- フォルダ、アーカイブ(zip等)の切り替え
    - ファイル選択ダイアログによるボリュームの切り替え
    - ウィンドウへのフォルダやアーカイブのDrag Dropによるボリュームの切り替え
    - 以前開いた履歴をメニューから選択して切り替える
    - 次のボリューム、前のボリューム
- 見開き表示(2枚の画像を左右に並べる)
    - 横長の画像は1枚だけ表示
    - 最初の画像(表紙)は1枚だけ表示
    - 右開き、左開きの切り替え
- スライドショー
- ページ切り替え
    - 次の画像、前の画像
    - 早送り、早戻し
    - 最初の画像、最後の画像
    - 見開き表示でも1ページだけ進める
- ブックマーク
    - 保存、読み込み、消去
- カタログ
    - 追加、編集、削除、本（フォルダ）のサムネイルの表示、キーワードでタイトル(フォルダ名)を検索
    - フォルダやアーカイブからデータベースを作成することで、高速に検索して表紙を表示する
    - カタログは『タグ』を生成する。それぞれのタグはボタンとして表示され、検索に使用できる
- 画像の表示倍率の切り替え
    - フィット表示(標準)
    - 縮小、拡大(13%, 25%, 33%, 50%, 75%, 100%, 150%, 200%, 300%, 400%, 800%のいずれか)
- 画像に対する操作
    - クリップボードに画像をコピー
    - クリップボードに画像ファイルをコピー
    - 画像ファイルをゴミに入れる(Shift+Delで直接削除)
    - 現在の表示中の画像ファイルをエクスプローラで表示
    - Exif情報を表示(JPEG)
    - 自動回転(JPEG)
    - ルーペツールで拡大表示(クリックでルーペ有効、クリックしながら移動で表示範囲変更)
    - 横長の画像を2ページに分けて半分ずつ表示(ウィンドウを縦長にした場合のみ有効)
- ウィンドウの表示方法の切り替え
    - フルスクリーン表示
    - 常に手前に表示
    - ウィンドウの表示を次回起動時に復元する
- [シェーダープログラム](shader-ja) による表示品質の切り替え
    - バイリニア補間(標準)
    - 最近傍補間
    - ~~バイキュービック補間~~ (v0.9.3で廃止)
    - ~~Lanczos補間~~ (v0.9.3で廃止)
    - バイキュービック補間 (CPU処理)
    - Lanczos3補間 (CPU処理, v1.0.9)
    - Lanczos4補間 (CPU処理, v1.0.9)
- タッチパネル入力
    - 画面の回転、拡大縮小、ページ切り替え(通常移動、１ページだけ移動)、フルスクリーン切り替え
- キー入力設定のカスタマイズ
- マウス入力設定のカスタマイズ


### 通常表示(1ページ表示)

![通常表示](https://github.com/kanryu/quickviewer/wiki/images/singleview.jpg)

『見開き表示』をオフにしている場合、画面に画像を1枚表示します。


### 見開き表示

![見開き表示](https://github.com/kanryu/quickviewer/wiki/images/dualview.jpg)

『見開き表示』をオンにしている場合、画像を2枚横に並べて表示します。


### シンプルな表示

画像だけを見たいというときは、シンプルな表示はいかがですか。
隠れたバーは必要なときに自動で表示されます。

![Stripped viewing](https://github.com/kanryu/quickviewer/wiki/images/stripped.jpg)


### JPEG EXIF情報の表示

![EXIF情報](https://github.com/kanryu/quickviewer/wiki/images/exifdialog.jpg)

デジタルカメラなどで撮影したJPEG画像について、画像ファイルの中のEXIF情報を確認することができます。
画面を右クリックしてコンテキストメニューを表示し、『Exif情報を表示する』を選択してください。


### シェーダーによる描画品質の変更

画像の描画品質が向上します。詳しくは [シェーダー](shader-ja) にて。

![1 of compared](compared1.png)


### 画像の場所をExplorerで確認

現在表示中の画像がどこにあるのかをExplorerで確認できます。
画面を右クリックしてコンテキストメニューを表示し、『エクスプローラーで開く』を選択してください。


### カタログ機能

v0.6.0以降、QuickViewerはあなたのデジタルブックやマンガからカタログを作ることができます。
『カタログ表示』をクリックし、画像の入ったフォルダをdropしましょう。

![Manage Catalog](https://github.com/kanryu/quickviewer/wiki/images/manage_catalog.png)

すると、あなたの本はカタログに登録されます。
(これらのサンプル本はこちらから入手しています https://comicstore.marvel.com/free-comics)

![Show Catalog](https://github.com/kanryu/quickviewer/wiki/images/show_catalog.png)

カタログに何千冊もの本を登録しても、瞬時に表示されます。キーワード入力やタグをクリックすることで検索できます。

カタログ画面はメインウィンドウに組み込まれる形でも表示できます。

![Embedded Catalog](https://github.com/kanryu/quickviewer/wiki/images/embedded_catalog.jpg)


## 画面の操作

画面の操作はメインメニュー、ツールバー、マウスボタン、ホイール、キーボードなどで行うことができます。

| 操作        | デバイス   | 入力内容 | 備考 |
|:------------|:----------|:--------|:--------|
| 次のページ   | キーボード | 右キー(→) | |
|             | キーボード | スペースキー | |
|             | マウスホイール | 下回転 | |
|             | マウス     | 進むボタン   | |
|             | タッチパッド | 右スワイプ | 画面下4分の1 |
| 前のページ   | キーボード | 左キー(←) | |
|             | キーボード | バックスペースキー | |
|             | マウスホイール | 上回転 | |
|             | マウス     | 戻るボタン | |
|             | タッチパッド | 左スワイプ | 画面下4分の1 |
| 1ページ次    | タッチパッド | ２つ指で右スワイプ | 画面下4分の1 |
| 1ページ前    | タッチパッド | ２つ指で左スワイプ | 画面下4分の1 |
| 最初のページ | キーボード | Homeキー | |
| 最後のページ | キーボード | Endキー | |
| 次のボリューム | キーボード | Page Down | 隣りあったフォルダやアーカイブに移動します |
| 前のボリューム | キーボード | Page Up | 隣りあったフォルダやアーカイブに移動します |
| 全画面表示   | キーボード | F11キー | |
|             | キーボード | ESCキー | 全画面解除のみ |
|             | マウス     | ホイールクリック | 中央ボタンクリック扱い |
|             | タッチパッド | ２つ指で上スワイプ | 画面上4分の1 |
| フィット表示 | キーボード | F12キー | |
|             | キーボード | テンキー(\*) | |
|             | マウス     | 右ボタン+ホイールクリック | 中央ボタンクリック扱い |
|             | マウス     | Ctrlキー+ホイールクリック | 中央ボタンクリック扱い |
| 拡大表示     | キーボード | テンキー(+) | フィット表示時使用不可 |
|             | マウスホイール | 右ボタン+上回転 | |
|             | マウスホイール | Ctrlキー+上回転 | |
|             | タッチパッド | ２つ指で広げる | 画面中央 |
| 縮小表示     | キーボード | テンキー(-) | フィット表示時使用不可 |
|             | マウスホイール | 右ボタン+下回転 | |
|             | マウスホイール | Ctrlキー+下回転 | |
|             | タッチパッド | ２つ指で狭める | 画面中央 |
| 拡大ツール      | マウス | 左ボタン | 拡大ツール使用時 |
| 拡大ツールのズームイン | マウス | 左ボタン+上回転 | 拡大ツール使用時 |
| 拡大ツールのズームアウト | マウス | 左ボタン+下回転 | 拡大ツール使用時 |
| ページ回転 | キーボード | Rキー | |
| 画面回転 | タッチパッド | ２つ指でコンパスの動き | 画面中央 |
| 拡大／縮小／回転のキャンセル | タッチパッド | ２つ指でダブルタップ | 画面中央 |
| 画面のスクロール(拡大時のみ) | タッチパッド | 上下左右スワイプ | 画面中央 |
